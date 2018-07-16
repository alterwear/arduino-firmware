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
#include "EPD_Temperature_IIC.h"
#include "EPD_drivers.h"
#include "COG_Drivers_List.h"
static volatile EPD_SIZE_t use_epd_size;
static Driver_Handle_t *EPD_Driver_Handle;
static int8_t temperature;
static bool PWD_State;
static OperationMode_t Cur_Mode;
void EPD_display_init(void)
{
	EPD_display_hardware_init();
	PWD_State=false;
	Cur_Mode=GU_Mode;
}
int8_t Set_AssignEPD_Drive(Driver_Type_t EPD_Driver,EPD_SIZE_t EPD_size,int8_t Seltemperature)
{
	uint8_t i,j;
	bool flag=false;
	uint8_t cnt=ArrayLength(Driver_Handle_list);
	for(i=0;i<cnt;i++)
	{
		if(Driver_Handle_list[i].Driver_ID==EPD_Driver)
		{
			EPD_Driver_Handle=(Driver_Handle_t *)&Driver_Handle_list[i];
			break;
		}
	}
    if(i>=cnt)
    {
    	EPD_Driver_Handle=NULL;
    }
    else
    {
    	EPD_Driver_Handle->EPD_IOConfig();
    	j=0;
    	while(EPD_Driver_Handle->Support_Size[j]!=EPD_Empty)
    	{
    		if(EPD_Driver_Handle->Support_Size[j]==EPD_size)
    		{
    			if(Seltemperature<=(-100))
    			{
    				temperature=getTemperature();
    			}
    			else temperature=Seltemperature;

    			flag=true;
    			use_epd_size=EPD_size;
    			break;
    		}
    		j++;
    	}
    }
    if(!flag)EPD_Driver_Handle=NULL;
	return temperature;
}

uint8_t EPD_Power_off_Ex()
{
	 uint8_t result=RES_OK;
	/* Power off COG Driver */
	if(EPD_Driver_Handle!=NULL)
	{
		if(PWD_State)
		{
			result=EPD_Driver_Handle->EPD_power_off();
			PWD_State=false;
		}
	}
	Cur_Mode=GU_Mode;
	return result;
}
uint8_t  EPD_display_PU_from_flash(long First_Frame_address, long Secon_Frame_address,EPD_read_memory_handler On_EPD_read_flash,bool IsCtrlPWOff,uint16_t PU_Time)
{
	uint8_t result=0;
	if(EPD_Driver_Handle==NULL) return  ERROR_NoSuport;
	if(EPD_Driver_Handle->EPD_Display_PU_From_Flash==NULL) return  ERROR_NoSuport;
	if(!PWD_State)
	{
		/* Power on COG Driver */
		EPD_Driver_Handle->EPD_power_on(use_epd_size,temperature);

		/* Initialize COG Driver */
		result=EPD_Driver_Handle->EPD_initialize_driver(PU_Mode);
		if((result & RES_OK)!=RES_OK)
		{
			PWD_State=false;
			 return result;
		}
		else PWD_State=true;
	}
	else if(Cur_Mode!=PU_Mode)
	{
		Cur_Mode=PU_Mode;
		/* FAST Initialize COG Driver */
		result=EPD_Driver_Handle->EPD_initialize_driver(PU_Mode);
		if((result & RES_OK)!=RES_OK) return result;
	}
	/* Display image data on EPD from image array */
	EPD_Driver_Handle->EPD_Display_PU_From_Flash(First_Frame_address,Secon_Frame_address,On_EPD_read_flash,PU_Time);

	if(IsCtrlPWOff)
	{
		EPD_Power_off_Ex();
	}
	 return result;
}
uint8_t EPD_display_PU_from_pointer(uint8_t *First_Frame_ptr ,
	uint8_t *Secon_Frame_ptr,bool IsCtrlPWOff,uint16_t PU_Time)
{
		uint8_t result=0;
		if(EPD_Driver_Handle==NULL) return  ERROR_NoSuport;
		if(EPD_Driver_Handle->EPD_Display_PU_from_Ram==NULL) return  ERROR_NoSuport;
		if(!PWD_State)
		{
			/* Power on COG Driver */
			EPD_Driver_Handle->EPD_power_on(use_epd_size,temperature);

			/* Initialize COG Driver */
			result=EPD_Driver_Handle->EPD_initialize_driver(PU_Mode);
			if((result & RES_OK)!=RES_OK)
			{
				PWD_State=false;
				 return result;
			}
			else PWD_State=true;

			PWD_State=true;
		}
		else if(Cur_Mode!=PU_Mode)
		{
			Cur_Mode=PU_Mode;
			/* FAST Initialize COG Driver */
			result=EPD_Driver_Handle->EPD_initialize_driver(PU_Mode);
			if((result & RES_OK)!=RES_OK) return result;
		}
		/* Display image data on EPD from image array */
        EPD_Driver_Handle->EPD_Display_PU_from_Ram(First_Frame_ptr ,Secon_Frame_ptr,PU_Time);

        if(IsCtrlPWOff)
		{
        	EPD_Power_off_Ex();
		}
        return result;
}
uint8_t EPD_display_FT_from_pointer(uint8_t *First_Frame_ptr ,
	uint8_t *Secon_Frame_ptr,bool IsCtrlPWOff)
{
		uint8_t result=0;
		if(EPD_Driver_Handle==NULL) return  ERROR_NoSuport;
		if(EPD_Driver_Handle->EPD_Display_PU_from_Ram==NULL) return  ERROR_NoSuport;
		if(!PWD_State)
		{
			/* Power on COG Driver */
			EPD_Driver_Handle->EPD_power_on(use_epd_size,temperature);

			/* Initialize COG Driver */
			result=EPD_Driver_Handle->EPD_initialize_driver(Fast_Mode);
			if((result & RES_OK)!=RES_OK)
			{
				PWD_State=false;
				 return result;
			}
			else PWD_State=true;

			PWD_State=true;
		}
		else if(Cur_Mode!=Fast_Mode)
		{
			Cur_Mode=Fast_Mode;
			/* FAST Initialize COG Driver */
			result=EPD_Driver_Handle->EPD_initialize_driver(Fast_Mode);
			if((result & RES_OK)!=RES_OK) return result;
		}
		/* Display image data on EPD from image array */
        EPD_Driver_Handle->EPD_Display_PU_from_Ram(First_Frame_ptr ,Secon_Frame_ptr,0);

        if(IsCtrlPWOff)
		{
        	EPD_Power_off_Ex();
		}
        return result;
}

