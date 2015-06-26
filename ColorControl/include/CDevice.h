#ifndef CDEVICE_H
#define CDEVICE_H

#include "CSensorData.h"

class CColorController
{
    public:
        CColorController();
        virtual     ~CColorController();
        void        SetConnectivity(bool status){m_isConnected = status;};
        bool        IsConnected(){return m_isConnected;};
        const char* GetSerialNumber(){return m_serialNumber;};
        void        SetSerialNumber(const char strSerial[128]){strcpy(m_serialNumber, strSerial);};
        void        SetWavelength(int iSensorIndex, int iWavelength);
        void        SetSaturation(int iSensorIndex, int iSaturation);
        void        SetIllumination(int iSensorIndex, int iIllumination);
        void        SetColour(int iSensorIndex, int r, int g, int b);
        void        SetGain(int iSensorIndex, tcs3472_gain_t tGain);
        void        SetIntTime(int iSensorIndex, tcs3472_intTime_t tIntTime);
        void        SetClearRatio(int iSensorIndex, int iRatio);
        int         GetWavelength(int iSensorIndex){return m_sensorData[iSensorIndex].GetWavelength();};
        int         GetSaturation(int iSensorIndex){return m_sensorData[iSensorIndex].GetSaturation();};
        int         GetIllumination(int iSensorIndex){return m_sensorData[iSensorIndex].GetIllumination();};
        int         GetClearRatio(int iSensorIndex){return m_sensorData[iSensorIndex].GetClearRatio();};
        wxColor     GetColour(int iSensorIndex){return m_sensorData[iSensorIndex].GetColour();};
    protected:
    private:
        CSensorData m_sensorData[16];
        char        m_serialNumber[128];
        bool        m_isConnected;
        int         m_deviceNumber;



};




#endif // CColorController_H
