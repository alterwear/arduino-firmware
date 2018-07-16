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
*
**/

#include <EPD_drivers.h>
#include <iTC_215_Aurora_Mb.h>
#include "iTC_Engine.h"

extern const iTC_WaveformLUT_t iTC_215Mb_LUT;//global update LUT in EPD_iTClib_TM4C123.lib
extern const iTC_WaveformLUT_t iTC_215Mb_PU_LUT;//Partial update LUT in EPD_iTClib_TM4C123.lib

const iTC_WaveformLUT_t iTC_215Mb_OTP_LUT={
	(const uint8_t []){//Power on LUT
				iCMD_IO_Ctrl,io_All,0,
				iCMD_IO_Ctrl,io_SPI_Pin,1,
				iCMD_IO_Ctrl,0x01,0x01,  // io_Panel_on=1
				iCMD_Delay,0x32,0x00,  //Delay 50 ms
				iCMD_IO_Ctrl,0x02,0x01,  // io_Res=1
				iCMD_Delay,0x01,0x00,  //Delay 1 ms
				iCMD_IO_Ctrl,0x03,0x01,  // io_CS=1
				iCMD_iTC_SPI,0x12,0x00, // SW RESET
				iCMD_END
				},
	(const uint8_t []){//Initial LUT
				iCMD_Busy,0x00,0xE8,0x03,  			// Wait BUSY =0
				iCMD_iTC_SPI,0x01,0x02,0xCF,0x00,  		// SPI(01,CF,00)
				iCMD_iTC_SPI,0x0F,0x01,0x00,  	  		// SPI(0F,00)
				iCMD_iTC_SPI,0x11,0x01,0x03,  			// SPI(11,03)
				iCMD_iTC_SPI,0x44,0x02,0x00,0x0D,  		// SPI(44,00,0D)
				iCMD_iTC_SPI,0x45,0x02,0x00,0xCF,  		// SPI(45,00,CF)
				iCMD_iTC_SPI,0x4E,0x01,0x00,  			// SPI(4E,00)
				iCMD_iTC_SPI,0x4F,0x01,0x00,  			// SPI(4F,00)
				iCMD_END
				},
	(const uint8_t []){//Input image update
				iCMD_iTC_SPI,0x3C,0x01,0x80,  			// SPI(3C,80)
				iCMD_iTC_SPI,0x03,0x02,0x10,0x0A,  		// SPI(03,10,0A)
				iCMD_iTC_SPI,0x05,0x01,0x00,  			// SPI(05,00)
				iCMD_iTC_SPI,0x75,0x03,0x00,0x00,0x00,  // SPI(75,00,00,00)
				iCMD_Image,0x00,0x00,0x00,0x01,0x24,0x70,0x00,0xD0,0x00,  // CM_Monochrome , 112 X 208 , Pixel_1Bits , SPI(24 , Image datas..)
				iCMD_Busy,0x00,0x10,0x27,  			// Wait BUSY =0
				iCMD_SetTemper,0x1A,0x02,0x1a,0x00,  		// SPI(1a,00,00)
				iCMD_iTC_SPI,0x22,0x01,0xf7,  			
				iCMD_iTC_SPI,0x20,0x00,  				// SPI(20)
				iCMD_Busy,0x00,0x10,0x27,  			// Wait BUSY =0
				iCMD_END
				},
	(const uint8_t []){//Power off
				iCMD_IO_Ctrl,0x04,0x00,  // io_DC=0
				iCMD_IO_Ctrl,0x01,0x00,  // io_Panel_on=0
				iCMD_IO_Ctrl,0x02,0x00,  // io_Res=0
				iCMD_IO_Ctrl,0x06,0x00,  // io_SPI_Pin=0
				iCMD_IO_Ctrl,0x03,0x00,  // io_CS=0
				iCMD_IO_Ctrl,0x05,0x01,  // io_discharge=1
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

void iTC_215Mb_IO_Config(void)
{

	iTC_IO_Config();
}

void iTC_215Mb_power_on (uint8_t EPD_type_index,int8_t temperature)
{
	iTC_power_on(EPD_type_index,temperature,&iTC_215Mb_LUT,&iTC_215Mb_OTP_LUT,&iTC_215Mb_PU_LUT);
}

uint8_t iTC_215Mb_initialize_driver (OperationMode_t operationmode)
{
    return iTC_initialize_driver(operationmode);
}


uint8_t iTC_215Mb_Display_from_Ram (uint8_t *previous_image_ptr,uint8_t *new_image_ptr)
{
    return iTC_Display_from_Ram(previous_image_ptr,new_image_ptr);
}

uint8_t iTC_215Mb_Display_from_flash ( long previous_image_flash_address,long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash)
{
	return iTC_Display_from_flash(previous_image_flash_address,new_image_flash_address,On_EPD_read_flash);
}
//Partial update cycle by giving from the pointer of memory
void iTC_215Mb_Display_PU_from_Ram(uint8_t *previous_image_ptr, uint8_t *new_image_ptr,uint16_t PU_Time)
{
    iTC_Display_PU_from_Ram(previous_image_ptr, new_image_ptr,PU_Time);
}

// Partial update cycle by giving from the address of memory
void iTC_215Mb_Display_PU_From_Flash(long previous_image_flash_address, long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash,uint16_t PU_Time)
{
	iTC_Display_PU_From_Flash(previous_image_flash_address, new_image_flash_address, On_EPD_read_flash, PU_Time);
}
uint8_t iTC_215Mb_power_off (void)
{
    return iTC_power_off();
}

