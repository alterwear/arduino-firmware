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
#include <math.h>
#include "driverlib.h"

#ifndef CONF_EPD_H_INCLUDED
#define CONF_EPD_H_INCLUDED

#define UART_Baudrate		(115200)

#define s_EPD_144		0
#define s_EPD_190		1
#define s_EPD_200		2
#define s_EPD_215		3
#define s_EPD_260		4
#define s_EPD_271		5
#define s_EPD_287		6


#ifdef eTC_G1_Aurora_Mb
#define USE_COG_Driver		DR_eTC_G1_Aurora_Mb
#define USE_EPD_SIZE		s_EPD_200
#endif
#ifdef eTC_G2_Aurora_Ma
#define USE_COG_Driver		DR_eTC_G2_Aurora_Ma
#define USE_EPD_SIZE		s_EPD_200
#endif
#ifdef eTC_G2_Aurora_Mb
#define USE_COG_Driver		DR_eTC_G2_Aurora_Mb
#define USE_EPD_SIZE		s_EPD_200
#endif
#ifdef iTC_215_Aurora_Mb
#define USE_COG_Driver		DR_iTC_215_Aurora_Mb
#define USE_EPD_SIZE		s_EPD_215
#endif
#ifdef iTC_271_Aurora_Mb
#define USE_COG_Driver		DR_iTC_271_Aurora_Mb
#define USE_EPD_SIZE		s_EPD_271
#endif

#define Firmware_Ver        (uint8_t *)"V1.21           "

#include "Board_HW_Driver.h"
#include "EPD_drivers.h"
#include "EPD_interface.h"

#ifdef USE_PDI_APPs

#include "HW_drivers/Mem_Flash.h"
#include "HW_drivers/UART_Driver.h"
#include "Rtos.h"
#endif

#endif /* CONF_EPD_H_INCLUDED */

