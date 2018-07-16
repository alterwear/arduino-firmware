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

#include <eTC_G2_Size_Aurora_Ma.h>

//#include <Extern_Board_HW_Driver.h>

#define USELastFrame        
// The COG parameters of different EPD size
const  COG_parameters_t eTC_G2Ma_parameters[] = {
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
/* \brief EPD Waveform parameters for Aurora Ma at Room Temperature
 * \note the parameters of waveform table below is different from the G2 COG document due to
 *       use block size is easier to achieve than accurate block time for different MCU.
 *       The approach is also working. */
const eTC_G2Ma_RT_WT_t eTC_G2Ma_RT_WT[][3]  = {
	{// FOR 1.44"
		{//50>= T 「 40
			4,				//stage1_frame1
			12,				//stage1_block1
			2,				//stage1_step1
			155,			//stage2_t1
			155,			//stage2_t2
			4,				//stage2_cycle
			4,				//stage3_frame3
			12,				//stage3_block3
			2				//stage3_step3
		}
		,{//40>= T 「 10
			4,				//stage1_frame1
			12,				//stage1_block1
			2,				//stage1_step1
			155,			//stage2_t1
			155,			//stage2_t2
			4,				//stage2_cycle
			4,				//stage3_frame3
			12,				//stage3_block3
			2				//stage3_step3
		}
		,{//10>= T 「 0
			4,				//stage1_frame1
			12,				//stage1_block1
			2,				//stage1_step1
			155,			//stage2_t1
			155,			//stage2_t2
			4,				//stage2_cycle
			4,				//stage3_frame3
			12,				//stage3_block3
			2				//stage3_step3
		}
	},
	{// For 2.0"
		{//50>= T 「 40
			4,				//stage1_frame1
			16,				//stage1_block1
			2,				//stage1_step1
			155,			//stage2_t1
			155,			//stage2_t2
			4,				//stage2_cycle
			4,				//stage3_frame3
			16,				//stage3_block3
			2				//stage3_step3
		}
		,{//40>= T 「 10
			2,				//stage1_frame1
			16,				//stage1_block1
			2,				//stage1_step1
			155,			//stage2_t1
			155,			//stage2_t2
			4,				//stage2_cycle
			2,				//stage3_frame3
			16,				//stage3_block3
			2				//stage3_step3
		}
		,{//10>= T 「 0
			3,				//stage1_frame1
			16,				//stage1_block1
			2,				//stage1_step1
			310,			//stage2_t1
			310,			//stage2_t2
			4,				//stage2_cycle
			3,				//stage3_frame3
			16,				//stage3_block3
			2				//stage3_step3
		}
	},
	{// For 2.7"
		{//50>= T 「 40
			4,				//stage1_frame1
			8,				//stage1_block1
			1,				//stage1_step1
			155,			//stage2_t1
			155,			//stage2_t2
			4,				//stage2_cycle
			4,				//stage3_frame3
			8,				//stage3_block3
			1				//stage3_step3
		}
		,{//40>= T 「 10
			2,				//stage1_frame1
			8,				//stage1_block1
			1,				//stage1_step1
			155,			//stage2_t1
			155,			//stage2_t2
			4,				//stage2_cycle
			2,				//stage3_frame3
			8,				//stage3_block3
			1,				//stage3_step3
		}
		,{//10>= T 「 0
			3,				//stage1_frame1
			8,				//stage1_block1
			1,				//stage1_step1
			310,			//stage2_t1
			310,			//stage2_t2
			4,				//stage2_cycle
			3,				//stage3_frame3
			8,				//stage3_block3
			1				//stage3_step3
		}
	}
};

static COG_parameters_t *cur_cog_param;
static eTC_G2Ma_line_data_t COG_Line;
const uint8_t   eTC_G2Ma_SCAN_TABLE[4] = {0xC0,0x30,0x0C,0x03};
	
static eTC_G2Ma_RT_WT_t *action__Waveform_param;
static eTC_G2Ma_Block_WT_t S_epd_AuroraMa;
static EPD_read_memory_handler _On_EPD_read_flash;
static uint8_t  *data_line_even;
static uint8_t  *data_line_odd;
static uint8_t  *data_line_scan;
static uint8_t  *data_line_border_byte;
static uint8_t cur_EPD_type_index=0;

void eTC_G2Ma_IO_Config(void)
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
/**
 * \brief According to EPD size and temperature to get stage_time
 * \param EPD_type_index The defined EPD size
 */
static void eTC_G2Ma_temperature_factor(int8_t temperature) {
        if (50 >= temperature  && temperature > 40){
			action__Waveform_param=(eTC_G2Ma_RT_WT_t *)&eTC_G2Ma_RT_WT[cur_EPD_type_index][0];
		}else if (40 >= temperature  && temperature > 10){
			action__Waveform_param=(eTC_G2Ma_RT_WT_t *)&eTC_G2Ma_RT_WT[cur_EPD_type_index][1];
		}else if (10 >= temperature  && temperature > 0){
			action__Waveform_param=(eTC_G2Ma_RT_WT_t *)&eTC_G2Ma_RT_WT[cur_EPD_type_index][2];
		}else action__Waveform_param=(eTC_G2Ma_RT_WT_t *)&eTC_G2Ma_RT_WT[cur_EPD_type_index][1]; //Default
}

/**
 * \brief Select the EPD size to get line data array for driving COG
 *
 * \param EPD_type_index The defined EPD size
 */
void eTC_G2Ma_RegAssign_Select(void) {
	switch(cur_cog_param->Size_ID) {
		case EPD_144_BW:
		data_line_even = &COG_Line.line_data_by_size.eTC_G2Ma_144_line_data.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.eTC_G2Ma_144_line_data.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.eTC_G2Ma_144_line_data.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.eTC_G2Ma_144_line_data.border_byte;
		break;
		case EPD_200_BW:
		data_line_even = &COG_Line.line_data_by_size.eTC_G2Ma_200_line_data.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.eTC_G2Ma_200_line_data.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.eTC_G2Ma_200_line_data.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.eTC_G2Ma_200_line_data.border_byte;
		break;
		case EPD_271_BW:
		data_line_even = &COG_Line.line_data_by_size.eTC_G2Ma_270_line_data.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.eTC_G2Ma_270_line_data.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.eTC_G2Ma_270_line_data.scan[0];
		data_line_border_byte = &COG_Line.line_data_by_size.eTC_G2Ma_270_line_data.border_byte;
		break;
	}
}

uint8_t eTC_G2Ma_GetSizeIndex(uint8_t EPD_type_index)
{
	uint8_t cnt=ArrayLength(eTC_G2Ma_parameters);
	uint8_t i;
	for(i=0;i<cnt;i++)
	{
		if(eTC_G2Ma_parameters[i].Size_ID==(EPD_SIZE_t)EPD_type_index)
		{
			cur_cog_param=(COG_parameters_t *)&eTC_G2Ma_parameters[i];
			break;
		}
	}
	if(i>=cnt)return 0;
	else return i;
}

// Power on COG Driver
void eTC_G2Ma_power_on (uint8_t EPD_type_index,int8_t temperature) {
	cur_EPD_type_index=eTC_G2Ma_GetSizeIndex(EPD_type_index);
	/* Initial state */
	EPD_Vcc_turn_on(); //Vcc and Vdd >= 2.7V	
	EPD_cs_high();
	EPD_spi_attach();
	EPD_border_high();
	EPD_rst_high();
	EPD_delay_ms(5);
	EPD_rst_low();
	EPD_delay_ms(5);
	EPD_rst_high();
	EPD_delay_ms(5);
	// Sense temperature to determine Temperature Factor
	eTC_G2Ma_temperature_factor(temperature);
}


// Initialize COG Driver
uint8_t eTC_G2Ma_initialize_driver (OperationMode_t operationmode) {
	
	uint16_t i;
	// Empty the Line buffer
	for (i = 0; i <= LINE_BUFFER_DATA_SIZE; i ++) {
		COG_Line.uint8[i] = 0x00;
	}
	// Determine the EPD size for driving COG
	eTC_G2Ma_RegAssign_Select();

	i = 0;
	
	while (EPD_IsBusy()) {
		if((i++) >= 0x0FFF) return ERROR_BUSY;
	}
	
	//Check COG ID
	if((EPD_Gx_spi_rid() & 0x0F)!=0x02) return ERROR_COG_ID;

	//Disable OE
	EPD_Gx_spi_send_byte(0x02,0x40);	

	//Check Breakage
	if((EPD_Gx_spi_r(0x0F,0x00) & 0x80) != 0x80) return ERROR_BREAKAGE;
	
	//Power Saving Mode
 	EPD_Gx_spi_send_byte(0x0B, 0x02);

	//Channel Select
	EPD_Gx_spi_send (0x01, (uint8_t *)&cur_cog_param->channel_select, 8);

	//High Power Mode Osc Setting
	EPD_Gx_spi_send_byte(0x07,0xD1);

	//Power Setting
	EPD_Gx_spi_send_byte(0x08,0x02);

	//Set Vcom level
	EPD_Gx_spi_send_byte(0x09,0xC2);

	//Power Setting
	EPD_Gx_spi_send_byte(0x04,0x03);

	//Driver latch on
	EPD_Gx_spi_send_byte(0x03,0x01);

	//Driver latch off
	EPD_Gx_spi_send_byte(0x03,0x00);

	EPD_delay_ms(5);

	//Chargepump Start
	i=0;
	do {
		//Start chargepump positive V
		//VGH & VDH on
		EPD_Gx_spi_send_byte(0x05,0x01);

		EPD_delay_ms(240);

		//Start chargepump neg voltage
		//VGL & VDL on
		EPD_Gx_spi_send_byte(0x05,0x03);

		EPD_delay_ms(40);

		//Set chargepump
		//Vcom_Driver to ON
		//Vcom_Driver on
		EPD_Gx_spi_send_byte(0x05,0x0F);

		EPD_delay_ms(40);

		//Check DC/DC
		if((EPD_Gx_spi_r(0x0F,0x00) & 0x40) == 0x40)
		{
			//Output enable to disable
			EPD_Gx_spi_send_byte(0x02,0x06);
			break;
		}

	}while((i++) != 4);

	if(i>=4) return ERROR_CHARGEPUMP;
	else return RES_OK;
}

// Initialize the parameters of Block type stage
void eTC_G2Ma_BL_init(
				uint8_t block_size,uint8_t step_size,
				uint8_t frame_cycle)
{
	S_epd_AuroraMa.frame_y0 = 0;
	S_epd_AuroraMa.frame_y1 = 176;
	S_epd_AuroraMa.block_y0 = 0;
	S_epd_AuroraMa.block_y1 = 0;
	S_epd_AuroraMa.step_y0 = 0;
	S_epd_AuroraMa.step_y1 = 0;
	S_epd_AuroraMa.block_size = action__Waveform_param->stage1_block1;
	S_epd_AuroraMa.step_size =action__Waveform_param->stage1_step1;
	S_epd_AuroraMa.frame_cycle = action__Waveform_param->stage1_frame1;
	S_epd_AuroraMa.number_of_steps = (cur_cog_param->vertical_size / S_epd_AuroraMa.step_size) + (action__Waveform_param->stage1_block1 / action__Waveform_param->stage1_step1) -1;
	
}

// For Frame type waveform to update all black/white pattern
static inline void eTC_G2Ma_BL_same_data_frame ( uint8_t bwdata, uint32_t work_time) {
	int16_t i;
	for (i = 0; i <  cur_cog_param->horizontal_size; i++) {
		data_line_even[i]=bwdata;
		data_line_odd[i]=bwdata;
	}
	start_EPD_timer();
	do 
	{	
		for (i= (cur_cog_param->vertical_size-1); i>=0 ; i--) {
			
			/* Scan byte shift per data line */
			data_line_scan[(i>>2)]=eTC_G2Ma_SCAN_TABLE[(i%4)];
			
			/* Sending data */
			EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, cur_cog_param->data_line_size);
		 
			/* Turn on Output Enable */
			EPD_Gx_spi_send_byte (0x02, 0x07);
		
			data_line_scan[(i>>2)]=0;
			
		}
	} while (get_EPD_time_tick()<(work_time));
		/* Stop system timer */
		stop_EPD_timer();
}

