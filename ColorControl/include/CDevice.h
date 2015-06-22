#ifndef CDEVICE_H
#define CDEVICE_H

#include "CSensorData.h"

class CColorController
{
    public:
        CColorController();
        void SetValues(int pos[16], int wavelength[16], int saturation[16], float illuminatin[16],
                        wxColor color[16], tcs3472_gain_t gain[16], tcs3472_intTime_t intTime[16] );
        virtual ~CColorController();
    protected:
    private:
        CSensorData m_sensorData[16];
        char m_serialNumber[128];
        bool m_isConnected;
        int  m_deviceNumber;

        const char* GetSerialNumber();

};




#endif // CColorController_H
