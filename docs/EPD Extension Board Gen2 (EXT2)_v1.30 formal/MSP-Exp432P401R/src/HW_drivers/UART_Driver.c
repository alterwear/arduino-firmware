#include <ringbuf.h>
#include <UART_Driver.h>
#include "driverlib.h"

static tRingBufObject 				recvbufObj;
static uint8_t 						Recv_Buffer[Receive_Buf_Len];
static tRingBufObject           	transmitbufObj;
static  uint8_t  					transmit_Buffer[Transmit_Buf_Len];

const eUSCI_UART_Config uartConfig =
{
	EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
	13,                                     // BRDIV = 26
	0,                                       // UCxBRF = 0
	37,                                       // UCxBRS = 111
	EUSCI_A_UART_NO_PARITY,                  // No Parity
	EUSCI_A_UART_LSB_FIRST,                  // MSB First
	EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
	EUSCI_A_UART_MODE,                       // UART mode
	EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION    // Oversampling
};
/* EUSCI A0 UART ISR */
void euscia0_isr(void)
{
	uint8_t RXData;
	uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
	MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);

	if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)
	{
		RXData = ROM_UART_receiveData(EUSCI_A0_BASE);
		RingBufWriteOne(&recvbufObj, RXData);
	}

}

void ConfigureUART(uint32_t Baudrate)
{
	/* Selecting P1.2 and P1.3 in UART mode  */
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
	        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

	/* Configuring UART Module */
	MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

	/* Enable UART module */
	MAP_UART_enableModule(EUSCI_A0_BASE);

	/* Enabling interrupts */
	MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
	MAP_Interrupt_registerInterrupt(INT_EUSCIA0,euscia0_isr);
	MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
	MAP_Interrupt_enableSleepOnIsrExit();

	MAP_Interrupt_enableMaster();
	RingBufInit(&recvbufObj,(uint8_t *)&Recv_Buffer,sizeof(Recv_Buffer));
	RingBufInit(&transmitbufObj,(uint8_t *)&transmit_Buffer,sizeof(transmit_Buffer));
}

void UartSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
	while(ui32Count--)
	{
		ROM_UART_transmitData(EUSCI_A0_BASE,*pui8Buffer++);
	}

}

void Uart_PeekRecvDatas(uint8_t *datas,uint8_t len)
{
	RingBufPeek(&recvbufObj,datas,len);
}

uint32_t Uart_RecvAvail(void)
{
	return RingBufUsed(&recvbufObj);
}

bool UartRecv(uint8_t * RecvBuf,uint32_t len)
{
	uint8_t flag=false;
	if(len>0)
	{
		if(len<=RingBufUsed(&recvbufObj))
		{
			RingBufRead(&recvbufObj,RecvBuf, len);
			flag=true;
		}
	}
	return flag;

}

void ClearUartBuffer(void)
{
	RingBufFlush(&recvbufObj);
	RingBufFlush(&transmitbufObj);
}


