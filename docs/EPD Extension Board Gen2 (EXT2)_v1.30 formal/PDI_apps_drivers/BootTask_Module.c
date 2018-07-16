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

#include "BootTask_Module.h"

extern void read_flash_handle(long flash_address, uint8_t *target_buffer, uint8_t byte_length);
static Boot_Info_t *boot_Info;
static uint8_t Boot_Info_Index;
RunImage_Info_t *RunImage_Info, *perv_RunImage_Info;
static int8_t RunImage_Info_Index;
static uint8_t RunImageCount;
static uint32_t addr;
static bool IsStopBootRun = false, IsOneRun = false;

bool LoadBootInfo()
{
	bool flag = true;
	check_flash_spi();
	do
	{
		addr = GetFunBootAddress(Boot_Info_Index++);
		read_flash(addr, (uint8_t *)&boot_Info->Mark, (sizeof(Boot_Info_t) - sizeof(Flash_Parameter_Info_t)));
		if(Boot_Info_Index == BootBlockMax || boot_Info->Mark == M_IsEmpty)
		{
			flag = false;
			break;
		}
	}
	while(boot_Info->Mark != M_IsExist);

	return flag;
}
void GetRunImageIndex(void)
{
	RunImageCount = 0;
	check_flash_spi();
	do
	{
		addr = GetFunRunAddress(RunImageCount);
		read_flash(addr, (uint8_t *)&RunImage_Info->Mark, (sizeof(RunImage_Info_t) - sizeof(Flash_Parameter_Info_t)));
		if(RunImage_Info_Index == RunBlockMax  || RunImage_Info->Mark == M_IsEmpty)
		{
			break;
		}
		RunImageCount++;
	}
	while(RunImage_Info->Mark == M_IsExist);

}
bool LoadRunInfo(void)
{
	bool flag = true;
	check_flash_spi();
	addr = GetFunRunAddress(RunImage_Info_Index++);
	read_flash(addr, (uint8_t *)&RunImage_Info->Mark, (sizeof(RunImage_Info_t) - sizeof(Flash_Parameter_Info_t)));
	if(RunImage_Info_Index >= RunImageCount)
	{
		RunImage_Info_Index = 0;
		if(IsOneRun)
		{
			IsOneRun = false;
			CancelBootTask_Module();
		}

	}
	return flag;
}
void DisplayImage()
{

	if(perv_RunImage_Info->Mark != M_IsExist)
	{
		memcpy(perv_RunImage_Info, RunImage_Info, sizeof(RunImage_Info_t));
	}

	switch(RunImage_Info->DisplayMode)
	{
		case FDM_GU_PWDCtrl:
			EPD_display_GU_from_flash(perv_RunImage_Info->Address, RunImage_Info->Address, read_flash_handle, RunImage_Info->RunOTP, true);
			break;
		case FDM_GU_NonPWDCtrl:
			EPD_display_GU_from_flash(perv_RunImage_Info->Address, RunImage_Info->Address, read_flash_handle, RunImage_Info->RunOTP, false);
			break;
		case FDM_PU_PWDCtrl:
			EPD_display_PU_from_flash(perv_RunImage_Info->Address, RunImage_Info->Address, read_flash_handle, true, RunImage_Info->Time);
			RunImage_Info->Time = 0;
			break;
		case FDM_PU_NonPWDCtrl:
			EPD_display_PU_from_flash(perv_RunImage_Info->Address, RunImage_Info->Address, read_flash_handle, false, RunImage_Info->Time);
			RunImage_Info->Time = 0;
			break;
	}

	memcpy(perv_RunImage_Info, RunImage_Info, sizeof(RunImage_Info_t));
}

