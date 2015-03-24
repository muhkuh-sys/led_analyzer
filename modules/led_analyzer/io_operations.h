


#include <stdio.h>
#include "ftdi.h"
#include "libusb.h"


int io_write(struct ftdi_context* ftdi, unsigned char* aucSendbuffer, unsigned char ucSizeSendbuffer);

int writeOutputs(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, const unsigned long ulOutput);

int readInputs(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, const unsigned char* readBack);

void process_pins(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned long ulIOMask, unsigned long ulOutput);

void process_pins_databack(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned long ulIOMask, unsigned long ulOutput);

int send_package_write8(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB);

int send_package_read8(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned char* aucReadBuffer, unsigned char ucReadBufferLength);

int send_package_read16(struct ftdi_context *ftdiA, struct ftdi_context *ftdiB, unsigned short* ausReadBuffer, unsigned char ucReadBufferLength);


