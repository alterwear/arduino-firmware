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

#ifndef RTOS_H_
#define RTOS_H_
#include "conf_EPD.h"
#define TASK_MAX    4
#define EVENT_MAX   32
typedef enum
{
	E_NONE,
	E_NOW,
	E_TIME
} EVEVT_State;
typedef struct
{
	uint32_t EventID;
	uint32_t WaitTime;
	EVEVT_State  State;
} task_event_t;

typedef void (*TASK_handler)(uint32_t EventID);

void Rtos_init(void);
void Rtos_Addtask(TASK_handler task,uint8_t task_id);
uint8_t Rtos_Event_Handle_Timer(uint8_t taskID,uint32_t eventID,uint32_t time);
uint8_t Rtos_Event_Handle(uint8_t taskID,uint32_t eventID);
uint8_t Rtos_Event_Handle_Cancel(uint8_t taskID,uint32_t eventID);
void Rtos_Event_Handle_ClearAll(uint8_t taskID);
void Rtos_Task(void);
extern task_event_t workTask[TASK_MAX][EVENT_MAX];
#endif
