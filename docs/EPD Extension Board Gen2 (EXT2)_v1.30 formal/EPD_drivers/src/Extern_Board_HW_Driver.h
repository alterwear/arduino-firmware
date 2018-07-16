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
#ifndef Extern_BOARD_HW_DRIVER_H_
#define Extern_BOARD_HW_DRIVER_H_

#ifdef USE_PDI_EDP_LIB
#define ArrayLength(array) (sizeof(array)/sizeof(array[0]))
typedef void (*Systick_handler)(uint32_t tick);
typedef struct Em_register_array{
	uint8_t register_index;
	uint8_t len;
	uint8_t *register_data;
}Em_register_array_t;

extern inline void Config_LED1_Pin();
extern inline void LED1_high();
extern inline void LED1_low();

extern inline void Config_Busy_Pin();
extern inline bool EPD_IsBusy();

extern inline void Config_EPD_cs_Pin();
extern inline void EPD_cs_high();
extern inline void EPD_cs_low();

extern inline void Config_EPD_flash_cs_Pin();
extern inline void EPD_flash_cs_high();
extern inline void EPD_flash_cs_low();

extern inline void Config_EPD_rst_Pin();
extern inline void EPD_rst_high();
extern inline void EPD_rst_low();

extern inline void Config_EPD_discharge_Pin();
extern inline void EPD_discharge_high();
extern inline void EPD_discharge_low();

inline void Config_EPD_panelon_Pin();
extern inline void EPD_Vcc_turn_on();
extern inline void EPD_Vcc_turn_off();

extern inline void Config_EPD_border_Pin();
extern inline void EPD_border_high();
extern inline void EPD_border_low();

extern inline void Config_EPD_pwm_Pin();
extern inline void EPD_pwm_high();
extern inline void EPD_pwm_low();

extern inline void SPIMISO_low();
extern inline void SPIMOSI_low();
extern inline void SPICLK_low();

extern inline void Config_EPD_DC_Pin();
extern inline void EPD_DC_high();
extern inline void EPD_DC_low();

extern inline void Config_EPD_DB1_Pin();
extern inline bool Get_EPD_DB1();

extern inline void Config_EPD_DB2_Pin();
extern inline bool Get_EPD_DB2();

//========================================================================================================

extern void start_EPD_timer(void);
extern void stop_EPD_timer(void);
extern uint32_t get_EPD_time_tick(void);
extern void EPD_delay_ms(unsigned int ms);
extern void EPD_spi_attach (void);
extern void EPD_spi_detach (void);
extern uint8_t EPD_spi_read(uint8_t data);
extern void EPD_spi_write (uint8_t data);

extern void iTC_spi_sendReg(uint8_t register_index);
extern void iTC_spi_sendRegData(uint8_t register_data);
extern void iTC_spi_send(uint8_t register_index,uint8_t *register_data,uint8_t len);
extern void iTC_spi_send_array(Em_register_array_t *register_array,uint8_t len);

extern void EPD_Gx_spi_send (unsigned char register_index, unsigned char *register_data, unsigned Length);
extern void EPD_Gx_spi_send_byte (uint8_t register_index, uint8_t register_data);
extern uint8_t EPD_Gx_spi_r(uint8_t register_index, uint8_t register_data);
extern uint8_t EPD_Gx_spi_rid(void);

extern void PWM_run(uint16_t time);
extern int16_t getTemperature(void);
extern void EPD_display_hardware_init (void);
#endif

#endif /* BOARD_HW_DRIVER_H_ */