/**
 * Write nothing Line to COG
 * \note A line whose all Scan Bytes are 0x00
 */
void eTC_G2Ma_BL_nothing_line(void) {
	uint16_t i;
	for (i = 0; i <  cur_cog_param->horizontal_size; i++) {
		data_line_even[i]	=	eTC_G2Ma_NOTHING;
		data_line_odd[i]	=	eTC_G2Ma_NOTHING;
	}
}


/**
 * Get line data of Stage 1 and 3
 *
 * \note
 * - One dot/pixel is comprised of 2 bits which are White(10), Black(11) or Nothing(01).
 *   The image data bytes must be divided into Odd and Even bytes.
 * - The COG driver uses a buffer to write one line of data (FIFO) - interlaced
 *   It's different order from COG_G1
 *   Odd byte {D(199,y),D(197,y), D(195,y), D(193,y)}, ... ,{D(7,y),D(5,y),D(3,y), D(1,y)}
 *   Scan byte {S(96), S(95)...}
 *   Odd byte  {D(2,y),D(4,y), D(6,y), D(8,y)}, ... ,{D(194,y),D(196,y),D(198,y), D(200,y)}
 * - For more details on the driving stages, please refer to the COG G2 document Section 5.
 *
 * \param image_ptr The pointer of memory that stores image that will send to COG
 * \param stage_no The assigned stage number that will proceed
 */