uint8_t EPD_display_GU_from_pointer(uint8_t *First_Frame_ptr ,
	uint8_t *Secon_Frame_ptr,
	OperationMode_t operationmode,bool IsCtrlPWOff)
{
		uint8_t result=0;
		if(EPD_Driver_Handle==NULL)
		 {
			 return ERROR_NoSuport;
		 }
		if(!PWD_State)
		{
			/* Power on COG Driver */
			EPD_Driver_Handle->EPD_power_on(use_epd_size,temperature);

			/* Initialize COG Driver */
			result=EPD_Driver_Handle->EPD_initialize_driver(operationmode);
			if((result & RES_OK)!=RES_OK)
			{
				PWD_State=false;
				 return result;
			}
			else PWD_State=true;
		}
		else if(Cur_Mode!=operationmode)
		{
			Cur_Mode=operationmode;
			/* FAST Initialize COG Driver */
			result=EPD_Driver_Handle->EPD_initialize_driver(operationmode);
			if((result & RES_OK)!=RES_OK) return result;
		}

		/* Display image data on EPD from image array */
        EPD_Driver_Handle->EPD_Display_from_Ram(First_Frame_ptr ,Secon_Frame_ptr);
        if(IsCtrlPWOff)
		{
        	result |=EPD_Power_off_Ex();
		}
        return result;
}

uint8_t EPD_display_GU_from_flash(long First_Frame_address,
	long Secon_Frame_address,EPD_read_memory_handler On_EPD_read_flash,
	OperationMode_t operationmode,bool IsCtrlPWOff)
{
		uint8_t result=0;
		if(EPD_Driver_Handle==NULL)
		 {
			 return ERROR_NoSuport;
		 }
		if(!PWD_State)
		{
			/* Power on COG Driver */
			EPD_Driver_Handle->EPD_power_on(use_epd_size,temperature);

			/* Initialize COG Driver */
			result=EPD_Driver_Handle->EPD_initialize_driver(operationmode);
			if((result & RES_OK)!=RES_OK)
			{
				 PWD_State=false;
				 return result;
			}
			else PWD_State=true;
		}
		else if(Cur_Mode!=operationmode)
		{
			Cur_Mode=operationmode;
			/* FAST Initialize COG Driver */
			result=EPD_Driver_Handle->EPD_initialize_driver(operationmode);
			if((result & RES_OK)!=RES_OK) return result;
		}
		/* Display image data on EPD from image array */
		result=EPD_Driver_Handle->EPD_Display_from_flash(First_Frame_address,Secon_Frame_address,On_EPD_read_flash);
        if(IsCtrlPWOff)
    	{
        	result |=EPD_Power_off_Ex();
    	}
        return result;
}
void EPD_display_iTC_SetColormode(ColorMode_t colormode)
{
     if(EPD_Driver_Handle->SetColormode !=NULL)  EPD_Driver_Handle->SetColormode(colormode);
}


