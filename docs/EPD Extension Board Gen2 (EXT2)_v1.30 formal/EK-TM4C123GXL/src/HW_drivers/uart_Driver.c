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

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "ringbuf.h"
#include "UART_Driver.h"

#define Rev_QUEUE_SIZE         (512*4)
static uint8_t g_psRevQueueBuffer[Rev_QUEUE_SIZE];
static tRingBufObject g_sRevQueue;

void DisableUART()
{
	//
	// Enable the UART interrupt.
	//
	ROM_IntDisable(INT_UART0);
	ROM_UARTIntDisable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}
void EnableUART()
{
	//
	// Enable the UART interrupt.
	//
	ROM_IntEnable(INT_UART0);
	ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
	RingBufFlush(&g_sRevQueue);

}
void ConfigureUART(uint32_t Baudrate)
{
	//
	// Enable the GPIO Peripheral used by the UART.
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	//
	// Enable UART0
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	//
	// Configure GPIO Pins for UART mode.
	//
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);


	//
   // Configure the UART for 115,200, 8-N-1 operation.
   // This function uses SysCtlClockGet() to get the system clock
   // frequency.  This could be also be a variable or hard coded value
   // instead of a function call.
   //

	UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), Baudrate,
							(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
							 UART_CONFIG_PAR_NONE));

	ROM_UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX4_8,UART_FIFO_RX1_8);
	ROM_UARTFIFOEnable(UART0_BASE);
	RingBufInit(&g_sRevQueue, (uint8_t *)g_psRevQueueBuffer,Rev_QUEUE_SIZE );
    EnableUART();
}



//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void
UartSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {

        //
        // Write the next character to the UART.
        //
       while(!UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer));
       pui8Buffer++;
    }
    while(UARTBusy(UART0_BASE));
}
uint32_t Uart_RecvAvail(void)
{
    return RingBufUsed(&g_sRevQueue);
}
bool UartRecv(uint8_t * RecvBuf,uint32_t len)
{
	uint8_t flag=false;

	if(len>0)
	{
		if(len<=RingBufUsed(&g_sRevQueue))
		{
			RingBufRead(&g_sRevQueue,RecvBuf, len);
			flag=true;
		}
	}
     return flag;

}
void ClearUartBuffer(void)
{
	RingBufFlush(&g_sRevQueue);
}
void Uart_PeekRecvDatas(uint8_t *datas,uint8_t len)
{
      RingBufPeek(&g_sRevQueue,datas,len);
}
//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
UARTIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while((ROM_UARTCharsAvail(UART0_BASE))>0)
    {
        ui32Status=ROM_UARTCharGetNonBlocking(UART0_BASE);
        RingBufWriteOne(&g_sRevQueue, (uint8_t)ui32Status);
    }
}


