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

#ifndef eTC_G1_AURORA_MB_H_
#define eTC_G1_AURORA_MB_H_
#include <EPD_drivers.h>
/**
 * \brief The definition for driving stage to compare with for getting Odd and Even data  */
#define eTC_G1Mb_BLACK0   (uint8_t)(0x03) /**< getting bit1 or bit0 as black color(11) */
#define eTC_G1Mb_BLACK1   (uint8_t)(0x0C) /**< getting bit3 or bit2 as black color(11) */
#define eTC_G1Mb_BLACK2   (uint8_t)(0x30) /**< getting bit5 or bit4 as black color(11) */
#define eTC_G1Mb_BLACK3   (uint8_t)(0xC0) /**< getting bit7 or bit6 as black color(11) */
#define eTC_G1Mb_WHITE0   (uint8_t)(0x02) /**< getting bit1 or bit0 as white color(10) */
#define eTC_G1Mb_WHITE1   (uint8_t)(0x08) /**< getting bit3 or bit2 as white color(10) */
#define eTC_G1Mb_WHITE2   (uint8_t)(0x20) /**< getting bit5 or bit4 as white color(10) */
#define eTC_G1Mb_WHITE3   (uint8_t)(0x80) /**< getting bit7 or bit6 as white color(10) */
#define eTC_G1Mb_NOTHING0 (uint8_t)(0x01) /**< getting bit1 or bit0 as nothing input(01) */
#define eTC_G1Mb_NOTHING1 (uint8_t)(0x04) /**< getting bit3 or bit2 as nothing input(01) */
#define eTC_G1Mb_NOTHING2 (uint8_t)(0x10) /**< getting bit5 or bit4 as nothing input(01) */
#define eTC_G1Mb_NOTHING3 (uint8_t)(0x40) /**< getting bit7 or bit6 as nothing input(01) */
#define eTC_G1Mb_NOTHING  (uint8_t)(0x55) /**< sending Nothing frame, 01=Nothing, 0101=0x5 */

/**
 * \brief Line data structure of 1.44 inch EPD
 * \note
 * 1.44 inch needs to put border_control byte at the front of data line. */
struct eTC_G1Mb_144_line_data_t {
	uint8_t border_byte;  /**< Internal border_control, for 1.44" EPD only */
	uint8_t even[16]; /**< 1.44" even byte array */
	uint8_t scan[24]; /**< 1.44" scan byte array */
	uint8_t odd [16]; /**< 1.44" odd byte array */
} ;

/**
 * \brief Line data structure of 2 inch EPD
 * \note
 * Add one byte x00 to complete a line */
struct eTC_G1Mb_200_line_data_t {
	uint8_t even[25]; /**< 2" even byte array */
	uint8_t scan[24]; /**< 2" scan byte array */
	uint8_t odd [25]; /**< 2" odd byte array */
	uint8_t dummy_data;	/**< dummy byte 0x00 */
} ;

/**
 * \brief Line data structure of 2.7 inch EPD
 * \note
 * Add one byte x00 to complete a line */
struct eTC_G1Mb_270_line_data_t {
	uint8_t even[33]; /**< 2.7" even byte array */
	uint8_t scan[44]; /**< 2.7" scan byte array */
	uint8_t odd [33]; /**< 2.7" odd byte array */
	uint8_t dummy_data;	/**< dummy byte 0x00 */
} ;


/**
 * \brief Line data structure of 1.9 inch EPD */
struct eTC_G1Mb_190_line_data_t {

    uint8_t border_byte;	/**< Border Byte, Internal border_control*/
    uint8_t scan_odd[16];/**< 1.9" scan odd byte array */
    uint8_t data[36];/**< 1.9" data byte array */
    uint8_t scan_even[16]; /**< 1.9"  scan even byte array */
} ;

/**
 * \brief Line data structure of 2.6 inch EPD */
struct eTC_G1Mb_260_line_data_t {
	uint8_t border_byte;	/**< Border Byte, Internal border_control */
	uint8_t scan_odd[16]; /**< 2.6" even byte array */
	uint8_t data[58]; /**< 2.6" scan byte array */
	uint8_t scan_even [16]; /**< 2.6" odd byte array */

} ;


/**
 * \brief Packet structure of a line data */
typedef union {
	union {
        //eTC_G1_Aurora_Mb
		struct eTC_G1Mb_144_line_data_t eTC_G1Mb_144_line_data; /**< line data structure of 1.44" EPD */
		struct eTC_G1Mb_200_line_data_t eTC_G1Mb_200_line_data; /**< line data structure of 2" EPD */
		struct eTC_G1Mb_270_line_data_t eTC_G1Mb_270_line_data; /**< line data structure of 2.7" EPD */
		struct eTC_G1Mb_190_line_data_t eTC_G1Mb_190_line_data; /**< line data structure of 1.9" EPD */
		struct eTC_G1Mb_260_line_data_t eTC_G1Mb_260_line_data; /**< line data structure of 2.6" EPD */

    } line_data_by_size; /**< the line data of specific EPD size */
	uint8_t uint8[LINE_BUFFER_DATA_SIZE]; /**< the maximum line buffer data size as length */
} eTC_G1Mb_line_data_t;

void eTC_G1Mb_IO_Config(void);
void eTC_G1Mb_power_on (uint8_t EPD_type_index,int8_t temperature);
uint8_t eTC_G1Mb_initialize_driver (OperationMode_t operationmode);
uint8_t eTC_G1Mb_Display_from_Ram (uint8_t *previous_image_ptr,uint8_t *new_image_ptr);
uint8_t eTC_G1Mb_Display_from_flash ( long previous_image_flash_address,long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash);
uint8_t eTC_G1Mb_power_off (void);

void eTC_G1Mb_Display_PU_from_Ram(uint8_t *previous_image_ptr, uint8_t *new_image_ptr,uint16_t PU_Time);
void eTC_G1Mb_Display_PU_From_Flash(long previous_image_address, long new_image_address,EPD_read_memory_handler On_EPD_read_flash,uint16_t PU_Time);

#endif /* eTC_G1AURORA_MB_H_ */
