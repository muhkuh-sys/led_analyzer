#ifndef CDEVICE_H
#define CDEVICE_H

#include "CSensorData.h"

class CDevice
{
    public:
        CDevice();
        virtual ~CDevice();
    protected:
    private:
        CSensorData m_sensorData[16];
};

#endif // CDEVICE_H
