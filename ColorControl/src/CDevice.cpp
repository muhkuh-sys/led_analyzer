#include "CDevice.h"

CDevice::CDevice()
{
    m_isConnected = false;
}

CDevice::~CDevice()
{
    //dtor
}

const char* CDevice::GetSerialNumber()
{
    return m_serialNumber;
}

void CDevice::SetValues()
{



    for(int i = 0; i<16; i++)
    {
        m_sensorData[i].SetPosition(i+1);
        m_sensorData[i].SetWavelength(0);
        m_sensorData[i].SetSaturation(0);
        m_sensorData[i].SetIllumination(0);
        m_sensorData[i].SetGain((tcs3472_gain_t)0);
        m_sensorData[i].SetIntTime((tcs3472_intTime_t)0);
        m_sensorData[i].SetColor(0xff, 0xff, 0xff);
    }

}