void eTC_G2Ma_BL_read_line_data_handle(uint8_t *image_prt,uint8_t stage_no)
{
	int16_t x,k;
	uint8_t	temp_byte; // Temporary storage for image data check
	k=cur_cog_param->horizontal_size-1;
	for (x =0 ; x < cur_cog_param->horizontal_size ; x++) {
				temp_byte = *image_prt++;
				switch(stage_no) {
					case Stage1: // Inverse image
					/* Example at stage 1 to get Even and Odd data. It's different order from G1.
					* +---------+----+----+----+----+----+----+----+----+
					* |         |bit7|bit6|bit5|bit4|bit3|bit2|bit1|bit0|
					* |temp_byte+----+----+----+----+----+----+----+----+
					* |         |  1 |  0 |  1 |  1 |  0 |  1 |  0 |  0 |
					* +---------+----+----+----+----+----+----+----+----+ */
					data_line_odd[x]       = ((temp_byte & 0x40) ? eTC_G2Ma_BLACK3  : eTC_G2Ma_WHITE3); // eTC_G2Ma_WHITE3 = 0x80 = 1000 0000
					data_line_odd[x]      |= ((temp_byte & 0x10) ? eTC_G2Ma_BLACK2  : eTC_G2Ma_WHITE2); // eTC_G2Ma_BLACK2 = 0x30 = 0011 0000
					data_line_odd[x]      |= ((temp_byte & 0x04) ? eTC_G2Ma_BLACK1  : eTC_G2Ma_WHITE1); // eTC_G2Ma_BLACK1 = 0x0C = 0000 1100
					data_line_odd[x]	  |= ((temp_byte & 0x01) ? eTC_G2Ma_BLACK0  : eTC_G2Ma_WHITE0); // eTC_G2Ma_WHITE0 = 0x02 = 0000 0010
					/* data_line_odd[x] = 1000 0000 | 0011 0000 | 0000 1100 | 0000 0010 = 1011 1110 ==> 1011 1110
					* See Even data row at the table below*/
					
					data_line_even[k]    = ((temp_byte & 0x80) ? eTC_G2Ma_BLACK0  : eTC_G2Ma_WHITE0); // eTC_G2Ma_BLACK0 = 0x03 = 0000 0011
					data_line_even[k]   |= ((temp_byte & 0x20) ? eTC_G2Ma_BLACK1  : eTC_G2Ma_WHITE1); // eTC_G2Ma_BLACK1 = 0x0C = 0000 1100
					data_line_even[k]   |= ((temp_byte & 0x08) ? eTC_G2Ma_BLACK2  : eTC_G2Ma_WHITE2); // eTC_G2Ma_WHITE2 = 0x20 = 0010 0000
					data_line_even[k--] |= ((temp_byte & 0x02) ? eTC_G2Ma_BLACK3  : eTC_G2Ma_WHITE3); // eTC_G2Ma_WHITE3 = 0x80 = 1000 0000
					/* data_line_even[k] = 0000 0011 | 0000 1100 | 0010 0000 | 1000 0000 = 1010 1111 ==> 1111 1010
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
					* |Even data| 11 |    | 11 |    | 10 |    | 10 |    | = 1111 1010
					* +---------+----+----+----+----+----+----+----+----+
					* |Odd data |    | 10 |    | 11 |    | 11 |    | 10 | = 1011 1110
					* +---------+----+----+----+----+----+----+----+----+ */
					break;				
					case Stage3: // New image
						data_line_odd[x]		 = ((temp_byte & 0x40) ? eTC_G2Ma_WHITE3  : eTC_G2Ma_BLACK3 );
						data_line_odd[x]		|= ((temp_byte & 0x10) ? eTC_G2Ma_WHITE2  : eTC_G2Ma_BLACK2 );
						data_line_odd[x]		|= ((temp_byte & 0x04) ? eTC_G2Ma_WHITE1  : eTC_G2Ma_BLACK1 );
						data_line_odd[x]		|= ((temp_byte & 0x01) ? eTC_G2Ma_WHITE0  : eTC_G2Ma_BLACK0 );

						data_line_even[k]		 = ((temp_byte & 0x80) ? eTC_G2Ma_WHITE0  : eTC_G2Ma_BLACK0 );
						data_line_even[k]		|= ((temp_byte & 0x20) ? eTC_G2Ma_WHITE1  : eTC_G2Ma_BLACK1 );
						data_line_even[k]		|= ((temp_byte & 0x08) ? eTC_G2Ma_WHITE2  : eTC_G2Ma_BLACK2 );
						data_line_even[k--]		|= ((temp_byte & 0x02) ? eTC_G2Ma_WHITE3  : eTC_G2Ma_BLACK3 );
					break;
				}
		}	
}


