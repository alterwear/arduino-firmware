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
*
* 3. The name of Atmel may not be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* 4. This software may only be redistributed and used in connection with an
*    Atmel microcontroller product.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
**/

// *** Please note the display with eTC_G1 COG is EOL since 2013 ***

#include <eTC_G1_Size_Aurora_Mb.h>

void eTC_G1Mb_dummy_line(void);
void eTC_G1Mb_nothing_frame (void);
void eTC_G1Mb_nothing_frame_19_26 (void);

/* Lookup table for 1.9" and 2.6" */
const uint8_t eTC_G1Mb_data_lookuptable[4][16]={
                        {0xAA,0xAB,0xAE,0xAF,0xBA,0xBB,0xBE,0xBF,0xEA,0xEB,0xEE,0xEF,0xFA,0xFB,0xFE,0xFF},
                        {0x00,0x02,0x08,0x0A,0x20,0x22,0x28,0x2A,0x80,0x82,0x88,0x8A,0xA0,0xA2,0xA8,0xAA},
                        {0x55,0x57,0x5D,0x5F,0x75,0x77,0x7D,0x7F,0xD5,0xD7,0xDD,0xDF,0xF5,0xF7,0xFD,0xFF},
                        {0xFF,0xFE,0xFB,0xFA,0xEF,0xEE,0xEB,0xEA,0xBF,0xBE,0xBB,0xBA,0xAF,0xAE,0xAB,0xAA}
                    };
const uint8_t eTC_G1Mb_scan_lookuptable[8]={0xc0,0x03,0x30,0x0c,0x0c,0x30,0x03,0xc0};     // 1.9",2.6" odd scan
static EPD_read_memory_handler _On_EPD_read_flash;
/**
 * \brief The COG parameters of different EPD size
 */
const  COG_parameters_t eTC_G1Mb_parameters[] = {
	{
		// FOR 1.44"
		EPD_144_BW,
		{0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0x00},
		0x03,
		(128/8),
		96,
		((((128+96)*2)/8)+1),
		0,
		480
	},
	{
		// For 2.0"
		EPD_200_BW,
		{0x00,0x00,0x00,0x00,0x01,0xFF,0xE0,0x00},
		0x03,
		(200/8),
		96,
		((((200+96)*2)/8)+1),
		0,
		480
	},
	{
		// For 2.7"
		EPD_271_BW,
		{0x00,0x00,0x00,0x7F,0xFF,0xFE,0x00,0x00},
		0x00,
		(264/8),
		176,
		((((264+176)*2)/8)+1),
		0,
		630
	},
	{
        // For 1.9"
		EPD_190_BW,
		{0x00,0x00,0x00,0x03,0xFC,0x00,0x00,0xFF},
		0x03,
		(144/8),
		128,
		((((144+128)*2)/8)+1),
		0,
		480
	},
	{
        // For 2.6"
		EPD_260_BW,
		{0x00,0x00,0x1F,0xE0,0x00,0x00,0x00,0xFF},
		0x03,
		(232/8),
		128,
		((((232+128)*2)/8)+1),
		0,
		630
	}
};

/* Temperature factor combines with stage time for each driving stage */
const uint16_t eTC_G1Mb_TF_table[][8] = {
	{(480*17),(480*12),(480*8),(480*4),(480*3),(480*2),(480*1),(480*0.7)}, // 1.44"
	{(480*17),(480*12),(480*8),(480*4),(480*3),(480*2),(480*1),(480*0.7)}, // 2.0"
	{(630*17),(630*12),(630*8),(630*4),(630*3),(630*2),(630*1),(630*0.7)}, // 2.7"
	{(480*17),(480*12),(480*8),(480*4),(480*3),(480*2),(480*1),(480*0.7)}, // 1.9"
	{(630*17),(630*12),(630*8),(630*4),(630*3),(630*2),(630*1),(630*0.7)}, // 2.6"
};
const uint8_t eTC_G1Mb_BORDER_TABLE[4]={0x00,0x00,0x00,0xAA};
const uint8_t eTC_G1Mb_SCAN_TABLE[4] = {0xC0,0x30,0x0C,0x03};
static eTC_G1Mb_line_data_t COG_Line;
static COG_parameters_t *cur_cog_param;
static uint16_t stage_time;
static uint16_t current_frame_time;
static uint8_t  cur_EPD_type_index=0;
uint16_t PartialUpdate_StageTime=240;//D_PartialUpdate_StageTime;

static uint8_t  *data_line_even;
static uint8_t  *data_line_odd;
static uint8_t  *data_line_scan;
static uint8_t  *data_line_border_byte;
uint8_t *previous_lin, *new_line;

void eTC_G1Mb_IO_Config(void)
{
		Config_Busy_Pin();
		Config_EPD_cs_Pin();
		Config_EPD_rst_Pin();
		Config_EPD_panelon_Pin();
		Config_EPD_discharge_Pin();
		Config_EPD_border_Pin();
		Config_EPD_flash_cs_Pin();
		Config_EPD_pwm_Pin();
		EPD_flash_cs_high();
		EPD_border_low();
		EPD_Vcc_turn_off();
		EPD_cs_low();
		EPD_rst_low();
		EPD_discharge_low();
}

// According to EPD size and temperature to get stage_time
static void eTC_G1Mb_temperature_factor(int8_t temperature) {
	if (temperature <= -10) {
		stage_time = eTC_G1Mb_TF_table[cur_EPD_type_index][0];
		} else if (-5 >= temperature && temperature > -10) {
		stage_time = eTC_G1Mb_TF_table[cur_EPD_type_index][1];
		} else if (5 >= temperature && temperature > -5) {
		stage_time = eTC_G1Mb_TF_table[cur_EPD_type_index][2];
		} else if (10 >= temperature && temperature > 5) {
		stage_time = eTC_G1Mb_TF_table[cur_EPD_type_index][3];
		} else if (15 >= temperature && temperature > 10) {
		stage_time = eTC_G1Mb_TF_table[cur_EPD_type_index][4];
		} else if (20 >= temperature && temperature > 15) {
		stage_time = eTC_G1Mb_TF_table[cur_EPD_type_index][5];
		} else if (40 >= temperature && temperature > 20) {
		stage_time = eTC_G1Mb_TF_table[cur_EPD_type_index][6];
	} else stage_time = eTC_G1Mb_TF_table[cur_EPD_type_index][7];
}


