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
#include <HW_drivers/UART_Driver.h>
static  volatile uint32_t sys_Counter,EPD_Counter;

uint32_t getnowtime(void)
{
	return sys_Counter;
}

void Systick_Configuration(void)
{
	systick_Start();
	sys_Counter =0;

}
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERB1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMERB1_VECTOR)))
#endif
void TIMER1_B0_ISR(void)
{
	//Any access, read or write, of the TAIV register automatically resets the
	//highest "pending" interrupt flag
	switch(__even_in_range(TBIV,14))
	{
		case 14:
			sys_Counter++;
			break;
		default:
			break;
	}
}
void systick_Stop(void)
{
	Timer_B_stop(TIMER_B0_BASE);
	Timer_B_disableInterrupt(TIMER_B0_BASE);
	Timer_B_clearTimerInterrupt(TIMER_B0_BASE);
}
/**
 * \brief Start Timer
 * \note
 * actual value:32 =~1ms, 327= ~10mSec,163=~5msec
 */
void systick_Start(void)
{
#define TIMER_B_PERIOD 				(uint16_t)((CPU_F/100)+40)
	//Start timer
	Timer_B_initUpModeParam initUpParam = {0};
	initUpParam.clockSource = TIMER_B_CLOCKSOURCE_ACLK;
	initUpParam.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_1;
	initUpParam.timerPeriod = 32;//ACLK=32768 HZ,
	initUpParam.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_ENABLE;
	initUpParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_B_CCIE_CCR0_INTERRUPT_DISABLE;
	initUpParam.timerClear = TIMER_B_DO_CLEAR;
	initUpParam.startTimer = true;
	Timer_B_initUpMode(TIMER_B0_BASE, &initUpParam);

	Timer_B_startCounter(TIMER_B0_BASE,
	                     TIMER_B_UP_MODE
	                    );
}
/**
 * \brief Start Timer
 * \note
 * desired value: 1mSec
 * actual value:  1.000mSec
 */
void start_EPD_timer(void)
{
#define TIMER_A_PERIOD 				((CPU_F/1000)+40)
	//Start timer
	Timer_A_initUpModeParam initUpParam = {0};
	initUpParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
	initUpParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
	initUpParam.timerPeriod = TIMER_A_PERIOD;
	initUpParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
	initUpParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
	initUpParam.timerClear = TIMER_A_DO_CLEAR;
	initUpParam.startTimer = true;
	Timer_A_initUpMode(TIMER_A1_BASE, &initUpParam);

	Timer_A_startCounter(TIMER_A1_BASE,
	                     TIMER_A_UP_MODE
	                    );
	EPD_Counter=0;
}
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A1_VECTOR)))
#endif
void TIMER1_A1_ISR(void)
{
	//Any access, read or write, of the TAIV register automatically resets the
	//highest "pending" interrupt flag
	switch(__even_in_range(TA1IV,14))
	{
		case 14:
			EPD_Counter++;
			break;
		default:
			break;
	}
}

/**
 * \brief Stop Timer
 */
void stop_EPD_timer(void)
{
	Timer_A_stop(TIMER_A1_BASE);
	Timer_A_disableInterrupt(TIMER_A1_BASE);
	Timer_A_clearTimerInterrupt(TIMER_A1_BASE);
}
/**
 * \brief Get current Timer after starting a new one
 */
uint32_t get_EPD_time_tick(void)
{

	return (EPD_Counter);
}

/**
 * \brief Delay mini-seconds
 * \param ms The number of mini-seconds
 */
void EPD_delay_ms(unsigned int ms)
{
	while(ms--)
	{
		_delay_ms(1);
	}
}

void delay_btwn_CS_H_L(void)
{
	//delay > 80ns
}

//static uint32_t clockValue;
void system_init(void)
{

	//Stop WDT
	WDT_A_hold(WDT_A_BASE);
	PMM_setVCoreUp(PMM_CORE_LEVEL_1);
	PMM_setVCoreUp(PMM_CORE_LEVEL_2);
	PMM_setVCoreUp(PMM_CORE_LEVEL_3);

	UCS_initClockSignal(
	    UCS_FLLREF,
	    UCS_REFOCLK_SELECT,
	    UCS_CLOCK_DIVIDER_1
	);
	UCS_initClockSignal(
	    UCS_ACLK,
	    UCS_REFOCLK_SELECT,
	    UCS_CLOCK_DIVIDER_1
	);

	UCS_initFLLSettle(
	    25000,
	    762
	);

	__bis_SR_register( GIE);
	//Verify if the Clock settings are as expected

	/*
		clockValue = UCS_getMCLK();//24969216
		clockValue = UCS_getACLK();//32768
		clockValue = UCS_getSMCLK();//24969216
	*/
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
		__delay_cycles(10);
		EPD_pwm_low();
		__delay_cycles(10);
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
void epd_spi_init(uint32_t spi_baudrate)
{
	USCI_B_SPI_disable(USCI_B0_BASE);
	//config  i/o
	config_gpio_dir_o(SPICLK_PORT, SPICLK_PIN);
	config_gpio_dir_o(SPIMOSI_PORT, SPIMOSI_PIN);
	config_gpio_dir_i(SPIMISO_PORT, SPIMISO_PIN);
	//P3.0,1,2 option select
	GPIO_setAsPeripheralModuleFunctionInputPin(
	    GPIO_PORT_P3,
	    GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2
	);
	//Initialize Master
	USCI_B_SPI_initMasterParam param = {0};
	param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK;
	param.clockSourceFrequency = UCS_getSMCLK();
	param.desiredSpiClock = spi_baudrate;
	param.msbFirst = USCI_B_SPI_MSB_FIRST;
	param.clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
	param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
	spi_state=USCI_B_SPI_initMaster(USCI_B0_BASE, &param);
	//Enable SPI module
	if(spi_state)USCI_B_SPI_enable(USCI_B0_BASE);
}
/**
 * \brief Initialize SPI
 */
void EPD_spi_attach()
{
	EPD_flash_cs_high();
	EPD_cs_high();
	epd_spi_init(COG_SPI_baudrate);
}
/**
 * \brief Disable SPI and change to GPIO
 */
void EPD_spi_detach(void)
{
	USCI_B_SPI_disable(USCI_B0_BASE);
	GPIO_setAsOutputPin(
	    GPIO_PORT_P3,
	    GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2
	);
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
	while(USCI_B_SPI_isBusy(USCI_B0_BASE));
	USCI_B_SPI_transmitData(USCI_B0_BASE, data);
	while(USCI_B_SPI_isBusy(USCI_B0_BASE));
	return USCI_B_SPI_receiveData(USCI_B0_BASE);
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
	_delay_us(20);
	EPD_spi_write(register_index);
	EPD_DC_high();
	_delay_us(20);
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

