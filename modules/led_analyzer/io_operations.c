#define W_LOWBYTE 0x80   // Channel AD and BD
#define W_HIGHBYTE 0x82  // Channel AC and BC

#define R_LOWBYTE 0x81   // Channel AD and BD
#define R_HIGHBYTE 0x83   // Channel AC and BC3




#define MASK_ALOW  0x000000FF
#define MASK_AHIGH 0x0000FF00
#define MASK_BLOW  0x00FF0000
#define MASK_BHIGH 0xFF000000

#define OUTPUT 0xFF
#define MYINPUT 0x00 


#include "io_operations.h"


unsigned int indexA = 0;
unsigned int indexB = 0;

unsigned int readIndexA = 0;
unsigned int readIndexB = 0;

unsigned char aucBufferA[4096];
unsigned char aucBufferB[4096];

/* Testfunction
Writes the content of aucSendbuffer to a single channel of a ftdi Chip (A or B) 
the Lowbyte is used as default 
*/ 
int io_write(struct ftdi_context* ftdi, unsigned char* aucSendbuffer, unsigned char ucSizeSendbuffer)
{
    int uiWritten;

    if(libusb_bulk_transfer(ftdi->usb_dev, ftdi->in_ep, aucSendbuffer, ucSizeSendbuffer, &uiWritten, ftdi->usb_write_timeout)<0)
    {
        printf("Writing to output was not successful ... \n");
        return -1;
    }

    return 0;

}



/* Writes an unsigned long variable ulOutput to both channels of a ftdi chip 
	ulOutput is split into two 16 bit words
	the upper word is assigned to ftdiB
	the lower word is assigned to ftdiA
*/
int writeOutputs(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, const unsigned long ulOutput)
{

     int uiWritten;
    unsigned char aucBuffer[6];

    aucBuffer[0] = W_LOWBYTE; // lowbyte ist ad //highbyte ist ac
    aucBuffer[1] = (unsigned char)(ulOutput&MASK_ALOW);
    aucBuffer[2] = OUTPUT; //output
    aucBuffer[3] = W_HIGHBYTE;
    aucBuffer[4] = (unsigned char)((ulOutput&MASK_AHIGH)>>8);
    aucBuffer[5] = OUTPUT; //output



    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->in_ep, aucBuffer, sizeof(aucBuffer), &uiWritten, ftdiA->usb_write_timeout)<0)
    {
        printf("usb bulk write failed");
        return -1;
    }

    printf("Lowbyte (AD) 0x%02x   Highbyte (AC) 0x%02x on interface %s\n ", aucBuffer[1], aucBuffer[4], ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));

    aucBuffer[0] = W_LOWBYTE;
    aucBuffer[1] = (unsigned char)((ulOutput&MASK_BLOW)>>16);
    aucBuffer[2] = OUTPUT; //output
    aucBuffer[3] = W_HIGHBYTE;
    aucBuffer[4] = (unsigned char)((ulOutput&MASK_BHIGH)>>24);
    aucBuffer[5] = OUTPUT; //output

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->in_ep, aucBuffer, sizeof(aucBuffer), &uiWritten, ftdiB->usb_write_timeout)<0)
    {
        printf("usb bulk write failed\n");
        return -1;
    }
    printf("Lowbyte (BD) 0x%02x   Highbyte (BC) 0x%02x on interface %s\n ", aucBuffer[1], aucBuffer[4], ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));



    return uiWritten;
}