// Select the EPD size to get line data array for driving COG
void eTC_G1Mb_RegAssign_Select(void) {
	switch(cur_cog_param->Size_ID) {
		case EPD_144_BW:
		data_line_even = &COG_Line.line_data_by_size.eTC_G1Mb_144_line_data.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.eTC_G1Mb_144_line_data.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.eTC_G1Mb_144_line_data.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.eTC_G1Mb_144_line_data.border_byte;
		break;
		case EPD_200_BW:
		data_line_even = &COG_Line.line_data_by_size.eTC_G1Mb_200_line_data.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.eTC_G1Mb_200_line_data.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.eTC_G1Mb_200_line_data.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.eTC_G1Mb_200_line_data.dummy_data;
		break;
		case EPD_271_BW:
		data_line_even = &COG_Line.line_data_by_size.eTC_G1Mb_270_line_data.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.eTC_G1Mb_270_line_data.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.eTC_G1Mb_270_line_data.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.eTC_G1Mb_270_line_data.dummy_data;
		break;
        case EPD_190_BW:
		data_line_even = &COG_Line.line_data_by_size.eTC_G1Mb_190_line_data.scan_even[0];
		data_line_odd  = &COG_Line.line_data_by_size.eTC_G1Mb_190_line_data.scan_odd[0];
		data_line_scan = &COG_Line.line_data_by_size.eTC_G1Mb_190_line_data.data[0];
        data_line_border_byte = &COG_Line.line_data_by_size.eTC_G1Mb_190_line_data.border_byte;
		break;
        case EPD_260_BW:
		data_line_even = &COG_Line.line_data_by_size.eTC_G1Mb_260_line_data.scan_even[0];
		data_line_odd  = &COG_Line.line_data_by_size.eTC_G1Mb_260_line_data.scan_odd[0];
		data_line_scan = &COG_Line.line_data_by_size.eTC_G1Mb_260_line_data.data[0];
        data_line_border_byte = &COG_Line.line_data_by_size.eTC_G1Mb_260_line_data.border_byte;
		break;
	}
    *data_line_border_byte=0;
}

uint8_t eTC_G1Mb_GetSizeIndex(uint8_t EPD_type_index)
{
	uint8_t cnt=ArrayLength(eTC_G1Mb_parameters);
	uint8_t i;
	for(i=0;i<cnt;i++)
	{
		if(eTC_G1Mb_parameters[i].Size_ID==(EPD_SIZE_t)EPD_type_index)
		{
			cur_cog_param=(COG_parameters_t *)&eTC_G1Mb_parameters[i];
			break;
		}
	}
	if(i>=cnt)return 0;
	else return i;
}

// Power on COG Driver
void eTC_G1Mb_power_on (uint8_t EPD_type_index,int8_t temperature) {

    cur_EPD_type_index=eTC_G1Mb_GetSizeIndex(EPD_type_index);
	/* Initial state */
	EPD_discharge_low();
	EPD_rst_low();
	EPD_cs_low();
	    

	PWM_run(5); //The PWM signal starts toggling
	EPD_Vcc_turn_on();
	EPD_spi_attach();
	PWM_run(10);
	EPD_cs_high(); // /CS=1
	EPD_border_high(); //BORDER=1
	EPD_rst_high(); // /RESET=1
	PWM_run(5);
	EPD_rst_low(); // /RESET=0
	PWM_run(5);
	EPD_rst_high(); // /RESET=1
	PWM_run(5);
    // Sense temperature to determine Temperature Factor
	eTC_G1Mb_temperature_factor(temperature);
}

// Initialize COG Driver
uint8_t eTC_G1Mb_initialize_driver (OperationMode_t operationmode) {
	uint8_t SendBuffer[2];
	uint16_t i;

	// Empty the Line buffer
	for (i = 0; i <= LINE_BUFFER_DATA_SIZE; i ++) {
		COG_Line.uint8[i] = 0x00;
	}
	// Determine the EPD size for driving COG
	eTC_G1Mb_RegAssign_Select();

	
	i = 0;
	while (EPD_IsBusy()) {
		if((i++) >= 0x0FFF) return ERROR_BUSY;
	}
	// Channel select
	EPD_Gx_spi_send (0x01, (uint8_t *)&cur_cog_param->channel_select, 8);

	// DC/DC frequency setting
	EPD_Gx_spi_send_byte (0x06, 0xFF);

	// High power mode OSC setting
	EPD_Gx_spi_send_byte (0x07, 0x9D);

	// Disable ADC
	EPD_Gx_spi_send_byte (0x08, 0x00);

	// Set Vcom level 0xD0
	SendBuffer[0] = 0xD0;
	SendBuffer[1] = 0x00;
	EPD_Gx_spi_send (0x09, SendBuffer, 2);

	// Gate and source voltage level
	EPD_Gx_spi_send_byte (0x04,cur_cog_param->voltage_level);
	PWM_run(5);

	// Driver latch on (cancel register noise)
	EPD_Gx_spi_send_byte(0x03, 0x01);

	// Driver latch off
	EPD_Gx_spi_send_byte(0x03, 0x00);

    // Start charge pump positive V VGH & VDH on
   	EPD_Gx_spi_send_byte (0x05, 0x01);
    EPD_delay_ms (10);

    // Start charge pump positive V VGH & VDH off
   	EPD_Gx_spi_send_byte (0x05, 0x00);
    EPD_delay_ms (5);

    PWM_run(30);

    // Set charge pump Vcom_Driver to ON
    EPD_Gx_spi_send_byte(0x05, 0x0F);
    EPD_delay_ms(240);

	// Output enable to disable
	EPD_Gx_spi_send_byte(0x02, 0x24);

	return RES_OK;
}



