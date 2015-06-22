#ifndef CDEVICE_H
#define CDEVICE_H

#include "CSensorData.h"

class CDevice
{
    public:
        CDevice();
        void SetValues();
        virtual ~CDevice();
    protected:
    private:
        CSensorData m_sensorData[16];
        char m_serialNumber[128];
        bool m_isConnected;
        int  m_deviceNumber;
        const char* GetSerialNumber();

};

#endif // CDEVICE_H
