/** \file io_operations.c 
	\brief io_operations provides functions to manipulate ftdi 2232h's I/O-Pins. 
	 
Once the ftdi2232h is set into BITMODE_MPSSE simple USB commands can be sent to it in order to mainpulate its input and output pins.
Special commands (for example found in AN_108) can be used to set the 32 GPIO Pins of the ftdi device as either input or output, and once done,
values can be assigned to the output pins and data can be read back from the input pins. These functions are designed for implementing software
i2c-functions.
 
 */
 
#include "io_operations.h"

/** global arrayindex for Channel a */
unsigned int indexA = 0;
/** global arrayindex for Channel B */
unsigned int indexB = 0; 
/** global readIndex for Channel A, incremented everytime a byte is expected to be read back from Channel A*/
unsigned int readIndexA = 0; /** global readIndex for Channel A, incremented everytime a byte is expected to be read back from Channel A*/
/** global readIndex for Channel B, incremented everytime a byte is expected to be read back from Channel B*/
unsigned int readIndexB = 0; /** global readIndex for Channel B, incremented everytime a byte is expected to be read back from Channel B*/
/** global Buffer stores the commands for channel A */
unsigned char aucBufferA[4096];
/** global Buffer stores the commands for channel B */
unsigned char aucBufferB[4096]; 


/** \brief writes a value to the ftdi 2232h output pins.
	@param[in] 		ftdiA, ftdiB pointer to a ftdi_context
	@param[in] 		ulOutput	 a 32 Bit value to be written to the ftdi pins
	@param[in] 		ulOutput     Bit0 will be assigned to AD0, Bit31 to BC7

	@return 		>0 : number of bytes written to the chip
	@return			<0 : USB functions failed 
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

/** \brief reads the input pins of both ftdi channels
	@param[in] 		ftdiA, ftdiB pointer to a ftdi_context
	@param[in,out] 	readBack	 contains the bytes read back from the input pins

	@return 		>0 : number of bytes written to the chip
	@return			<0 : USB functions failed 
*/

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



/** \brief stores a ftdi write command in a global buffer for later sending

This function gets called repeatedly by i2c functions. It stores the commands in global Buffers
(aucBufferA and aucBufferB). The commands consist of a mask which determines which pins are configured as output and input
plus the actual output value to be written to the pins. All stored commands can be sent by the send_package_xx functions
which form the software i2c protocol.
	@param[in] 		ftdiA, ftdiB pointer to a ftdi_context
	@param[in] 		ulIOMask	 input / output mask to set pin functionality
	@param[in]		ulOutput	 value to be assigned to pins set as output 

*/

void process_pins(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned long ulIOMask, unsigned long ulOutput)
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
	
}


/** \brief stores a ftdi write command in a global buffer for later sending

This function gets called repeatedly by i2c functions. It stores the commands in global Buffers
(aucBufferA and aucBufferB). The commands consist of a mask which determines which pins are set as input and output and and output value
which will be written to the pins set as output. 
	@param[in] 		ftdiA, ftdiB pointer to a ftdi_context
	@param[in] 		ulIOMask	 input / output mask to set pin direction
	@param[in]		ulOutput	 value to be assigned to pins set as output 

*/
void process_pins_databack(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned long ulIOMask, unsigned long ulOutput)
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
	
}


