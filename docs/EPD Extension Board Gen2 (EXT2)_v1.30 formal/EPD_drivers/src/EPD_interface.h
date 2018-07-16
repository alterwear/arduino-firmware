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

#ifndef EPD_INTERFACE_H_
#define EPD_INTERFACE_H_



#define USE_Temperature_Sensor				-100
int8_t Set_AssignEPD_Drive(Driver_Type_t EPD_Driver,EPD_SIZE_t EPD_size,int8_t Seltemperature);
void EPD_display_init(void);
uint8_t EPD_Power_off_Ex();
uint8_t EPD_display_GU_from_pointer(uint8_t *First_Frame_ptr ,uint8_t *Secon_Frame_ptr,OperationMode_t operationmode,bool IsCtrlPWOff);
uint8_t EPD_display_GU_from_flash(long First_Frame_address,long Secon_Frame_address,EPD_read_memory_handler On_EPD_read_flash,OperationMode_t operationmode,bool IsCtrlPWOff);
uint8_t EPD_display_PU_from_pointer(uint8_t *First_Frame_ptr ,	uint8_t *Secon_Frame_ptr,bool IsCtrlPWOff,uint16_t PU_Time);
uint8_t  EPD_display_PU_from_flash(long First_Frame_address, long Secon_Frame_address,EPD_read_memory_handler On_EPD_read_flash,bool IsCtrlPWOff,uint16_t PU_Time);
uint8_t EPD_display_FT_from_pointer(uint8_t *First_Frame_ptr ,uint8_t *Secon_Frame_ptr,bool IsCtrlPWOff);
void EPD_display_iTC_SetColormode(ColorMode_t colormode);

#endif /* EPD_INTERFACE_H_ */
