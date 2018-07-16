/**
* Copyright (c) Pervasive Displays Inc. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
**/

#include <Data_Module.h>
#include <Flash_Mem_Map.h>
#include "conf_EPD.h"
#include "CommandHandle.h"
#include "ringbuf.h"
#define RecvBuf_Size            	16
Command_info_t       				*Recv_CmdInfo;
static receive_response_info_t  	Metadata_Info;
static tRingBufObject           	RecvPacketbufObj;
static  receive_response_info_t  	RecvPacket_Buffer[RecvBuf_Size];
Command_feedback_handler 			_RxResultHandle;
//static volatile uint16_t 			ImageLength;
static  Result_Packet_t 			Result_Packet;

bool AddPacketTask_Handle();
void SendOut( uint8_t *pui8Buffer, uint32_t ui32Count);
bool CheckRecvData(uint8_t *datas,uint8_t len);

bool CheckRecvData(uint8_t *datas,uint8_t len)
{
	if(len==0) return true;
	return UartRecv(datas,len);
}
void SendOut(uint8_t *pui8Buffer, uint32_t ui32Count)
{
	UartSend(pui8Buffer,ui32Count);
}

void SendResult(receive_response_info_t *rrp_info)
{
	//  Result_Packet.cmd_info.Result=rrp_info->Result;
	if(rrp_info->Recv_Packet_info.cmd_info.Response!=Res_Not)
	{
		memcpy(&Result_Packet,&rrp_info->Recv_Packet_info,sizeof(Result_Packet_t));
		SendOut((uint8_t *)&Result_Packet.cmd_info,sizeof(Command_info_t));
		if(rrp_info->Recv_Packet_info.cmd_info.Response==Res_ResultData)
		{
			if(Result_Packet.cmd_info.Length>0)
			{
				SendOut((uint8_t *)&Result_Packet.ResultData[0],Result_Packet.cmd_info.Length);
			}
		}
	}
}

void SendResult_Datas(receive_response_info_t *rrp_info,uint8_t *data,uint8_t len)
{
	memcpy(rrp_info->Recv_Packet_info.payload,data,len);
	rrp_info->Recv_Packet_info.cmd_info.Length=len;
	rrp_info->Recv_Packet_info.cmd_info.Response= Res_ResultData;
	SendResult(rrp_info);
}

void SendResultOnly(receive_response_info_t *rrp_info)
{
	rrp_info->Recv_Packet_info.cmd_info.Length=0;
	SendResult(rrp_info);
}

//====================================================================
// Recevie Handle
//====================================================================
void RecvDataEvent(void)
{
	bool flag=false;
	if(Metadata_Info.Recv_Packet_info.cmd_info.Length<=PayloadSize)
	{
		if(CheckRecvData(Metadata_Info.Recv_Packet_info.payload,Metadata_Info.Recv_Packet_info.cmd_info.Length)==true)
		{
			Metadata_Info.Recv_Packet_info.cmd_info.Result=Result_OK;
			if(!AddPacketTask_Handle())
			{
				Metadata_Info.Recv_Packet_info.cmd_info.Result=Result_Fail;
			}
			flag=true;
			Rtos_Event_Handle(DM_TASK_ID,DM_EVT_Receive_UART);
		}
	}
	if(!flag)
	{
		if((Metadata_Info.RetryTime--)>0)
		{
			Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_Receive_Packet,1);
		}
		else
		{
			Metadata_Info.Recv_Packet_info.cmd_info.Result=Result_Fail;
			Rtos_Event_Handle(DM_TASK_ID,DM_EVT_Receive_UART);
		}
	}
}

void RunPacketTaskHandle()
{
	receive_response_info_t tmpRRInfo;
	RingBufRead(&RecvPacketbufObj,(uint8_t *)&tmpRRInfo,sizeof(receive_response_info_t));
	if(tmpRRInfo.feedback!=NULL)tmpRRInfo.feedback(&tmpRRInfo);
	if(RingBufUsed(&RecvPacketbufObj)>=sizeof(receive_response_info_t)) Rtos_Event_Handle(DM_TASK_ID,DM_EVT_RunPacket);
}
bool AddPacketTask_Handle()
{
	bool flag=false;
	if(RingBufFree(&RecvPacketbufObj)>=sizeof(receive_response_info_t))
	{
		RingBufWrite(&RecvPacketbufObj,(uint8_t *)&Metadata_Info,sizeof(receive_response_info_t));
		RunPacketTaskHandle();
		flag=true;
	}

	return flag;
}

//COG Show ReadData Handle

static void DM_Event_Handle(uint32_t eventid)
{

	switch(eventid)
	{
		case DM_EVT_Receive_UART:
			Recv_CmdInfo=&Metadata_Info.Recv_Packet_info.cmd_info;
			if(CheckRecvData((uint8_t *)Recv_CmdInfo,sizeof(Command_info_t)))
			{
				LED1_high();
				//	UartSend((const uint8_t *)Recv_CmdInfo,sizeof(Command_info_t));
				if((Recv_CmdInfo->Header0==RECV_HEADER0) &&( Recv_CmdInfo->Header1==RECV_HEADER1))
				{

					Metadata_Info.feedback=Command_Event[Recv_CmdInfo->cmd];
					Metadata_Info.RetryTime=200;
					Recv_CmdInfo->Result=Result_None;
					RecvDataEvent();
				}
				else
				{

					Rtos_Event_Handle(DM_TASK_ID,DM_EVT_Receive_UART);
				}

			}
			else
			{
				LED1_low();
				Rtos_Event_Handle(DM_TASK_ID,DM_EVT_Receive_UART);
			}
			break;
		case DM_EVT_Receive_Packet:
			RecvDataEvent();
			break;
		case DM_EVT_UART_Init:
			ClearUartBuffer();
			Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_Receive_UART,5);
			break;
		case DM_EVT_RunPacket:
			RunPacketTaskHandle();

			break;

	}
}

void Data_Module_init(void)
{
	ConfigureUART(UART_Baudrate);
	RingBufInit(&RecvPacketbufObj,(uint8_t *)&RecvPacket_Buffer,sizeof(RecvPacket_Buffer));
	Rtos_Addtask(DM_Event_Handle,DM_TASK_ID);
	Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_UART_Init,5);
}
