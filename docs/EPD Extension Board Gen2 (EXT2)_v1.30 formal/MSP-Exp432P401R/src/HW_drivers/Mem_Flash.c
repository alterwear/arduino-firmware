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


#include <HW_drivers/Mem_Flash.h>

static void send_byte(uint8_t byte_value)
{
	EPD_spi_write(byte_value);
}
static uint8_t  get_byte(void)
{
	return EPD_spi_read(0);
}
/**
 * \brief Set Flash_CS pin to high and EPD_CS to low
 */
void Flash_cs_high(void)
{
	EPD_flash_cs_high();
	EPD_cs_low ();
}

/**
 * \brief Set EPD_CS to high and Flash_CS to low
 */
void Flash_cs_low(void)
{
	EPD_cs_high();
	EPD_flash_cs_low();
}

/**
 * \brief Send address to Flash
 *
 * \param flash_address The address
 */
static void send_flash_address(long flash_address)
{
	/** A23-A0 */
	send_byte( (flash_address >> 16) );
	send_byte( (flash_address >> 8) );
	send_byte( (flash_address));
}

/**
 * \brief Read status register
 *
 * \return Register status
 */
static uint8_t CMD_RDSR(void)
{
	uint8_t	gDataBuffer;

	// Chip select go low to start a flash command
	Flash_cs_low();

	// Send command
	send_byte( FLASH_CMD_RDSR );
	gDataBuffer = get_byte();

	// Chip select go high to end a flash command
	Flash_cs_high();

	return gDataBuffer;
}

/**
 * \brief Check if the flash is busy
 *
 * \return 1=busy, 0=not busy
 */
uint8_t IsFlashBusy( void )
{
	uint8_t	 gDataBuffer;

	gDataBuffer= CMD_RDSR();
	if( (gDataBuffer & FLASH_WIP_MASK)  == FLASH_WIP_MASK )
		return 0;
	else
		return 1;
}

/**
 * \brief Read Flash data into buffer
 *
 * \param flash_address The start address of Flash
 * \param target_buffer The target address of buffer will be read
 * \param byte_length The data length will be read
 */
static void flash_cmd_read( long flash_address, uint8_t *target_buffer, long byte_length )
{
	long index;
	//while( IsFlashBusy());
	/** Chip select go low to start a flash command */
	Flash_cs_low();


	/** Write READ command and address */
	send_byte( FLASH_CMD_FASTREAD );
	//send_byte( FLASH_CMD_READ );
	send_flash_address( flash_address );
	send_byte(0);//FLASH_CMD_FASTREAD

	/** Set a loop to read data into buffer */
	for( index=0; index < byte_length; index++ )
	{
		// Read one data byte at a time
		*(target_buffer + index) = get_byte();
	}

	/** Chip select go high to end a flash command */
	Flash_cs_high();
}

/**
 * \brief Check the flash memory of EPD extension board is existed or not in order
 *         to determine the board is connected
 * \return The Flash is existed
 */
uint8_t is_flash_existed(void)
{
	/*
	uint8_t	get_data_buffer=0;
	uint8_t check_times=3, flash_existed=0;
	EPD_spi_attach();
	while(check_times--) {
		Flash_cs_high();
		delay_ms(1);
		Flash_cs_low();
		delay_ms(1);
		if(epd_spi_write_ex( FLASH_CMD_RES )==1) {
			epd_spi_write_ex(0);
			epd_spi_write_ex(0);
			epd_spi_write_ex(0);
			get_data_buffer = get_byte();
		}
		Flash_cs_high();
		if(get_data_buffer==ElectronicID) {
			flash_existed=1;
			break;
		}
	};
	return flash_existed;
	*/
	return true;
}

/**
 * \brief Check if the flash is write enable
 *
 * \return 1=write enable, 0=not write enable
 */
static uint8_t checkWREN( void )
{
	uint8_t	 gDataBuffer;

	gDataBuffer= CMD_RDSR();
	if( (gDataBuffer & 0x02)  == 0x02 )
		return 1;
	else
		return 0;
}
/**
 * \brief Set flash write enable
 */
static void CMD_WREN( void )
{
	do
	{
		// Chip select go low to start a flash command
		Flash_cs_low();
		// Write Enable command = 0x06, Setting Write Enable Latch Bit
		send_byte( FLASH_CMD_WREN );

		// Chip select go high to end a flash command
		Flash_cs_high();
	}
	while(!checkWREN());
}

/**
 * \brief Write the data to flash
 *
 * \param flash_address 32 bit flash memory address
 * \param source_address The source address of buffer will be written
 * \param byte_length The data length will be read
 */
static void CMD_PP( long flash_address, uint8_t *source_address, uint8_t byte_length )
{
	long index;
	//while( IsFlashBusy());
	// Setting Write Enable Latch bit
	CMD_WREN();

	// Chip select go low to start a flash command
	Flash_cs_low();

	// Write Page Program command
	send_byte( FLASH_CMD_PP );
	send_flash_address( flash_address);

	// Set a loop to download whole page data into flash's buffer
	// Note: only last 256 byte will be programmed
	for( index=0; index < byte_length; index++ )
	{
		send_byte( *(source_address + index) );
	}

	// Chip select go high to end a flash command
	Flash_cs_high();
	//while( IsFlashBusy()) ;
}


/**
 * \brief Erase the data of the chosen sector (4KB) to be "1"
 *
 * \param flash_address 32 bit flash memory address
 */
void CMD_SE( long flash_address )
{
	//while( IsFlashBusy()) ;
	// Setting Write Enable Latch bit
	CMD_WREN();
	//while(IsFlashBusy());
	// Chip select go low to start a flash command
	Flash_cs_low();

	//Write Sector Erase command = 0x20;
	send_byte( FLASH_CMD_SE );

	send_flash_address( flash_address );

	// Chip select go high to end a flash command
	Flash_cs_high();
	//while(IsFlashBusy());
}

/**
 * \brief Erase all of the flash memory
 */
void CMD_CE(void)
{
	//while(IsFlashBusy());
	// Setting Write Enable Latch bit
	CMD_WREN();
	// Chip select go low to start a flash command
	Flash_cs_low();
	//Write Chip Erase command = 0x60;
	send_byte( FLASH_CMD_CE);
	// Chip select go high to end a flash command
	Flash_cs_high();
	//while( IsFlashBusy());

}

/**
 * \brief Read Flash data into buffer
 *
 * \param flash_address The start address of Flash
 * \param target_buffer The target address of buffer will be read
 * \param byte_length The data length will be read
 */
void read_flash(long flash_address,uint8_t *target_buffer, uint8_t byte_length)
{
	flash_cmd_read(flash_address,target_buffer,byte_length);
}

/**
 * \brief Write Flash data from buffer
 *
 * \param flash_address 32 bit flash memory address
 * \param source_address The source address of buffer will be written
 * \param byte_length The data length will be read
 */
void write_flash(long flash_address,uint8_t *source_address, uint8_t byte_length)
{
	CMD_PP(flash_address,source_address,byte_length);

}
void erase_flash(long address,uint16_t sectorLen)
{

	uint8_t i;
	if(sectorLen>=256)
	{
		CMD_CE();
		delay_ms(700);
	}
	else
	{
		for(i=0; i<sectorLen; i++)
		{
			CMD_SE(address); //Erase data of the chosen sector
			address+=_flash_sector_size; //4K
			delay_ms(45);
		}
	}
}

