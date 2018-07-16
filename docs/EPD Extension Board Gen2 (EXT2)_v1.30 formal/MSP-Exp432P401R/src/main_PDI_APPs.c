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


#include "conf_EPD.h"
#include "Data_Module.h"
#include "BootTask_Module.h"
void main(void)
{
	system_init();
	EPD_display_init();
	Systick_Configuration();
	Rtos_init();
	Data_Module_init();
	BootTask_Module_init();
	while(1)
	{
		Rtos_Task();
	}
}