/**
 * The base function to handle the driving stages for Frame and Block type
 *
 * \note
 * - There are 3 stages to complete an image update cycle on AuroraMa_G2 type EPD.
 * - For more details on the driving stages, please refer to the COG G2 document Section 5.4
 *
 * \param image_ptr The pointer of image array that stores image that will send to COG
 * \param image_data_address The address of memory that stores image
 * \param stage_no The assigned stage number that will proceed
 * \param lineoffset Line data offset
 */
void eTC_G2Ma_BL_handle_Base(uint8_t *image_prt,long image_data_address,
						uint8_t stage_no,uint8_t lineoffset)
{		
	int16_t cycle,m,i; //m=number of steps
	uint8_t isLastframe = 0;	//If it is the last frame to send Nothing at the fist scan line
	uint8_t isLastBlock=0;		//If the beginning line of block is in active range of EPD
	int16_t scanline_no=0;
#ifdef ISDebug
    uint32_t DetectTime=0;
    BlockTime=0;
#endif
	static uint8_t *action_block_prt;
	long action_block_address;
	uint8_t byte_array[LINE_BUFFER_DATA_SIZE];
	/** Stage 2: BLACK/WHITE image, Frame type */
	if(stage_no==Stage2)
	{
		for(i=0;i<action__Waveform_param->stage2_cycle;i++)
		{
			eTC_G2Ma_BL_same_data_frame (ALL_BLACK,action__Waveform_param->stage2_t1);
			eTC_G2Ma_BL_same_data_frame (ALL_WHITE,action__Waveform_param->stage2_t2);
		}
		return;
	}
	/** Stage 1 & 3, Block type */
	// The frame/block/step of Stage1 and Stage3 are default the same.
	eTC_G2Ma_BL_init(action__Waveform_param->stage1_block1,
				action__Waveform_param->stage1_step1,
				action__Waveform_param->stage1_frame1);
	 
	 /* Repeat number of frames */
   	 for (cycle = 0; cycle < (S_epd_AuroraMa.frame_cycle ); cycle++)
   	 {
		
	     if (cycle == (S_epd_AuroraMa.frame_cycle - 1)) isLastframe = 1;
		 
		 isLastBlock = 0;
		 S_epd_AuroraMa.step_y0 = 0;
		 S_epd_AuroraMa.step_y1 = S_epd_AuroraMa.step_size ;
		 S_epd_AuroraMa.block_y0 = 0;
		 S_epd_AuroraMa.block_y1 = 0;
		 /* Move number of steps */
	   	 for (m = 0; m < S_epd_AuroraMa.number_of_steps; m++)
	   	 {		   	
			 S_epd_AuroraMa.block_y1 += S_epd_AuroraMa.step_size;
			 S_epd_AuroraMa.block_y0 = S_epd_AuroraMa.block_y1 - S_epd_AuroraMa.block_size;
			/* reset block_y0=frame_y0 if block is not in active range of EPD */
		   	 if (S_epd_AuroraMa.block_y0 < S_epd_AuroraMa.frame_y0) S_epd_AuroraMa.block_y0 = S_epd_AuroraMa.frame_y0;
		
			/* if the beginning line of block is in active range of EPD */
			 if (S_epd_AuroraMa.block_y1 == S_epd_AuroraMa.block_size) isLastBlock = 1;
			 	
			 if(image_prt!=NULL)
			 {
				 action_block_prt=(image_prt+(int)(S_epd_AuroraMa.block_y0*lineoffset));
			 }
			 else if(_On_EPD_read_flash!=NULL)	//Read line data in range of block, read first
			 {
				action_block_address=image_data_address+(long)(S_epd_AuroraMa.block_y0*lineoffset);
				_On_EPD_read_flash(action_block_address,(uint8_t *)&byte_array,
									cur_cog_param->horizontal_size);
				action_block_prt=(uint8_t *)&byte_array;
			 }	
             else 
             {
                action_block_prt=(image_prt+(int)(S_epd_AuroraMa.block_y0*lineoffset)+1);
             }
#ifdef ISDebug             
              start_EPD_timer();
#endif	             
			/* Update line data */
		   	 for (i = S_epd_AuroraMa.block_y0; i < S_epd_AuroraMa.block_y1; i++)
		   	 {						
			     if (i >= cur_cog_param->vertical_size) break;
#ifdef USELastFrame
                  if (isLastframe &&
#else
                    if (
#endif
                    isLastBlock &&(i < (S_epd_AuroraMa.step_size + S_epd_AuroraMa.block_y0)))
                  {
					  eTC_G2Ma_BL_nothing_line();
				  }
				  else	 
				  {			  					 
					  eTC_G2Ma_BL_read_line_data_handle(action_block_prt,stage_no);
				  }
			   		
				if(_On_EPD_read_flash!=NULL)	//Read line data in range of block
				{
					action_block_address +=lineoffset;
					_On_EPD_read_flash(action_block_address,(uint8_t *)&byte_array,
					cur_cog_param->horizontal_size);
					action_block_prt=(uint8_t *)&byte_array;
				}
				else action_block_prt+=lineoffset;
					
				scanline_no= (cur_cog_param->vertical_size-1)-i;
					
				/* Scan byte shift per data line */
				data_line_scan[(scanline_no>>2)] = eTC_G2Ma_SCAN_TABLE[(scanline_no%4)];
				   
				/*  the border uses the internal signal control byte. */
				*data_line_border_byte=0x00;
					   
				/* Sending data */
				EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8,
				cur_cog_param->data_line_size);
				
					 
				/* Turn on Output Enable */
				EPD_Gx_spi_send_byte (0x02, 0x07);
					   
				data_line_scan[(scanline_no>>2)]=0;		
										
		   	 }	
#ifdef ISDebug           
	   	    DetectTime=get_EPD_time_tick();
            stop_EPD_timer();
            if(BlockTime<DetectTime) BlockTime=DetectTime;
#endif		             
             
	   	 }
		
    }	
}

