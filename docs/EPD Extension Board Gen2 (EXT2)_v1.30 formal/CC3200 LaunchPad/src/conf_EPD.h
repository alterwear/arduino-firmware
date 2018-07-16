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
// Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "interrupt.h"
#include "hw_apps_rcm.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "gpio.h"
#include "utils.h"
#include "pin.h"
#include "spi.h"
#include "timer.h"
// Common interface includes
#include "timer_if.h"

#ifndef CONF_EPD_H_INCLUDED
#define CONF_EPD_H_INCLUDED


#define s_EPD_144		0
#define s_EPD_190		1
#define s_EPD_200		2
#define s_EPD_215		3
#define s_EPD_260		4
#define s_EPD_271		5
#define s_EPD_287		6
#define s_EPD_SP_271  8
#define s_EPD_420		10
#define s_EPD_SP_420	11

#ifdef eTC_G1_Aurora_Mb
#define USE_COG_Driver		dr_eTC_G1_Aurora_Mb
#define USE_EPD_SIZE		s_EPD_200
#endif
#ifdef eTC_G2_Aurora_Ma
#define USE_COG_Driver		dr_eTC_G2_Aurora_Ma
#define USE_EPD_SIZE		s_EPD_200
#endif
#ifdef eTC_G2_Aurora_Mb
#define USE_COG_Driver		dr_eTC_G2_Aurora_Mb
#define USE_EPD_SIZE		s_EPD_200
#endif
#ifdef iTC_215_Aurora_Mb
#define USE_COG_Driver		dr_iTC_215_Aurora_Mb
#define USE_EPD_SIZE		s_EPD_215
#endif
#ifdef iTC_420_Spectra
#define USE_COG_Driver		dr_iTC_420_Spectra
#define USE_EPD_SIZE		s_EPD_420
#endif
#ifdef iTC_420_Aurora_Mb
#define USE_COG_Driver		dr_iTC_420_Aurora_Mb
#define USE_EPD_SIZE		s_EPD_420
#endif



#define Firmware_Ver        (uint8_t *)"V1.21           "

#include "Board_HW_Driver.h"
#include "EPD_drivers.h"
#include "EPD_interface.h"



#endif /* CONF_EPD_H_INCLUDED */

