

#include "i2c_routines.h"



int i2c_setSpeed(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned int uiSpeedkHz)
{
    return 0;
}


/* Send a start condition */
int i2c_startCond(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
    int retval = 0;
    retval = process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, (!SCL) | SDA_0_OUTPUT | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT);
    retval = process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SCL | SDA_0_OUTPUT | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT);
    retval = process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SCL | !SDA_0_OUTPUT | !SDA_1_OUTPUT | !SDA_2_OUTPUT | !SDA_3_OUTPUT);
    retval = process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, (!SCL) | !SDA_0_OUTPUT | !SDA_1_OUTPUT | !SDA_2_OUTPUT | !SDA_3_OUTPUT);

    return retval;
}




int i2c_stopCond(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB )
{
    int retval = 0;

    /* Set clock High */
    retval = process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, 0);
    retval = process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SCL | !SDA_0_OUTPUT | !SDA_1_OUTPUT | !SDA_2_OUTPUT | !SDA_3_OUTPUT);
    retval = process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL);

    return retval;
}


/* Adresse R/W - ack - register - ack - data */

int i2c_write8(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucSendBuffer, unsigned char ucLength)
{
    unsigned int uiBufferIndex = 0;
    unsigned char ucMask = 0x80;
    unsigned char ucBitnumber = 7;
    unsigned long ucDataToSend = 0;
    unsigned long ulDataToSend = 0;
    int iRetval = 0;

    i2c_startCond(ftdiA, ftdiB);

        /* Send Adress leave Bit0 for WR Bit */
        while(ucMask!=1)
        {
            ucDataToSend = ((aucSendBuffer[uiBufferIndex] & ucMask)>>ucBitnumber);
            ulDataToSend = ucDataToSend << 0 | ucDataToSend << 2 | ucDataToSend << 4 | ucDataToSend << 6
                         | ucDataToSend << 8 | ucDataToSend << 10| ucDataToSend << 12| ucDataToSend <<14
                         | ucDataToSend <<16 | ucDataToSend << 18| ucDataToSend << 20| ucDataToSend <<22
                         | ucDataToSend <<24 | ucDataToSend << 26| ucDataToSend <<28 | ucDataToSend <<30;

            process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, ulDataToSend);
            i2c_clock(ftdiA, ftdiB, ulDataToSend);

            ucMask>>=1;
            ucBitnumber--;
        }


    /* 0 write 1 read */
    process_pins(ftdiA, ftdiB,  SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SDA_WRITE);
    i2c_clock(ftdiA, ftdiB, SDA_WRITE);
    i2c_getAck(ftdiA, ftdiB);
    uiBufferIndex++;
    ucMask = 128;
    ucBitnumber = 7;

    /* Iterate to all elements of aucBuffer, Index 1 will be the register written to / read from, index 2+ will be data */
    while(ucLength > 1)
    {
       /* Process the byte with indexnumber uiBufferIndex - apply masks and put the byte into the buffer beginning with msb */
        while(ucMask)
        {
            ucDataToSend = ((aucSendBuffer[uiBufferIndex] & ucMask)>>ucBitnumber);
            ulDataToSend = ucDataToSend << 0 | ucDataToSend << 2 | ucDataToSend << 4 | ucDataToSend << 6  // DA0-3
                         | ucDataToSend << 8 | ucDataToSend << 10| ucDataToSend << 12| ucDataToSend <<14  // DA4-7
                         | ucDataToSend <<16 | ucDataToSend << 18| ucDataToSend << 20| ucDataToSend <<22  // DA8-11
                         | ucDataToSend <<24 | ucDataToSend << 26| ucDataToSend <<28 | ucDataToSend <<30; // DA12-15

            process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, ulDataToSend);
            i2c_clock(ftdiA, ftdiB, ulDataToSend);

            ucMask>>=1;
            ucBitnumber--;
        }
        // an ack bit should come here
        //i2c_fakeAck(ftdiA, ftdiB);
        i2c_getAck(ftdiA, ftdiB);
        ucMask = 128;
        ucBitnumber = 7;
        ucLength--;
        uiBufferIndex++;
    }

    i2c_stopCond(ftdiA, ftdiB);

    iRetval = send_package_write8(ftdiA, ftdiB); // 3 Acknowladges expected
    return iRetval;

}