/** \brief sends the content of the global buffers to the ftdi chip 

This function sends the content of the global Buffers aucBufferA and aucBufferB to the ftdi chip 
Furthermore it reads back the data of pins which were configured as input. In case of i2c these read back pins
can be acknowledge bits or data send back by the device. 
	@param[in] 		ftdiA, ftdiB pointer to a ftdi_context
	@return			>0: number of bytes sent to the ftdi chip 
	@return			-1: writing to channel A failed 
	@return			-2: writing to channel B failed
	@return			-3: reading from channel A failed
	@return			-4: reading from channel B failed
					

*/
int send_package_write8(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB)
{

    unsigned int uiWritten;
    unsigned int uiRead;


	/* Send to Channel A */
    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->in_ep, aucBufferA, indexA, &uiWritten, ftdiA->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -1;
    }
	
	/* Send to Channel B */
    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->in_ep, aucBufferB, indexB, &uiWritten, ftdiB->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -2;
    }

	/* Read from Channel A */
    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->out_ep, aucBufferA, sizeof(aucBufferA), &uiRead, ftdiA->usb_write_timeout)<0)
    {
        printf("Reading from channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -3;
    }

	/* Read from Channel B */
    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->out_ep, aucBufferB, sizeof(aucBufferB), &uiRead, ftdiB->usb_write_timeout)<0)
    {
        printf("Reading from channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -4;
    }

	
	/* Reset the index Counters for channel A and channel B */
    indexA = 0;
    indexB = 0;
    readIndexA = 0;
    readIndexB = 0;

    return uiWritten;

}


/** \brief sends the content of the global buffers to the ftdi chip 

This function sends the content of the global Buffers aucBufferA and aucBufferB to the ftdi chip. 
Furthermore it reads back the data of pins which were configured as input. The function returns a value which equals the amount of read back bytes.
The parameter aucReadbuffer will be used for storing 16 read back unsigned char values
	@param[in] 		ftdiA, ftdiB pointer to a ftdi_context
	@param[in, out] aucReadBuffer pointer to array of unsigned char values
	@param[in]		ucReadBufferLength number of elements to be stored in aucReadbuffer
	@return			>0: number of bytes read back from the ftdi chip 
	@return			-1: writing to channel A failed 
	@return			-2: writing to channel B failed
	@return			-3: reading from channel A failed
	@return			-4: reading from channel B failed
					

*/

int send_package_read8(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned char* aucReadBuffer, unsigned char ucReadBufferLength)
{

    unsigned int uiWritten;
    unsigned int uiRead;

	
	/* Send to Channel A */
	
    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->in_ep, aucBufferA, indexA, &uiWritten, ftdiA->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -1;
    }

	/* Send to chanel B */
    if(libusb_bulk_transfer(ftdiB->usb_dev, ftdiB->in_ep, aucBufferB, indexB, &uiWritten, ftdiB->usb_write_timeout)<0)
    {
        printf("Writing to Channel %s failed!\n", ftdiB->interface==0?"A":(ftdiB->interface==1?"B":" error - invalid channel"));
        return -2;
    }

	/* Read from Channel A */
    if(libusb_bulk_transfer(ftdiA->usb_dev, ftdiA->out_ep, aucBufferA, sizeof(aucBufferA), &uiRead, ftdiA->usb_write_timeout)<0)
    {
        printf("Reading from channel %s failed!\n", ftdiA->interface==0?"A":(ftdiA->interface==1?"B":" error - invalid channel"));
        return -3;
    }

	/* Read from Channel B */
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

	/* Reset the index counters for Channel A and channel B */
    indexA = 0;
    indexB = 0;
    readIndexA = 0;
    readIndexB = 0;
    return uiRead;

}


/** \brief sends the content of the global buffers to the ftdi chip 

This function sends the content of the global Buffers aucBufferA and aucBufferB to the ftdi chip. 
Furthermore it reads back the data of pins which were configured as input. The function returns a value which equals the amount of read back bytes.
The parameter ausReadbuffer will be used for storing 16 read back unsigned short int values of 16 sensors 
	@param[in] 		ftdiA, ftdiB pointer to a ftdi_context
	@param[in, out] ausReadBuffer pointer to array of unsigned short values
	@param[in]		ucReadBufferLength number of elements to be stored in ausReadbuffer
	@return			>0: number of bytes read back from the ftdi chip 
	@return			-1: writing to channel A failed 
	@return			-2: writing to channel B failed
	@return			-3: reading from channel A failed
	@return			-4: reading from channel B failed
					

*/
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

        /* Channel BC */
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

	
	/* Reset the index counters for Channel A and channel B */
    indexA = 0;
    indexB = 0;
    readIndexA = 0;
    readIndexB = 0;
    return uiRead;

}
