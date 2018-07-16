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
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#ifndef BOARD_UART_DRIVER_H_
#define BOARD_UART_DRIVER_H_



void ConfigureUART(uint32_t Baudrate);
void UartSend(const uint8_t *pui8Buffer, uint32_t ui32Count);
uint32_t Uart_RecvAvail(void);
bool UartRecv(uint8_t * RecvBuf,uint32_t len);
void ClearUartBuffer(void);
void Uart_PeekRecvDatas(uint8_t *datas,uint8_t len);
void DisableUART();
void EnableUART();
#endif /* BOARD_UART_DRIVER_H_ */
