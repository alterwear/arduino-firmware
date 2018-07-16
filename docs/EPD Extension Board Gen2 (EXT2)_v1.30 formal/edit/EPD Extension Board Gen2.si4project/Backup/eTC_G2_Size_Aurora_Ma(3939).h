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

#ifndef eTC_G2_AURORA_MA_H_
#define eTC_G2_AURORA_MA_H_
#include <EPD_drivers.h>
/**
 * The definition for driving stage to compare with for getting Odd and Even data  */
#define eTC_G2Ma_BLACK0   (uint8_t)(0x03) /**< getting bit1 or bit0 as black color(11) */
#define eTC_G2Ma_BLACK1   (uint8_t)(0x0C) /**< getting bit3 or bit2 as black color(11) */
#define eTC_G2Ma_BLACK2   (uint8_t)(0x30) /**< getting bit5 or bit4 as black color(11) */
#define eTC_G2Ma_BLACK3   (uint8_t)(0xC0) /**< getting bit7 or bit6 as black color(11) */
#define eTC_G2Ma_WHITE0   (uint8_t)(0x02) /**< getting bit1 or bit0 as white color(10) */
#define eTC_G2Ma_WHITE1   (uint8_t)(0x08) /**< getting bit3 or bit2 as white color(10) */
#define eTC_G2Ma_WHITE2   (uint8_t)(0x20) /**< getting bit5 or bit4 as white color(10) */
#define eTC_G2Ma_WHITE3   (uint8_t)(0x80) /**< getting bit7 or bit6 as white color(10) */
#define eTC_G2Ma_NOTHING0 (uint8_t)(0x00) /**< getting bit1 or bit0 as nothing input(01) */
#define eTC_G2Ma_NOTHING1 (uint8_t)(0x00) /**< getting bit3 or bit2 as nothing input(01) */
#define eTC_G2Ma_NOTHING2 (uint8_t)(0x00) /**< getting bit5 or bit4 as nothing input(01) */
#define eTC_G2Ma_NOTHING3 (uint8_t)(0x00) /**< getting bit7 or bit6 as nothing input(01) */
#define eTC_G2Ma_NOTHING  (uint8_t)(0x55) /**< sending Nothing frame, 01=Nothing, 0101=0x5 */

// Line data structure of 1.44 inch Aurora_Ma EPD with G2 COG
struct eTC_G2Ma_144_line_data_t {
    uint8_t border_byte; /**< Internal border_control*/
	uint8_t even[16]; /**< 1.44" even byte array */
	uint8_t scan[24]; /**< 1.44" scan byte array */
	uint8_t odd [16]; /**< 1.44" odd byte array */
	
} ;

// Line data structure of 2 inch Aurora_Ma EPD with G2 COG
struct eTC_G2Ma_200_line_data_t {
    uint8_t border_byte; /**< Internal border_control*/
	uint8_t even[25]; /**< 2" even byte array */
	uint8_t scan[24]; /**< 2" scan byte array */
	uint8_t odd [25]; /**< 2" odd byte array */
} ;

// Line data structure of 2.7 inch Aurora_Ma EPD with G2 COG
struct eTC_G2Ma_270_line_data_t {
    uint8_t border_byte; /**< Internal border_control*/
	uint8_t even[33]; /**< 2.7" even byte array */
	uint8_t scan[44]; /**< 2.7" scan byte array */
	uint8_t odd [33]; /**< 2.7" odd byte array */
} ;

// Define room temperature waveform stages for Aurora_Ma EPD with G2 COG
typedef struct
{
	uint8_t stage1_frame1;
	uint8_t stage1_block1;
	uint8_t stage1_step1;

	uint16_t stage2_t1;
	uint16_t stage2_t2;
	uint8_t stage2_cycle;

	uint8_t stage3_frame3;
	uint8_t stage3_block3;
	uint8_t stage3_step3;
}eTC_G2Ma_RT_WT_t;

// Define low temperature waveform stages for Aurora_Ma EPD with G2 COG
typedef struct
{
	uint16_t stage1_FrameTime;
	uint8_t  stage1_Cycle;

	uint16_t stage2_FrameTime;

	uint16_t stage3_FrameTime;
	uint8_t  stage3_Cycle;

	uint16_t stage4_FrameTime;
}eTC_G2Ma_LT_WT_t;


// Define the Block type waveform structure
typedef struct
{
	 int16_t frame_y0;
	 int16_t frame_y1;
	 int16_t block_y0;
	 int16_t block_y1;
	 int16_t block_size;
	 int16_t step_size;
	 int16_t frame_cycle;
	 int16_t step_y0;
	 int16_t step_y1;
	 int16_t number_of_steps;
}eTC_G2Ma_Block_WT_t;

// Packet structure of a line data */
typedef union {
	union {
        //eTC_G2_Aurora_Ma
         struct eTC_G2Ma_144_line_data_t eTC_G2Ma_144_line_data; /**< line data structure of 1.44" EPD */
		 struct eTC_G2Ma_200_line_data_t eTC_G2Ma_200_line_data; /**< line data structure of 2" EPD */
		 struct eTC_G2Ma_270_line_data_t eTC_G2Ma_270_line_data; /**< line data structure of 2.7" EPD */
    } line_data_by_size; /**< the line data of specific EPD size */
	uint8_t uint8[LINE_BUFFER_DATA_SIZE]; /**< the maximum line buffer data size as length */
} eTC_G2Ma_line_data_t;

void 	eTC_G2Ma_IO_Config(void);
void    eTC_G2Ma_power_on (uint8_t EPD_type_index,int8_t temperature);
uint8_t eTC_G2Ma_initialize_driver (OperationMode_t operationmode);
uint8_t eTC_G2Ma_Display_from_Ram (uint8_t *previous_image_ptr,uint8_t *new_image_ptr);
uint8_t eTC_G2Ma_Display_from_flash ( long previous_image_flash_address,long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash);
uint8_t eTC_G2Ma_power_off (void);

#endif /* eTC_G2_AURORA_MA_H_ */
