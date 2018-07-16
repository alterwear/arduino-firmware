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

#include "Data_Module.h"
#include <Flash_Mem_Map.h>
#include "BootTask_Module.h"
#include "conf_EPD.h"
#include "CommandHandle.h"
static volatile uint16_t 			ImageLength;

void read_flash_handle(long flash_address,uint8_t *target_buffer,
                       uint8_t byte_length)
{
	read_flash(flash_address,target_buffer,byte_length);
}


void CheckMCU_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;

	SendResult(ResponseData);
}
void RecvVer_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	SendResult_Datas(ResponseData,Firmware_Ver,16);
}
void EraseEntireFlash_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result== Result_OK)
	{
		check_flash_spi();
		erase_flash(0,0xfff);
	}
	SendResultOnly(ResponseData);
}
void EraseFlash_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		Flash_Parameter_Info_t *f_ParameterInfo=malloc(sizeof(Flash_Parameter_Info_t));
		memcpy(f_ParameterInfo,(Flash_Parameter_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(Flash_Parameter_Info_t));
		check_flash_spi();
		erase_flash(f_ParameterInfo->Address,f_ParameterInfo->Length);
		free(f_ParameterInfo);
	}
	SendResultOnly(ResponseData);
}
void ReadData_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		Flash_Info_t *flashinfo=malloc(sizeof(Flash_Info_t));
		memcpy(flashinfo,(Flash_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(Flash_Info_t));
		check_flash_spi();
		read_flash(flashinfo->Address,&flashinfo->data[0],flashinfo->Length);
		SendResult_Datas(ResponseData,(uint8_t *)&flashinfo->data[0],flashinfo->Length);
		free(flashinfo);
	}
	else SendResultOnly(ResponseData);
}

void WriteData_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		Flash_Info_t *flashinfo=malloc(sizeof(Flash_Info_t));
		memcpy(flashinfo,(Flash_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(Flash_Info_t));
		check_flash_spi();
		write_flash(flashinfo->Address,(uint8_t *)&flashinfo->data[0],flashinfo->Length);
		SendResultOnly(ResponseData);
		free(flashinfo);
	}
	else SendResultOnly(ResponseData);
}
void WriteImageData_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		Flash_Info_t *flashinfo=malloc(sizeof(Flash_Info_t));
		memcpy(flashinfo,(Flash_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(Flash_Info_t));
		check_flash_spi();
		write_flash(flashinfo->Address,(uint8_t *)&flashinfo->data[0],flashinfo->Length);
		uint16_t 	tmpImageLength=ImageLength;
		if((--tmpImageLength)==0)
		{
			SendResultOnly(ResponseData);
		}

		free(flashinfo);
	}
	else SendResultOnly(ResponseData);
}
static uint32_t Prev_addr=0;
void EPDShow_Feedback_Handle(void *FeedbackData)
{

	ShowEpd_Result_t ShowEpd_Result;

	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{

		ShowEpd_Info_t *ShowEpd_Info=malloc(sizeof(ShowEpd_Info_t));
		memcpy(ShowEpd_Info,(ShowEpd_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(ShowEpd_Info_t));
       
		ShowEpd_Result.Temperature=Set_AssignEPD_Drive((Driver_Type_t)ShowEpd_Info->Driver_Type,(EPD_SIZE_t)ShowEpd_Info->EPD_Size,ShowEpd_Info->Temperature);
        if(ShowEpd_Info->color_mode!=CM_NONE)
       {
            EPD_display_iTC_SetColormode(ShowEpd_Info->color_mode);

       }
		ShowEpd_Result.time=getnowtime();
		if(Prev_addr==0)Prev_addr=ShowEpd_Info->NewImageAddress;
		if(ShowEpd_Info->Driver_Type==dr_eTC_G1_Aurora_Mb || ShowEpd_Info->Driver_Type==dr_eTC_G2_Aurora_Mb || ShowEpd_Info->Driver_Type==dr_eTC_G2_Aurora_Ma)
		{
			ShowEpd_Result.Result=EPD_display_GU_from_flash(Prev_addr,ShowEpd_Info->NewImageAddress,read_flash_handle,ShowEpd_Info->IsOTP,true);
		}
		else
		{
			ShowEpd_Result.Result=EPD_display_GU_from_flash(ShowEpd_Info->NewImageAddress,Prev_addr,read_flash_handle,ShowEpd_Info->IsOTP,true);
		}
		ShowEpd_Result.time =getnowtime()- ShowEpd_Result.time-100;
		if(ShowEpd_Result.time<1000)ShowEpd_Result.Result=ERROR_DC;
		SendResult_Datas(ResponseData,(uint8_t *)&ShowEpd_Result,sizeof(ShowEpd_Result_t));
       Prev_addr=ShowEpd_Info->NewImageAddress;
		free(ShowEpd_Info);
	}

	Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_Receive_UART,10);
}
void WriteImageFileInfo_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		ImageFlie_info_t *Imageinfo=malloc(sizeof(ImageFlie_info_t));
		memcpy(Imageinfo,(ImageFlie_info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(ImageFlie_info_t));
		ImageLength=Imageinfo->ImagePacketLen;
		check_flash_spi();
		write_flash(Imageinfo->Address,(uint8_t *)&Imageinfo->Mark,sizeof(ImageFlie_info_t)-4);

		SendResultOnly(ResponseData);
		free(Imageinfo);
	}
	else SendResultOnly(ResponseData);
}
void ReadImageFileInfo_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		ImageFlie_info_t *Imageinfo=malloc(sizeof(ImageFlie_info_t));
		memcpy((uint32_t *)&Imageinfo->Address,(uint32_t *)&ResponseData->Recv_Packet_info.payload,sizeof(uint32_t));
		check_flash_spi();
		read_flash(Imageinfo->Address,(uint8_t *)&Imageinfo->Mark,sizeof(ImageFlie_info_t)-4);
		SendResult_Datas(ResponseData,(uint8_t *)Imageinfo,sizeof(ImageFlie_info_t));
		free(Imageinfo);
	}
	else SendResultOnly(ResponseData);
}


