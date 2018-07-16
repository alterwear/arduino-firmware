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

#include <Data_Module.h>
#include <Flash_Mem_Map.h>
#ifndef SRC_PDI_APPS_DRIVERS_BOOTTASK_MODULE_H_
#define SRC_PDI_APPS_DRIVERS_BOOTTASK_MODULE_H_

enum BTM_EVT
{
	BTM_EVT_NONE,
	BTM_Init,
	BTM_Load_BootInfo,
	BTM_RunScript,
	BTM_DisplayImage,
	BTM_EndBoot,
	BTM_RunOne,
	BTM_WaitButtonToggle
};

#define BTM_TASK_ID         			2

void BootTask_Module_init(void);
void Previewer(Boot_Info_t *bootInfo);
void CancelBootTask_Module();

#endif /* SRC_PDI_APPS_DRIVERS_BOOTTASK_MODULE_H_ */
