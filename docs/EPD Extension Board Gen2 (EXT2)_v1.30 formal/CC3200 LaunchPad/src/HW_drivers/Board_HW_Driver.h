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

#include "conf_EPD.h"
#include <stdbool.h>
#include <stdint.h>
#ifndef BOARD_HW_DRIVER_H_
#define BOARD_HW_DRIVER_H_

typedef void (*Systick_handler)(uint32_t tick);
typedef struct Em_register_array
{
	uint8_t register_index;
	uint8_t len;
	uint8_t *register_data;
} Em_register_array_t;

#define	_BV(bit)   								(1 << (bit % 8)) /**< left shift 1 bit */
#define	_HIGH      								1            /**< signal high */
#define	_LOW       								!_HIGH       /**< signal low */

#define	config_gpio_dir_o(GPIO_BASE,ucPin,PinIO)  {MAP_PinTypeGPIO(PinIO, PIN_MODE_0, false);\
									 	 	 	   MAP_GPIODirModeSet(GPIO_BASE, _BV(ucPin), GPIO_DIR_MODE_OUT);}/**< set output direction for an IOPORT pin */
#define	config_gpio_dir_i(GPIO_BASE,ucPin,PinIO)  {MAP_PinTypeGPIO(PinIO, PIN_MODE_0, false);\
									 	 	 	   MAP_GPIODirModeSet(GPIO_BASE, _BV(ucPin), GPIO_DIR_MODE_IN);}  /**< set input direction for an IOPORT pin */
#define	set_gpio_high(GPIO_BASE,Pin)      		   GPIOPinWrite (GPIO_BASE, _BV(Pin),_BV(Pin)) /**< set HIGH for an IOPORT pin */
#define	set_gpio_low(GPIO_BASE,Pin)          	   GPIOPinWrite (GPIO_BASE, _BV(Pin),0)  /**< set LOW for an IOPORT pin */
//#define	set_gpio_invert(GPIO_BASE,Pin)    BITINV(GPIO_BASE,Pin) /**< toggle the value of an IOPORT pin */
#define	input_get(GPIO_BASE,Pin)                  (GPIOPinRead(GPIO_BASE,_BV(Pin))  & _BV(Pin) )   /**< get current value of an IOPORT pin */


/** The SPI frequency of this kit (8MHz) */
#define COG_SPI_baudrate    					8000000/**< the baud rate of SPI */

/******************************************************************************
* GPIO Defines
*****************************************************************************/
#define EPD_CS_PinIO            PIN_18
#define EPD_CS_PIN              28
#define EPD_CS_PORT             GPIOA3_BASE         /**< LaunchPad 18  */

#define Flash_CS_PinIO          PIN_08
#define Flash_CS_PIN            17
#define Flash_CS_PORT           GPIOA2_BASE       /**< LaunchPad 8 */

#define SPIMOSI_PinIO           PIN_07
#define SPIMOSI_PIN             16
#define SPIMOSI_PORT            GPIOA2_BASE       	/**< LaunchPad 7 */

#define SPIMISO_PinIO           PIN_06
#define SPIMISO_PIN             15
#define SPIMISO_PORT            GPIOA1_BASE       	/**< LaunchPad 6  */

#define EPD_DB1_PinIO			PIN_21
#define EPD_DB1_PORT            25       			/**< LaunchPad 21  */
#define EPD_DB1_PIN             GPIOA3_BASE
#define EPD_BORDER_PinIO        PIN_21
#define EPD_BORDER_PIN          25
#define EPD_BORDER_PORT         GPIOA3_BASE         /**< LaunchPad 21  */
#define EPD_DISCHARGE_PinIO     PIN_55
#define EPD_DISCHARGE_PIN       1
#define EPD_DISCHARGE_PORT      GPIOA0_BASE       /**< LaunchPad 55  */
#define EPD_PANELON_PinIO       PIN_15
#define EPD_PANELON_PIN         22
#define EPD_PANELON_PORT        GPIOA2_BASE       /**< LaunchPad 22  */

