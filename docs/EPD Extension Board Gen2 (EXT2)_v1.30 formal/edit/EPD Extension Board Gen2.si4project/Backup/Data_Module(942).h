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
*
* 3. The name of Atmel may not be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* 4. This software may only be redistributed and used in connection with an
*    Atmel microcontroller product.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef DATA_MODULE_H_
#define DATA_MODULE_H_
#include "conf_EPD.h"


#define  RECV_HEADER0  0xAA
#define  RECV_HEADER1  0x54


typedef enum { CMD_Check,
               CMD_Ver,
               CMD_EraseFlash,
               CMD_EraseEntireFlash,
               CMD_ReadData,
               CMD_WriteData,
               CMD_EPDShow,
               CMD_WriteImageFileInfo,
               CMD_ReadImageFileInfo,
               CMD_WriteImageData,
               CMD_FastShow,
               CMD_WriteRunInfo,
               CMD_ReadRunIinfo,
               CMD_EraseRunInfo,
               CMD_WriteBootInfo,
               CMD_ReadBootInfo,
               CMD_EraseBootInfo,
               CMD_Debug,
               CMD_PreRun
             } CmdArray_t;
typedef enum
{
	FDM_GU_PWDCtrl,
	FDM_GU_NonPWDCtrl,
	FDM_PU_PWDCtrl,
	FDM_PU_NonPWDCtrl,
} DisplayMode_e;

typedef enum
{
	Result_Fail,
	Result_OK,
	Result_Error_BUSY,
	Result_Error_COG_ID,
	Result_Error_BREAKAGE ,
	Result_Error_DC,
	Result_Error_CHARGEPUMP,
	Result_None
} Result_e;
enum DM_EVT {DM_EVT_NONE,
             DM_EVT_Receive_UART,
             DM_EVT_Receive_Packet,
             DM_EVT_UART_Init,
             DM_EVT_RunPacket,
             DM_EVT_WriteImage,
             DM_EVT_ReadImage,
             DM_EVT_WriteData,
             DM_EVT_ReadData,
             DM_EVT_Flash_End,
             DM_EVT_ReadFSInfo,
             DM_EVT_Update_DeviceID,
             DM_EVT_Error_Detect,
             DM_EVT_EPD_PowerOff
            };
typedef enum __attribute__ ((packed))
{
	M_IsDel = 0x80,
	M_IsExist = 0xFE,
	M_IsEmpty = 0xFF,
}
Mark_State_t;
typedef enum __attribute__ ((packed))
{
	Res_Not,
	Res_Result,
	Res_ResultData
}
Response_t;
#define PayloadSize         38
#define Flash_Payload_Size  32
typedef struct __attribute__((__packed__))
{
	uint8_t         Header0;
	uint8_t         Header1;
	uint16_t        Packet_index;
	CmdArray_t      cmd;
	uint16_t        Length;
	Response_t        Response;
	Result_e        Result;
}
Command_info_t ;

typedef struct
{
	Command_info_t  cmd_info;
	uint8_t         payload[PayloadSize];

} Recv_Packet_info_t;

typedef void (*Command_feedback_handler)(void *ResponseData);

typedef struct  __attribute__((__packed__))
{
	Recv_Packet_info_t        Recv_Packet_info;
	uint8_t                   RetryTime;
	Command_feedback_handler  feedback;
}
receive_response_info_t;

typedef struct __attribute__((__packed__))
{
	Command_info_t              cmd_info;
	uint8_t                     ResultData[PayloadSize];
}
Result_Packet_t ;

typedef struct __attribute__((__packed__))
{
	uint32_t  Address;
	uint16_t  Length;
}
Flash_Parameter_Info_t;
typedef struct __attribute__((__packed__))
{
	uint32_t  Address;
	uint16_t  Length;
	uint8_t   data[Flash_Payload_Size];
}
Flash_Info_t;


typedef struct __attribute__((__packed__))
{
	uint8_t   		Driver_Type;
	uint8_t   		EPD_Size;
	int8_t    		Temperature;
	OperationMode_t  	IsOTP;
	uint32_t  		PrevImageAddress;
	uint32_t  		NewImageAddress;
}
ShowEpd_Info_t;
typedef struct __attribute__((__packed__))
{
	uint8_t   		Result;
	int8_t    		Temperature;
	uint32_t   		time;
}
ShowEpd_Result_t;

typedef struct __attribute__((__packed__))
{
	Flash_Parameter_Info_t StroreInfo;
	uint8_t 			Mark;
	uint32_t  		Address;
	DisplayMode_e  	DisplayMode;
	uint32_t 			Time;
	OperationMode_t			RunOTP;
	uint8_t 			reserve[5];
}
RunImage_Info_t;
typedef enum __attribute__ ((packed))
{
	RM_Golbal,
	RM_Partial,
	RM_Fast
}
RunMode_t;
typedef enum __attribute__ ((packed))
{
	ARM_STOP,
	ARM_INTERVAL,
	ARM_BUTTON
}
AutoRunMode_t;

typedef struct __attribute__((__packed__))
{
	Flash_Parameter_Info_t StroreInfo;
	uint8_t 			Mark;
	uint32_t  		Address;
	AutoRunMode_t	    IsRun;
	uint8_t 			IsRepeat;
	//uint16_t      	PageOffset;
	uint8_t   		Driver_Type;
	uint8_t   		EPD_Size;
	int8_t    		Temperature;
	uint8_t 			reserve[6];
}
Boot_Info_t;
typedef struct
{
	uint32_t  		Address;
	uint16_t    	ImagePacketLen;
	uint8_t 		Mark;
	uint8_t   		PanelSize;
	uint8_t		 	ImageType;
	char        	Name[23];
} ImageFlie_info_t;

#define Flash_Addr_Size     4
#define Flash_Sector_Size   2
#define Flash_WR_Size       32


#define DM_TASK_ID         			1


void Data_Module_init(void);
void SendResult(receive_response_info_t *rrp_info);
void SendResult_Datas(receive_response_info_t *rrp_info,uint8_t *data,uint8_t len);
void SendResultOnly(receive_response_info_t *rrp_info);
#endif /* DATA_MODULE_H_ */
