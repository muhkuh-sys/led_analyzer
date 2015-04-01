
#include "io_operations.h"

/* Wird auf Kanal a Lowbyte (AD) gemapped */
#define SDA_0_OUTPUT 0x55
#define SDA_0_INPUT  0x00
#define SCL_0        0xAA
#define SDA0         0x01
#define SCL0         0x02
#define SDA1         0x04
#define SCL1         0x08
#define SDA2         0x10
#define SCL2         0x20
#define SDA3         0x40
#define SCL3         0x80


/* Wird später auf Kanal A, Highbyte (AC) gemapped */
#define SDA_1_OUTPUT 0x5500
#define SDA_1_INPUT  0x00
#define SCL_1        0xAA00
#define SDA4         0x100
#define SCL4         0x200
#define SDA5         0x400
#define SCL5         0x800
#define SDA6         0x1000
#define SCL6         0x2000
#define SDA7         0x4000
#define SCL7         0x8000


/* Wird später auf Kanal B, Lowbyte(BD) gemapped */
#define SDA_2_OUTPUT 0x550000
#define SDA_2_INPUT  0x00
#define SCL_2        0xAA0000
#define SDA8         0x10000
#define SCL8         0x20000
#define SDA9         0x40000
#define SCL9         0x80000
#define SDA10        0x100000
#define SCL10        0x200000
#define SDA11        0x400000
#define SCL11        0x800000

/* Wird später auf Kanal B, Highbyte (BC) gemapped */
#define SDA_3_OUTPUT 0x55000000
#define SDA_3_INPUT  0x00
#define SCL_3        0xAA000000
#define SDA12        0x1000000
#define SCL12        0x2000000
#define SDA13        0x4000000
#define SCL13        0x8000000
#define SDA14        0x10000000
#define SCL14        0x20000000
#define SDA15        0x40000000
#define SCL15        0x80000000


#define I2C_DELAYTIME 10

#define SDA_WRITE 0x0
#define SDA_READ 0x55555555

#define SCL 0xAAAAAAAA

#define SDA_0WRITE 0x00
#define SDA_0READ  0x00000055

int  i2c_setSpeed(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned int uiSpeedkHz);
void i2c_startCond   (struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
void i2c_stopCond    (struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
void i2c_clock       (struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned long ulDataToSend);
void i2c_clockInput(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned long ulDataToSend);
void i2c_giveAck(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
void i2c_clock_forACK(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned long ulDataToSend);
void i2c_getAck(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
int  i2c_read16(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucSendBuffer, unsigned char ucLength,
              unsigned short* ausReadBuffer, unsigned char ucReadBufferLength);
int  i2c_read8(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucSendBuffer, unsigned char ucLength,
              unsigned char* aucRecBuffer, unsigned char ucRecLength);
			  
int  i2c_write8  (struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucSendBuffer, unsigned char ucLength);
int  i2c_write8_x(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucSendBuffer, unsigned char ucLength, unsigned int uiX);