/* Reads input of both Channels of a ftdi chip and prints it */
int readInputs(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, const unsigned char* readBack)
{
     int uiRead;
     int uiWritten;
    unsigned char aucBuffer[8];


    aucBuffer[0] = W_LOWBYTE; // AD
    aucBuffer[1] = 0xFF;
    aucBuffer[2] = MYINPUT; //MYINPUT
    aucBuffer[3] = W_HIGHBYTE; // AC
    aucBuffer[4] = 0xFF;
    aucBuffer[5] = MYINPUT; //MYINPUT
    aucBuffer[6] = R_LOWBYTE;
    aucBuffer[7] = R_HIGHBYTE;


    /* Set the needed pins as MYINPUT */

    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->in_ep, aucBuffer, sizeof(aucBuffer), &uiWritten, ftdiA->usb_write_timeout)<0)
    {
        printf("usb bulk write failed");
        return -1;
    }

    /* Read back the needed pins */



    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->out_ep, aucBuffer, sizeof(aucBuffer), &uiRead, ftdiA->usb_write_timeout)<0)
    {
        printf("Reading back failed");
        return -2;
    }
     printf("Read back from channel %s - Lowbyte (AD): 0x%02x Highbyte (AC): 0x%02x\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":"error - invalid channel"), aucBuffer[2],aucBuffer[3]);


    aucBuffer[0] = W_LOWBYTE;
    aucBuffer[1] = 0xFF;
    aucBuffer[2] = MYINPUT; //MYINPUT
    aucBuffer[3] = W_HIGHBYTE;
    aucBuffer[4] = 0xFF;
    aucBuffer[5] = MYINPUT; //MYINPUT
    aucBuffer[6] = R_LOWBYTE;
    aucBuffer[7] = R_HIGHBYTE;


         /* Set ftdiB needed pins as MYINPUT */

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->in_ep, aucBuffer, sizeof(aucBuffer), &uiWritten, ftdiB->usb_write_timeout)<0)
    {
        printf("usb bulk write failed");
        return -1;
    }

    /* Read back the needed pins */

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->out_ep, aucBuffer, sizeof(aucBuffer), &uiRead, ftdiB->usb_write_timeout)<0)
    {
        printf("Reading back failed");
        return -2;
    }
     printf("Read back from channel %s - Lowbyte (BD): 0x%02x Highbyte (BC): 0x%02x\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":"error - invalid channel"), aucBuffer[2],aucBuffer[3]);


    return uiRead;
}

/* This function gets called repeatedly by i2c functions. It stores the commands in global Buffers
(aucBufferA and aucBufferB). The commands consist of a mask which determines which pins are configured as output and input
plus the actual output value to be written to the pins */
int process_pins(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned long ulIOMask, unsigned long ulOutput)
{

    aucBufferA[indexA++] = W_LOWBYTE; //
    aucBufferA[indexA++] = (unsigned char)(ulOutput&MASK_ALOW); 
    aucBufferA[indexA++] = (unsigned char)(ulIOMask&MASK_ALOW);
    aucBufferA[indexA++] = W_HIGHBYTE; // AC
    aucBufferA[indexA++] = (unsigned char)((ulOutput&MASK_AHIGH)>>8);
    aucBufferA[indexA++] = (unsigned char)((ulIOMask&MASK_AHIGH)>>8); 

    /* Now Channel B first configure the channels for IO */
    aucBufferB[indexB++] = W_LOWBYTE; //
    aucBufferB[indexB++] = (unsigned char)((ulOutput&MASK_BLOW)>>16);
    aucBufferB[indexB++] = (unsigned char)((ulIOMask&MASK_BLOW)>>16);
    aucBufferB[indexB++] = W_HIGHBYTE; // BC
    aucBufferB[indexB++] = (unsigned char)((ulOutput&MASK_BHIGH)>>24); // BC
    aucBufferB[indexB++] = (unsigned char)((ulIOMask&MASK_BHIGH)>>24);

    return 0;


}

/* This function gets called repeatedly by i2c functions. It stores the commands in glbal Buffers
(aucBufferA and aucBufferB). The commands consist of a mask which determines which pins are set as input and output and and output value
which will be written to the pins set as output. 
*/
int process_pins_databack(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned long ulIOMask, unsigned long ulOutput)
{

    aucBufferA[indexA++] = W_LOWBYTE; //
    aucBufferA[indexA++] = (unsigned char)(ulOutput&MASK_ALOW); 
    aucBufferA[indexA++] = (unsigned char)(ulIOMask&MASK_ALOW);
    aucBufferA[indexA++] = W_HIGHBYTE; // AC
    aucBufferA[indexA++] = (unsigned char)((ulOutput&MASK_AHIGH)>>8);
    aucBufferA[indexA++] = (unsigned char)((ulIOMask&MASK_AHIGH)>>8); 
    aucBufferA[indexA++] = R_LOWBYTE;
    aucBufferA[indexA++] = R_HIGHBYTE;
    readIndexA+=2;

 
    /* Now Channel B first configure the channels for IO */
    aucBufferB[indexB++] = W_LOWBYTE; //
    aucBufferB[indexB++] = (unsigned char)((ulOutput&MASK_BLOW)>>16);
    aucBufferB[indexB++] = (unsigned char)((ulIOMask&MASK_BLOW)>>16);
    aucBufferB[indexB++] = W_HIGHBYTE; // BC
    aucBufferB[indexB++] = (unsigned char)((ulOutput&MASK_BHIGH)>>24); // BC
    aucBufferB[indexB++] = (unsigned char)((ulIOMask&MASK_BHIGH)>>24);
    aucBufferB[indexB++] = R_LOWBYTE;
    aucBufferB[indexB++] = R_HIGHBYTE;
    readIndexB+=2;

    return 0;
}