/**
 * \brief The Global Update driving stages for getting Odd/Even data and writing the data
 * from memory array to COG
 *
 * \note
 * - One dot/pixel is comprised of 2 bits which are White(10), Black(11) or Nothing(01 or 00).
 *   The image data bytes must be divided into Odd and Even bytes.
 * - For 1.44", 2" and 2.7", the line data flow is half_Data-Scan-half_Data
 *
 * \param image_ptr The pointer of memory that stores image that will send to COG
 * \param stage_no The assigned stage number that will proceed
 */
static void eTC_G1Mb_GU_Handle(uint8_t *image_prt,long image_data_address,uint8_t stage_no) {
	/* x for horizontal_size loop, y for vertical_size loop, which are EPD pixel size */
	uint16_t x,y,k;
	uint8_t	temp_byte; // Temporary storage for image data check
	uint8_t *backup_image_prt; // Backup image address pointer
	long original_image_address;
    uint8_t byte_array[COG_line_Max_Size];
	original_image_address=image_data_address;
	backup_image_prt = image_prt;
	current_frame_time = cur_cog_param->frame_time_offset;
	/* Start a system SysTick timer to ensure the same duration of each stage  */
	start_EPD_timer();

	/* Do while total time of frames exceed stage time
	* Per frame */
	do {
		image_prt=backup_image_prt;
        image_data_address=original_image_address;
		/* Per data line (vertical size) */
		for (y = 0; y < cur_cog_param->vertical_size; y++) {
			/* Set charge pump voltage level reduce voltage shift */
			EPD_Gx_spi_send_byte (0x04, cur_cog_param->voltage_level);

			k = cur_cog_param->horizontal_size-1;
            if(_On_EPD_read_flash!=NULL) {
				_On_EPD_read_flash(image_data_address,(uint8_t *)&byte_array,
				cur_cog_param->horizontal_size);
                image_prt=&byte_array[0];
			}
			for (x = 0; x < cur_cog_param->horizontal_size; x++) {
				temp_byte =*image_prt++;
				switch(stage_no) {
					case Stage1: // Compensate, Inverse previous image
					/* Example at stage 1 to get Even and Odd data
					* +---------+----+----+----+----+----+----+----+----+
					* |         |bit7|bit6|bit5|bit4|bit3|bit2|bit1|bit0|
					* |temp_byte+----+----+----+----+----+----+----+----+
					* |         |  1 |  0 |  1 |  1 |  0 |  1 |  0 |  0 |
					* +---------+----+----+----+----+----+----+----+----+ */
					data_line_odd[x]     = ((temp_byte & 0x80) ? eTC_G1Mb_BLACK3  : eTC_G1Mb_WHITE3); // eTC_G1Mb_BLACK3 = 0xC0 = 1100 0000
					data_line_odd[x]    |= ((temp_byte & 0x20) ? eTC_G1Mb_BLACK2  : eTC_G1Mb_WHITE2); // eTC_G1Mb_BLACK2 = 0x30 = 0011 0000
					data_line_odd[x]    |= ((temp_byte & 0x08) ? eTC_G1Mb_BLACK1  : eTC_G1Mb_WHITE1); // eTC_G1Mb_WHITE1 = 0x08 = 0000 1000
					data_line_odd[x]    |= ((temp_byte & 0x02) ? eTC_G1Mb_BLACK0  : eTC_G1Mb_WHITE0); // eTC_G1Mb_WHITE0 = 0x02 = 0000 0010
					/* data_line_odd[x] = 1100 0000 | 0011 0000 | 0000 1000 | 0000 0010 = 1111 1010
					* See Even data row at the table below*/

					data_line_even[k]    = ((temp_byte & 0x01) ? eTC_G1Mb_BLACK3  : eTC_G1Mb_WHITE3); // eTC_G1Mb_WHITE3 = 0x80 = 1000 0000
					data_line_even[k]   |= ((temp_byte & 0x04) ? eTC_G1Mb_BLACK2  : eTC_G1Mb_WHITE2); // eTC_G1Mb_BLACK2 = 0x30 = 0011 0000
					data_line_even[k]   |= ((temp_byte & 0x10) ? eTC_G1Mb_BLACK1  : eTC_G1Mb_WHITE1); // eTC_G1Mb_BLACK1 = 0x0C = 0000 1100
					data_line_even[k--] |= ((temp_byte & 0x40) ? eTC_G1Mb_BLACK0  : eTC_G1Mb_WHITE0); // eTC_G1Mb_WHITE0 = 0x02 = 0000 0010
					/* data_line_even[k] = 1000 0000 | 0011 0000 | 0000 1100 | 0000 0010 = 1011 1110
					* See Odd data row at the table below
					* +---------+----+----+----+----+----+----+----+----+
					* |         |bit7|bit6|bit5|bit4|bit3|bit2|bit1|bit0|
					* |temp_byte+----+----+----+----+----+----+----+----+
					* |         |  1 |  0 |  1 |  1 |  0 |  1 |  0 |  0 |
					* +---------+----+----+----+----+----+----+----+----+
					* | Color   |  W |  B |  W |  W |  B |  W |  B |  B | W=White, B=Black, N=Nothing
					* +---------+----+----+----+----+----+----+----+----+
					* | Stage 1 |  B |  W |  B |  B |  W |  B |  W |  W | Inverse
					* +---------+----+----+----+----+----+----+----+----+
					* | Input   | 11 | 10 | 11 | 11 | 10 | 11 | 10 | 10 | W=10, B=11, N=01
					* +---------+----+----+----+----+----+----+----+----+
					* |Odd data | 11 |    | 11 |    | 10 |    | 10 |    | = 1111 1010
					* +---------+----+----+----+----+----+----+----+----+
					* |Even data|    | 10 |    | 11 |    | 11 |    | 10 | = 1011 1110
					* +---------+----+----+----+----+----+----+----+----+ */
						break;
					case Stage2: // White
					data_line_odd[x]     = ((temp_byte & 0x80) ?  eTC_G1Mb_WHITE3 : eTC_G1Mb_NOTHING3);
					data_line_odd[x]    |= ((temp_byte & 0x20) ?  eTC_G1Mb_WHITE2 : eTC_G1Mb_NOTHING2);
					data_line_odd[x]    |= ((temp_byte & 0x08) ?  eTC_G1Mb_WHITE1 : eTC_G1Mb_NOTHING1);
					data_line_odd[x]    |= ((temp_byte & 0x02) ?  eTC_G1Mb_WHITE0 : eTC_G1Mb_NOTHING0);

					data_line_even[k]    = ((temp_byte & 0x01) ?  eTC_G1Mb_WHITE3 : eTC_G1Mb_NOTHING3);
					data_line_even[k]   |= ((temp_byte & 0x04) ?  eTC_G1Mb_WHITE2 : eTC_G1Mb_NOTHING2);
					data_line_even[k]   |= ((temp_byte & 0x10) ?  eTC_G1Mb_WHITE1 : eTC_G1Mb_NOTHING1);
					data_line_even[k--] |= ((temp_byte & 0x40) ?  eTC_G1Mb_WHITE0 : eTC_G1Mb_NOTHING0);
						break;
					case Stage3: // Inverse new image
					data_line_odd[x]     = ((temp_byte & 0x80) ? eTC_G1Mb_BLACK3  : eTC_G1Mb_NOTHING3);
					data_line_odd[x]    |= ((temp_byte & 0x20) ? eTC_G1Mb_BLACK2  : eTC_G1Mb_NOTHING2);
					data_line_odd[x]    |= ((temp_byte & 0x08) ? eTC_G1Mb_BLACK1  : eTC_G1Mb_NOTHING1);
					data_line_odd[x]    |= ((temp_byte & 0x02) ? eTC_G1Mb_BLACK0  : eTC_G1Mb_NOTHING0);

					data_line_even[k]    = ((temp_byte & 0x01) ? eTC_G1Mb_BLACK3  : eTC_G1Mb_NOTHING3);
					data_line_even[k]   |= ((temp_byte & 0x04) ? eTC_G1Mb_BLACK2  : eTC_G1Mb_NOTHING2);
					data_line_even[k]   |= ((temp_byte & 0x10) ? eTC_G1Mb_BLACK1  : eTC_G1Mb_NOTHING1);
					data_line_even[k--] |= ((temp_byte & 0x40) ? eTC_G1Mb_BLACK0  : eTC_G1Mb_NOTHING0);
						break;
					case Stage4: // New image
					data_line_odd[x]     = ((temp_byte & 0x80) ? eTC_G1Mb_WHITE3  : eTC_G1Mb_BLACK3 );
					data_line_odd[x]    |= ((temp_byte & 0x20) ? eTC_G1Mb_WHITE2  : eTC_G1Mb_BLACK2 );
					data_line_odd[x]    |= ((temp_byte & 0x08) ? eTC_G1Mb_WHITE1  : eTC_G1Mb_BLACK1 );
					data_line_odd[x]    |= ((temp_byte & 0x02) ? eTC_G1Mb_WHITE0  : eTC_G1Mb_BLACK0 );

					data_line_even[k]    = ((temp_byte & 0x01) ? eTC_G1Mb_WHITE3  : eTC_G1Mb_BLACK3 );
					data_line_even[k]   |= ((temp_byte & 0x04) ? eTC_G1Mb_WHITE2  : eTC_G1Mb_BLACK2 );
					data_line_even[k]   |= ((temp_byte & 0x10) ? eTC_G1Mb_WHITE1  : eTC_G1Mb_BLACK1 );
					data_line_even[k--] |= ((temp_byte & 0x40) ? eTC_G1Mb_WHITE0  : eTC_G1Mb_BLACK0 );
						break;
				}

			}
            image_data_address+=cur_cog_param->horizontal_size;
			/* Scan byte shift per data line */
			data_line_scan[(y>>2)] = eTC_G1Mb_SCAN_TABLE[(y%4)];

			/* Sending data */
			EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8,
			cur_cog_param->data_line_size);

			/* Turn on Output Enable */
			EPD_Gx_spi_send_byte (0x02, 0x2F);

			data_line_scan[(y>>2)]=0;
		}
		/* Count the frame time with offset */
		current_frame_time=(uint16_t)get_EPD_time_tick()+
			cur_cog_param->frame_time_offset;
	} while (stage_time>current_frame_time);

	/* Do while the SysTick timer fulfills the stage time */
	while(stage_time>get_EPD_time_tick());

	/* Stop system timer */
	stop_EPD_timer();
}



