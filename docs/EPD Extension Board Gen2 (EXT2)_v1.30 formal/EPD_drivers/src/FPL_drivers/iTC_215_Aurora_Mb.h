/**
* Copyright (c) Pervasive Displays Inc. All rights reserved.
*
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

#ifndef SRC_FPL_DRIVERS_ITC_215_AURORA_MB_H_
#define SRC_FPL_DRIVERS_ITC_215_AURORA_MB_H_

void iTC_215Mb_IO_Config(void);
void iTC_215Mb_power_on (uint8_t EPD_type_index,int8_t temperature);
uint8_t iTC_215Mb_initialize_driver (OperationMode_t operationmode);
uint8_t iTC_215Mb_Display_from_Ram (uint8_t *First_Frame_ptr ,uint8_t *Secon_Frame_ptr);
uint8_t iTC_215Mb_Display_from_flash ( long First_Frame_flash_address,long Secon_Frame_flash_address,EPD_read_memory_handler On_EPD_read_flash);
uint8_t iTC_215Mb_power_off (void);
void iTC_215Mb_Display_PU_from_Ram(uint8_t *First_Frame_ptr , uint8_t *Secon_Frame_ptr,uint16_t PU_Time);
void iTC_215Mb_Display_PU_From_Flash(long First_Frame_address, long Secon_Frame_address,EPD_read_memory_handler On_EPD_read_flash,uint16_t PU_Time);

#endif /* SRC_FPL_DRIVERS_ITC_215_AURORA_MB_H_ */
