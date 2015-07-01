#include "CDevice.h"

CColorController::CColorController()
{
    m_isConnected = false;

}

CColorController::~CColorController()
{

}


void CColorController::SetWavelength(int iSensorIndex, int iWavelength)
{
	m_sensorData[iSensorIndex].SetWavelength(iWavelength);
}

void CColorController::SetSaturation(int iSensorIndex, int iSaturation)
{
	m_sensorData[iSensorIndex].SetSaturation(iSaturation);
}

void CColorController::SetIllumination(int iSensorIndex, int iIllumination)
{
	m_sensorData[iSensorIndex].SetIllumination(iIllumination);
}

void CColorController::SetColour(int iSensorIndex, int r, int g, int b)
{
    m_sensorData[iSensorIndex].SetColor(r, g, b);
}

void CColorController::SetGain(int iSensorIndex, tcs3472_gain_t tGain)
{
	m_sensorData[iSensorIndex].SetGain(tGain);
}

void CColorController::SetIntTime(int iSensorIndex, tcs3472_intTime_t tIntTime)
{
	m_sensorData[iSensorIndex].SetIntTime(tIntTime);
}

void CColorController::SetClearRatio(int iSensorIndex, int iClearRatio)
{
    m_sensorData[iSensorIndex].SetClearRatio(iClearRatio);
}

void CColorController::SetTolNm(int tolNm)
{
    if(tolNm > 0)
    {
        m_tolnm = tolNm;
    }

    else m_tolnm = 10; // Default wavelength tolerance
}

void CColorController::SetTolSat(int tolSat)
{
    if(tolSat > 0)
    {
        m_tolsat = tolSat;
    }

    else m_tolsat = 10; // Default saturation tolerance
}

void CColorController::SetTolIllu(int tolIllu)
{
    if(tolIllu > 0)
    {
        m_tolillu = tolIllu;
    }

    else m_tolillu = 50;
}