/**
 * \brief The driving stages for getting Odd/Even data and writing the data
 * from memory array to COG for 1.9" and 2.6"
 * \note For 1.9" and 2.6", the line data flow is half_Scan-Data-half_Scan
 *
 * \param image_ptr The pointer of memory that stores image that will send to COG
 * \param stage_no The assigned stage number that will proceed
 */
static void eTC_G1Mb_GU_Handle_19_26(uint8_t *image_prt,long image_data_address,uint8_t stage_no) {
	/* x for horizontal_size loop, y for vertical_size loop, which are EPD pixel size */
	uint16_t x,y;
    uint8_t cnt;
    uint8_t s_index,b_index,line_len;
    long original_image_address; // Backup original image address
    uint8_t	temp_byte; // Temporary storage for image data check
	uint8_t *backup_image_prt; // Backup image address pointer
	uint8_t byte_array[COG_line_Max_Size];
	backup_image_prt = image_prt;
    original_image_address=image_data_address;
	current_frame_time = cur_cog_param->frame_time_offset;
	/* Start a system SysTick timer to ensure the same duration of each stage  */
	start_EPD_timer();
    line_len=(cur_cog_param->vertical_size/8)-1;
	/* Do while total time of frames exceed stage time
	* Per frame */
	do {
		image_prt=backup_image_prt;
        image_data_address=original_image_address;
        *data_line_border_byte=eTC_G1Mb_BORDER_TABLE[stage_no];
		/* Per data line (vertical size) */
		for (y = 0; y < cur_cog_param->vertical_size; y++) {
          if(_On_EPD_read_flash!=NULL) {
				_On_EPD_read_flash(image_data_address,(uint8_t *)&byte_array,
				cur_cog_param->horizontal_size);
                image_prt=&byte_array[0];
			}
			/* Set charge pump voltage level reduce voltage shift */
			EPD_Gx_spi_send_byte (0x04, cur_cog_param->voltage_level);
            cnt=0;
			for (x = 0; x < cur_cog_param->horizontal_size; x++) {
				temp_byte =*image_prt++;
				data_line_scan[cnt++]=eTC_G1Mb_data_lookuptable[stage_no][((temp_byte>>4) &0x0f)];
				data_line_scan[(cnt++)]=eTC_G1Mb_data_lookuptable[stage_no][(temp_byte&0x0f)];
			}
            s_index=y>>3;
            b_index=(y%8);
            if((y%2)==0)
            {//odd
                data_line_odd[s_index]=eTC_G1Mb_scan_lookuptable[b_index];
            }
            else
            {//even
                data_line_even[line_len-s_index]=eTC_G1Mb_scan_lookuptable[b_index];
            }
            image_data_address+=cur_cog_param->horizontal_size;
            /* Sending data */
			EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8,
				cur_cog_param->data_line_size);

			/* Turn on Output Enable */
			EPD_Gx_spi_send_byte (0x02, 0x2F);

			data_line_odd[s_index]=0;
            data_line_even[line_len-s_index]=0;
		}
		/* Count the frame time with offset */
		current_frame_time=(uint16_t)get_EPD_time_tick()+
			cur_cog_param->frame_time_offset;
	} while (stage_time>current_frame_time);

	/* Do while the SysTick timer fulfills the stage time */
	while(stage_time>get_EPD_time_tick());

	/* Stop system timer */
	stop_EPD_timer();
}