/**
 * Write image data from memory array (image_data.h) to the EPD
 *
 * \param previous_image_ptr The pointer of memory that stores previous image
 * \param new_image_ptr The pointer of memory that stores new image
 */
uint8_t eTC_G2Ma_Display_from_Ram (uint8_t *previous_image_ptr,
		uint8_t *new_image_ptr) {
#ifdef ISDebug		
	totalTime=get_EPD_time_tick();
#endif
	_On_EPD_read_flash=0;
	eTC_G2Ma_BL_handle_Base(new_image_ptr,ADDRESS_NULL,Stage1,cur_cog_param->horizontal_size);
	eTC_G2Ma_BL_handle_Base(new_image_ptr,ADDRESS_NULL,Stage2,cur_cog_param->horizontal_size);
	eTC_G2Ma_BL_handle_Base(new_image_ptr,ADDRESS_NULL,Stage3,cur_cog_param->horizontal_size);
#ifdef ISDebug
    totalTime=get_EPD_time_tick()-totalTime;
#endif    
    return RES_OK;
}


/**
 * Write image data from Flash memory to the EPD
 * \note This function is additional added here for developer if the image data
 * is stored in Flash.
 *
 * \param previous_image_flash_address The start address of memory that stores previous image
 * \param new_image_flash_address The start address of memory that stores new image
 * \param On_EPD_read_flash Developer needs to create an external function to read flash
 */
