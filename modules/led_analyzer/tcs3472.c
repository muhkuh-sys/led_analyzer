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
 
#include "tcs3472.h"


/* This function identifies the 16 sensors of a device 
   It will return an errormask which provides information about the sensors that failed
   
   return value ==0: everything ok 
   return value > 0: if bit0 is high -> first sensor identification failure 
					 if bit1 is high -> second sensor identification failure
					 and so on
					 */

unsigned short int tcs_identify(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer)
{
    unsigned int uiErrorcounter = 0;
    unsigned int uiSuccesscounter = 0;
	unsigned short int usErrorMask = 0;

    int i = 0;

    unsigned char aucTempbuffer[2] = {(TCS_ADDRESS<<1), TCS3471_ID_REG | TCS3471_COMMAND_BIT};
    unsigned char aucErrorbuffer[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer));
		
            for(i = 0; i<=15; i++)
            {
				/* 0x14 = ID for tcs3471        0x44 = ID for tcs3472 */
               if(aucReadbuffer[i] != (0x14) && aucReadbuffer[i] != 0x44)
               {
                    aucErrorbuffer[i] = i+1;
                    uiErrorcounter ++;
					usErrorMask |= (1<<i);
               }

               else uiSuccesscounter ++;

               if(uiSuccesscounter == 16)
               {
                   printf("Identification successful.\n");
                   return 0; // SUCCESFULL IDENTFICATION OF ALL SENSORS
               }
            }
			
        printf("Identification errors with following Sensors ...\n");
        for(i = 0; i<16; i++)
        {
            if(aucErrorbuffer[i] != 0xFF) printf("%d ", aucErrorbuffer[i]);
        }
        printf("\n");
        
		return usErrorMask;
		
}


/* This function turns the tcs3472 sensor on, in case it was sent to sleep before
   If function is called without the sensor being priorily sent to sleep this function does nothing 
   
   retVal == 0: everything ok
   retVal == 1: I2C-Functions failed
   */
unsigned short int tcs_ON(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
   unsigned char aucTempbuffer[3] = {(TCS_ADDRESS<<1), TCS3471_ENABLE_REG | TCS3471_COMMAND_BIT, TCS3471_AIEN_BIT | TCS3471_AEN_BIT
                                    | TCS3471_PON_BIT };
   if(i2c_write8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer)) <0) return 1;
   return 0;
}


/* Following 4 functions have to be set up properly to have a decent detection */

/* This function sets the integration time of all sensor, darker leds need longer integration times.
whereas brighter leds need shorter integration times 

retVal == 0: everything ok
retVal == 1: I2C-Functions failed 
*/
unsigned short int tcs_setIntegrationTime(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3471Integration_t uiIntegrationtime)
{
    unsigned char aucTempbuffer[3] = {(TCS_ADDRESS<<1), TCS3471_ATIME_REG | TCS3471_COMMAND_BIT, uiIntegrationtime};
    if(i2c_write8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer)) <0) return 1;

    return 0;
}

/* This function sets the integration time of one sensor given in uiX (ranges from 0 ... 15), darker leds need longer integration times.
whereas brighter leds need shorter integration times 

retVal == 0: everything ok
retVal == 1: I2C-Functions failed 

*/
unsigned short int tcs_setIntegrationTime_x(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3471Integration_t uiIntegrationtime, unsigned int uiX)
{
    unsigned char aucTempbuffer[3] = {(TCS_ADDRESS<<1), TCS3471_ATIME_REG | TCS3471_COMMAND_BIT, uiIntegrationtime};
    if(i2c_write8_x(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), uiX) <0) return 1;

    return 0;
}

/* this function sets the gain of all sensors
just like the integration time, darker leds need a higher gain setting and brighter leds can have a lower gain setting

retVal == 0: everything ok
retVal == 1: I2C-Functions failed 
*/
unsigned short int tcs_setGain(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3471Gain_t gain)
{
    unsigned char aucTempbuffer[3] = {(TCS_ADDRESS<<1), TCS3471_CONTROL_REG | TCS3471_COMMAND_BIT, gain};

    if(i2c_write8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer)) <0) return 1;
    return 0;
}

/* this function sets the gain of one sensor given in uiX (ranges from 0 ... 15)
just like the integration time, darker leds need a higher gain setting and brighter leds can have a lower gain setting

retVal == 0: everything ok
retVal == 1: I2C-Functions failed 
*/
unsigned short int tcs_setGain_x(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3471Gain_t gain, unsigned int uiX)
{
    unsigned char aucTempbuffer[3] = {(TCS_ADDRESS<<1), TCS3471_CONTROL_REG | TCS3471_COMMAND_BIT, gain};

    if(i2c_write8_x(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), uiX) <0) return 1;
    return 0;
}






/* This function checks the color validity of the 16 sensors per device
   It will return an errormask which provides information about the sensors that failed
   
   return value ==0: everything ok 
   return value > 0: if bit0 is high -> first sensor rgbc dataset failure 
					 if bit1 is high -> second sensor rgbc dataset failure
					 and so on
					 */
