/**
* Copyright (c) Pervasive Displays Inc. All rights reserved.
*
* \asf_license_start
*
* \page License
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
* \asf_license_stop
**/

#ifndef SRC_APP_FLASH_MEM_MAP_H_
#define SRC_APP_FLASH_MEM_MAP_H_
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#define TemporaryMinSize		50
#define TemporaryMaxSize		62
#define BlockMaxSize  			62
#define FunctionBlock  			63

#define PayloadLen 				32
#define BlockSector 			8
#define ImageInfoSize 			32
#define SectorSize 				(1024 * 4)
#define BlockSize 				(uint32_t)(BlockSector * SectorSize)//1 Block=32 KBytes

#define BootBlockMax			32
#define FunBootAddress  		(uint32_t)(FunctionBlock * SectorSize*4)

#define RunBlockMax				50
#define FunRunAddress  			(uint32_t)((FunctionBlock * SectorSize*4) + SectorSize)

uint32_t GetFunBootAddress(int index);
uint32_t GetFunRunAddress(int index);
uint32_t GetBlockAddress(int BlockIndex);
uint32_t GetImageInfoAddress(int BlockIndex);
uint32_t GetTemporaryAddress(int index);

#endif /* SRC_APP_FLASH_MEM_MAP_H_ */