int i2c_read8(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucSendBuffer, unsigned char ucLength,
              unsigned char* aucRecBuffer, unsigned char ucRecLength)
{
    unsigned int uiBufferIndex = 0;
    unsigned char ucMask = 0x80;
    unsigned char ucBitnumber = 7;
    unsigned long ucDataToSend = 0;
    unsigned long ulDataToSend = 0;
    int iRetval = 0;

    i2c_startCond(ftdiA, ftdiB);

        /* Send Adress - leave Bit0 for RW */
        while(ucMask!=1)
        {
            ucDataToSend = ((aucSendBuffer[uiBufferIndex] & ucMask)>>ucBitnumber);
            ulDataToSend = ucDataToSend << 0 | ucDataToSend << 2 | ucDataToSend << 4 | ucDataToSend << 6  // DA0-3
                         | ucDataToSend << 8 | ucDataToSend << 10| ucDataToSend << 12| ucDataToSend <<14  // DA4-7
                         | ucDataToSend <<16 | ucDataToSend << 18| ucDataToSend << 20| ucDataToSend <<22  // DA8-11
                         | ucDataToSend <<24 | ucDataToSend << 26| ucDataToSend <<28 | ucDataToSend <<30; // DA12-15

            process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, ulDataToSend);
            i2c_clock(ftdiA, ftdiB, ulDataToSend);

            ucMask>>=1;
            ucBitnumber--;
        }

    /* 0 write 1 read */
    process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL , SDA_WRITE );
    i2c_clock(ftdiA, ftdiB, SDA_WRITE);
    i2c_getAck(ftdiA, ftdiB);

    uiBufferIndex++;
    ucMask = 128;
    ucBitnumber = 7;

    /* Iterate to all elements of aucBuffer, Index 1 will be the register written to / read from, index 0+ 2and on will be data */
    while(ucLength > 1)
    {
       /* Process the byte with indexnumber uiBufferIndex - apply masks and put the byte into the buffer beginning with msb */
        while(ucMask)
        {
            ucDataToSend = ((aucSendBuffer[uiBufferIndex] & ucMask)>>ucBitnumber);
            ulDataToSend = ucDataToSend << 0 | ucDataToSend << 2 | ucDataToSend << 4 | ucDataToSend << 6  // DA0-3
                         | ucDataToSend << 8 | ucDataToSend << 10| ucDataToSend << 12| ucDataToSend <<14  // DA4-7
                         | ucDataToSend <<16 | ucDataToSend << 18| ucDataToSend << 20| ucDataToSend <<22  // DA8-11
                         | ucDataToSend <<24 | ucDataToSend << 26| ucDataToSend <<28 | ucDataToSend <<31; // DA12-15

            process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, ulDataToSend);
            i2c_clock(ftdiA, ftdiB, ulDataToSend);

            ucMask>>=1;
            ucBitnumber--;
        }
        // an ack bit should come here
        //i2c_fakeAck(ftdiA, ftdiB);
        i2c_getAck(ftdiA, ftdiB);
        ucMask = 128;
        ucBitnumber = 7;
        ucLength--;
        uiBufferIndex++;
    }

    uiBufferIndex = 0;
    ucMask = 0x80;
    ucBitnumber = 7;
    ucDataToSend = 0;
    ulDataToSend = 0;


    /* Send a repeated start condition */
    i2c_startCond(ftdiA, ftdiB);

        /* Send Adress again with following RW Bit */
        while(ucMask!=1)
        {
            ucDataToSend = ((aucSendBuffer[uiBufferIndex] & ucMask)>>ucBitnumber);
            ulDataToSend = ucDataToSend << 0 | ucDataToSend << 2 | ucDataToSend << 4 | ucDataToSend << 6  // DA0-3
                         | ucDataToSend << 8 | ucDataToSend << 10| ucDataToSend << 12| ucDataToSend <<14  // DA4-7
                         | ucDataToSend <<16 | ucDataToSend << 18| ucDataToSend << 20| ucDataToSend <<22  // DA8-11
                         | ucDataToSend <<24 | ucDataToSend << 26| ucDataToSend <<28 | ucDataToSend <<30; // DA12-15

            process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, ulDataToSend);
            i2c_clock(ftdiA, ftdiB, ulDataToSend);

            ucMask>>=1;
            ucBitnumber--;
        }

    process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SDA_READ);
    i2c_clock(ftdiA, ftdiB, SDA_READ);
    i2c_getAck(ftdiA, ftdiB);

    /* Now the bytes can be read back beginning from the MSB */

    int counter = 8;

    while(counter--)
    {
        i2c_clockInput(ftdiA, ftdiB, 0);
    }

    i2c_giveAck(ftdiA, ftdiB);
    i2c_stopCond(ftdiA, ftdiB);


    iRetval = send_package_read8(ftdiA, ftdiB, aucRecBuffer, ucRecLength);
    return iRetval;

}