void Previewer(Boot_Info_t *bootInfo)
{
	boot_Info = malloc(sizeof(Boot_Info_t));
	memcpy(boot_Info, bootInfo, sizeof(Boot_Info_t));
	IsStopBootRun = false;
	IsOneRun = true;
	GetRunImageIndex();
	Rtos_Event_Handle(BTM_TASK_ID, BTM_RunOne);
}
void CancelBootTask_Module()
{
	IsStopBootRun = true;
}
static void BootTask_Event_Handle(uint32_t eventid)
{

	switch(eventid)
	{
		case BTM_RunOne:

			RunImage_Info = malloc(sizeof(RunImage_Info_t));
			perv_RunImage_Info = malloc(sizeof(RunImage_Info_t));
			RunImage_Info_Index = 0;
			Boot_Info_Index = 0;
			if(boot_Info != NULL)
			{
				Set_AssignEPD_Drive((Driver_Type_t)boot_Info->Driver_Type, (EPD_SIZE_t)boot_Info->EPD_Size, boot_Info->Temperature);
				Rtos_Event_Handle(BTM_TASK_ID, BTM_RunScript);
			}
			else Rtos_Event_Handle(BTM_TASK_ID, BTM_EndBoot);
			break;
		case BTM_Init:
			boot_Info = malloc(sizeof(Boot_Info_t));
			RunImage_Info = malloc(sizeof(RunImage_Info_t));
			perv_RunImage_Info = malloc(sizeof(RunImage_Info_t));

			Rtos_Event_Handle(BTM_TASK_ID, BTM_Load_BootInfo);
			RunImage_Info_Index = 0;
			Boot_Info_Index = 0;
			break;
		case BTM_Load_BootInfo:
			if(IsStopBootRun)
			{
				IsStopBootRun = false;
				Rtos_Event_Handle(BTM_TASK_ID, BTM_EndBoot);
				break;
			}
			if(LoadBootInfo())
			{
				GetRunImageIndex();
				if(boot_Info->IsRun == ARM_INTERVAL || boot_Info->IsRun == ARM_BUTTON) //Load Boot Info Script
				{
					Set_AssignEPD_Drive((Driver_Type_t)boot_Info->Driver_Type, (EPD_SIZE_t)boot_Info->EPD_Size, boot_Info->Temperature);
					Rtos_Event_Handle(BTM_TASK_ID, BTM_RunScript);
				}
				else Rtos_Event_Handle(BTM_TASK_ID, BTM_EndBoot);
			}
			else Rtos_Event_Handle(BTM_TASK_ID, BTM_EndBoot);

			break;
		case BTM_WaitButtonToggle:
			if(!SW2_State())
			{
				Rtos_Event_Handle(BTM_TASK_ID, BTM_RunScript);
				Disable_SW_Pin();
			}
			else if(!SW1_State())
			{
				RunImage_Info_Index -= 2;
				if(RunImage_Info_Index < 0) RunImage_Info_Index = (RunImageCount - 1);
				Rtos_Event_Handle(BTM_TASK_ID, BTM_RunScript);
				Disable_SW_Pin();
			}
			else Rtos_Event_Handle_Timer(BTM_TASK_ID, BTM_WaitButtonToggle, 30);
			if(IsStopBootRun)
			{
				IsStopBootRun = false;
				Rtos_Event_Handle_Cancel(BTM_TASK_ID, BTM_WaitButtonToggle);
				Rtos_Event_Handle(BTM_TASK_ID, BTM_EndBoot);
				break;
			}
			break;
		case BTM_RunScript:
			if(IsStopBootRun)
			{
				IsStopBootRun = false;
				Rtos_Event_Handle(BTM_TASK_ID, BTM_EndBoot);
				break;
			}
			if(boot_Info->Mark != M_IsExist) Rtos_Event_Handle(BTM_TASK_ID, BTM_EndBoot);
			if(LoadRunInfo())
			{
				Rtos_Event_Handle(BTM_TASK_ID, BTM_DisplayImage);
			}
			else
			{
				Rtos_Event_Handle(BTM_TASK_ID, BTM_Load_BootInfo);
			}
			break;
		case BTM_DisplayImage:

			DisplayImage();
			if(boot_Info->IsRun == ARM_BUTTON)
			{
				Enable_SW_Pin();
				Rtos_Event_Handle(BTM_TASK_ID, BTM_WaitButtonToggle); //Auto Button Mode
			}
			else if(RunImage_Info->Time == 0) Rtos_Event_Handle(BTM_TASK_ID, BTM_RunScript);
			else Rtos_Event_Handle_Timer(BTM_TASK_ID, BTM_RunScript, (RunImage_Info->Time * 100));
			break;
		case BTM_EndBoot:
			free(boot_Info);
			free(RunImage_Info);
			free(perv_RunImage_Info);
			break;

	}
}
void BootTask_Module_init(void)
{
	RunImage_Info_Index = 0;
	Boot_Info_Index = 0;
	IsStopBootRun = false;
	Rtos_Addtask(BootTask_Event_Handle, BTM_TASK_ID);
	Rtos_Event_Handle_Timer(BTM_TASK_ID, BTM_Init, 2000);
}