uint8_t eTC_G2Ma_Display_from_flash (long previous_image_flash_address,
    long new_image_flash_address,EPD_read_memory_handler On_EPD_read_flash) {
		
	uint8_t line_len;
	line_len=cur_cog_param->horizontal_size;
	if(line_len==0) line_len=cur_cog_param->horizontal_size;
		
	_On_EPD_read_flash=On_EPD_read_flash;	
	eTC_G2Ma_BL_handle_Base(NULL,new_image_flash_address,Stage1,line_len);
	eTC_G2Ma_BL_handle_Base(NULL,new_image_flash_address,Stage2,line_len);
	eTC_G2Ma_BL_handle_Base(NULL,new_image_flash_address,Stage3,line_len);
	return RES_OK;
}


/**
 * Write Dummy Line to COG
 * \note A line whose all Scan Bytes are 0x00
 */
static inline void eTC_G2Ma_dummy_line(void) {
		uint8_t	i;
	for (i = 0; i < (cur_cog_param->vertical_size/8); i++) {
		switch(cur_cog_param->Size_ID) {
			case EPD_144_BW:
			COG_Line.line_data_by_size.eTC_G2Ma_144_line_data.scan[i]=0x00;
			break;
			case EPD_200_BW:
			COG_Line.line_data_by_size.eTC_G2Ma_200_line_data.scan[i]=0x00;
			break;
			case EPD_271_BW:
			COG_Line.line_data_by_size.eTC_G2Ma_270_line_data.scan[i]=0x00;
			break;
		}
	}
	/* Set charge pump voltage level reduce voltage shift */
	EPD_Gx_spi_send_byte (0x04, cur_cog_param->voltage_level);
	
	/* Sending data */
	EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, cur_cog_param->data_line_size);

	/* Turn on Output Enable */
	EPD_Gx_spi_send_byte (0x02, 0x07);
}