/**
 * \brief Write image data from memory array to the EPD
 * \note
 * - There are 4 stages to complete an image update on EPD.
 * - The same stage time for Each of the 4 stages.
 *
 * \param previous_image_ptr The pointer of memory that stores previous image
 * \param new_image_ptr The pointer of memory that stores new image
 */
uint8_t eTC_G1Mb_Display_from_Ram (uint8_t *previous_image_ptr,
		uint8_t *new_image_ptr) {
    _On_EPD_read_flash=NULL;
    if(cur_cog_param->Size_ID ==EPD_190_BW || cur_cog_param->Size_ID ==EPD_260_BW)
    {
    	eTC_G1Mb_GU_Handle_19_26(previous_image_ptr,ADDRESS_NULL,Stage1);
    	eTC_G1Mb_GU_Handle_19_26(previous_image_ptr,ADDRESS_NULL,Stage2);
    	eTC_G1Mb_GU_Handle_19_26(new_image_ptr,ADDRESS_NULL,Stage3);
    	eTC_G1Mb_GU_Handle_19_26(new_image_ptr,ADDRESS_NULL,Stage4);
    }
    else
    {
        eTC_G1Mb_GU_Handle(previous_image_ptr,ADDRESS_NULL,Stage1);
    	eTC_G1Mb_GU_Handle(previous_image_ptr,ADDRESS_NULL,Stage2);
    	eTC_G1Mb_GU_Handle(new_image_ptr,ADDRESS_NULL,Stage3);
    	eTC_G1Mb_GU_Handle(new_image_ptr,ADDRESS_NULL,Stage4);
    }
    return RES_OK;
}

/**
 * \brief Write image data from Flash memory to the EPD
 *
 * \param previous_image_flash_address The previous image address of flash memory
 * \param new_image_flash_address The new image address of flash memory
 * \param On_EPD_read_flash Developer needs to create an external function to read flash
 */
uint8_t eTC_G1Mb_Display_from_flash (long previous_image_flash_address,
     long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash) {
	_On_EPD_read_flash=On_EPD_read_flash;
    if(cur_cog_param->Size_ID ==EPD_190_BW || cur_cog_param->Size_ID ==EPD_260_BW)
    {
        eTC_G1Mb_GU_Handle_19_26(NULL,previous_image_flash_address,Stage1);
        eTC_G1Mb_GU_Handle_19_26(NULL,previous_image_flash_address,Stage2);
        eTC_G1Mb_GU_Handle_19_26(NULL,new_image_flash_address,Stage3);
        eTC_G1Mb_GU_Handle_19_26(NULL,new_image_flash_address,Stage4);
    }
    else
    {
        eTC_G1Mb_GU_Handle(NULL,previous_image_flash_address,Stage1);
        eTC_G1Mb_GU_Handle(NULL,previous_image_flash_address,Stage2);
        eTC_G1Mb_GU_Handle(NULL,new_image_flash_address,Stage3);
        eTC_G1Mb_GU_Handle(NULL,new_image_flash_address,Stage4);
    }
    return RES_OK;
}

/**
 * \brief The Partial Update driving stages for getting Odd/Even data and writing the data
 * from memory array to COG
 *
 * \note
 * - This function for 1.9" and 2.6"
 * - Just run the last stage (of 4 stages of global update) to update image immediately.
 * - If the new data byte is same as previous data byte, send ¡§Nothing¡¨ data byte which
 *   means the data byte on EPD won¡¦t be changed.
 * ¡V If the new data byte is different from the previous data byte, send the new data byte.
 * - For more details on the Partial Update driving method, please contact techsupport@pervasivedisplays.com *
 */
