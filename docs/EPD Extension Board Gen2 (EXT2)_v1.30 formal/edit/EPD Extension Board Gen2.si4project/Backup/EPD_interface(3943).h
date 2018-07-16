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

#ifndef EPD_INTERFACE_H_
#define EPD_INTERFACE_H_



#define USE_Temperature_Sensor				-100
int8_t Set_AssignEPD_Drive(Driver_Type_t EPD_Driver,EPD_SIZE_t EPD_size,int8_t Seltemperature);
void EPD_display_init(void);
uint8_t EPD_Power_off_Ex();
uint8_t EPD_display_GU_from_pointer(uint8_t *First_Frame_ptr ,uint8_t *Secon_Frame_ptr,OperationMode_t operationmode,bool IsCtrlPWOff);
uint8_t EPD_display_GU_from_flash(long First_Frame_address,long new_image_address,EPD_read_memory_handler On_EPD_read_flash,OperationMode_t operationmode,bool IsCtrlPWOff);
uint8_t EPD_display_PU_from_pointer(uint8_t *First_Frame_ptr ,	uint8_t *Secon_Frame_ptr,bool IsCtrlPWOff,uint16_t PU_Time);
uint8_t  EPD_display_PU_from_flash(long First_Frame_address, long new_image_address,EPD_read_memory_handler On_EPD_read_flash,bool IsCtrlPWOff,uint16_t PU_Time);
uint8_t EPD_display_FT_from_pointer(uint8_t *First_Frame_ptr ,uint8_t *Secon_Frame_ptr,bool IsCtrlPWOff);

#endif /* EPD_INTERFACE_H_ */
