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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef COG_FPL_CONFIGURE_H_
#define COG_FPL_CONFIGURE_H_

#define ArrayLength(array) (sizeof(array)/sizeof(array[0]))

typedef void (*EPD_read_memory_handler)(long flash_address,uint8_t *target_buffer,
		uint8_t byte_length);

#define ADDRESS_NULL		0xffffffff
#define ALL_BLACK	 	 (uint8_t)(0xFF)
#define ALL_WHITE		 (uint8_t)(0xAA)
#define BORDER_BYTE_B    (uint8_t)(0xFF)
#define BORDER_BYTE_W    (uint8_t)(0xAA)
#define ERROR_BUSY       (uint8_t)(0x02)
#define ERROR_COG_ID     (uint8_t)(0x04)
#define ERROR_BREAKAGE   (uint8_t)(0x08)
#define ERROR_DC         (uint8_t)(0x10)
#define ERROR_CHARGEPUMP (uint8_t)(0x20)
#define ERROR_NoSuport   (uint8_t)(0x40)
#define ERROR_NoSuportOTP(uint8_t)(0x80)
#define RES_OK           (uint8_t)(0x01)
#define RES_Fail         (uint8_t)(0x00)
#define ArrayLen(ary)	 sizeof(ary)/sizeof(ary[0])
#define Line_Offset(index) COG_parameters[index].horizontal_size;

#define LINE_BUFFER_DATA_SIZE 128
#define COG_line_Max_Size     33

#define VSS			(uint8_t)0x00
#define VSH			(uint8_t)0x01
#define VSL			(uint8_t)0x02
#define VSF			(uint8_t)0x03

#define _HH(x)			(x<<6)
#define _HL(x)			(x<<4)
#define _LH(x)			(x<<2)
#define _LL(x)			(x)

#define WF_VS(HH,HL,LH,LL)	(uint8_t)(_HH(HH)+_HL(HL)+_LH(LH)+_LL(LL))


//Four driving stages for eTC
enum Stage {
	Stage1, /**< Inverse previous image */
	Stage2, /**< White */
	Stage3, /**< Inverse new image */
	Stage4, /**< New image */
	Stage5,
	Stage6,
	LowTemp_Stage1,
	LowTemp_Stage2,
	LowTemp_Stage3,
	LowTemp_Stage4
};

//Supported Driver+EPD types
typedef enum  {
	dr_eTC_G1_Aurora_Mb=0,
	dr_eTC_G2_Aurora_Mb,
	dr_eTC_G2_Aurora_Ma,
	dr_iTC_215_Aurora_Mb,
	dr_iTC_287_Aurora_Mb=7,
	dr_iTC_287_Spectra,
	dr_iTC_420_Aurora_Ma,
	dr_iTC_420_Spectra=10,
	dr_iTC_420_Aurora_Mb,
	dr_iTC_UC_Spectra,
	dr_COUNT
}Driver_Type_t;

//Support EPD Sizes
typedef enum  {
	EPD_144_BW=0,
    EPD_190_BW,
	EPD_200_BW,
	EPD_215_BW,
	EPD_260_BW,
	EPD_271_BW=5,
	EPD_287_BW,
	EPD_271_BWR=8,
	EPD_287_BWR=9,
	EPD_420_BW=10,
	EPD_420_BWR,
	EPD_154uc_BWR,
	EPD_213uc_BWR,
	EPD_266uc_BWR,
	EPD_271uc_BWR,
	EPD_287uc_BWR,
	EPD_Empty
}EPD_SIZE_t;
typedef enum{
	GU_Mode,
    OTP_Mode,
	PU_Mode,
	Fast_Mode
}OperationMode_t;
/*
typedef enum{
    BW_Mode, 
    BWR_Mode
}ColorMode_t;
*/
typedef enum 
{
    CM_Monochrome,
    CM_Color,
    CM_ALL
}ColorMode_t;

//Define the COG driver's parameters */
typedef struct  {
	EPD_SIZE_t	  	Size_ID;
	uint8_t   		channel_select[8]; /**< the SPI register data of Channel Select */
    union{
	uint8_t   		voltage_level;     /**< the SPI register data of Voltage Level */
    uint8_t   		Dummy_line_offset;     /**<dummy line offset length*/
    };
	uint16_t  		horizontal_size;   /**< the bytes of width of EPD */
	uint16_t  		vertical_size;     /**< the bytes of height of EPD */
	uint8_t   		data_line_size;    /**< Data + Scan + Dummy bytes */
	uint16_t  		frame_time_offset; /**< the rest of frame time in a stage */
	uint16_t  		stage_time;        /**< defined stage time */
} COG_parameters_t;

typedef void (*EPD_IO_Configuration_handler)(void);
typedef void (*EPD_power_on_handler)(uint8_t EPD_type_index,int8_t temperature);
typedef uint8_t (*EPD_initialize_driver_handler)(OperationMode_t operationmode);
typedef uint8_t (*EPD_Display_from_Ram_handler)(uint8_t *First_Frame_ptr ,uint8_t *Secon_Frame_ptr);
typedef uint8_t (*EPD_Display_from_flash_handler)( long First_Frame_flash_address,long Secon_Frame_flash_address,EPD_read_memory_handler On_EPD_read_flash);
typedef void (*EPD_Display_PU_from_Ram_handler)(uint8_t *First_Frame_ptr , uint8_t *Secon_Frame_ptr,uint16_t PU_Time);
typedef void (*EPD_Display_PU_From_Flash_handler)(long First_Frame_address, long Secon_Frame_address,EPD_read_memory_handler On_EPD_read_flash,uint16_t PU_Time);
typedef uint8_t (*EPD_power_off_handler)(void);
typedef void (*SetColormode_handler)(ColorMode_t colormode);

typedef struct {
		uint8_t								Driver_ID;
		uint8_t *							Support_Size;
		EPD_IO_Configuration_handler		EPD_IOConfig;
        EPD_power_on_handler 				EPD_power_on;
        EPD_initialize_driver_handler 		EPD_initialize_driver;
        EPD_Display_from_Ram_handler 		EPD_Display_from_Ram;
        EPD_Display_from_flash_handler 		EPD_Display_from_flash;
        EPD_Display_PU_from_Ram_handler	 	EPD_Display_PU_from_Ram; //PU means partial update
        EPD_Display_PU_From_Flash_handler 	EPD_Display_PU_From_Flash;
        EPD_power_off_handler 				EPD_power_off;
        SetColormode_handler                SetColormode;
}Driver_Handle_t;



#ifdef USE_PDI_EDP_LIB
#include <Extern_Board_HW_Driver.h>
#else
#include <Board_HW_Driver.h>
#endif

#endif /* COG_FPL_CONFIGURE_H_ */


