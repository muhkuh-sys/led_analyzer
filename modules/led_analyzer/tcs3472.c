
#include "tcs3472.h"
#define MAXERROR 50



/* This function dentifies the 16 sensors of a device 
   It will return the index of the snesor(s) that could not be identified
*/
unsigned char tcs_identify(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer)
{
    unsigned int uiErrorcounter = 0;
    unsigned int uiSuccesscounter = 0;

    int i = 0;

    unsigned char aucTempbuffer[2] = {(0x29<<1), TCS3471_ID_REG | TCS3471_COMMAND_BIT};
    unsigned char aucErrorbuffer[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer));
		
            for(i = 0; i<=15; i++)
            {
                
				/* 0x14 = ID for tcs3471        0x44 = ID for tcs3472 */
               if(aucReadbuffer[i] != (0x14) && aucReadbuffer[i] != 0x44)
               {
				  
                    aucErrorbuffer[i] = i;
                    uiErrorcounter ++;
               }

               else uiSuccesscounter ++;

               if(uiSuccesscounter == 16)
               {
                   printf("Identification successful.\n");
                   return 0; // SUCCESFULL IDENTFICATION OF ALL SENSORS
               }
            }
        printf("Identification errors with following sensorindices ...\n");
        for(i = 0; i<16; i++)
        {
            if(aucErrorbuffer[i] != 0xFF) printf("%d ", aucErrorbuffer[i]);
        }
        printf("\n");
        return 1;
}


/* This function turns the tcs3472 sensor on, in case it was sent to sleep before
   If function is called without the sensor being priorily sent to sleep this function does nothing */
unsigned char tcs_ON(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
   unsigned char aucTempbuffer[3] = {(0x29<<1), TCS3471_ENABLE_REG | TCS3471_COMMAND_BIT, TCS3471_AIEN_BIT | TCS3471_AEN_BIT
                                    | TCS3471_PON_BIT };
   if(i2c_write8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer)) <0) return 1;
   return 0;
}


/* Following two functions have to be set up properly to have a decent detection. 
*/


/* This function sets the integration time of the sensor, darker leds need longer integration times.
whereas brighter leds need shorter integration times */
unsigned char tcs_setIntegrationTime(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3471Integration_t uiIntegrationtime)
{
    unsigned char aucTempbuffer[3] = {(0x29<<1), TCS3471_ATIME_REG | TCS3471_COMMAND_BIT, uiIntegrationtime};
    if(i2c_write8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer)) <0) return 1;

    return 0;
}
/* this function sets the gain of the sensor
just like the integration time, darker leds need a higher gain setting and brighter leds can have a lower gain setting
*/
unsigned char tcs_setGain(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3471Gain_t gain)
{
    unsigned char aucTempbuffer[3] = {(0x29<<1), TCS3471_CONTROL_REG | TCS3471_COMMAND_BIT, gain};

    if(gain == 0xFF) printf("Fehler!\n");

    if(i2c_write8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer)) <0) return 1;
    return 0;
}




unsigned char tcs_rgbcInvalid(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer)
{
    unsigned int uiErrorcounter = 0;
    unsigned int uiSuccesscounter = 0;
    int i = 0;

    unsigned char aucTempbuffer[2] = {(0x29<<1), TCS3471_STATUS_REG | TCS3471_COMMAND_BIT};
    unsigned char aucErrorbuffer[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer));

            for(i = 0; i<=15; i++)
            {
               if((aucReadbuffer[i]&TCS3471_AVALID_BIT) != TCS3471_AVALID_BIT)
               {
                    aucErrorbuffer[i] = i;
                    uiErrorcounter ++;
               }
               else uiSuccesscounter ++;

               if(uiSuccesscounter == 16)
               {
                   printf("RGBC datasets valid.\n");
                   return 0; // Valid RGBC data from all sensors
               }
            }
        printf("Invalid RGBC data with following sensorindices ...\n");
        for(i = 0; i<16; i++)
        {
            if(aucErrorbuffer[i] != 0xFF) printf("%d ", aucErrorbuffer[i]);
        }
        printf("\n");
        return 1;
}


unsigned char tcs_waitForData(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer)
{
    unsigned int uiErrorcounter = 0;
    unsigned int uiSuccesscounter = 0;
    int i = 0;

    unsigned char aucTempbuffer[2] = {(0x29<<1), TCS3471_STATUS_REG | TCS3471_COMMAND_BIT};
    unsigned char aucErrorbuffer[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer));

            for(i = 0; i<=15; i++)
            {
               if((aucReadbuffer[i]&TCS3471_AINT_BIT) != TCS3471_AINT_BIT)
               {
                    aucErrorbuffer[i] = i;
                    uiErrorcounter ++;
               }
               else uiSuccesscounter ++;

               if(uiSuccesscounter == 16)
               {
                   printf("Conversions complete.\n");
                   return 0; // SUCCESFULL IDENTFICATION OF ALL SENSORS
               }
            }

        printf("Incomplete conversions with following sensorindices ...\n");
        for(i = 0; i<16; i++)
        {
            if(aucErrorbuffer[i] != 0xFF) printf("%d ", aucErrorbuffer[i]);
        }
        printf("\n");
        return 1;
}


