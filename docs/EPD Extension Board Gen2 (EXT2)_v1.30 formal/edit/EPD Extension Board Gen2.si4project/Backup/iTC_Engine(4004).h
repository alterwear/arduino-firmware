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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <EPD_drivers.h>
#ifndef SRC_FPL_DRIVERS_ITC_ENGINE_H_
#define SRC_FPL_DRIVERS_ITC_ENGINE_H_
#define TP_Empty			(uint8_t)(-128)
#define sig_TP_Empty		(int8_t)(-128)
#define ATTRIBUTE_PACKED __attribute__ ((packed))
//#define ATTRIBUTE_PACKED
typedef void (*ImageData_handler)(uint8_t *LineData,uint16_t len,uint8_t PixelBits);
enum iTC_Engine_EVT{
			  iTCE_EVT_NONE,
			  BTM_Init,
			  BTM_Load_BootInfo,
			  BTM_RunScript,
			  BTM_DisplayImage,
			  BTM_EndBoot
            };
#define Res_CR_OK		0x01
#define Res_TP_OK		0x02
/*
typedef enum ATTRIBUTE_PACKED
{
	CM_Monochrome,
	CM_Color,
	CM_ALL
}ColorMode_t;
*/
typedef enum ATTRIBUTE_PACKED
{
	io_All,
	io_Panel_on,
	io_Res,
	io_CS,
	io_DC,
	io_discharge,
	io_SPI_Pin
}IO_Define_t;

// iCMD means commands for iTC, Cr = commands for Spectra, TP = commands for temperature
// IO_Ctrl = commands for ontrolling GPIO of IO_Define_t, image = commands for sending image data
typedef enum ATTRIBUTE_PACKED
{
	iCMD_END,
	iCMD_iTC_SPI,
	iCMD_iTC_SPI_Cr,
	iCMD_iTC_SPI_TP,
	iCMD_iTC_SPI_Cr_TP,
	iCMD_Busy=0x10,
	iCMD_IO_Ctrl,
	iCMD_Delay,
	iCMD_Image,
	iCMD_Image_PU,
	iCMD_SetTemper
}iTC_Cmd_t;

typedef struct ATTRIBUTE_PACKED
{
	uint16_t 		time;
}iTC_delay_param_t;

typedef struct ATTRIBUTE_PACKED
{
	uint8_t 		io_pin;
	uint8_t 		io_data;
}iTC_IO_param_t;

typedef struct ATTRIBUTE_PACKED
{
	uint8_t 		compare_data;
	uint16_t 		time;
}iTC_Busy_param_t;
#define RegTemper_Header		2
typedef struct ATTRIBUTE_PACKED
{
	uint8_t 		regIndex_cmd;
	uint8_t 		DataLen;
	uint8_t 		*reg_data;
}iTC_Reg_Temper_t;
#define RegData_Header		2
typedef struct ATTRIBUTE_PACKED
{
	uint8_t 		regIndex_cmd;
	uint8_t 		DataLen;
	uint8_t 		*reg_data;
}iTC_Reg_data_t;

#define RegCr_Header		3
typedef struct ATTRIBUTE_PACKED
{
	ColorMode_t  	CrMode;
	uint8_t 		regIndex_cmd;
	uint8_t 		DataLen;
	uint8_t 		*reg_data;
}iTC_Reg_Cr_t;

#define RegCrTP_Header		5
typedef struct ATTRIBUTE_PACKED
{
	ColorMode_t  	CrMode;
	int8_t 			Tmax;
	int8_t 			Tmin;
	uint8_t 		regIndex_cmd;
	uint8_t 		DataLen;
	uint8_t 		*reg_data;
}iTC_Reg_Cr_TP_t;

#define RegTP_Header		4
typedef struct ATTRIBUTE_PACKED
{
	int8_t 			Tmax;
	int8_t 			Tmin;
	uint8_t 		regIndex_cmd;
	uint8_t 		DataLen;
	uint8_t 		*reg_data;
}iTC_Reg_TP_t;


#define RegImage_Header		9
typedef struct ATTRIBUTE_PACKED
{
	ColorMode_t  	CrMode;
	bool 			UseInternalData;
	uint8_t 		InternalData;
	uint8_t 		pixel_bit;
	uint8_t 		regIndex_cmd;
    uint16_t 		Horizontal;
	uint16_t 		Vertical;
	//uint8_t 		PixelBits;
}iTC_Reg_Image_t;

typedef struct ATTRIBUTE_PACKED
{
	const uint8_t 		*PowerOn_LUT;
	const uint8_t 		*Initial_LUT;
	const uint8_t			*Update_LUT;
	const uint8_t			*PowerOffLUT;
	const uint8_t			*ExceptionLUT;
}iTC_WaveformLUT_t;


void iTC_Engine_init(ColorMode_t cr,int8_t temper,ImageData_handler OnImageData_handler,EPD_read_memory_handler OnReadExternalMemory);
uint8_t RunEngine(const void *runLUTFile);
uint8_t Ex_RunEngine(long ExtenalAddress);
void SetPU_ImageDataHandle(ImageData_handler OnImageDataPU_handler);

void iTC_IO_Config(void);
void iTC_power_on (uint8_t EPD_type_index,int8_t temperature,const iTC_WaveformLUT_t *GU_LUT,
                        const iTC_WaveformLUT_t *OTP_LUT,const iTC_WaveformLUT_t *PU_LUT);
uint8_t iTC_initialize_driver (OperationMode_t operationmode);
uint8_t iTC_Display_from_Ram (uint8_t *First_Frame_ptr ,uint8_t *Secon_Frame_ptr);
uint8_t iTC_Display_from_flash ( long First_Frame_flash_address,long Secon_Frame_flash_address,EPD_read_memory_handler On_EPD_read_flash);
uint8_t iTC_power_off (void);

void iTC_Display_PU_from_Ram(uint8_t *First_Frame_ptr , uint8_t *Secon_Frame_ptr,uint16_t PU_Time);
void iTC_Display_PU_From_Flash(long First_Frame_flash_address, long Secon_Frame_flash_address,EPD_read_memory_handler On_EPD_read_flash,uint16_t PU_Time);
void iTC_SetColormode(ColorMode_t colormode);

#endif /* SRC_FPL_DRIVERS_ITC_ENGINE_H_ */
