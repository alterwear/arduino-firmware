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
#ifndef eTC_G2_AURORA_MB_H_
#define eTC_G2_AURORA_MB_H_
#include <EPD_drivers.h>

// The definition for driving stage to compare with for getting Odd and Even data  */
#define eTC_G2Mb_BLACK0   (uint8_t)(0x03) /**< getting bit1 or bit0 as black color(11) */
#define eTC_G2Mb_BLACK1   (uint8_t)(0x0C) /**< getting bit3 or bit2 as black color(11) */
#define eTC_G2Mb_BLACK2   (uint8_t)(0x30) /**< getting bit5 or bit4 as black color(11) */
#define eTC_G2Mb_BLACK3   (uint8_t)(0xC0) /**< getting bit7 or bit6 as black color(11) */
#define eTC_G2Mb_WHITE0   (uint8_t)(0x02) /**< getting bit1 or bit0 as white color(10) */
#define eTC_G2Mb_WHITE1   (uint8_t)(0x08) /**< getting bit3 or bit2 as white color(10) */
#define eTC_G2Mb_WHITE2   (uint8_t)(0x20) /**< getting bit5 or bit4 as white color(10) */
#define eTC_G2Mb_WHITE3   (uint8_t)(0x80) /**< getting bit7 or bit6 as white color(10) */
#define eTC_G2Mb_NOTHING0 (uint8_t)(0x00) /**< getting bit1 or bit0 as nothing input(01) */
#define eTC_G2Mb_NOTHING1 (uint8_t)(0x00) /**< getting bit3 or bit2 as nothing input(01) */
#define eTC_G2Mb_NOTHING2 (uint8_t)(0x00) /**< getting bit5 or bit4 as nothing input(01) */
#define eTC_G2Mb_NOTHING3 (uint8_t)(0x00) /**< getting bit7 or bit6 as nothing input(01) */
#define eTC_G2Mb_NOTHING  (uint8_t)(0x55) /**< sending Nothing frame, 01=Nothing, 0101=0x5 */

// Line data structure of 1.44 inch EPD
struct eTC_G2Mb_144_line_data_t {
	uint8_t even[16]; /**< 1.44" even byte array */
	uint8_t scan[24]; /**< 1.44" scan byte array */
	uint8_t odd [16]; /**< 1.44" odd byte array */
	uint8_t border_byte;  /**< Internal border_control, for 1.44" EPD only */
} ;

// Line data structure of 2 inch EPD
struct eTC_G2Mb_200_line_data_t {
    uint8_t dummy_data;	/**< dummy byte 0x00 */
	uint8_t even[25]; /**< 2" even byte array */
	uint8_t scan[24]; /**< 2" scan byte array */
	uint8_t odd [25]; /**< 2" odd byte array */

} ;

// Line data structure of 2.7 inch EPD
struct eTC_G2Mb_270_line_data_t {
    uint8_t dummy_data;	/**< dummy byte 0x00 */
	uint8_t even[33]; /**< 2.7" even byte array */
	uint8_t scan[44]; /**< 2.7" scan byte array */
	uint8_t odd [33]; /**< 2.7" odd byte array */
} ;


// Line data structure of 1.9 inch EPD
struct eTC_G2Mb_190_line_data_t {
    uint8_t scan_odd[16];/**< 1.9" scan odd byte array */
    uint8_t data[36];/**< 1.9" data byte array */
    uint8_t scan_even[16]; /**< 1.9"  scan even byte array */
    uint8_t border_byte;	/**< Border Byte, Internal border_control*/
} ;

// Line data structure of 2.6 inch EPD
struct eTC_G2Mb_260_line_data_t {
	uint8_t scan_odd[16]; /**< 2.6" even byte array */
	uint8_t data[58]; /**< 2.6" scan byte array */
	uint8_t scan_even [16]; /**< 2.6" odd byte array */
    uint8_t border_byte;	/**< Border Byte, Internal border_control */
} ;

// Packet structure of a line data */
typedef union {
	union {
        //eTC_G2_Aurora_Mb
        struct eTC_G2Mb_144_line_data_t eTC_G2Mb_144_line_data; /**< line data structure of 1.44" EPD */
		struct eTC_G2Mb_200_line_data_t eTC_G2Mb_200_line_data; /**< line data structure of 2" EPD */
		struct eTC_G2Mb_270_line_data_t eTC_G2Mb_270_line_data; /**< line data structure of 2.7" EPD */
		struct eTC_G2Mb_190_line_data_t eTC_G2Mb_190_line_data; /**< line data structure of 1.9" EPD */
		struct eTC_G2Mb_260_line_data_t eTC_G2Mb_260_line_data; /**< line data structure of 2.6" EPD */

    } line_data_by_size; /**< the line data of specific EPD size */
	uint8_t uint8[LINE_BUFFER_DATA_SIZE]; /**< the maximum line buffer data size as length */
} eTC_G2Mb_line_data_t;

void 	eTC_G2Mb_IO_Config(void);
void    eTC_G2Mb_power_on (uint8_t EPD_type_index,int8_t temperature);
uint8_t eTC_G2Mb_initialize_driver (OperationMode_t operationmode);
uint8_t eTC_G2Mb_Display_from_Ram (uint8_t *First_Frame_ptr ,uint8_t *Secon_Frame_ptr);
uint8_t eTC_G2Mb_Display_from_flash ( long First_Frame_flash_address,long Secon_Frame_flash_address,EPD_read_memory_handler On_EPD_read_flash);
uint8_t eTC_G2Mb_power_off (void);

void    eTC_G2Mb_Display_PU_from_Ram(uint8_t *First_Frame_ptr , uint8_t *Secon_Frame_ptr,uint16_t PU_Time);
void    eTC_G2Mb_Display_PU_From_Flash(long First_Frame_address, long Secon_Frame_address,EPD_read_memory_handler On_EPD_read_flash,uint16_t PU_Time);

#endif /* eTC_G2_AURORA_MB_H_ */

