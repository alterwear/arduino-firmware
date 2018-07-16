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

/***************************************************************************
 * The definition in this file is switched from Configuration under project.
 * It defines what functions can be supported in Driver_Handle_t structure.
 ***************************************************************************/

#ifndef COG_Drivers_List_H_
#define COG_Drivers_List_H_

#ifdef USE_PDI_APPs

#define eTC_G2_Aurora_Ma
#define eTC_G2_Aurora_Mb
#define iTC_215_Aurora_Mb
#define iTC_287_Aurora_Mb
//#define iTC_287_Spectra
#define iTC_420_Spectra
#define iTC_420_Aurora_Mb
#define iTC_420_Spectra
#define iTC_UC_Spectra


#endif

#ifdef eTC_G1_Aurora_Mb
#include "eTC_G1_Size_Aurora_Mb.h"
#endif
#ifdef eTC_G2_Aurora_Ma
#include "eTC_G2_Size_Aurora_Ma.h"
#endif
#ifdef eTC_G2_Aurora_Mb
#include "eTC_G2_Size_Aurora_Mb.h"
#endif
#ifdef iTC_215_Aurora_Mb
#include "iTC_215_Aurora_Mb.h"
#endif

#ifdef iTC_287_Aurora_Mb
#include "iTC_287_Aurora_Mb.h"
#endif

#ifdef iTC_287_Spectra
#include "iTC_287_Spectra.h"
#endif

#ifdef iTC_UC_Spectra
#include "iTC_UC8451c_Spectra.h"
#endif

#ifdef iTC_420_Spectra
#include "iTC_420_Spectra.h"
#endif

#ifdef iTC_420_Aurora_Mb
#include "iTC_420_Aurora_Mb.h"
#endif

#ifdef iTC_287_Aurora_Mb
#include "iTC_287_Aurora_Mb.h"
#endif

static const Driver_Handle_t Driver_Handle_list[]=
{
#ifdef eTC_G1_Aurora_Mb
		{
			dr_eTC_G1_Aurora_Mb,
			(uint8_t []){EPD_144_BW,EPD_200_BW,EPD_271_BW,EPD_Empty},
			eTC_G1Mb_IO_Config,
			eTC_G1Mb_power_on,
			eTC_G1Mb_initialize_driver,
			eTC_G1Mb_Display_from_Ram,
			eTC_G1Mb_Display_from_flash,
			eTC_G1Mb_Display_PU_from_Ram,
			eTC_G1Mb_Display_PU_From_Flash,
			eTC_G1Mb_power_off,
			NULL
		},
#endif
#ifdef eTC_G2_Aurora_Mb
		{
			dr_eTC_G2_Aurora_Mb,
			(uint8_t []){EPD_144_BW,EPD_200_BW,EPD_271_BW,EPD_190_BW,EPD_260_BW,EPD_Empty},
		    eTC_G2Mb_IO_Config,
			eTC_G2Mb_power_on,
			eTC_G2Mb_initialize_driver,
			eTC_G2Mb_Display_from_Ram,
			eTC_G2Mb_Display_from_flash,
			eTC_G2Mb_Display_PU_from_Ram,
			eTC_G2Mb_Display_PU_From_Flash,
			eTC_G2Mb_power_off,
			NULL
		},
#endif
#ifdef eTC_G2_Aurora_Ma
		{
			dr_eTC_G2_Aurora_Ma,
			(uint8_t []){EPD_144_BW,EPD_200_BW,EPD_271_BW,EPD_190_BW,EPD_260_BW,EPD_Empty},
			eTC_G2Ma_IO_Config,
			eTC_G2Ma_power_on,
			eTC_G2Ma_initialize_driver,
			eTC_G2Ma_Display_from_Ram,
			eTC_G2Ma_Display_from_flash,
			NULL,
			NULL,
			eTC_G2Ma_power_off,
			NULL
		},
#endif
#ifdef iTC_215_Aurora_Mb
		
		{
			dr_iTC_215_Aurora_Mb,
			(uint8_t []){EPD_215_BW,EPD_Empty},
			iTC_215Mb_IO_Config,
			iTC_215Mb_power_on,
			iTC_215Mb_initialize_driver,
			iTC_215Mb_Display_from_Ram,
			iTC_215Mb_Display_from_flash,
			iTC_215Mb_Display_PU_from_Ram,
			iTC_215Mb_Display_PU_From_Flash,
			iTC_215Mb_power_off,
			NULL
		},
#endif
#ifdef iTC_287_Aurora_Mb

		{
			dr_iTC_287_Aurora_Mb,
			(uint8_t []){EPD_287_BW,EPD_Empty},
			iTC_287Mb_IO_Config,
			iTC_287Mb_power_on,
			iTC_287Mb_initialize_driver,
			iTC_287Mb_Display_from_Ram,
			iTC_287Mb_Display_from_flash,
			iTC_287Mb_Display_PU_from_Ram,
			iTC_287Mb_Display_PU_From_Flash,
			iTC_287Mb_power_off,
			NULL
		},
#endif
#ifdef iTC_287_Spectra

		{
			dr_iTC_287_Spectra,
			(uint8_t []){EPD_287_BW,EPD_287_BWR,EPD_Empty},
			iTC_287Sp_IO_Config,
			iTC_287Sp_power_on,
			iTC_287Sp_initialize_driver,
			iTC_287Sp_Display_from_Ram,
			iTC_287Sp_Display_from_flash,
			NULL,
			NULL,
			iTC_287Sp_power_off,
			NULL
		},
#endif
#ifdef iTC_420_Spectra
		{
			dr_iTC_420_Spectra,
			(uint8_t []){EPD_420_BW,EPD_420_BWR,EPD_Empty},
			iTC_420Sp_IO_Config,
			iTC_420Sp_power_on,
			iTC_420Sp_initialize_driver,
			iTC_420Sp_Display_from_Ram,
			iTC_420Sp_Display_from_flash,
			NULL,
			NULL,
			iTC_420Sp_power_off,
			NULL
		},
#endif
#ifdef iTC_420_Aurora_Mb

		{
			dr_iTC_420_Aurora_Mb,
			(uint8_t []){EPD_420_BW,EPD_Empty},
			iTC_420Mb_IO_Config,
			iTC_420Mb_power_on,
			iTC_420Mb_initialize_driver,
			iTC_420Mb_Display_from_Ram,
			iTC_420Mb_Display_from_flash,
			iTC_420Mb_Display_PU_from_Ram,
			iTC_420Mb_Display_PU_From_Flash,
			iTC_420Mb_power_off,
			NULL
		},
#endif
#ifdef iTC_UC_Spectra
		{
			dr_iTC_UC_Spectra,
			(uint8_t []){EPD_287_BW,EPD_287_BWR,
			             EPD_271_BW,EPD_271_BWR,
			             EPD_266_BW,EPD_266_BWR,
			             EPD_213_BW,EPD_213_BWR,
			             EPD_154_BW,EPD_154_BWR,
			             EPD_Empty},
			iTC_UC8451cSp_IO_Config,
			iTC_UC8451cSp_power_on,
			iTC_UC8451cSp_initialize_driver,
			iTC_UC8451cSp_Display_from_Ram,
			iTC_UC8451cSp_Display_from_flash,
			NULL,
			NULL,
			iTC_UC8451cSp_power_off,
			iTC_UC8451cSp_SetColormode
		},
#endif

};

#endif
