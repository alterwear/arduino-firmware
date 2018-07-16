/*
 * usb_Driver.h
 *
 *  Created on: 2015¦~9¤ë3¤é
 *      Author: 7000005
 */

#ifndef USB_DRIVER_H_
#define USB_DRIVER_H_


#define USB_BIT_RATE      500000//(115200*2)
void usb_init(void);
void usb_clear_buffer(void);
int usb_DataAvailable();
bool usb_Recv(uint8_t *RecvBuf,uint32_t len);
void usb_Send(const uint8_t *pui8Buffer, uint32_t ui32Count);
uint32_t usb_Read(uint8_t *pui8Data, uint32_t ui32Length);
uint32_t usb_Write(uint8_t *pui8Data, uint32_t ui32Length);
#endif /* USB_DRIVER_H_ */
