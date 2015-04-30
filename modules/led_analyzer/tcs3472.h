/***************************************************************************
 *   Copyright (C) 2014 by Subhan Waizi                           		   *
 *                                     									   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
#include "i2c_routines.h"

// slave address
#define TCS_ADDRESS 0x29
#define TCS3472_ADDRESS_2 0x39

// registers to read
#define TCS3472_ENABLE_REG 0x00
#define TCS3472_ATIME_REG 0x01
#define TCS3472_WTIME_REG 0x03
#define TCS3472_AILTL_REG 0x04
#define TCS3472_AILTH_REG 0x05
#define TCS3472_AIHTL_REG 0x06
#define TCS3472_AIHTH_REG 0x07
#define TCS3472_PERS_REG 0x0C
#define TCS3472_CONFIG_REG 0x0D
#define TCS3472_CONTROL_REG 0x0F
#define TCS3472_ID_REG 0x12
#define TCS3472_STATUS_REG 0x13
#define TCS3472_CDATA_REG 0x14
#define TCS3472_CDATAH_REG 0x15
#define TCS3472_RDATA_REG 0x16
#define TCS3472_RDATAH_REG 0x17
#define TCS3472_GDATA_REG 0x18
#define TCS3472_GDATAH_REG 0x19
#define TCS3472_BDATA_REG 0x1A
#define TCS3472_BDATAH_REG 0x1B

// command register bits
#define TCS3472_COMMAND_BIT 0x80
#define TCS3472_AUTOINCR_BIT 0x20
#define TCS3472_SPECIAL_BIT 0x60
#define TCS3472_INTCLEAR_BIT 0x06

// enable register bits
#define TCS3472_AIEN_BIT 0x10
#define TCS3472_WEN_BIT 0x08
#define TCS3472_AEN_BIT 0x02
#define TCS3472_PON_BIT 0x01

// configuration register bits
#define TCS3472_WLONG_BIT 0x02

// ID register values
#define TCS3472_1_5_VALUE 0x14
#define TCS3472_3_7_VALUE 0x1D

// status register bits
#define TCS3472_AINT_BIT 0x10
#define TCS3472_AVALID_BIT 0x01


typedef enum
{
    TCS3472_GAIN_1X = 0x00,
    TCS3472_GAIN_4X = 0x01,
    TCS3472_GAIN_16X = 0x02,
    TCS3472_GAIN_60X = 0x03,
    TCS3472_GAIN_ERROR = 0xFF
}
tcs3472Gain_t;

typedef enum
{
    TCS3472_INTEGRATION_2_4ms 		 = 0xFF,
    TCS3472_INTEGRATION_24ms 		 = 0xF6,
    TCS3472_INTEGRATION_100ms 		 = 0xD6,
    TCS3472_INTEGRATION_200ms		 = 0xAD,
    TCS3472_INTEGRATION_154ms 		 = 0xC0,
    TCS3472_INTEGRATION_700ms        = 0x00
}
tcs3472Integration_t;

enum tcs_color_t
{
  RED       = 0x00,
  GREEN     = 0x01,
  BLUE      = 0x02,
  CLEAR     = 0x03
}
colors;

unsigned short int tcs_setIntegrationTime   (struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3472Integration_t integration);
unsigned short int tcs_setIntegrationTime_x (struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3472Integration_t integration, unsigned int uiX);

unsigned short int tcs_identify(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer);

unsigned short int tcs_setGain   (struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3472Gain_t gain);
unsigned short int tcs_setGain_x (struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3472Gain_t gain, unsigned int uiX); 

unsigned short int tcs_waitForData(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
unsigned short int tcs_rgbcInvalid(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
unsigned short int tcs_readColour(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* ausColourArray, enum tcs_color_t colour);
unsigned short int tcs_sleep(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
unsigned short int tcs_wakeUp(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
unsigned short int tcs_ON(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
unsigned short int tcs_exClear(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* ausClear, unsigned char* aucIntegrationtime);
unsigned short int tcs_clearInt(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
void               tcs_waitIntegrationtime(tcs3472Integration_t uiIntegrationtime);
unsigned short int tcs_getGain(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucGainSettings);
unsigned short int tcs_getIntegrationtime(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucInttimeSettings);
unsigned int 	   getGainDivisor(tcs3472Gain_t gain);


