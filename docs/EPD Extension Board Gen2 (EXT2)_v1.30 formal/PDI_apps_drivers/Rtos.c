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

#include <Rtos.h>
TASK_handler task_handle[TASK_MAX];
task_event_t workTask[TASK_MAX][EVENT_MAX];
extern uint32_t getnowtime(void);
void Rtos_init(void)
{
	uint8_t i,j;
	for(i=0; i<TASK_MAX; i++)
	{
		for(j=0; j<EVENT_MAX; j++)
		{
			workTask[i][j].EventID=0;
			workTask[i][j].WaitTime=0;
			workTask[i][j].State=E_NONE;
		}
		task_handle[i]=NULL;
	}
}

void Rtos_Addtask(TASK_handler task,uint8_t task_id)
{
	task_handle[task_id]=task;
}

uint8_t Rtos_Event_Handle_Timer(uint8_t taskID,uint32_t eventID,uint32_t time)
{
	uint8_t i;
	uint8_t result=false;
	for(i=0; i<EVENT_MAX; i++)
	{
		if(workTask[taskID][i].EventID==eventID)
		{
			//workTask[taskID][i].EventID=eventID;
			workTask[taskID][i].WaitTime=(time+getnowtime());
			workTask[taskID][i].State=E_TIME;
			result=true;
			break;
		}
		else if(workTask[taskID][i].State==E_NONE)
		{
			workTask[taskID][i].EventID=eventID;
			workTask[taskID][i].WaitTime=(time+getnowtime());
			workTask[taskID][i].State=E_TIME;
			result=true;
			break;
		}

	}
	return result;
}
uint8_t Rtos_Event_Handle(uint8_t taskID,uint32_t eventID)
{
	uint8_t i;
	uint8_t result=false;
	for(i=0; i<EVENT_MAX; i++)
	{
		if(workTask[taskID][i].EventID==eventID)
		{
			workTask[taskID][i].State=E_NOW;
			result=true;
			break;
		}
		else if(workTask[taskID][i].State==E_NONE)
		{
			workTask[taskID][i].EventID=eventID;
			workTask[taskID][i].State=E_NOW;
			result=true;
			break;
		}
	}
	return result;
}

uint8_t Rtos_Event_Handle_Cancel(uint8_t taskID,uint32_t eventID)
{
	uint8_t i;
	uint8_t result=false;
	for(i=0; i<EVENT_MAX; i++)
	{
		if(workTask[taskID][i].EventID==eventID)
		{
			workTask[taskID][i].State=E_NONE;
			result=true;
			break;
		}
	}
	return result;
}
void Rtos_Event_Handle_ClearAll(uint8_t taskID)
{
	uint8_t i;
	for(i=0; i<EVENT_MAX; i++)
	{
		workTask[taskID][i].State=E_NONE;
	}
}

void Rtos_Task(void)
{
	uint8_t i,j;
	uint16_t eventid;
	uint32_t Rtos_time=getnowtime();
	for(i=0; i<TASK_MAX; i++)
	{
		if(task_handle[i]!=NULL)
		{
			eventid=0;
			for(j=0; j<EVENT_MAX; j++)
			{
				switch(workTask[i][j].State)
				{
					case E_NONE:

						break;
					case E_NOW:
						eventid=workTask[i][j].EventID;
						workTask[i][j].State=E_NONE;
						task_handle[i](eventid);
						break;
					case E_TIME:
						if(Rtos_time>=workTask[i][j].WaitTime)
						{
							eventid=workTask[i][j].EventID;
							workTask[i][j].State=E_NONE;
							task_handle[i](eventid);
						}
						break;
				}
				//if(eventid>0) task_handle[i](eventid);
			}

		}

	}
}
