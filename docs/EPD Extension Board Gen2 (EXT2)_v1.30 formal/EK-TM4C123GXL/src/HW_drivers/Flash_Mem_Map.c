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

#include <HW_drivers/Flash_Mem_Map.h>
#include "conf_EPD.h"
#include "Data_Module.h"
uint32_t GetFunBootAddress(int index)
{
	if(index>BootBlockMax) index=BootBlockMax-1;
	return (uint32_t)(FunBootAddress + (uint32_t)((sizeof(Boot_Info_t)-sizeof(Flash_Parameter_Info_t))*index));
}
uint32_t GetFunRunAddress(int index)
{
	if(index>RunBlockMax) index=RunBlockMax-1;
	return (uint32_t)(FunRunAddress + (uint32_t)((sizeof(RunImage_Info_t)-sizeof(Flash_Parameter_Info_t))*index));
}
uint32_t GetBlockAddress(int BlockIndex)
{
	  if (BlockIndex > BlockMaxSize) BlockIndex = BlockMaxSize;
	  return (uint32_t)(BlockSize * BlockIndex);
}
uint32_t GetImageInfoAddress(int BlockIndex)
{
	if (BlockIndex > BlockMaxSize) BlockIndex = BlockMaxSize;
    return (uint32_t)((BlockSize * (BlockIndex + 1)) - ImageInfoSize);
}
uint32_t GetTemporaryAddress(int index)
{
	return  (uint32_t)(index * BlockSize);
}
