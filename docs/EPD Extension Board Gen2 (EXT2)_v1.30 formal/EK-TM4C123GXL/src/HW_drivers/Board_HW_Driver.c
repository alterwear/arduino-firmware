/**
* Copyright (c) Pervasive Displays Inc. All rights reserved.
*
* \asf_license_start
*
* \page License
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
*
* \asf_license_stop
**/

#define isDebug		0

#include "Board_HW_Driver.h"

#if isDebug
#include "UART_Driver.h"
#endif

static  volatile uint32_t sys_Counter,EPD_Counter;
#define CS_H_L_Delay()		ROM_SysCtlDelay(1000);
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
	  ROM_SysTickPeriodSet(( ROM_SysCtlClockGet()  / 1000));//1 ms
	  ROM_SysTickIntEnable();
	  ROM_SysTickEnable();
	  sys_Counter=0;
}
void SysTickIntHandler(void)
{
	sys_Counter++;
}
void systick_Stop(void)
{
	ROM_SysTickIntDisable();
	ROM_SysTickDisable();
}
void systick_Start(void)
{
	ROM_SysTickIntEnable();
	 ROM_SysTickEnable();
}
/**
 * \brief Start Timer
 * \note
 * desired value: 1mSec
 * actual value:  1.000mSec
 */
void start_EPD_timer(void) {

	EPD_Counter=sys_Counter;
}

/**
 * \brief Stop Timer
 */
void stop_EPD_timer(void) {

}
/**
 * \brief Get current Timer after starting a new one
 */
uint32_t get_EPD_time_tick(void) {

	return (sys_Counter-EPD_Counter);
}

void Timer2BIntHandler(void)
{

   TimerIntClear(TIMER2_BASE, TIMER_TIMB_TIMEOUT);
   EPD_Counter++;
}
/**
 * \brief Delay mini-seconds
 * \param ms The number of mini-seconds
 */
void EPD_delay_ms(unsigned int ms) {
	start_EPD_timer();
	while(get_EPD_time_tick()<=ms)
	{

	}
}

void delay_btwn_CS_H_L(void) {
	//delay > 80ns
}
/**
 * \brief PWM toggling.
 *
 * \param ms The interval of PWM toggling (mini seconds)
 */
void PWM_run(uint16_t ms) {
    start_EPD_timer();
	do {

		EPD_pwm_high();
		ROM_SysCtlDelay(20);
		EPD_pwm_low();
		ROM_SysCtlDelay(20);
	} while (get_EPD_time_tick() < ms); //wait Delay Time

	stop_EPD_timer();

}
//******************************************************************
//* SPI  Configuration
//******************************************************************
bool spi_state=false;

/**
 * \brief Configure SPI
 */
void epd_spi_init(uint32_t spi_baudrate) {


}
/**
 * \brief Initialize SPI
 */