/* This function sends the content of the global Buffers aucBufferA and aucBufferB to the ftdi chip 
Furthermore it reads back the data of pins which were configured as input. In case of i2c these read back pins
can be acknowledes send back by the device. */

int send_package_write8(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB)
{

    unsigned int uiWritten;
    unsigned int uiRead;

        /*
       Missing: Check if ACKNOWLEDGES were received
                waiting for all sensors
    */

    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->in_ep, aucBufferA, indexA, &uiWritten, ftdiA->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -1;
    }

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->in_ep, aucBufferB, indexB, &uiWritten, ftdiB->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -2;
    }


    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->out_ep, aucBufferA, sizeof(aucBufferA), &uiRead, ftdiA->usb_write_timeout)<0)
    {
        printf("Reading from channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -3;
    }

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->out_ep, aucBufferB, sizeof(aucBufferB), &uiRead, ftdiB->usb_write_timeout)<0)
    {
        printf("Reading from channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -4;
    }

    //if(aucBufferA[2] & aucBufferA[3] & aucBufferA[6] & aucBufferA[7] & aucBufferA[10] & aucBufferA[11] & 0xAAAAAAAA == 0)
    // printf("acks: %d\n", aucBufferA[2] & aucBufferA[3] & aucBufferA[6] & aucBufferA[7] & aucBufferA[10] & aucBufferA[11] & 0xAAAAAAAA);

    indexA = 0;
    indexB = 0;
    readIndexA = 0;
    readIndexB = 0;

    return uiWritten;

}

/* This function sends the content of the global Buffers aucBufferA and aucBufferB to the ftdi chip. 
Furthermore it reads back the data of pins which were configured as input. The function returns a value which equals the amount of read back bytes.
The parameter aucReadbuffer will be used for storing 16 read back unsigned char values of 16 sensors  */

