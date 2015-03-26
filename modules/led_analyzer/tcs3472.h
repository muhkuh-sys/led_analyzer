
#include "i2c_routines.h"

// slave address
#define TCS_ADDRESS 0x29
#define TCS3471_ADDRESS_2 0x39

// registers to read
#define TCS3471_ENABLE_REG 0x00
#define TCS3471_ATIME_REG 0x01
#define TCS3471_WTIME_REG 0x03
#define TCS3471_AILTL_REG 0x04
#define TCS3471_AILTH_REG 0x05
#define TCS3471_AIHTL_REG 0x06
#define TCS3471_AIHTH_REG 0x07
#define TCS3471_PERS_REG 0x0C
#define TCS3471_CONFIG_REG 0x0D
#define TCS3471_CONTROL_REG 0x0F
#define TCS3471_ID_REG 0x12
#define TCS3471_STATUS_REG 0x13
#define TCS3471_CDATA_REG 0x14
#define TCS3471_CDATAH_REG 0x15
#define TCS3471_RDATA_REG 0x16
#define TCS3471_RDATAH_REG 0x17
#define TCS3471_GDATA_REG 0x18
#define TCS3471_GDATAH_REG 0x19
#define TCS3471_BDATA_REG 0x1A
#define TCS3471_BDATAH_REG 0x1B

// command register bits
#define TCS3471_COMMAND_BIT 0x80
#define TCS3471_AUTOINCR_BIT 0x20
#define TCS3471_SPECIAL_BIT 0x60
#define TCS3471_INTCLEAR_BIT 0x06

// enable register bits
#define TCS3471_AIEN_BIT 0x10
#define TCS3471_WEN_BIT 0x08
#define TCS3471_AEN_BIT 0x02
#define TCS3471_PON_BIT 0x01

// configuration register bits
#define TCS3471_WLONG_BIT 0x02

// ID register values
#define TCS3471_1_5_VALUE 0x14
#define TCS3471_3_7_VALUE 0x1D

// status register bits
#define TCS3471_AINT_BIT 0x10
#define TCS3471_AVALID_BIT 0x01


typedef enum
{
    TCS3471_GAIN_1X = 0x00,
    TCS3471_GAIN_4X = 0x01,
    TCS3471_GAIN_16X = 0x02,
    TCS3471_GAIN_60X = 0x03,
    TCS3471_GAIN_ERROR = 0xFF
}
tcs3471Gain_t;

typedef enum
{
    TCS3471_INTEGRATION_2_4ms 		 = 0xFF,
    TCS3471_INTEGRATION_24ms 		 = 0xF6,
    TCS3471_INTEGRATION_100ms 		 = 0xD6,
    TCS3471_INTEGRATION_200ms		 = 0xAD,
    TCS3471_INTEGRATION_154ms 		 = 0xC0,
    TCS3471_INTEGRATION_700ms        = 0x00
}
tcs3471Integration_t;

enum tcs_color_t
{
  RED       = 0x00,
  GREEN     = 0x01,
  BLUE      = 0x02,
  CLEAR     = 0x03
}
colors;

unsigned short int tcs_setIntegrationTime(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3471Integration_t integration);
unsigned short int tcs_identify(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer);
unsigned short int tcs_setGain(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, tcs3471Gain_t gain);
unsigned short int tcs_waitForData(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer);
unsigned short int tcs_rgbcInvalid(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned char* aucReadbuffer);
unsigned short int tcs_readColour(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* ausColourArray, enum tcs_color_t colour);
unsigned short int tcs_sleep(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
unsigned short int tcs_wakeUp(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
unsigned short int tcs_ON(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
unsigned short int tcs_exClear(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* usClear, unsigned int uiIntegrationtime);
unsigned short int tcs_clearInt(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB);
void               tcs_waitIntegrationtime(tcs3471Integration_t uiIntegrationtime);
unsigned short int tcs_getGain(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* usGainSettings);
unsigned short int tcs_getIntegrationtime(struct ftdi_context* ftdiA, struct ftdi_context* ftdiB, unsigned short* ausInttimeSettings);