/**
* Write Border(Input) Dummy Line
* \note Set Border byte 0xFF to write Black and set 0xAA to write White
*/
static void eTC_G2Ma_border_dummy_line(void)
{
	uint16_t	i;
    for (i =0 ; i < cur_cog_param->horizontal_size ; i++)
    {
    	data_line_odd[i]=0x00;
        data_line_even[i]=0x00;
    }

    for (i = 0; i < (cur_cog_param->vertical_size/8); i++)
    {
        data_line_scan[i] =0x00;
    }

	*data_line_border_byte=BORDER_BYTE_W;
	//Write a Borde(B) Dummy Line
	EPD_Gx_spi_send (0x0a, (uint8_t *)&COG_Line.uint8, cur_cog_param->data_line_size);
	//Turn on OE
	EPD_Gx_spi_send_byte (0x02, 0x07);
}

/**
 * Write Nothing Frame to COG
 * \note A frame that all D(x,y) are N(01). 0101=0x55=eTC_G2Ma_NOTHING
 */
void eTC_G2Ma_nothing_frame (void) {
	uint16_t i;
	for (i = 0; i <  cur_cog_param->horizontal_size; i++) {
		data_line_even[i]=eTC_G2Ma_NOTHING;
		data_line_odd[i]=eTC_G2Ma_NOTHING;
	}

	for (i = 0; i < cur_cog_param->vertical_size; i++) {

		/* Scan byte shift per data line */
		data_line_scan[(i>>2)]=eTC_G2Ma_SCAN_TABLE[(i%4)];

		/* Sending data */
		EPD_Gx_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, cur_cog_param->data_line_size);

		/* Turn on Output Enable */
		EPD_Gx_spi_send_byte (0x02, 0x07);

		data_line_scan[(i>>2)]=0;
	}
}