#define EPD_DB2_PinIO			PIN_58
#define EPD_DB2_PORT            3       			/**< LaunchPad 58  */
#define EPD_DB2_PIN             GPIOA0_BASE
#define SPICLK_PinIO            PIN_05
#define SPICLK_PIN              14
#define SPICLK_PORT             GPIOA1_BASE       /**< LaunchPad 5 */
#define EPD_BUSY_PinIO          PIN_62
#define EPD_BUSY_PIN            7
#define EPD_BUSY_PORT           GPIOA0_BASE       /**< LaunchPad 62  */
#define PWM_PinIO               PIN_01
#define PWM_PIN                 10
#define PWM_PORT                GPIOA1_BASE       /**< LaunchPad 1  */
#define EPD_DC_PinIO            PIN_01
#define EPD_DC_PIN              10
#define EPD_DC_PORT             GPIOA1_BASE       /**< LaunchPad 1  */
#define EPD_RST_PinIO           PIN_02
#define EPD_RST_PIN             11
#define EPD_RST_PORT            GPIOA1_BASE       /**< LaunchPad 2 */


#define LED1_PinIO           	PIN_64
#define LED1_PIN             	9
#define LED1_PORT            	GPIOA1_BASE       /**< LaunchPad 64 */

#define BS1_PinIO           	PIN_45
#define BS1_PIN             	31
#define BS1_PORT            	GPIOA3_BASE       /**< LaunchPad 45 */
#define SW1_PinIO           	PIN_15
#define SW1_PIN             	22
#define SW1_PORT            	GPIOA2_BASE       /**< LaunchPad 15 */
#define SW2_PinIO           	PIN_4
#define SW2_PIN             	13
#define SW2_PORT            	GPIOA1_BASE       /**< LaunchPad 4 */


inline void Config_BS1_Pin()
{
	config_gpio_dir_o(BS1_PORT,BS1_PIN,BS1_PinIO);
}
inline void BS1_high()
{
	set_gpio_high(BS1_PORT,BS1_PIN);
}
inline void BS1_low()
{
	set_gpio_low(BS1_PORT,BS1_PIN);
}