int i2c_read16(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucSendBuffer, unsigned char ucLength,
              unsigned short* ausReadBuffer, unsigned char ucReadBufferLength)
{
    unsigned int uiBufferIndex = 0;
    unsigned char ucMask = 0x80;
    unsigned char ucBitnumber = 7;
    unsigned long ucDataToSend = 0;
    unsigned long ulDataToSend = 0;
    int iRetval = 0;

    i2c_startCond(ftdiA, ftdiB);

        /* Send Adress / RW Bit */
        while(ucMask!=1)
        {
            ucDataToSend = ((aucSendBuffer[uiBufferIndex] & ucMask)>>ucBitnumber);
            ulDataToSend = ucDataToSend << 0 | ucDataToSend << 2 | ucDataToSend << 4 | ucDataToSend << 6  // DA0-3
                         | ucDataToSend << 8 | ucDataToSend << 10| ucDataToSend << 12| ucDataToSend <<14  // DA4-7
                         | ucDataToSend <<16 | ucDataToSend << 18| ucDataToSend << 20| ucDataToSend <<22  // DA8-11
                         | ucDataToSend <<24 | ucDataToSend << 26| ucDataToSend <<28 | ucDataToSend <<30; // DA12-15

            process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL , ulDataToSend );
            i2c_clock(ftdiA, ftdiB, ulDataToSend);

            ucMask>>=1;
            ucBitnumber--;
        }

    /* 0 write 1 read */
    process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL , SDA_WRITE);
    i2c_clock(ftdiA, ftdiB, 0);
    i2c_getAck(ftdiA, ftdiB);

    uiBufferIndex++;
    ucMask = 128;
    ucBitnumber = 7;

    /* Iterate to all elements of aucBuffer, Index 1, will be the register written to / read from, index 0+ 2and on will be data */
    while(ucLength > 1)
    {
       /* Process the byte with indexnumber uiBufferIndex - apply masks and put the byte into the buffer beginning with msb */
        while(ucMask)
        {
            ucDataToSend = ((aucSendBuffer[uiBufferIndex] & ucMask)>>ucBitnumber);
            ulDataToSend = ucDataToSend << 0 | ucDataToSend << 2 | ucDataToSend << 4 | ucDataToSend << 6  // DA0-3
                         | ucDataToSend << 8 | ucDataToSend << 10| ucDataToSend << 12| ucDataToSend <<14  // DA4-7
                         | ucDataToSend <<16 | ucDataToSend << 18| ucDataToSend << 20| ucDataToSend <<22  // DA8-11
                         | ucDataToSend <<24 | ucDataToSend << 26| ucDataToSend <<28 | ucDataToSend <<30; // DA12-15

            process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, ulDataToSend);
            i2c_clock(ftdiA, ftdiB, ulDataToSend);

            ucMask>>=1;
            ucBitnumber--;
        }

        i2c_getAck(ftdiA, ftdiB);
        ucMask = 128;
        ucBitnumber = 7;
        ucLength--;
        uiBufferIndex++;
    }

    uiBufferIndex = 0;
    ucMask = 0x80;
    ucBitnumber = 7;
    ucDataToSend = 0;
    ulDataToSend = 0;


    /* Send a repeated start condition */
    i2c_startCond(ftdiA, ftdiB);

        /* Send Adress again / RW Bit */
        while(ucMask!=1)
        {
            ucDataToSend = ((aucSendBuffer[uiBufferIndex] & ucMask)>>ucBitnumber);
            ulDataToSend = ucDataToSend << 0 | ucDataToSend << 2 | ucDataToSend << 4 | ucDataToSend << 6  // DA0-3
                         | ucDataToSend << 8 | ucDataToSend << 10| ucDataToSend << 12| ucDataToSend <<14  // DA4-7
                         | ucDataToSend <<16 | ucDataToSend << 18| ucDataToSend << 20| ucDataToSend <<22  // DA8-11
                         | ucDataToSend <<24 | ucDataToSend << 26| ucDataToSend <<28 | ucDataToSend <<30; // DA12-15

            process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, ulDataToSend);
            i2c_clock(ftdiA, ftdiB, ulDataToSend);

            ucMask>>=1;
            ucBitnumber--;
        }

    process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SDA_READ );
    i2c_clock(ftdiA, ftdiB, SDA_READ);


    i2c_getAck(ftdiA, ftdiB);

    /* Now the bytes can be read back beginning from the MSB */

    int counter = 16;

    while(counter--)
    {
        i2c_clockInput(ftdiA, ftdiB, 0);
        if(counter == 8) i2c_giveAck(ftdiA, ftdiB);
    }

    i2c_giveAck(ftdiA, ftdiB);
    i2c_stopCond(ftdiA, ftdiB);


    iRetval = send_package_read16(ftdiA, ftdiB, ausReadBuffer, ucReadBufferLength);
    return iRetval;

}