static void eTC_G1Mb_Handle_PU_19_26(uint8_t *previous_image_ptr, uint8_t *new_image_ptr,
												  long previous_image_address, long new_image_address)
{
	/* x for horizontal_size loop, y for vertical_size loop, which are EPD pixel size */
	uint16_t x,y;
    uint8_t cnt;
    uint8_t s_index,b_index,line_len;
    uint8_t *r_previous_image_ptr, *r_new_image_ptr;
    uint8_t old_byte,new_byte;
	long address_offset=0;
	/* Start a system SysTick timer to ensure the same duration of each stage  */
	start_EPD_timer();
    line_len=(cur_cog_param->vertical_size/8)-1;
	/* Do while total time of frames exceed stage time
	* Per frame */
	do {
		address_offset=0;
		r_previous_image_ptr=previous_image_ptr;
		r_new_image_ptr=new_image_ptr;
        *data_line_border_byte=BORDER_BYTE_W;
		/* Per data line (vertical size) */
		for (y = 0; y < cur_cog_param->vertical_size; y++) {
			/* Set charge pump voltage level reduce voltage shift */
			EPD_Gx_spi_send_byte (0x04, cur_cog_param->voltage_level);
             if(_On_EPD_read_flash!=NULL)
    		 {
    			_On_EPD_read_flash((previous_image_address + address_offset),
    									previous_lin,
    									cur_cog_param->horizontal_size);
    			r_previous_image_ptr=previous_lin;

    			_On_EPD_read_flash((new_image_address + address_offset),
    					new_line,
    					cur_cog_param->horizontal_size);
    			r_new_image_ptr=new_line;

    		 }
            cnt=0;
			for (x = 0; x < cur_cog_param->horizontal_size; x++)
            {				
               old_byte = *r_previous_image_ptr++;
			   new_byte = *r_new_image_ptr++;

			   data_line_scan[cnt]  	 = ((old_byte ^ new_byte) & 0x80) ? ((new_byte & 0x80) ? eTC_G1Mb_WHITE3 : eTC_G1Mb_BLACK3) : eTC_G1Mb_NOTHING3;
			   data_line_scan[cnt] 	    |= ((old_byte ^ new_byte) & 0x40) ? ((new_byte & 0x40) ? eTC_G1Mb_WHITE2 : eTC_G1Mb_BLACK2) : eTC_G1Mb_NOTHING2;
			   data_line_scan[cnt] 	    |= ((old_byte ^ new_byte) & 0x20) ? ((new_byte & 0x20) ? eTC_G1Mb_WHITE1 : eTC_G1Mb_BLACK1) : eTC_G1Mb_NOTHING1;
			   data_line_scan[cnt++] 	|= ((old_byte ^ new_byte) & 0x10) ? ((new_byte & 0x10) ? eTC_G1Mb_WHITE0 : eTC_G1Mb_BLACK0) : eTC_G1Mb_NOTHING0;

			   data_line_scan[cnt] 	     = ((old_byte ^ new_byte) & 0x08) ? ((new_byte & 0x08) ? eTC_G1Mb_WHITE3 : eTC_G1Mb_BLACK3) : eTC_G1Mb_NOTHING3;
			   data_line_scan[cnt] 	    |= ((old_byte ^ new_byte) & 0x04) ? ((new_byte & 0x04) ? eTC_G1Mb_WHITE2 : eTC_G1Mb_BLACK2) : eTC_G1Mb_NOTHING2;
			   data_line_scan[cnt] 	    |= ((old_byte ^ new_byte) & 0x02) ? ((new_byte & 0x02) ? eTC_G1Mb_WHITE1 : eTC_G1Mb_BLACK1) : eTC_G1Mb_NOTHING1;
			   data_line_scan[cnt++] 	|= ((old_byte ^ new_byte) & 0x01) ? ((new_byte & 0x01) ? eTC_G1Mb_WHITE0 : eTC_G1Mb_BLACK0) : eTC_G1Mb_NOTHING0;              
			}
            if(_On_EPD_read_flash!=NULL) address_offset += cur_cog_param->horizontal_size;
            s_index=y>>3;
            b_index=(y%8);
            if((y%2)==0)
            {//odd
                data_line_odd[s_index]=eTC_G1Mb_scan_lookuptable[b_index];
            }
            else
            {//even
                data_line_even[line_len-s_index]=eTC_G1Mb_scan_lookuptable[b_index];
            }

            /* Sending data */
			EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8,
				cur_cog_param->data_line_size);

			/* Turn on Output Enable */
			EPD_Gx_spi_send_byte (0x02, 0x2F);

			data_line_odd[s_index]=0;
            data_line_even[line_len-s_index]=0;
		}

	} while (PartialUpdate_StageTime>get_EPD_time_tick());

	/* Do while the SysTick timer fulfills the stage time */
	while(PartialUpdate_StageTime>get_EPD_time_tick());

	/* Stop system timer */
	stop_EPD_timer();
}

/**
 * \brief The Partial Update driving stages for getting Odd/Even data and writing the data
 * from memory array to COG
 *
 * \note
 * - This function for 1.44", 2" and 2.7"
 * - Just run the last stage (of 4 stages of global update) to update image immediately.
 * - If the new data byte is same as previous data byte, send ¡§Nothing¡¨ data byte which
 *   means the data byte on EPD won¡¦t be changed.
 * ¡V If the new data byte is different from the previous data byte, send the new data byte.
 * - For more details on the Partial Update driving method, please contact techsupport@pervasivedisplays.com *
 */