unsigned char tcs_readColour(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* ausColorArray, enum tcs_color_t color)
{
    unsigned char aucTempbuffer[2] = {(0x29<<1), TCS3471_AUTOINCR_BIT | TCS3471_COMMAND_BIT};

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



unsigned char tcs_sleep(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
    unsigned char aucReadbuffer[16];
    unsigned char aucTempbuffer[2]  = {(0x29<<1), TCS3471_COMMAND_BIT | TCS3471_ENABLE_REG};
    if(i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer))<0) return 1;
    unsigned char aucTempbuffer2[3] = {(0x29<<1), TCS3471_COMMAND_BIT | TCS3471_ENABLE_REG,  aucReadbuffer[0] & ~(TCS3471_PON_BIT | TCS3471_AEN_BIT)};
    if(i2c_write8(ftdiA, ftdiB,  aucTempbuffer2, sizeof(aucTempbuffer2))<0) return 1;

    return 0;
}

unsigned char tcs_wakeUp(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
    unsigned char aucReadbuffer[16];
    unsigned char aucTempbuffer[2]  = {(0x29<<1), TCS3471_COMMAND_BIT | TCS3471_ENABLE_REG};
    if(i2c_read8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer), aucReadbuffer, sizeof(aucReadbuffer))<0) return 1;
    unsigned char aucTempbuffer2[3] = {(0x29<<1), TCS3471_COMMAND_BIT | TCS3471_ENABLE_REG,  aucReadbuffer[0] | TCS3471_PON_BIT};
    if(i2c_write8(ftdiA, ftdiB,  aucTempbuffer2, sizeof(aucTempbuffer2))<0) return 1;

    return 0;
}

unsigned char tcs_exClear(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* ausClear, unsigned int uiIntegrationtime)
{
    int i= 0;
    unsigned int uiSuccesscounter = 0;
    unsigned char aucErrorbuffer[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    for(i=0; i<16; i++)
    {
        switch(uiIntegrationtime)
        {
            case TCS3471_INTEGRATION_2_4ms:
                if(ausClear[i] >= 1024)
                {
                    aucErrorbuffer[i] = i;
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_24ms:
                if(ausClear[i] >= 10240)
                {
                    aucErrorbuffer[i] = i;
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_100ms:
                if(ausClear[i] >= 43007)
                {
                    aucErrorbuffer[i] = i;
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_154ms:
                if(ausClear[i] >= 65535)
                {
                    aucErrorbuffer[i] = i;
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_200ms:
                if(ausClear[i] >= 65535)
                {
                    aucErrorbuffer[i] = i;
                }
                else uiSuccesscounter++;
                break;

            case TCS3471_INTEGRATION_700ms:
                if(ausClear[i] >= 65535)
                {
                    aucErrorbuffer[i] = i;
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
    printf("Turn down gain for following sensorindices ...\n");
    for(i; i<16; i++)
    {
       if(aucErrorbuffer[i] != 0xFF) printf("%d ", aucErrorbuffer[i]);
    }
    printf("\n");
    return 1;

}

unsigned char tcs_clearInt(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
    unsigned char aucTempbuffer[2]  = {(0x29<<1), TCS3471_COMMAND_BIT | TCS3471_SPECIAL_BIT | TCS3471_INTCLEAR_BIT};

    if(i2c_write8(ftdiA, ftdiB, aucTempbuffer, sizeof(aucTempbuffer))<0) return 1;
    return 0;

}

void tcs_waitIntegrationtime(tcs3471Integration_t uiIntegrationtime, unsigned int uiShorter)
{
        switch(uiIntegrationtime)
        {
            case TCS3471_INTEGRATION_2_4ms:
                Sleep(3);
                break;

            case TCS3471_INTEGRATION_24ms:
                if(uiShorter <= 12) Sleep(24-uiShorter);
                else Sleep(24);
                break;

            case TCS3471_INTEGRATION_100ms:
                if(uiShorter <= 50) Sleep(100-uiShorter);
                else Sleep(100);
                break;

            case TCS3471_INTEGRATION_154ms:
                if(uiShorter <= 70) Sleep(154-uiShorter);
                else Sleep(154);
                break;


            case TCS3471_INTEGRATION_200ms:
                if(uiShorter <= 80) Sleep(200-uiShorter);
                else Sleep(200);
                break;


            case TCS3471_INTEGRATION_700ms:
                if(uiShorter <= 200) Sleep(700-uiShorter);
                else Sleep(700);
                break;


        }
}
