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

#include <EPD_drivers.h>
#include <iTC_UC8451c_Spectra.h>
#include "iTC_Engine.h"

//extern const iTC_WaveformLUT_t iTC_UC8451cSp_LUT;
const iTC_WaveformLUT_t iTC_UC8451cSp_OTP_LUT =
{
	(const uint8_t []) //Power on LUT
	{
		iCMD_IO_Ctrl, io_All, 0,    //all pin =0
		iCMD_IO_Ctrl, io_Panel_on, 1, //Turn-on VCC / VDD
		iCMD_Delay, 0x05, 0x00,     //Delay 5ms
		iCMD_IO_Ctrl, io_Res, 1,    //RES=1
		iCMD_Delay, 0x05, 0x00,     //Delay 5ms
		iCMD_IO_Ctrl, io_Res, 0,    //RES=0
		iCMD_IO_Ctrl, io_Res, 1,    //RES=1
		iCMD_Delay, 0x05, 0x00,     //Delay 5ms
		iCMD_IO_Ctrl, io_CS, 1,     //CS=1
		iCMD_IO_Ctrl, io_SPI_Pin, 1, //spi attach
		iCMD_iTC_SPI, 0x00, 1, 0x0E,
		iCMD_END
	},
	(const uint8_t []) //Initial LUT
	{
		//iCMD_iTC_SPI	, 0x00, 1, 0x8f,                         //Panel Settings
		//iCMD_iTC_SPI	, 0x06, 3, 0x17, 0x17, 0x17,             //Booster soft start settings
		//iCMD_iTC_SPI	, 0x61, 3, 0xB0, 0x01, 0x08,    	     //Resolution settnigs
		//iCMD_iTC_SPI	, 0x50, 1, 0x87,                         //Vcom and data interval setting
		//iCMD_iTC_SPI	, 0xe0, 1, 0x02,                         //Active Temperature

		iCMD_SetTemper, 0xe5, 0x01, 0x1a,  		                 //SPI(e5,T)
		iCMD_iTC_SPI	, 0xE0, 1, 0x02,                         //Active Temperature
		iCMD_END
	},
	(const uint8_t []) //Input image update
	{

		/*
		iCMD_Image, CM_Monochrome, false	, 0x00	, 1, 0x10, 0xB0, 0x00, 0x08, 0x01,
		iCMD_Image, CM_Monochrome, true 	, 0x00	, 1, 0x13, 0xB0, 0x00, 0x08, 0x01,
		iCMD_Image, CM_Color		, false	, 0x00	, 1, 0x10, 0xB0, 0x00, 0x08, 0x01,
		iCMD_Image, CM_Color		, false	, 0x00	, 1, 0x13, 0xB0, 0x00, 0x08, 0x01,

		iCMD_Busy				, 0x01	, 0xE8	, 0x03,
		iCMD_iTC_SPI			, 0x04	, 0,
		iCMD_Busy				, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI			, 0x12	, 0		,
		iCMD_END*/
	},
	(const uint8_t []) //Power off
	{

		iCMD_Busy				, 0x01, 0xFF, 0xFF,
		iCMD_iTC_SPI			, 0x02, 0,
		iCMD_Busy				, 0x01, 0x64, 0x00,
		iCMD_IO_Ctrl			, io_All, 0,
		iCMD_IO_Ctrl			, io_SPI_Pin, 0,
		iCMD_IO_Ctrl			, io_discharge, 1,
		iCMD_END
	}
	,
	(const uint8_t []) //ExceptionL
	{
		iCMD_IO_Ctrl			, io_discharge, 1,
		iCMD_IO_Ctrl			, io_SPI_Pin, 0,
		iCMD_IO_Ctrl			, io_All, 0,
		iCMD_END
	}
};
//Initial settnigs OTP
const uint8_t 	*ImageSetting_LUT[5] =
{
	(const uint8_t []) //2.87"
	{
		iCMD_Image, CM_Monochrome, false, 0x00, 1, 0x10, 0x80,0x00,0x28,0x01,
		iCMD_Image, CM_Monochrome, true , 0x00, 1, 0x13, 0x80,0x00,0x28,0x01,
		iCMD_Image, CM_Color     , false, 0x00, 1, 0x10, 0x80,0x00,0x28,0x01,
		iCMD_Image, CM_Color     , false, 0x00, 1, 0x13, 0x80,0x00,0x28,0x01,

		iCMD_Busy, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI, 0x04, 0,
		iCMD_Busy, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI, 0x12, 0,
		iCMD_END
	},
	(const uint8_t []) //2.7"
	{
	
        iCMD_iTC_SPI    , 0x00, 1, 0x8f,                         //Panel Settings
        iCMD_iTC_SPI    , 0x06, 3, 0x17, 0x17, 0x17,             //Booster soft start settings
        iCMD_iTC_SPI    , 0x61, 3, 0xB0, 0x01, 0x08,             //Resolution settnigs
        iCMD_iTC_SPI    , 0x50, 1, 0x87,                         //Vcom and data interval setting
        iCMD_iTC_SPI    , 0xe0, 1, 0x02,                         //Active Temperature
        
		iCMD_Image, CM_Monochrome, false	, 0x00	, 1, 0x10, 0xB0, 0x00, 0x08, 0x01,
		iCMD_Image, CM_Monochrome, true 	, 0x00	, 1, 0x13, 0xB0, 0x00, 0x08, 0x01,
		iCMD_Image, CM_Color	 , false	, 0x00	, 1, 0x10, 0xB0, 0x00, 0x08, 0x01,
		iCMD_Image, CM_Color	 , false	, 0x00	, 1, 0x13, 0xB0, 0x00, 0x08, 0x01,
		
		iCMD_Busy				, 0x01	, 0xE8	, 0x03,
		iCMD_iTC_SPI			, 0x04	, 0,
		iCMD_Busy				, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI			, 0x12	, 0		,
		iCMD_END
	},
	(const uint8_t []) //2.66"
	{

		iCMD_Image, CM_Monochrome, false, 0x00, 1, 0x10, 0x98, 0x00, 0x28, 0x01,
		iCMD_Image, CM_Monochrome, true , 0x00, 1, 0x13, 0x98, 0x00, 0x28, 0x01,
		iCMD_Image, CM_Color     , false, 0x00, 1, 0x10, 0x98, 0x00, 0x28, 0x01,
		iCMD_Image, CM_Color     , false, 0x00, 1, 0x13, 0x98, 0x00, 0x28, 0x01,

		iCMD_Busy, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI, 0x04, 0,
		iCMD_Busy, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI, 0x12, 0,
		iCMD_END
	},
	(const uint8_t []) //2.13"
	{

		iCMD_Image, CM_Monochrome, false, 0x00, 1, 0x10, 0x68, 0x00, 0xD4, 0x00,
		iCMD_Image, CM_Monochrome, true , 0x00, 1, 0x13, 0x68, 0x00, 0xD4, 0x00,
		iCMD_Image, CM_Color     , false, 0x00, 1, 0x10, 0x68, 0x00, 0xD4, 0x00,
		iCMD_Image, CM_Color     , false, 0x00, 1, 0x13, 0x68, 0x00, 0xD4, 0x00,
		iCMD_Busy, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI, 0x04, 0,
		iCMD_Busy, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI, 0x12, 0,
		iCMD_END
	},
	(const uint8_t []) //1.54"
	{

		iCMD_Image, CM_Monochrome, false, 0x00, 1, 0x10, 0x98, 0x00, 0x98, 0x00,
		iCMD_Image, CM_Monochrome, true , 0x00, 1, 0x13, 0x98, 0x00, 0x98, 0x00,
		iCMD_Image, CM_Color     , false, 0x00, 1, 0x10, 0x98, 0x00, 0x98, 0x00,
		iCMD_Image, CM_Color     , false, 0x00, 1, 0x13, 0x98, 0x00, 0x98, 0x00,
		iCMD_Busy, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI, 0x04, 0,
		iCMD_Busy, 0x01, 0xE8, 0x03,
		iCMD_iTC_SPI, 0x12, 0,
		iCMD_END
	}

};