int send_package_read8(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned char* aucReadBuffer, unsigned char ucReadBufferLength)
{

    unsigned int uiWritten;
    unsigned int uiRead;


    /*
       Missing: Check if ACKNOWLEDGES were received
                waiting for all sensors
    */
    /* Reset the receive and the transmit buffers */


    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->in_ep, aucBufferA, indexA, &uiWritten, ftdiA->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -1;
    }

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->in_ep, aucBufferB, indexB, &uiWritten, ftdiB->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -2;
    }

    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->out_ep, aucBufferA, sizeof(aucBufferA), &uiRead, ftdiA->usb_write_timeout)<0)
    {
        printf("Reading from channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -3;
    }

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->out_ep, aucBufferB, sizeof(aucBufferB), &uiRead, ftdiB->usb_write_timeout)<0)
    {
        printf("Reading from channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -4;
    }

    /* Fill your readBuffer with zeroes, so nothing can go wrong mate ! */
    int i = 0;
    for(i; i<16; i++)
    {
        aucReadBuffer[i] = 0;
    }

/* ucBitnumber marks the start of data in the buffer read out of eprom
            with 3 Acknowledges expected

*/

    unsigned char ucBitnumber = 14;
    unsigned char ucMask = 7;
    unsigned char ucBufferIndexA = 0;
    unsigned char ucBufferIndexB = 8;
    unsigned int uiCounter = 8;

    while(uiCounter>0)
    {
        ucBufferIndexA = 0;
        ucBufferIndexB = 8;

        /* Process parallel incoming bits of each channel */
        /* Channel AD */
        /* DA0 */
        aucReadBuffer[ucBufferIndexA++] |= ((unsigned char)(aucBufferA[ucBitnumber]&0x01)<<ucMask);
        /* DA1 */
        aucReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x04)>>2)<<ucMask);
        /* DA2 */
        aucReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x10)>>4)<<ucMask);
        /* DA3 */
        aucReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x40)>>6)<<ucMask);

        /* Channel BD */
        /* DA8 */
        aucReadBuffer[ucBufferIndexB++] |= ((unsigned char)(aucBufferB[ucBitnumber]&0x01)<<ucMask);
        /* DA9 */
        aucReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x04)>>2)<<ucMask);
        /* DA10 */
        aucReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x10)>>4)<<ucMask);
        /* DA11 */
        aucReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x40)>>6)<<ucMask);


        ucBitnumber += 1; 

        /* Channel AC */
        /* DA4 */
        aucReadBuffer[ucBufferIndexA++] |= ((unsigned char)(aucBufferA[ucBitnumber]&0x01)<<ucMask);
        /* DA5 */
        aucReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x04)>>2)<<ucMask);
        /* DA6 */
        aucReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x10)>>4)<<ucMask);
        /* DA7 */
        aucReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x40)>>6)<<ucMask);

        /* Channel BC */
        /* DA4 */
        aucReadBuffer[ucBufferIndexB++] |= ((unsigned char)(aucBufferB[ucBitnumber]&0x01)<<ucMask);
        /* DA5 */
        aucReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x04)>>2)<<ucMask);
        /* DA6 */
        aucReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x10)>>4)<<ucMask);
        /* DA7 */
        aucReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x40)>>6)<<ucMask);


        ucBitnumber +=3;
        uiCounter--;
        ucMask--;
    }

    indexA = 0;
    indexB = 0;
    readIndexA = 0;
    readIndexB = 0;
    return uiRead;

}



