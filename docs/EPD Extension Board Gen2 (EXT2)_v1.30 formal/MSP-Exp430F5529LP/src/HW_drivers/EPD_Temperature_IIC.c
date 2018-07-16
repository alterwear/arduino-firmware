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

#include "EPD_Temperature_IIC.h"

IIC_IO_Assign_t IIC_IO;

uint8_t inline getSDA()
{
	return input_get(IIC_IO.SDA_Port,IIC_IO.SDA_Pin);
}
void inline  TS_SDA_High()
{
	set_gpio_high(IIC_IO.SDA_Port,IIC_IO.SDA_Pin);
}
void inline  TS_SDA_Low()
{
	set_gpio_low(IIC_IO.SDA_Port,IIC_IO.SDA_Pin);
}
void inline  TS_SCL_High()
{
	set_gpio_high(IIC_IO.SCL_Port,IIC_IO.SCL_Pin);
}
void inline  TS_SCL_Low()
{
	set_gpio_low(IIC_IO.SCL_Port,IIC_IO.SCL_Pin);
}
void i2c_delay(void)
{
	int i=1000;
	while(i--);
}
void SDA_High(void)
{
	TS_SDA_High();
	config_gpio_dir_i(IIC_IO.SDA_Port,IIC_IO.SDA_Pin);
	SDA_PullUP();
	i2c_delay();
}
void SDA_Low(void)
{
	config_gpio_dir_o(IIC_IO.SDA_Port,IIC_IO.SDA_Pin);
	SDA_PullUP();
	TS_SDA_Low();
	i2c_delay();
}
void SCL_High(void)
{
	TS_SCL_High();
	i2c_delay();
}
void SCL_Low(void)
{
	TS_SCL_Low();
	i2c_delay();
}
void i2c_Init(void)
{

	config_gpio_dir_i(IIC_IO.SDA_Port,IIC_IO.SDA_Pin);
	SDA_PullUP();

	config_gpio_dir_o(IIC_IO.SCL_Port,IIC_IO.SCL_Pin);
	SCL_PullUP();
}

uint8_t i2c_in_BYTE(void)
{
	uint8_t i_BYTE=0, n;
	SDA_High();
	for (n=0; n<8; n++)
	{
		SCL_High();
		i_BYTE<<=1;
		if(getSDA()) i_BYTE |=1;
		SCL_Low();
	}
	return i_BYTE;
}
void i2c_out_BYTE(uint8_t o_BYTE)
{
	uint8_t n;
	for(n=0; n<8; n++)
	{
		if(o_BYTE&0x80) SDA_High();
		else SDA_Low();
		SCL_High();
		SCL_Low();
		o_BYTE = o_BYTE << 1;
	}
}
uint8_t i2c_ReadAck(void)
{
	uint8_t ack=0;
	SDA_High();
	SCL_High();
	ack =~getSDA();
	SCL_Low();
	return ack;
}
void i2c_WriteAck(void)
{
	SDA_Low();
	SCL_High();
	SCL_Low();
}
void i2c_start(void)
{
	SDA_High();
	SCL_High();
	SDA_Low();
	SCL_Low();
}
void i2c_stop(void)
{
	SCL_Low();
	SDA_Low();
	SCL_High();
	SDA_High();
}

bool getTemperatureOne(int16_t *temp)
{
	bool flag=false;

	i2c_Init();
	i2c_start();
	i2c_out_BYTE(IIC_Slave_address);
	flag=i2c_ReadAck();
	*temp=i2c_in_BYTE();
	i2c_WriteAck();
	i2c_in_BYTE();
	i2c_stop();
	if(!flag)*temp=0xFF;
	return flag;
}

bool DetectionTemperature(int16_t *temper)
{
	uint8_t i=4;
	bool flag=false;
	getTemperatureOne(temper);
	do
	{
		delay_ms(1);
		if(getTemperatureOne(temper))
		{
			flag=true;
			break;
		}
	}
	while(i--);
	if(*temper==255)flag=false;
	return flag;
}

int16_t getTemperature(void)
{
	bool flag=false;
	int16_t temper;
	IIC_IO.SDA_Port=TS_SDA0_PORT;
	IIC_IO.SDA_Pin=TS_SDA0_PIN;
	IIC_IO.SCL_Port=TS_SCL0_PORT;
	IIC_IO.SCL_Pin=TS_SCL0_PIN;
	flag=DetectionTemperature(&temper);

	if(!flag)
	{
		IIC_IO.SDA_Port=TS_SDA1_PORT;
		IIC_IO.SDA_Pin=TS_SDA1_PIN;
		IIC_IO.SCL_Port=TS_SCL1_PORT;
		IIC_IO.SCL_Pin=TS_SCL1_PIN;
		flag=DetectionTemperature(&temper);
	}
	else flag=true;
	if(!flag)temper=25;
	return temper;
}