unsigned short int tcs_rgbcInvalid(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer)
{
    unsigned int uiErrorcounter = 0;
    unsigned int uiSuccesscounter = 0;
	
	unsigned short int usErrorMask = 0;
    int i = 0;

    unsigned char aucTempbuffer[2] = {(TCS_ADDRESS<<1), TCS3471_STATUS_REG | TCS3471_COMMAND_BIT};
    unsigned char aucErrorbuffer[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer));

            for(i = 0; i<=15; i++)
            {
               if((aucReadbuffer[i]&TCS3471_AVALID_BIT) != TCS3471_AVALID_BIT)
               {
                    aucErrorbuffer[i] = i+1;
                    uiErrorcounter ++;
					usErrorMask |= (1<<i);
               }
               else uiSuccesscounter ++;

               if(uiSuccesscounter == 16)
               {
                   printf("RGBC datasets valid.\n");
                   return 0; 
               }
            }
        printf("Invalid RGBC data with following Sensors ...\n");
        for(i = 0; i<16; i++)
        {
            if(aucErrorbuffer[i] != 0xFF) printf("%d ", aucErrorbuffer[i]);
        }
        printf("\n");
       			
		
		return usErrorMask;
		
}


unsigned short int tcs_waitForData(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer)
{
    unsigned int uiErrorcounter = 0;
    unsigned int uiSuccesscounter = 0;
	
	unsigned short int usErrorMask = 0;
    int i = 0;

    unsigned char aucTempbuffer[2] = {(TCS_ADDRESS<<1), TCS3471_STATUS_REG | TCS3471_COMMAND_BIT};
    unsigned char aucErrorbuffer[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer));

            for(i = 0; i<=15; i++)
            {
               if((aucReadbuffer[i]&TCS3471_AINT_BIT) != TCS3471_AINT_BIT)
               {
                    aucErrorbuffer[i] = i+1;
					usErrorMask  |= (1<<i);
                    uiErrorcounter ++;
               }
               else uiSuccesscounter ++;

               if(uiSuccesscounter == 16)
               {
                   printf("Conversions complete.\n");
                   return 0; 
               }
            }

        printf("Incomplete conversions with following Sensors ...\n");
        for(i = 0; i<16; i++)
        {
            if(aucErrorbuffer[i] != 0xFF) printf("%d ", aucErrorbuffer[i]);
        }
        printf("\n");
       			
		return usErrorMask;
		
}

/* Read 4 color values per sensor - RED; GREEN; BLUE; CLEAR 
   Color arrays will contain 16 elements corresponding to the 16 sensors of a device 
   
   retVal == 0: everything ok
   retVal == 1: I2C-Functions failed 
*/
unsigned short int tcs_readColour(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* ausColorArray, enum tcs_color_t color)
{
    unsigned char aucTempbuffer[2] = {(TCS_ADDRESS<<1), TCS3471_AUTOINCR_BIT | TCS3471_COMMAND_BIT};

    switch(color)
    {
        case RED:
            aucTempbuffer[1] |= TCS3471_RDATA_REG;
            break;
        case GREEN:
            aucTempbuffer[1] |= TCS3471_GDATA_REG;
            break;
        case BLUE:
            aucTempbuffer[1] |= TCS3471_BDATA_REG;
            break;
        case CLEAR:
            aucTempbuffer[1] |= TCS3471_CDATA_REG;
            break;
        default:
            printf("Unknown color ... \n");
            break;
    }

    if(i2c_read16(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), ausColorArray, 16)<0) return 1;
    return 0;

}


/* Send 16 color sensors into sleep state

retVal == 0: everything ok
retVal == 1: I2C-Functions failed 
*/

unsigned short int tcs_sleep(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
    unsigned char aucReadbuffer[16];
    unsigned char aucTempbuffer[2]  = {(TCS_ADDRESS<<1), TCS3471_COMMAND_BIT | TCS3471_ENABLE_REG};
    if(i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer))<0) return 1;
    unsigned char aucTempbuffer2[3] = {(TCS_ADDRESS<<1), TCS3471_COMMAND_BIT | TCS3471_ENABLE_REG,  aucReadbuffer[0] & ~(TCS3471_PON_BIT | TCS3471_AEN_BIT)};
    if(i2c_write8(ftdiA, ftdiB,  aucTempbuffer2, sizeof(aucTempbuffer2))<0) return 1;

    return 0;
}

/* Wake up 16 color sensors which were sent to sleep state before 

	retVal == 0: everything ok
	retVal == 1: I2C-Functions failed 
*/
unsigned short int tcs_wakeUp(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
    unsigned char aucReadbuffer[16];
    unsigned char aucTempbuffer[2]  = {(TCS_ADDRESS<<1), TCS3471_COMMAND_BIT | TCS3471_ENABLE_REG};
    if(i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer))<0) return 1;
    unsigned char aucTempbuffer2[3] = {(TCS_ADDRESS<<1), TCS3471_COMMAND_BIT | TCS3471_ENABLE_REG,  aucReadbuffer[0] | TCS3471_PON_BIT};
    if(i2c_write8(ftdiA, ftdiB,  aucTempbuffer2, sizeof(aucTempbuffer2))<0) return 1;

    return 0;
}

