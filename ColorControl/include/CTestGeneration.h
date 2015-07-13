#ifndef CTESTGENERATION_H
#define CTESTGENERATION_H

#include "../GUIFrame.h"
#include "PanelSensor.h"


#define COLOR_WARNING{210, 150, 0  }
#define COLOR_OK     {0  , 255, 0  }

class CTestGeneration
{
    private:
        enum E_TESTCASES
        {
            ENTRY_NAME_EXISTENT = 1,
            ENTRY_PINNUMBER_EXISTENT,
            NAME_FITS_PINNUMBER,
            SAME_NAME_DIFFERENT_SENSORS
        };

    public:
        CTestGeneration();
        virtual ~CTestGeneration();

        void GenerateColorTestTable(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile);
        void GenerateNetXTestTable(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile, bool useNetX);
        void GenerateTestStepFunctions(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile, bool useNetX);
        void InsertHeaders(wxTextFile* tFile, bool useNetX);
        void GenerateTest(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile, bool useNetX, wxTextCtrl* txtCtrlLog);

        int  GetMaximumNumberOfTestsets(wxVector<PanelSensor*> sensorPanel);
        int  GetLastEntry(wxVector<PanelSensor*> sensorPanel);
        bool TestEntriesOK(wxVector<PanelSensor*> sensorPanel, wxTextCtrl* txtCtrlLog, bool useNetX);
};

#endif // CTESTGENERATION_H