void FastShow_Feedback_Handle(void *FeedbackData)
{

}
void WriteRunInfo_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		RunImage_Info_t *RunImage_Info=malloc(sizeof(RunImage_Info_t));
		memcpy(RunImage_Info,(RunImage_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(RunImage_Info_t));
		check_flash_spi();
		write_flash(RunImage_Info->StroreInfo.Address,(uint8_t *)&RunImage_Info->Mark,RunImage_Info->StroreInfo.Length);
		SendResultOnly(ResponseData);
		free(RunImage_Info);
	}
	else   SendResultOnly(ResponseData);
	Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_Receive_UART,10);

}
void ReadRunInfo_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		RunImage_Info_t *RunImage_Info=malloc(sizeof(RunImage_Info_t));
		memcpy(RunImage_Info,(RunImage_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(RunImage_Info_t));
		check_flash_spi();
		read_flash(RunImage_Info->StroreInfo.Address,(uint8_t *)&RunImage_Info->Mark,RunImage_Info->StroreInfo.Length);

		SendResult_Datas(ResponseData,(uint8_t *)RunImage_Info,sizeof(RunImage_Info_t));
		free(RunImage_Info);
	}
	else SendResultOnly(ResponseData);

	Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_Receive_UART,10);
}
void EraseRunInfo_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		uint8_t ChageState=M_IsDel;
		Flash_Parameter_Info_t *fParam=malloc(sizeof(Flash_Parameter_Info_t));
		memcpy(fParam,(Flash_Parameter_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(Flash_Parameter_Info_t));
		check_flash_spi();
		if(fParam->Length==0) erase_flash((fParam->Address&0xFFFFF000),1);
		else write_flash(fParam->Address,(uint8_t *)&ChageState,fParam->Length);
		SendResultOnly(ResponseData);
		free(fParam);
	}
	else SendResultOnly(ResponseData);
}
void WriteBootInfo_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		Boot_Info_t *boot_Info=malloc(sizeof(Boot_Info_t));
		memcpy(boot_Info,(Boot_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(Boot_Info_t));
		check_flash_spi();
		write_flash(boot_Info->StroreInfo.Address,(uint8_t *)&boot_Info->Mark,boot_Info->StroreInfo.Length);
		SendResultOnly(ResponseData);
		free(boot_Info);
		BootTask_Module_init();
	}
	else   SendResultOnly(ResponseData);
	Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_Receive_UART,10);
}
void ReadBootInfo_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		Boot_Info_t *boot_Info=malloc(sizeof(Boot_Info_t));
		memcpy(boot_Info,(Boot_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(Boot_Info_t));
		check_flash_spi();
		read_flash(boot_Info->StroreInfo.Address,(uint8_t *)&boot_Info->Mark,boot_Info->StroreInfo.Length);
		SendResult_Datas(ResponseData,(uint8_t *)boot_Info,sizeof(Boot_Info_t));
		free(boot_Info);
	}
	else SendResultOnly(ResponseData);

	Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_Receive_UART,10);
}
void EraseBootInfo_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		uint8_t ChageState=M_IsDel;
		Flash_Parameter_Info_t *fParam=malloc(sizeof(Flash_Parameter_Info_t));
		memcpy(fParam,(Flash_Parameter_Info_t *)&ResponseData->Recv_Packet_info.payload,sizeof(Flash_Parameter_Info_t));
		check_flash_spi();
		if(fParam->Length==0) erase_flash((fParam->Address&0xFFFFF000),1);
		else write_flash(fParam->Address,(uint8_t *)&ChageState,fParam->Length);
		SendResultOnly(ResponseData);
		free(fParam);
		CancelBootTask_Module();
	}
	else SendResultOnly(ResponseData);
}

void CMD_Debug_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		BootTask_Module_init();
		SendResultOnly(ResponseData);
	}
	else SendResultOnly(ResponseData);
}
void PreRun_Feedback_Handle(void *FeedbackData)
{
	receive_response_info_t *ResponseData=(receive_response_info_t *)FeedbackData;
	if(ResponseData->Recv_Packet_info.cmd_info.Result == Result_OK)
	{
		Previewer((Boot_Info_t *)&ResponseData->Recv_Packet_info.payload);
		SendResultOnly(ResponseData);
	}
	else   SendResultOnly(ResponseData);
	Rtos_Event_Handle_Timer(DM_TASK_ID,DM_EVT_Receive_UART,10);


}