void i2c_clock(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned long ulDataToSend)
{
      process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SCL | ulDataToSend);
      process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, (!SCL) | ulDataToSend);
}



void i2c_clockInput(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned long ulDataToSend)
{
      process_pins_databack(ftdiA, ftdiB, SDA_0_INPUT | SDA_1_INPUT | SDA_2_INPUT | SDA_3_INPUT | SCL, SCL | ulDataToSend);
      process_pins_databack(ftdiA, ftdiB, SDA_0_INPUT | SDA_1_INPUT | SDA_2_INPUT | SDA_3_INPUT | SCL, !SCL | ulDataToSend);
}


void i2c_giveAck(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
      process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, SDA_READ );process_pins(ftdiA, ftdiB, SDA_0_OUTPUT  | SDA_1_OUTPUT | SDA_2_OUTPUT | SDA_3_OUTPUT | SCL, 0);
      i2c_clock(ftdiA, ftdiB, 0);
}


void i2c_clock_forACK(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned long ulDataToSend)
{
      process_pins_databack(ftdiA, ftdiB, SDA_0_INPUT | SDA_1_INPUT | SDA_2_INPUT | SDA_3_INPUT | SCL, SCL | ulDataToSend);
      process_pins_databack(ftdiA, ftdiB, SDA_0_INPUT | SDA_1_INPUT | SDA_2_INPUT | SDA_3_INPUT | SCL, !SCL | ulDataToSend);

}

void i2c_getAck(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB)
{
    process_pins(ftdiA, ftdiB, SDA_0_INPUT | SDA_1_INPUT | SDA_2_INPUT | SDA_3_INPUT | SCL, 0);
    i2c_clock_forACK(ftdiA, ftdiB, 0);
}