inline void Enable_SW_Pin()
{
	//config_gpio_dir_i(SW1_PORT,SW1_PIN |SW2_PIN );
	//ROM_GPIODirModeSet(SW1_PORT, SW1_PIN | SW2_PIN, GPIO_DIR_MODE_IN);
	//ROM_GPIOPadConfigSet(SW1_PORT, SW1_PIN | SW2_PIN,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
inline void Disable_SW_Pin()
{
	//config_gpio_dir_o(BS1_PORT,BS1_PIN);
	BS1_low();
}
inline bool SW1_State()
{
	return (bool)input_get(SW1_PORT,SW1_PIN);
}
inline bool SW2_State()
{
	return (bool)input_get(SW2_PORT,SW2_PIN);
}

inline void Config_LED1_Pin()
{
	config_gpio_dir_o(LED1_PORT,LED1_PIN,LED1_PinIO);
}
inline void LED1_high()
{
	set_gpio_high(LED1_PORT,LED1_PIN);
}
inline void LED1_low()
{
	set_gpio_low(LED1_PORT,LED1_PIN);
}
inline void LED1_toggle()
{

}

inline void Config_Busy_Pin()
{
	config_gpio_dir_i(EPD_BUSY_PORT,EPD_BUSY_PIN,EPD_BUSY_PinIO);
}
inline bool EPD_IsBusy()
{
	return (bool)input_get(EPD_BUSY_PORT,EPD_BUSY_PIN);
}

inline void Config_EPD_cs_Pin()
{
	config_gpio_dir_o(EPD_CS_PORT,EPD_CS_PIN,EPD_CS_PinIO);
}
inline void EPD_cs_high()
{
	set_gpio_high(EPD_CS_PORT,EPD_CS_PIN);
}
inline void EPD_cs_low()
{
	set_gpio_low(EPD_CS_PORT,EPD_CS_PIN);
}

inline void Config_EPD_flash_cs_Pin()
{
	config_gpio_dir_o(Flash_CS_PORT,Flash_CS_PIN,Flash_CS_PinIO);
}
inline void EPD_flash_cs_high()
{
	set_gpio_high(Flash_CS_PORT,Flash_CS_PIN);
}
inline void EPD_flash_cs_low()
{
	set_gpio_low(Flash_CS_PORT,Flash_CS_PIN);
}

inline void Config_EPD_rst_Pin()
{
	config_gpio_dir_o(EPD_RST_PORT,EPD_RST_PIN,EPD_RST_PinIO);
}
inline void EPD_rst_high()
{
	set_gpio_high(EPD_RST_PORT,EPD_RST_PIN);
}
inline void EPD_rst_low()
{
	set_gpio_low(EPD_RST_PORT,EPD_RST_PIN);
}

inline void Config_EPD_discharge_Pin()
{
	config_gpio_dir_o(EPD_DISCHARGE_PORT,EPD_DISCHARGE_PIN,EPD_DISCHARGE_PinIO);
}
inline void EPD_discharge_high()
{
	set_gpio_high(EPD_DISCHARGE_PORT,EPD_DISCHARGE_PIN);
}
inline void EPD_discharge_low()
{
	set_gpio_low(EPD_DISCHARGE_PORT,EPD_DISCHARGE_PIN);
}

inline void Config_EPD_panelon_Pin()
{
	config_gpio_dir_o(EPD_PANELON_PORT,EPD_PANELON_PIN,EPD_PANELON_PinIO);
}
inline void EPD_Vcc_turn_on()
{
	set_gpio_high(EPD_PANELON_PORT,EPD_PANELON_PIN);
}
inline void EPD_Vcc_turn_off()
{
	set_gpio_low(EPD_PANELON_PORT,EPD_PANELON_PIN);
}

inline void Config_EPD_border_Pin()
{
	config_gpio_dir_o(EPD_BORDER_PORT,EPD_BORDER_PIN,EPD_BORDER_PinIO);
}
inline void EPD_border_high()
{
	set_gpio_high(EPD_BORDER_PORT,EPD_BORDER_PIN);
}
inline void EPD_border_low()
{
	set_gpio_low(EPD_BORDER_PORT,EPD_BORDER_PIN);
}

inline void Config_EPD_pwm_Pin()
{
	config_gpio_dir_o(PWM_PORT,PWM_PIN,PWM_PinIO);
}
inline void EPD_pwm_high()
{
	set_gpio_high(PWM_PORT,PWM_PIN);
}
inline void EPD_pwm_low()
{
	set_gpio_low(PWM_PORT,PWM_PIN);
}

inline void SPIMISO_low()
{
	set_gpio_low(SPIMISO_PORT,SPIMISO_PIN);
}
inline void SPIMOSI_low()
{
	set_gpio_low(SPIMOSI_PORT,SPIMOSI_PIN);
}
inline void SPICLK_low()
{
	set_gpio_low(SPICLK_PORT,SPICLK_PIN);
}

inline void Config_EPD_DC_Pin()
{
	config_gpio_dir_o(EPD_DC_PORT,EPD_DC_PIN,EPD_DC_PinIO);
}
inline void EPD_DC_high()
{
	set_gpio_high(EPD_DC_PORT,EPD_DC_PIN);
}
inline void EPD_DC_low()
{
	set_gpio_low(EPD_DC_PORT,EPD_DC_PIN);
}

inline void Config_EPD_DB1_Pin()
{
	config_gpio_dir_i(EPD_DB1_PORT,EPD_DB1_PIN,EPD_DB1_PinIO);
}
inline bool Get_EPD_DB1()
{
	return (bool)input_get(EPD_DB1_PORT,EPD_DB1_PIN);
}

inline void Config_EPD_DB2_Pin()
{
	config_gpio_dir_i(EPD_DB2_PORT,EPD_DB2_PIN,EPD_DB2_PinIO);
}
inline bool Get_EPD_DB2()
{
	return (bool)input_get(EPD_DB2_PORT,EPD_DB2_PIN);
}






//========================================================================================================
void system_init(void);
uint32_t getnowtime(void);
void Systick_Configuration(void);
void systick_Start(void);
void systick_Stop(void);

void start_EPD_timer(void);
void stop_EPD_timer(void);
uint32_t get_EPD_time_tick(void);
void EPD_delay_ms(unsigned int ms);

void EPD_spi_attach (void);
void EPD_spi_detach (void);
bool check_flash_spi(void);
uint8_t EPD_spi_read(uint8_t data);
void EPD_spi_write (uint8_t data);

void iTC_spi_sendReg(uint8_t register_index);
void iTC_spi_sendRegData(uint8_t register_data);
void iTC_spi_send(uint8_t register_index,uint8_t *register_data,uint8_t len);
void iTC_spi_send_array(Em_register_array_t *register_array,uint8_t len);

void EPD_Gx_spi_send (unsigned char register_index, unsigned char *register_data, unsigned Length);
void EPD_Gx_spi_send_byte (uint8_t register_index, uint8_t register_data);
uint8_t EPD_Gx_spi_r(uint8_t register_index, uint8_t register_data);
uint8_t EPD_Gx_spi_rid(void);

void EPD_display_hardware_init (void);
void PWM_run(uint16_t time);

#define delay_ms(x)  EPD_delay_ms(x)

#endif /* BOARD_HW_DRIVER_H_ */
