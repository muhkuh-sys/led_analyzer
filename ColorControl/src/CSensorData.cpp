#include "CSensorData.h"

CSensorData::CSensorData()
{

    m_rgbColor.Set(255, 255, 255);

}

CSensorData::~CSensorData()
{
    //dtor
}

void CSensorData::SetPosition(int pos)
{
    if((pos>0) && (pos<17)) m_posSensor = pos;
    else
    {
       wxLogMessage(wxT("ERROR unknown sensor position"));
       m_posSensor = 999;
    }
}

void CSensorData::SetColor(unsigned char red, unsigned char green, unsigned char blue)
{
    m_rgbColor.Set(red, green, blue);
}

void CSensorData::SetWavelength(int wavelength)
{
    if ((wavelength < 380) || (wavelength > 730))
        m_wavelength = 0;
    else m_wavelength = wavelength;
}

void CSensorData::SetSaturation(int saturation)
{
    if(saturation >= 0 || saturation <= 100)
        m_saturation = saturation;
    else m_saturation = 0;
}

void CSensorData::SetIllumination(float illumination)
{
    if(illumination >= 0.)
        m_illumination = illumination;
    else m_illumination = 0.;
}

const wxString CSensorData::StateToString(sensor_state_t state)
{
    switch(state)
    {
        case SENSOR_OK:
            return "OK";
            break;
        case SENSOR_ID_ERROR:
            return "ID ERROR";
            break;
        case SENSOR_INCOMPLETE_CONVERSION:
            return "INCOMPL. CONV.";
            break;
        case SENSOR_EXCEEDED_CLEAR:
            return "MAXIMUM CLEAR";
            break;
        case DEVICE_ERROR_FATAL:
            return "DEVICE ERROR FATAL";
        default:
            return "UNKNOWN";
            break;
    }
}
