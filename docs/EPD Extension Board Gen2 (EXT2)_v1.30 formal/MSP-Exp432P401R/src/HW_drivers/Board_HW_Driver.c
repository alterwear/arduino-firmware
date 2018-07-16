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


#include "Board_HW_Driver.h"
static  volatile uint32_t sys_Counter,EPD_Counter;

uint32_t getnowtime(void)
{
	return sys_Counter;
}
/**
 * \brief Start Timer
 * \note
 * desired value: 1mSec
 * actual value:  1.00mSec
 */
void Systick_Configuration(void)
{
	/* Configuring SysTick to trigger at 48000 (MCLK is 48MHz so this will
	 * make it toggle every ~1ms) */
	MAP_SysTick_enableModule();
	MAP_SysTick_setPeriod((CPU_F/1000));
	MAP_Interrupt_enableSleepOnIsrExit();
	MAP_SysTick_enableInterrupt();
	sys_Counter =0;

}
void systick_isr(void)
{
	sys_Counter++;
}
void systick_Stop(void)
{
	MAP_SysTick_disableInterrupt();
	MAP_SysTick_disableModule();
}
void systick_Start(void)
{
	Systick_Configuration();
}
/**
 * \brief Start Timer
 * \note
 * desired value: 1mSec
 * actual value:  1.000mSec
 */
void start_EPD_timer(void)
{
	EPD_Counter=sys_Counter;
}

/**
 * \brief Stop Timer
 */
void stop_EPD_timer(void)
{

}
/**
 * \brief Get current Timer after starting a new one
 */
uint32_t get_EPD_time_tick(void)
{
	return (sys_Counter-EPD_Counter);
}

/**
 * \brief Delay mini-seconds
 * \param ms The number of mini-seconds
 */
void EPD_delay_ms(unsigned int ms)
{
	start_EPD_timer();
	while(get_EPD_time_tick()<=ms)
	{

	}

}

void delay_btwn_CS_H_L(void)
{
	//delay > 80ns
}
/**
 * \brief PWM toggling.
 *
 * \param ms The interval of PWM toggling (mini seconds)
 */
void PWM_run(uint16_t ms)
{
	start_EPD_timer();
	do
	{
		//~156K Hz
		EPD_pwm_high();
		__delay_cycles(20);
		EPD_pwm_low();
		__delay_cycles(20);
	}
	while (get_EPD_time_tick() < ms);   //wait Delay Time

	stop_EPD_timer();

}
//******************************************************************
//* SPI  Configuration
//******************************************************************
bool spi_state=false;
/**
 * \brief Configure SPI
 */
/* SPI Master Configuration Parameter */
const eUSCI_SPI_MasterConfig spiMasterConfig =
{
	EUSCI_B_SPI_CLOCKSOURCE_SMCLK,              		 		// SMCLK Clock Source
	CPU_F,                                     			 		// SMCLK = 48Mhz
	COG_SPI_baudrate,                                    		// SPICLK = 12Mhz
	EUSCI_B_SPI_MSB_FIRST,                     			 		// MSB First
	EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
	EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, 					// High polarity
	EUSCI_B_SPI_3PIN                           					// 3Wire SPI Mode
};
/**
 * \brief Configure SPI
 */
void epd_spi_init(uint32_t spi_baudrate)
{
	/* Selecting P1.1 P1.2 and P1.3 in SPI mode */
	GPIO_setAsPeripheralModuleFunctionInputPin(SPICLK_PORT,
	        SPICLK_PIN | SPIMISO_PIN | SPIMOSI_PIN, GPIO_PRIMARY_MODULE_FUNCTION);

	/* Configuring SPI in 3wire master mode */
	spi_state=SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);

	/* Enable SPI module */
	if(spi_state)SPI_enableModule(EUSCI_B0_BASE);
}
/**
 * \brief Initialize SPI
 */
void EPD_spi_attach()
{
	if(spi_state) return;
	EPD_flash_cs_high();
	EPD_cs_high();
	epd_spi_init(COG_SPI_baudrate);
}
/**
 * \brief Disable SPI and change to GPIO
 */
void EPD_spi_detach(void)
{
	if(!spi_state) return;
	SPI_disableModule(EUSCI_B0_BASE);
	config_gpio_dir_o( SPICLK_PORT,SPICLK_PIN);
	config_gpio_dir_o( SPIMISO_PORT,SPIMISO_PIN);
	config_gpio_dir_o( SPIMOSI_PORT,SPIMOSI_PIN);
	SPIMISO_low();
	SPIMOSI_low();
	SPICLK_low();
	spi_state=false;
}
bool check_flash_spi(void)
{
	if(!spi_state) EPD_spi_attach();
	return spi_state;
}
/**
 * \brief SPI synchronous read
 */
uint8_t EPD_spi_read(unsigned char data)
{
	SPI_transmitData(EUSCI_B0_BASE, data);
	/* USCI_B0 TX buffer ready? */
	while (!(SPI_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT)));
	return SPI_receiveData(EUSCI_B0_BASE);
}

/**
 * \brief SPI synchronous write
 */
