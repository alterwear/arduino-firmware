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


#ifndef MEM_FLASH_H_
#define MEM_FLASH_H_
#include "conf_EPD.h"
/******************************************************************************
 * \brief Each EPD size has 32 pages of image
 *
 * \note
 * - Divided 32 pages into 2 segments A and B. Each segment has 16 pages.
 * - Segment A: for sequence image buffer at "Drawing" tab of EPD Kit Tool
 * - Segment B: for Slideshow, ASCII and custom assigned images of EPD Kit Tool
 */

/** Flash map *****************************************************************/
#define _flash_sector_size          (long)4*1024                //4K

//#define _page_size                  (long)_flash_sector_size*Image_sector_size  //16k
//#define _page_max	                1024/16 //64 pages 1M bytes/16KByte=64


/******************************************************************************/
/** The Flash MX25 series command hex code definition */
#define ElectronicID   0x13

/** ID commands */
#define FLASH_CMD_RDID 0x9F      //RDID (Read Identification)
#define FLASH_CMD_RES  0xAB      //RES (Read Electronic ID)
#define FLASH_CMD_REMS 0x90      //REMS (Read Electronic & Device ID)

/** Register commands */
#define FLASH_CMD_WRSR 0x01      //WRSR (Write Status Register)
#define FLASH_CMD_RDSR 0x05      //RDSR (Read Status Register)

/** READ commands */
#define FLASH_CMD_READ     0x03  //READ (1 x I/O)
#define FLASH_CMD_FASTREAD 0x0B  //FAST READ (Fast read data)

/** Program commands */
#define FLASH_CMD_WREN 0x06      //WREN (Write Enable)
#define FLASH_CMD_WRDI 0x04      //WRDI (Write Disable)
#define FLASH_CMD_PP   0x02      //PP (page program)

/** Erase commands */
#define FLASH_CMD_SE 0x20        //SE (Sector Erase)
#define FLASH_CMD_BE 0xD8        //BE (Block Erase)
#define FLASH_CMD_CE 0x60        //CE (Chip Erase) hex code: 60 or C7

/** Mode setting commands */
#define FLASH_CMD_DP  0xB9       //DP (Deep Power Down)
#define FLASH_CMD_RDP 0xAB       //RDP (Release form Deep Power Down)

/** status register */
#define FLASH_WIP_MASK  0x01
#define FLASH_LDSO_MASK 0x02
#define FLASH_QE_MASK   0x40

uint8_t is_flash_existed(void);

void Flash_cs_high(void);
void Flash_cs_low(void);
//void CMD_SE( long flash_address );

//void CMD_CE(void);

void read_flash(long Address,uint8_t *target_address, uint8_t byte_length);
void write_flash(long Address,uint8_t *source_address, uint8_t byte_length);
void erase_flash(long Address,uint16_t sectorLen);

#endif /* MEM_FLASH_H_ */