static void eTC_G1Mb_Handle_PU(uint8_t *previous_image_ptr, uint8_t *new_image_ptr,
										long previous_image_address, long new_image_address){
	/** x for horizontal_size loop, y for vertical_size loop, which are EPD pixel size */
	uint16_t x, y, k;
	uint8_t *r_previous_image_ptr, *r_new_image_ptr;
	uint8_t old_byte,new_byte;
    long address_offset=0;
	/** Get line data array of EPD size */
	eTC_G1Mb_RegAssign_Select();

	/* Start a system SysTick timer to ensure the same duration of each stage  */
	start_EPD_timer();
	/* Do while total time of frames exceed stage time
	 * Per frame */
	do {
        address_offset=0;
		r_previous_image_ptr=previous_image_ptr;
	    r_new_image_ptr=new_image_ptr;
		/* Per data line (vertical size) */
		for (y = 0; y < cur_cog_param->vertical_size; y++) {
			/* Set charge pump voltage level reduce voltage shift */
			EPD_Gx_spi_send_byte(0x04, cur_cog_param->voltage_level);
           if(_On_EPD_read_flash!=NULL)
			 {
				_On_EPD_read_flash((previous_image_address + address_offset),
				 				   previous_lin,
				 				   cur_cog_param->horizontal_size);
				r_previous_image_ptr=previous_lin;

				_On_EPD_read_flash((new_image_address + address_offset),
						           new_line,
						           cur_cog_param->horizontal_size);
				r_new_image_ptr=new_line;
			}
			k = cur_cog_param->horizontal_size - 1;
			/** Per dot/pixel */
			for (x = 0; x < cur_cog_param->horizontal_size;	x++)
			{             
               old_byte = *r_previous_image_ptr++;
               new_byte = *r_new_image_ptr++;
			   data_line_odd[x]  	 = ((old_byte ^ new_byte) & 0x80) ? ((new_byte & 0x80) ? eTC_G1Mb_WHITE3 : eTC_G1Mb_BLACK3) : eTC_G1Mb_NOTHING3;
			   data_line_odd[x] 	|= ((old_byte ^ new_byte) & 0x20) ? ((new_byte & 0x20) ? eTC_G1Mb_WHITE2 : eTC_G1Mb_BLACK2) : eTC_G1Mb_NOTHING2;
			   data_line_odd[x] 	|= ((old_byte ^ new_byte) & 0x08) ? ((new_byte & 0x08) ? eTC_G1Mb_WHITE1 : eTC_G1Mb_BLACK1) : eTC_G1Mb_NOTHING1;
			   data_line_odd[x] 	|= ((old_byte ^ new_byte) & 0x02) ? ((new_byte & 0x02) ? eTC_G1Mb_WHITE0 : eTC_G1Mb_BLACK0) : eTC_G1Mb_NOTHING0;

			   data_line_even[k] 	 = ((old_byte ^ new_byte) & 0x01) ? ((new_byte & 0x01) ? eTC_G1Mb_WHITE3 : eTC_G1Mb_BLACK3) : eTC_G1Mb_NOTHING3;
			   data_line_even[k] 	|= ((old_byte ^ new_byte) & 0x04) ? ((new_byte & 0x04) ? eTC_G1Mb_WHITE2 : eTC_G1Mb_BLACK2) : eTC_G1Mb_NOTHING2;
			   data_line_even[k] 	|= ((old_byte ^ new_byte) & 0x10) ? ((new_byte & 0x10) ? eTC_G1Mb_WHITE1 : eTC_G1Mb_BLACK1) : eTC_G1Mb_NOTHING1;
			   data_line_even[k--] 	|= ((old_byte ^ new_byte) & 0x40) ? ((new_byte & 0x40) ? eTC_G1Mb_WHITE0 : eTC_G1Mb_BLACK0) : eTC_G1Mb_NOTHING0;
			 }
            if(_On_EPD_read_flash!=NULL) address_offset += cur_cog_param->horizontal_size;
			/* Scan byte shift per data line */
			data_line_scan[(y >> 2)] = eTC_G1Mb_SCAN_TABLE[(y % 4)];

			/* Sending data */
			EPD_Gx_spi_send(0x0A, (uint8_t *) &COG_Line.uint8,
					cur_cog_param->data_line_size);

			/* Turn on Output Enable */
			EPD_Gx_spi_send_byte(0x02, 0x2F);

			data_line_scan[(y >> 2)] = 0;
		}

	} while ( PartialUpdate_StageTime> get_EPD_time_tick());

	/* Do while the SysTick timer fulfills the stage time */
	while (PartialUpdate_StageTime > get_EPD_time_tick());


	/* Stop system timer */
	stop_EPD_timer();
}


// Complete partial update cycle by giving from the pointer of memory or the address of memory
void eTC_G1Mb_PU_Collection(uint8_t *previous_image_ptr, uint8_t *new_image_ptr,
										  long previous_image_address, long new_image_address,
										  EPD_read_memory_handler On_EPD_read_flash)
{
	uint8_t bk_previous_lin[COG_line_Max_Size], bk_new_line[COG_line_Max_Size];
	_On_EPD_read_flash = On_EPD_read_flash;
	previous_lin=&bk_previous_lin[0];
	new_line=&bk_new_line[0];
	EPD_Gx_spi_send_byte(0x09,0xC2);	//Vcom level

    if(cur_cog_param->Size_ID ==EPD_190_BW || cur_cog_param->Size_ID ==EPD_260_BW)
    {
    	 eTC_G1Mb_Handle_PU_19_26(previous_image_ptr,new_image_ptr,previous_image_address,new_image_address);
    	 eTC_G1Mb_nothing_frame_19_26();
    }
    else
    {
    	 eTC_G1Mb_Handle_PU(previous_image_ptr,new_image_ptr,previous_image_address,new_image_address);
    	 eTC_G1Mb_nothing_frame();
    	 eTC_G1Mb_dummy_line();
    }
}

// Partial update cycle by giving from the pointer of memory
void eTC_G1Mb_Display_PU_from_Ram(uint8_t *previous_image_ptr, uint8_t *new_image_ptr,uint16_t PU_Time)
{
		PartialUpdate_StageTime=PU_Time;
    	eTC_G1Mb_PU_Collection(previous_image_ptr,
							 new_image_ptr,
							 ADDRESS_NULL,
							 ADDRESS_NULL,
							 NULL);
}

// Partial update cycle by giving from the address of memory
void eTC_G1Mb_Display_PU_From_Flash(long previous_image_address, long new_image_address,EPD_read_memory_handler On_EPD_read_flash,uint16_t PU_Time)
{
		PartialUpdate_StageTime=PU_Time;
    	eTC_G1Mb_PU_Collection(NULL,
						 NULL,
						 previous_image_address,
						 new_image_address,
						 On_EPD_read_flash);
}

/**
 * Write Nothing Frame to COG
 * \note A frame that all D(x,y) are N(01). 0101=0x55=eTC_G1Mb_NOTHING */
void eTC_G1Mb_nothing_frame (void) {
	uint16_t i;
	for (i = 0; i <  cur_cog_param->horizontal_size; i++) {
		data_line_even[i]=eTC_G1Mb_NOTHING;
		data_line_odd[i]=eTC_G1Mb_NOTHING;
	}

	*data_line_border_byte=eTC_G1Mb_NOTHING;
	for (i = 0; i < cur_cog_param->vertical_size; i++) {
		/* Set charge pump voltage level reduce voltage shift */
		EPD_Gx_spi_send_byte (0x04, cur_cog_param->voltage_level);

		/* Scan byte shift per data line */
		data_line_scan[(i>>2)]=eTC_G1Mb_SCAN_TABLE[(i%4)];

		/* Sending data */
		EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, cur_cog_param->data_line_size);

		/* Turn on Output Enable */
		EPD_Gx_spi_send_byte (0x02, 0x2F);

		data_line_scan[(i>>2)]=0;
	}
}