void EPD_spi_write(unsigned char data)
{
	EPD_spi_read(data);
}
void iTC_spi_sendReg(uint8_t register_index)
{
	EPD_cs_low();
	EPD_DC_low();
	EPD_spi_write(register_index);
	EPD_DC_high();
}
void iTC_spi_sendRegData(uint8_t register_data)
{
	EPD_spi_write(register_data);
}

void iTC_spi_send(uint8_t register_index,uint8_t *register_data,uint8_t len)
{
#if 0
	UartSend((const uint8_t *)&register_index,1);
	if(len>0)UartSend((const uint8_t *)register_data,len);
#endif
	EPD_cs_low();
	EPD_DC_low();
	EPD_spi_write(register_index);
	EPD_DC_high();
	while(len--)
	{
		EPD_spi_write(*register_data++);
	}

	EPD_cs_high();
}
void iTC_spi_send_array(Em_register_array_t *register_array,uint8_t len)
{
	uint8_t i;
	for(i=0; i<len; i++)
	{
		iTC_spi_send(register_array[i].register_index,register_array[i].register_data,register_array[i].len);
	}
}
/**
* \brief SPI command
*
* \param register_index The Register Index as SPI Data to COG
* \param register_data The Register Data for sending command data to COG
* \return the SPI read value
*/
uint8_t EPD_Gx_spi_r(uint8_t register_index, uint8_t register_data)
{
	uint8_t result;
	EPD_cs_low ();
	EPD_spi_write (0x70); // header of Register Index
	EPD_spi_write (register_index);
	EPD_cs_high ();
	delay_btwn_CS_H_L ();
	EPD_cs_low ();

	EPD_spi_write (0x73); // header of Register Data of read command
	result=EPD_spi_read (register_data);

	EPD_cs_high ();

	return result;
}
uint8_t EPD_Gx_spi_rid(void)
{
	uint8_t result;
	EPD_cs_low ();
	EPD_spi_write (0x71);
	result=EPD_spi_read (0x00);
	EPD_cs_high ();
	return result;
}

/**
* \brief SPI command if register data is larger than two bytes
*
* \param register_index The Register Index as SPI command to COG
* \param register_data The Register Data for sending command data to COG
* \param length The number of bytes of Register Data which depends on which
* Register Index is selected.
*/
void EPD_Gx_spi_send (unsigned char register_index, unsigned char *register_data,
                      unsigned length)
{
	EPD_cs_low ();
	EPD_spi_write (0x70); // header of Register Index
	EPD_spi_write (register_index);
	EPD_cs_high ();
	delay_btwn_CS_H_L ();
	EPD_cs_low ();

	EPD_spi_write (0x72); // header of Register Data of write command
	while(length--)
	{
		EPD_spi_write (*register_data++);
	}
	EPD_cs_high ();
}

/**
* \brief SPI command
*
* \param register_index The Register Index as SPI command to COG
* \param register_data The Register Data for sending command data to COG
*/
void EPD_Gx_spi_send_byte (uint8_t register_index, uint8_t register_data)
{
	EPD_cs_low ();
	EPD_spi_write (0x70); // header of Register Index
	EPD_spi_write (register_index);
	EPD_cs_high ();
	delay_btwn_CS_H_L ();
	EPD_cs_low ();
	EPD_spi_write (0x72); // header of Register Data
	EPD_spi_write (register_data);
	EPD_cs_high ();
}

//static uint32_t clockValue;
void system_init(void)
{
	/* Halting the Watchdog */
	MAP_WDT_A_holdTimer();

	/* Enabling FPU for DCO Frequency calculation */
	MAP_FPU_enableModule();

	/* Setting the DCO Frequency to a non-standard 48MHz */
	//MAP_CS_setDCOFrequency(48000000);
	/* Setting DCO to 48MHz (upping Vcore) */
	MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
	MAP_Interrupt_enableMaster();
	//MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
	//CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

	/*
		clockValue = CS_getACLK();//32000 Hz
		clockValue = CS_getMCLK();//48M Hz
		clockValue = CS_getSMCLK();//48M Hz
		clockValue = CS_getHSMCLK();//48M Hz
		clockValue = CS_getBCLK();//32000 Hz
	*/
}
/**
* \brief Configure GPIO
*/
void EPD_initialize_gpio(void)
{
	//COG Control IO Configuration
	Config_Busy_Pin();
	Config_EPD_cs_Pin();
	Config_EPD_rst_Pin();
	Config_EPD_panelon_Pin();
	Config_EPD_discharge_Pin();
	Config_EPD_border_Pin();
	Config_EPD_flash_cs_Pin();
	Config_EPD_pwm_Pin();
	Config_LED1_Pin();
	Config_BS1_Pin();
	BS1_low();//Must be LOW
	EPD_pwm_low();
	EPD_flash_cs_high();
	EPD_border_low();
}
/**
 * \brief Initialize the EPD hardware setting
 */
void EPD_display_hardware_init(void)
{
	EPD_initialize_gpio();
	EPD_Vcc_turn_off();
	EPD_cs_low();
	EPD_rst_low();
	EPD_discharge_low();
}

