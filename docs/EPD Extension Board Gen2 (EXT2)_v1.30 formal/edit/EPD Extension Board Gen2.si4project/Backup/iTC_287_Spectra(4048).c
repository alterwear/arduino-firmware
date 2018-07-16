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

#include <EPD_drivers.h>
#include <iTC_287_Spectra.h>
#include "iTC_Engine.h"

extern const iTC_WaveformLUT_t iTC_287Sp_LUT;
const iTC_WaveformLUT_t iTC_287Sp_OTP_LUT={
	(const uint8_t []){//Power on LUT
					iCMD_IO_Ctrl,io_All,0,      //all pin =0
					iCMD_IO_Ctrl,io_Panel_on,1, //Turn-on VCC / VDD
					iCMD_Delay,0x05,0x00,       //Delay 5ms
					iCMD_IO_Ctrl,io_Res,1,      //RES=1
					iCMD_Delay,0x01,0x00,       //Delay 1ms
					iCMD_IO_Ctrl,io_CS,1,       //CS=1
					iCMD_IO_Ctrl,io_SPI_Pin,1,  //spi attach
					iCMD_END
				},
	(const uint8_t []){//Initial LUT
					iCMD_iTC_SPI	         ,0x00,1,0x8f,                   //Panel Settings
	                iCMD_iTC_SPI	         ,0x06,3,0x17,0x17,0x17,         //Booster soft start settings
	                iCMD_iTC_SPI	         ,0x61,3,0x80,0x01,0x28,    	 //Resolution settnigs
                    iCMD_iTC_SPI	         ,0x50,1,0x87,                   //Vcom and data interval setting
					iCMD_iTC_SPI	         ,0xe0,1,0x02,                   //Active Temperature
					iCMD_SetTemper           ,0xe5,0x01,0x1a,  		         //SPI(e5,T)
					iCMD_END
				},
	(const uint8_t []){//Input image update
					iCMD_Image,CM_Monochrome,false	,0x00	,1,0x10,0x80,0x00,0x28,0x01,
					iCMD_Image,CM_Monochrome,true 	,0x00	,1,0x13,0x80,0x00,0x28,0x01,
					iCMD_Image,CM_Color		,false	,0x00	,1,0x10,0x80,0x00,0x28,0x01,
					iCMD_Image,CM_Color		,false	,0x00	,1,0x13,0x80,0x00,0x28,0x01,
					iCMD_Busy				,0x01	,0xE8	,0x03,
					iCMD_iTC_SPI			,0x04	,0,
					iCMD_Busy				,0x01   ,0xE8   ,0x03,
					iCMD_iTC_SPI			,0x12	,0		,
					iCMD_END
				},
	(const uint8_t []){//Power off

					iCMD_Busy				,0x01   ,0xFF   ,0xFF,
					iCMD_iTC_SPI			,0x02,0 ,
					iCMD_Busy				,0x01   ,0x64   ,0x00,
					iCMD_IO_Ctrl			,io_All ,0,
					iCMD_IO_Ctrl			,io_SPI_Pin,0,
					iCMD_IO_Ctrl			,io_discharge,1,
					iCMD_END
				}
				,
	(const uint8_t []){//ExceptionL
					iCMD_IO_Ctrl			,io_discharge,1,
					iCMD_IO_Ctrl			,io_SPI_Pin,0,
					iCMD_IO_Ctrl			,io_All,0,
					iCMD_END
				}
};

void iTC_287Sp_IO_Config(void)
{

	iTC_IO_Config();
}

void iTC_287Sp_power_on (uint8_t EPD_type_index,int8_t temperature)
{

	iTC_power_on(EPD_type_index,temperature,&iTC_287Sp_LUT,&iTC_287Sp_OTP_LUT,NULL);
}

uint8_t iTC_287Sp_initialize_driver (OperationMode_t operationmode)
{
	return iTC_initialize_driver(operationmode);
}

uint8_t iTC_287Sp_Display_from_Ram (uint8_t *previous_image_ptr,uint8_t *new_image_ptr)
{
	return iTC_Display_from_Ram(previous_image_ptr,new_image_ptr);
}

uint8_t iTC_287Sp_Display_from_flash ( long previous_image_flash_address,long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash)
{
	return iTC_Display_from_flash(previous_image_flash_address,new_image_flash_address,On_EPD_read_flash);
}

uint8_t iTC_287Sp_power_off (void)
{
	return iTC_power_off();
}

