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
**/
#ifndef SRC_FPL_DRIVERS_ITC_287_AURORA_MB_H_
#define SRC_FPL_DRIVERS_ITC_287_AURORA_MB_H_

void iTC_287Mb_IO_Config(void);
void iTC_287Mb_power_on (uint8_t EPD_type_index,int8_t temperature);
uint8_t iTC_287Mb_initialize_driver (OperationMode_t operationmode);
uint8_t iTC_287Mb_Display_from_Ram (uint8_t *previous_image_ptr,uint8_t *new_image_ptr);
uint8_t iTC_287Mb_Display_from_flash ( long previous_image_flash_address,long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash);
uint8_t iTC_287Mb_power_off (void);
void iTC_287Mb_Display_PU_from_Ram(uint8_t *previous_image_ptr, uint8_t *new_image_ptr,uint16_t PU_Time);
void iTC_287Mb_Display_PU_From_Flash(long previous_image_flash_address, long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash,uint16_t PU_Time);
#endif /* SRC_FPL_DRIVERS_ITC_287_AURORA_MB_H_ */