/* Check if the sensors' color values for clear channel were exceeded - this means we had an inappropriate gain / integration time setting

   return value ==0: everything ok 
   return value > 0: if bit0 is high -> first sensor exceeded maximum clear
					 if bit1 is high -> second sensor exceeded maximum clear
					 and so on
*/			 
unsigned short int tcs_exClear(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* ausClear, unsigned char* aucIntegrationtime)
{
    int i= 0;
    unsigned int uiSuccesscounter = 0;
    unsigned char aucErrorbuffer[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	unsigned short int usErrorMask = 0;
	
	
	
    for(i=0; i<16; i++)
    {
		
	//TODO: pass an integration time parameter which contains 16 different integration times
	// so each sensor can be checked for itself, as each sensor can have different integration time settings
        switch(aucIntegrationtime[i])
        {
            case TCS3471_INTEGRATION_2_4ms:
                if(ausClear[i] >= 1024)
                {
                    aucErrorbuffer[i] = i+1;
					usErrorMask |= (1<<i);
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_24ms:
                if(ausClear[i] >= 10240)
                {
                    aucErrorbuffer[i] = i+1;
					usErrorMask |= (1<<i);
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_100ms:
                if(ausClear[i] >= 43007)
                {
                    aucErrorbuffer[i] = i+1;
					usErrorMask |= (1<<i);
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_154ms:
                if(ausClear[i] >= 65535)
                {
                    aucErrorbuffer[i] = i+1;
					usErrorMask |= (1<<i);
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_200ms:
                if(ausClear[i] >= 65535)
                {
                    aucErrorbuffer[i] = i+1;
					usErrorMask |= (1<<i);
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_700ms:
                if(ausClear[i] >= 65535)
                {
                    aucErrorbuffer[i] = i+1;
					usErrorMask |= (1<<i);
                }               
			    else uiSuccesscounter++;
                break;
        }

        if(uiSuccesscounter ==16)
        {
            printf("All gain settings ok - no clear level exceedings.\n");
            return 0;
        }
		

    }

    i = 0;
    printf("Turn down gain for following Sensors ...\n");
    for(i; i<16; i++)
    {
       if(aucErrorbuffer[i] != 0xFF) printf("%d ", aucErrorbuffer[i]);
    }
    printf("\n");		
		
	return usErrorMask;
		
}


/* Clear the interrupt channel of all sensors 
	
	retVal == 0: everything ok
	retVal == 1: I2C-Functions failed 
	
*/
unsigned short int tcs_clearInt(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
    unsigned char aucTempbuffer[2]  = {(TCS_ADDRESS<<1), TCS3471_COMMAND_BIT | TCS3471_SPECIAL_BIT | TCS3471_INTCLEAR_BIT};

    if(i2c_write8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer))<0) return 1;
    return 0;

}

/* Wait the integration time needed by the sensor to make a color reading */
void tcs_waitIntegrationtime(tcs3471Integration_t uiIntegrationtime)
{
        switch(uiIntegrationtime)
        {
            case TCS3471_INTEGRATION_2_4ms:
                Sleep(3);
                break;

            case TCS3471_INTEGRATION_24ms:
                Sleep(24);
                break;

            case TCS3471_INTEGRATION_100ms:
               Sleep(100);
                break;

            case TCS3471_INTEGRATION_154ms:
                Sleep(154);
                break;

            case TCS3471_INTEGRATION_200ms:
                Sleep(200);
                break;

            case TCS3471_INTEGRATION_700ms:
                Sleep(700);
                break;

        }
}

/* Reads gain settings of 16 sensors and stores them in usGainSettings 

	retVal == 0: everything ok
	retVal == 1: I2C-Functions failed 
*/
unsigned short int tcs_getGain(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucGainSettings)
{
	unsigned char aucTempbuffer[2] = {(TCS_ADDRESS<<1), TCS3471_CONTROL_REG | TCS3471_COMMAND_BIT};
	
	if(i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucGainSettings, sizeof(aucGainSettings) < 0)) return 1;
	
	return 0;
}

/* Read the integration time setings of 16 sensors and store them into aucInttimeSettings 
	
	retVal == 0: everything ok
	retVal == 1: I2C-Functions failed 
	
*/
unsigned short int tcs_getIntegrationtime(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucInttimeSettings)
{
	unsigned char aucTempbuffer[2] = {(TCS_ADDRESS<<1), TCS3471_ATIME_REG | TCS3471_COMMAND_BIT};

	if(i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucInttimeSettings, sizeof(aucInttimeSettings) < 0)) return 1;
	
	return 0;
}