static EPD_SIZE_t use_EDP_Size;

void iTC_UC8451cSp_IO_Config(void)
{

	iTC_IO_Config();
}

void iTC_UC8451cSp_power_on(uint8_t EPD_type_index, int8_t temperature)
{
	use_EDP_Size = (EPD_SIZE_t)EPD_type_index;
	iTC_power_on(EPD_type_index, temperature, NULL, &iTC_UC8451cSp_OTP_LUT, NULL);
}

uint8_t iTC_UC8451cSp_initialize_driver(OperationMode_t operationmode)
{
	return iTC_initialize_driver(operationmode);
}

uint8_t iTC_UC8451cSp_Display_from_Ram(uint8_t *First_Frame_ptr, uint8_t *Secon_Frame_ptr)
{
        int8_t index=-1;
        switch(use_EDP_Size)
        {
           case EPD_287_BWR:
           case EPD_287_BW:
                            index=0;
                      break;
           case EPD_271_BWR:
           case EPD_271_BW:
                            index=1;
                      break;   
           case EPD_266_BWR:
           case EPD_266_BW:
                            index=2;
                      break;   
           case EPD_213_BWR:
           case EPD_213_BW:
                            index=3;
                      break;   
           case EPD_154_BWR:
           case EPD_154_BW:
                            index=4;
                      break;   

        }
	return iTC_Display_from_Ram_ex(First_Frame_ptr, Secon_Frame_ptr,ImageSetting_LUT[index]);
}

uint8_t iTC_UC8451cSp_Display_from_flash(long First_Frame_flash_address, long Secon_Frame_flash_address, 
EPD_read_memory_handler On_EPD_read_flash)
{
        int8_t index=-1;
        switch(use_EDP_Size)
        {
           case EPD_287_BWR:
           case EPD_287_BW:
                            index=0;
                      break;
           case EPD_271_BWR:
           case EPD_271_BW:
                            index=1;
                      break;   
           case EPD_266_BWR:
           case EPD_266_BW:
                            index=2;
                      break;   
           case EPD_213_BWR:
           case EPD_213_BW:
                            index=3;
                      break;   
           case EPD_154_BWR:
           case EPD_154_BW:
                            index=4;
                      break;   

        }
	return iTC_Display_from_flash_ex(First_Frame_flash_address, Secon_Frame_flash_address,
	                                On_EPD_read_flash,ImageSetting_LUT[index]);
}

uint8_t iTC_UC8451cSp_power_off(void)
{
	return iTC_power_off();
}
void iTC_UC8451cSp_SetColormode(ColorMode_t colormode)
{
	iTC_SetColormode(colormode);
}

