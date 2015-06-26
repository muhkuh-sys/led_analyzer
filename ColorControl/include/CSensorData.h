#ifndef CSENSORDATA_H
#define CSENSORDATA_H

#include "../GUIFrame.h"

enum tcs3472_intTime_t
{
    TCS3472_INTEGRATION_2_4ms 		= 0xFF,
    TCS3472_INTEGRATION_24ms 		= 0xF6,
    TCS3472_INTEGRATION_100ms 		= 0xD6,
    TCS3472_INTEGRATION_200ms	    = 0xAD,
    TCS3472_INTEGRATION_154ms 		= 0xC0,
    TCS3472_INTEGRATION_700ms       = 0x00
};

enum tcs3472_gain_t
{
    TCS3472_GAIN_1X  = 0x00,
    TCS3472_GAIN_4X  = 0x01,
    TCS3472_GAIN_16X = 0x02,
    TCS3472_GAIN_60X = 0x03
};


class CSensorData
{
    private:
        int               m_posSensor;
        int               m_wavelength;
        int               m_saturation;
        int               m_clearRatio;
        float             m_illumination;
        wxColor           m_rgbColor;
        tcs3472_gain_t    m_gain;
        tcs3472_intTime_t m_intTime;



    public:
        CSensorData();
        ~CSensorData();

        void SetPosition(int pos);
        void SetWavelength(int wavelength);
        void SetSaturation(int saturation);
        void SetIllumination(float illumination);
        void SetColor(unsigned char red, unsigned char green, unsigned char blue);
        void SetGain(tcs3472_gain_t gain){m_gain = gain;};
        void SetIntTime(tcs3472_intTime_t intTime){m_intTime = intTime;};
        void SetClearRatio(int iClearRatio){m_clearRatio = iClearRatio;};

        int     GetPosition(){return m_posSensor;};
        int     GetWavelength(){return m_wavelength;};
        int     GetSaturation(){return m_saturation;};
        int     GetClearRatio(){return m_clearRatio;};
        wxColour GetColour(){return m_rgbColor;};
        float   GetIllumination(){return m_illumination;};
        wxColor GetColor(){return m_rgbColor;};
        tcs3472_gain_t    GetGain(){return m_gain;};
        tcs3472_intTime_t GetIntTime(){return m_intTime;};


};


#endif // CSENSORDATA_H