// Write Nothing Frame to COG for 1.9" and 2.6"
void eTC_G1Mb_nothing_frame_19_26 (void) {
	uint16_t i;
    uint8_t s_index,b_index,line_len;
	for (i = 0; i <  (cur_cog_param->horizontal_size*2); i++) {
		data_line_scan[i]=eTC_G1Mb_NOTHING;
	}
    line_len=(cur_cog_param->vertical_size/8)-1;
	for (i = 0; i < cur_cog_param->vertical_size; i++) {
		/* Set charge pump voltage level reduce voltage shift */
		EPD_Gx_spi_send_byte (0x04, cur_cog_param->voltage_level);
        s_index=i>>3;
        b_index=(i%8);
        if((i%2)==0)
        {//odd
            data_line_odd[s_index]=eTC_G1Mb_scan_lookuptable[b_index];
        }
        else
        {//even
            data_line_even[line_len-s_index]=eTC_G1Mb_scan_lookuptable[b_index];
        }

		/* Sending data */
		EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, cur_cog_param->data_line_size);

		/* Turn on Output Enable */
		EPD_Gx_spi_send_byte (0x02, 0x2F);

        data_line_odd[s_index]=0;
        data_line_even[line_len-s_index]=0;

	}
}

// BORDER Dummy Line for 1.44" and 2"
void eTC_G1Mb_border_dummy_line(void)
{
	uint16_t i;
	for (i = 0; i < cur_cog_param->horizontal_size; i++) {
		data_line_even[i]=eTC_G1Mb_NOTHING;
		data_line_odd[i]=eTC_G1Mb_NOTHING;
	}
	for (i = 0; i < (cur_cog_param->vertical_size/4); i++) {
		data_line_scan[i]=0x00;
	}
	if(cur_cog_param->Size_ID==EPD_144_BW) COG_Line.line_data_by_size.eTC_G1Mb_144_line_data.border_byte=0xaa;
    else if(cur_cog_param->Size_ID==EPD_200_BW) COG_Line.line_data_by_size.eTC_G1Mb_200_line_data.dummy_data=0xaa;
	EPD_Gx_spi_send_byte (0x04, 0x03);

	// SPI (0x0a, line data....)
	EPD_Gx_spi_send (0x0a, (uint8_t *)&COG_Line.uint8, cur_cog_param->data_line_size);

	// SPI (0x02, 0x2F)
	EPD_Gx_spi_send_byte (0x02, 0x2F);
}

/**
 * \brief Write Dummy Line to COG
 * \note A line that all Scan Bytes are 0x00 */
void eTC_G1Mb_dummy_line(void) {
	uint8_t	i;
    for (i = 0; i <= cur_cog_param->data_line_size; i ++) {
		COG_Line.uint8[i] = 0x00;
	}

	/* Set charge pump voltage level reduce voltage shift */
	EPD_Gx_spi_send_byte (0x04, cur_cog_param->voltage_level);

	/* Sending data */
	EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, cur_cog_param->data_line_size);

	/* Turn on Output Enable */
	EPD_Gx_spi_send_byte (0x02, 0x2F);
}

// Power Off COG Driver
uint8_t eTC_G1Mb_power_off (void) {

    if(cur_cog_param->Size_ID ==EPD_190_BW || cur_cog_param->Size_ID ==EPD_260_BW)
	{		//Internal border control
	    eTC_G1Mb_nothing_frame_19_26();
	    eTC_G1Mb_dummy_line();
	    EPD_delay_ms (25);
    }
    else     // 1.44", 2" and 2.7"
    {
    	 eTC_G1Mb_nothing_frame ();
    	 if(cur_cog_param->Size_ID==EPD_144_BW || cur_cog_param->Size_ID==EPD_200_BW) {
    	  EPD_border_high();
    	  eTC_G1Mb_border_dummy_line();	//Internal border control
    	  EPD_delay_ms (200);
    	 }
    	 else {
    	  eTC_G1Mb_dummy_line();
    	  EPD_delay_ms (25);
    	  EPD_border_low();
    	  EPD_delay_ms (200);
    	  EPD_border_high();	//external border control circuit
    	 }


    }
    // Latch reset turn on
    EPD_Gx_spi_send_byte (0x03, 0x01);

    //Power off chargepump Vcom
    EPD_Gx_spi_send_byte (0x05, 0x03);

    EPD_delay_ms (40);

    // Power off charge negative voltage
    EPD_Gx_spi_send_byte (0x05, 0x01);

    EPD_delay_ms (40);

    //Turn off all chargepumps
    EPD_Gx_spi_send_byte (0x05, 0x00);

    EPD_delay_ms (40);

    // Discharge internal
    EPD_Gx_spi_send_byte (0x04, 0xc0);
    EPD_delay_ms (15);

    // Discharge internal
    EPD_Gx_spi_send_byte (0x04, 0xd0);
    EPD_delay_ms (25);

    // Discharge internal
    EPD_Gx_spi_send_byte (0x04, 0xdc);

    EPD_delay_ms (10);

    // Discharge internal
    EPD_Gx_spi_send_byte (0x04, 0xfc);

    EPD_delay_ms (5);

    // Discharge internal
    EPD_Gx_spi_send_byte (0x04, 0x00);

    EPD_delay_ms (5);

    // Turn off osc
    EPD_Gx_spi_send_byte (0x07, 0x0D);

    // Set power and signals = 0
    EPD_rst_low ();
    EPD_spi_detach ();
    EPD_cs_low ();
    EPD_Vcc_turn_off ();
    EPD_border_low();

    EPD_delay_ms (10);

    // External discharge = 1
    EPD_discharge_high ();
    EPD_delay_ms (150);

    // External discharge = 0
    EPD_discharge_low ();

    return RES_OK;
   }