void EPD_spi_attach() {
	if(spi_state) return;
	EPD_flash_cs_high();
	EPD_cs_high();
	ROM_SysCtlPeripheralEnable(SPI_Peripheral);
    ROM_SysCtlPeripheralEnable(SPI_SYSCTL_PERIPH);
	GPIOPinConfigure(SPI_CLK_Config);
	GPIOPinConfigure(SPI_MISO_Config);
	GPIOPinConfigure(SPI_MOSI_Config);
	GPIOPinTypeSSI(SPI_PORT, SPICLK_PIN | SPIMOSI_PIN | SPIMISO_PIN );
	GPIOPadConfigSet(SPI_PORT, SPICLK_PIN | SPIMOSI_PIN | SPIMISO_PIN, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
	ROM_SSIClockSourceSet(SPI_BASE,SYSCTL_OSC_MAIN);
	ROM_SSIConfigSetExpClk(SPI_BASE, ROM_SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
					   SSI_MODE_MASTER, COG_SPI_baudrate, 8);
	ROM_SSIEnable(SPI_BASE);
    spi_state=true;
}
/**
 * \brief Disable SPI and change to GPIO
 */
void EPD_spi_detach(void) {
	if(!spi_state) return;
	EPD_cs_high();
    ROM_SSIDisable(SPI_BASE);
	config_gpio_dir_o(SPICLK_PORT,SPICLK_PIN);
	config_gpio_dir_o(SPIMOSI_PORT,SPIMOSI_PIN);
	config_gpio_dir_o(SPIMISO_PORT,SPIMISO_PIN);
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
uint8_t EPD_spi_read(unsigned char data) {
	uint32_t tmp;
	while(ROM_SSIBusy(SPI_BASE));
	ROM_SSIDataPut(SPI_BASE,(uint32_t)data);
	while(ROM_SSIBusy(SPI_BASE));
	ROM_SSIDataGet(SPI_BASE, (uint32_t *)&tmp);
	return (uint8_t)(tmp&0x00FF);
}

/**
 * \brief SPI synchronous write
 */
void EPD_spi_write(unsigned char data) {
	EPD_spi_read(data);
}
void iTC_spi_sendReg(uint8_t register_index)
{
	EPD_cs_low();
	EPD_DC_low();
	CS_H_L_Delay();
	EPD_spi_write(register_index);
	EPD_cs_high();
	CS_H_L_Delay();
	EPD_DC_high();
	EPD_cs_low();
	CS_H_L_Delay();
}
void iTC_spi_sendRegData(uint8_t register_data)
{
	EPD_spi_write(register_data);
}

void iTC_spi_send(uint8_t register_index,uint8_t *register_data,uint8_t len)
{
#if isDebug
	UartSend((const uint8_t *)&register_index,1);
	if(len>0)UartSend((const uint8_t *)register_data,len);
#endif
	EPD_cs_low();
	EPD_DC_low();
	CS_H_L_Delay();
	EPD_spi_write(register_index);
	//EPD_cs_high();
	//CS_H_L_Delay();
	EPD_DC_high();
	//EPD_cs_low();
	CS_H_L_Delay();
	while(len--)
	{
		EPD_spi_write(*register_data++);
	}

	EPD_cs_high();
}
void iTC_spi_send_array(Em_register_array_t *register_array,uint8_t len)
{
	uint8_t i;
	for(i=0;i<len;i++)
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
uint8_t EPD_Gx_spi_r(uint8_t register_index, uint8_t register_data) {
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
               unsigned length) {
	EPD_cs_low ();
	EPD_spi_write (0x70); // header of Register Index
	EPD_spi_write (register_index);
	EPD_cs_high ();
	delay_btwn_CS_H_L ();
	EPD_cs_low ();

	EPD_spi_write (0x72); // header of Register Data of write command
	while(length--) {
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
void EPD_Gx_spi_send_byte (uint8_t register_index, uint8_t register_data) {
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

void system_init(void)
{
    //
    // Enable stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
  //  ROM_FPUEnable();
   // ROM_FPUStackingEnable();
	// Set the clocking to run directly from the PLL at 20 MHz.
	// The following code:
	// -sets the system clock divider to 10 (200 MHz PLL divide by 10 = 20 MHz)
	// -sets the system clock to use the PLL
	// -uses the main oscillator
	// -configures for use of 16 MHz crystal/oscillator input
	// Set clock to 200 MHz/4=50MHz
	SysCtlClockSet(SYSCTL_SYSDIV_4| SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}
/**
* \brief Configure GPIO
*/
void EPD_initialize_gpio(void) {
	//ROM_FPULazyStackingEnable();
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//COG Control IO Configuration
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
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
	GPIOPadConfigSet(EPD_CS_PORT, EPD_CS_PIN , GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
	EPD_pwm_low();
	EPD_flash_cs_high();
	EPD_border_low();
	EPD_Vcc_turn_off();
}
/**
 * \brief Initialize the EPD hardware setting
 */
void EPD_display_hardware_init(void) {
	EPD_initialize_gpio();
	EPD_Vcc_turn_off();
	EPD_cs_low();
	EPD_rst_low();
	EPD_discharge_low();
#if isDebug
	ConfigureUART(115200);
#endif
}

