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
        void        SetState(int iErrorCode);
        void        SetClearRatio(int iSensorIndex, int iRatio);
        void        SetTolNm(int tolNm);
        void        SetTolSat(int tolSat);
        void        SetTolIllu(int tolIllu);
        int         GetWavelength(int iSensorIndex){return m_sensorData[iSensorIndex].GetWavelength();};
        int         GetSaturation(int iSensorIndex){return m_sensorData[iSensorIndex].GetSaturation();};
        int         GetIllumination(int iSensorIndex){return m_sensorData[iSensorIndex].GetIllumination();};
        int         GetClearRatio(int iSensorIndex){return m_sensorData[iSensorIndex].GetClearRatio();};
        int         GetTolNm(){return m_tolnm;};
        int         GetTolSat(){return m_tolsat;};
        int         GetTolIllu(){return m_tolillu;};
        wxColor     GetColour(int iSensorIndex){return m_sensorData[iSensorIndex].GetColour();};
        tcs3472_gain_t    GetGain(int iSensorIndex) {return m_sensorData[iSensorIndex].GetGain();};
        tcs3472_intTime_t GetIntTime(int iSensorIndex) {return m_sensorData[iSensorIndex].GetIntTime();};
        const wxString    GetState(int iSensorIndex) {return m_sensorData[iSensorIndex].GetState();};
    protected:
    private:
        CSensorData m_sensorData[16];
        char        m_serialNumber[128];
        bool        m_isConnected;
        int         m_deviceNumber;

        int         m_tolnm;
        int         m_tolsat;
        int         m_tolillu;
        int         IntegrationToIndex(tcs3472_intTime_t intTime);


};




#endif // CColorController_H