// Power Off COG Driver
uint8_t eTC_G2Ma_power_off(void) {

	    eTC_G2Ma_nothing_frame();

		if(cur_cog_param->Size_ID==EPD_271_BW)
		{
			eTC_G2Ma_dummy_line();
			EPD_delay_ms (25);
			EPD_border_low();
			EPD_delay_ms (200);
			EPD_border_high();
		}
		else
		{
			eTC_G2Ma_border_dummy_line();
			EPD_delay_ms (200);
		}
		EPD_Gx_spi_send_byte (0x0B, 0x00);

		//Turn on Latch Reset
		EPD_Gx_spi_send_byte (0x03, 0x01);
		//Power off charge pump Vcom
		EPD_Gx_spi_send_byte (0x05, 0x03);
		//Power off charge pump neg voltage
		EPD_Gx_spi_send_byte (0x05, 0x01);
		EPD_delay_ms(150);
		EPD_Gx_spi_send_byte (0x04, 0x80);
		//Turn off all charge pump
		EPD_Gx_spi_send_byte (0x05, 0x00);

		//Turn off OSC
		EPD_Gx_spi_send_byte (0x07, 0x01);

		EPD_delay_ms(50);

		EPD_spi_detach ();
		EPD_border_low();
		EPD_Vcc_turn_off ();
		EPD_delay_ms (10);
		EPD_cs_low();
		EPD_rst_low();

		EPD_discharge_high ();
		EPD_delay_ms (150);
		EPD_discharge_low ();


	return RES_OK;
}

