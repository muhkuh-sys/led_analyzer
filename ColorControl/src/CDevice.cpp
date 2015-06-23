#include "CDevice.h"

CColorController::CColorController()
{
    m_isConnected = false;
}

CColorController::~CColorController()
{

}

void CColorController::SetValues(int pos[16], int wavelength[16], int saturation[16], float illuminatin[16],
                                 wxColor color[16], tcs3472_gain_t gain[16], tcs3472_intTime_t intTime[16] )
{
    for(int i = 0; i<16; i++)
    {
        m_sensorData[i].SetPosition(pos[i]);
        m_sensorData[i].SetWavelength(wavelength[i]);
        m_sensorData[i].SetSaturation(saturation[i]);
        m_sensorData[i].SetIllumination(illuminatin[i]);
        m_sensorData[i].SetGain(gain[i]);
        m_sensorData[i].SetIntTime(intTime[i]);
        m_sensorData[i].SetColor(0xff, 0xff, 0xff);

    }
}
