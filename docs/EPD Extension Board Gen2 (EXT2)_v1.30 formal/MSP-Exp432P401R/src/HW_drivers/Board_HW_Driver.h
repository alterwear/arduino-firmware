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

#include "driverlib.h"
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

#define	config_gpio_dir_o(Port,Pin)  			GPIO_setAsOutputPin(Port, Pin) /**< set output direction for an IOPORT pin */
#define	config_gpio_dir_i(Port,Pin)  			GPIO_setAsInputPin(Port, Pin)  /**< set input direction for an IOPORT pin */
#define	set_gpio_high(Port,Pin)      			GPIO_setOutputHighOnPin (Port, Pin) /**< set HIGH for an IOPORT pin */
#define	set_gpio_low(Port,Pin)       			GPIO_setOutputLowOnPin (Port, Pin)  /**< set LOW for an IOPORT pin */
#define	set_gpio_invert(Port,Pin)    			GPIO_toggleOutputOnPin(Port, Pin) /**< toggle the value of an IOPORT pin */
#define	input_get(Port,Pin)          			(bool)(GPIO_getInputPinValue (Port, Pin ))   /**< get current value of an IOPORT pin */

/******************************************************************************
* GPIO Defines
*****************************************************************************/
#define SPICLK_PORT             		GPIO_PORT_P1       /**< LaunchPad P1.5 */
#define SPICLK_PIN              		GPIO_PIN5
#define EPD_BUSY_PORT           		GPIO_PORT_P4       /**< LaunchPad P4.6  */
#define EPD_BUSY_PIN            		GPIO_PIN6
#define PWM_PORT                		GPIO_PORT_P6       /**< LaunchPad P6.5  */
#define PWM_PIN                 		GPIO_PIN5
#define EPD_RST_PORT            		GPIO_PORT_P6       /**< LaunchPad P6.4 */
#define EPD_RST_PIN             		GPIO_PIN4
#define EPD_PANELON_PORT        		GPIO_PORT_P3       /**< LaunchPad P3.6  */
#define EPD_PANELON_PIN         		GPIO_PIN6
#define EPD_DISCHARGE_PORT      		GPIO_PORT_P5       /**< LaunchPad P5.2  */
#define EPD_DISCHARGE_PIN       		GPIO_PIN2
#define EPD_BORDER_PORT         		GPIO_PORT_P5       /**< LaunchPad P5.0  */
#define EPD_BORDER_PIN          		GPIO_PIN0
#define SPIMISO_PORT            		GPIO_PORT_P1       /**< LaunchPad P1.7  */
#define SPIMISO_PIN             		GPIO_PIN7
#define SPIMOSI_PORT            		GPIO_PORT_P1       /**< LaunchPad P1.6  */
#define SPIMOSI_PIN             		GPIO_PIN6
#define Flash_CS_PORT           		GPIO_PORT_P3       /**< LaunchPad P3.0  */
#define Flash_CS_PIN            		GPIO_PIN0
#define EPD_CS_PORT             		GPIO_PORT_P2       /**< LaunchPad P2.5  */
#define EPD_CS_PIN              		GPIO_PIN5

#define EPD_DC_PORT             		GPIO_PORT_P6       /**< LaunchPad P6.5  */
#define EPD_DC_PIN              		GPIO_PIN5
#define EPD_DB1_PORT             		GPIO_PORT_P5       /**< LaunchPad P5.0  */
#define EPD_DB1_PIN              		GPIO_PIN0
#define EPD_DB2_PORT             		GPIO_PORT_P6       /**< LaunchPad P6.0  */
#define EPD_DB2_PIN              		GPIO_PIN0

#define LED1_PORT           		    GPIO_PORT_P1       /**< LaunchPad P1.0  */
#define LED1_PIN            			GPIO_PIN0
#define BS1_PORT           				GPIO_PORT_P5       /**< LaunchPad P5.7  */
#define BS1_PIN            				GPIO_PIN7

#define SW2_PORT           				GPIO_PORT_P1       /**< LaunchPad P1.4  */
#define SW2_PIN            				GPIO_PIN4
#define SW1_PORT           				GPIO_PORT_P1       /**< LaunchPad P1.1  */
#define SW1_PIN            				GPIO_PIN1



inline void Config_BS1_Pin()
{
	config_gpio_dir_o(BS1_PORT,BS1_PIN);
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
	config_gpio_dir_i(SW1_PORT,SW1_PIN |SW2_PIN );
}
inline void Disable_SW_Pin()
{
	config_gpio_dir_o(BS1_PORT,BS1_PIN);
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
	config_gpio_dir_o(LED1_PORT,LED1_PIN);
}
inline void LED1_high()
{
	set_gpio_high(LED1_PORT,LED1_PIN);
}
inline void LED1_low()
{
	set_gpio_low(LED1_PORT,LED1_PIN);
}

inline void Config_Busy_Pin()
{
	config_gpio_dir_i(EPD_BUSY_PORT,EPD_BUSY_PIN);
}
inline bool EPD_IsBusy()
{
	return (bool)input_get(EPD_BUSY_PORT,EPD_BUSY_PIN);
}

inline void Config_EPD_cs_Pin()
{
	config_gpio_dir_o(EPD_CS_PORT,EPD_CS_PIN);
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
	config_gpio_dir_o(Flash_CS_PORT,Flash_CS_PIN);
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
	config_gpio_dir_o(EPD_RST_PORT,EPD_RST_PIN);
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
	config_gpio_dir_o(EPD_DISCHARGE_PORT,EPD_DISCHARGE_PIN);
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
	config_gpio_dir_o(EPD_PANELON_PORT,EPD_PANELON_PIN);
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
	config_gpio_dir_o(EPD_BORDER_PORT,EPD_BORDER_PIN);
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
	config_gpio_dir_o(PWM_PORT,PWM_PIN);
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
	config_gpio_dir_o(EPD_DC_PORT,EPD_DC_PIN);
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
	config_gpio_dir_i(EPD_DB1_PORT,EPD_DB1_PIN);
}
inline bool Get_EPD_DB1()
{
	return (bool)input_get(EPD_DB1_PORT,EPD_DB1_PIN);
}

inline void Config_EPD_DB2_Pin()
{
	config_gpio_dir_i(EPD_DB2_PORT,EPD_DB2_PIN);
}
inline bool Get_EPD_DB2()
{
	return (bool)input_get(EPD_DB2_PORT,EPD_DB2_PIN);
}

#define CPU_F 									((double)48000000)

/** The SPI frequency of this kit (8MHz) */
#define COG_SPI_baudrate    					8000000
#define FLASH_SPI_baudrate    					12000000

#define _delay_us(A)\
  __delay_cycles( (uint32_t) ( (double)(CPU_F) *((A)/1000000.0) + 0.5))

#define _delay_ms(A)\
  __delay_cycles( (uint32_t) ( (double)(CPU_F)*((A)/1000.0) + 0.5))

#define _delay_s(A)\
  __delay_cycles( (uint32_t) ( (double)(CPU_F)*((A)/1.0) + 0.5))



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