int send_package_read16(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned short* ausReadBuffer, unsigned char ucReadBufferLength)
{

    unsigned int uiWritten;
    unsigned int uiRead;

    /* Reset the receive and the transmit buffers  */


    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->in_ep, aucBufferA, indexA, &uiWritten, ftdiA->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -1;
    }

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->in_ep, aucBufferB, indexB, &uiWritten, ftdiB->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -2;
    }


    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->out_ep, aucBufferA, sizeof(aucBufferA), &uiRead, ftdiA->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -3;
    }

    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->out_ep, aucBufferB, sizeof(aucBufferB), &uiRead, ftdiB->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -4;
    }

    /* Fill your readBuffer with zeroes, so nothing can go wrong mate ! */
    int i = 0;
    for(i; i<16; i++)
    {
        ausReadBuffer[i] = 0;
    }

    unsigned char ucBitnumber = 14;
    unsigned char ucMask = 7;
    unsigned char ucBufferIndexA = 0;
    unsigned char ucBufferIndexB = 8;
    unsigned int uiCounter = 8;

    /*
       Missing: Check if ACKNOWLEDGES were received
                waiting for all sensors
    */


    while(uiCounter>0)
    {
        ucBufferIndexA = 0;
        ucBufferIndexB = 8;
        /* Process parallel incoming bits of each channel */
        /* Channel AD */
        /* DA0 */
        ausReadBuffer[ucBufferIndexA++] |= ((unsigned char)(aucBufferA[ucBitnumber]&0x01)<<ucMask);
        /* DA1 */
        ausReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x04)>>2)<<ucMask);
        /* DA2 */
        ausReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x10)>>4)<<ucMask);
        /* DA3 */
        ausReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x40)>>6)<<ucMask);

        /* Channel BD */
        /* DA8 */
        ausReadBuffer[ucBufferIndexB++] |= ((unsigned char)(aucBufferB[ucBitnumber]&0x01)<<ucMask);
        /* DA9 */
        ausReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x04)>>2)<<ucMask);
        /* DA10 */
        ausReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x10)>>4)<<ucMask);
        /* DA11 */
        ausReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x40)>>6)<<ucMask);


        ucBitnumber += 1; 

        /* Channel AC */
        /* DA4 */
        ausReadBuffer[ucBufferIndexA++] |= ((unsigned char)(aucBufferA[ucBitnumber]&0x01)<<ucMask);
        /* DA5 */
        ausReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x04)>>2)<<ucMask);
        /* DA6 */
        ausReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x10)>>4)<<ucMask);
        /* DA7 */
        ausReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x40)>>6)<<ucMask);

        /* Channel AD */
        /* DA12 */
        ausReadBuffer[ucBufferIndexB++] |= ((unsigned char)(aucBufferB[ucBitnumber]&0x01)<<ucMask);
        /* DA13 */
        ausReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x04)>>2)<<ucMask);
        /* DA14 */
        ausReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x10)>>4)<<ucMask);
        /* DA15 */
        ausReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x40)>>6)<<ucMask);

        ucBitnumber +=3;
        uiCounter--;
        ucMask--;
    }

    ucMask = 7;
    uiCounter = 8;

    /* Process colorH */
    while(uiCounter>0)
    {
        ucBufferIndexA = 0;
        ucBufferIndexB = 8;
        /* Process parallel incoming bits of each channel */
        /* Channel AD */
        /* DA0 */
        ausReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x01)<<ucMask)<<8);
        /* DA1 */
        ausReadBuffer[ucBufferIndexA++] |= ((((unsigned char)(aucBufferA[ucBitnumber]&0x04)>>2)<<ucMask)<<8);
        /* DA2 */
        ausReadBuffer[ucBufferIndexA++] |= ((((unsigned char)(aucBufferA[ucBitnumber]&0x10)>>4)<<ucMask)<<8);
        /* DA3 */
        ausReadBuffer[ucBufferIndexA++] |= ((((unsigned char)(aucBufferA[ucBitnumber]&0x40)>>6)<<ucMask)<<8);

        /* Channel BD */
        /* DA8 */
        ausReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x01)<<ucMask)<<8);
        /* DA9 */
        ausReadBuffer[ucBufferIndexB++] |= ((((unsigned char)(aucBufferB[ucBitnumber]&0x04)>>2)<<ucMask)<<8);
        /* DA10 */
        ausReadBuffer[ucBufferIndexB++] |= ((((unsigned char)(aucBufferB[ucBitnumber]&0x10)>>4)<<ucMask)<<8);
        /* DA11 */
        ausReadBuffer[ucBufferIndexB++] |= ((((unsigned char)(aucBufferB[ucBitnumber]&0x40)>>6)<<ucMask)<<8);


        ucBitnumber += 1;

        /* Channel AC */
        /* DA4 */
        ausReadBuffer[ucBufferIndexA++] |= (((unsigned char)(aucBufferA[ucBitnumber]&0x01)<<ucMask)<<8);
        /* DA5 */
        ausReadBuffer[ucBufferIndexA++] |= ((((unsigned char)(aucBufferA[ucBitnumber]&0x04)>>2)<<ucMask)<<8);
        /* DA6 */
        ausReadBuffer[ucBufferIndexA++] |= ((((unsigned char)(aucBufferA[ucBitnumber]&0x10)>>4)<<ucMask)<<8);
        /* DA7 */
        ausReadBuffer[ucBufferIndexA++] |= ((((unsigned char)(aucBufferA[ucBitnumber]&0x40)>>6)<<ucMask)<<8);

        /* Channel AD */
        /* DA12 */
        ausReadBuffer[ucBufferIndexB++] |= (((unsigned char)(aucBufferB[ucBitnumber]&0x01)<<ucMask)<<8);
        /* DA13 */
        ausReadBuffer[ucBufferIndexB++] |= ((((unsigned char)(aucBufferB[ucBitnumber]&0x04)>>2)<<ucMask)<<8);
        /* DA14 */
        ausReadBuffer[ucBufferIndexB++] |= ((((unsigned char)(aucBufferB[ucBitnumber]&0x10)>>4)<<ucMask)<<8);
        /* DA15 */
        ausReadBuffer[ucBufferIndexB++] |= ((((unsigned char)(aucBufferB[ucBitnumber]&0x40)>>6)<<ucMask)<<8);

        ucBitnumber +=3;
        uiCounter--;
        ucMask--;
    }

    indexA = 0;
    indexB = 0;
    readIndexA = 0;
    readIndexB = 0;
    return uiRead;

}
