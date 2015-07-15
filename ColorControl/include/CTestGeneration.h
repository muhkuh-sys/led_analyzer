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

        void GenerateColorTestTable(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile);
        void GenerateNetXTestTable(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile, bool useNetX);
        void GenerateTestStepFunctions(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile, bool useNetX);
        void GenerateInitialization(wxTextFile* tFile, bool useNetX);
        void InsertHeaders(wxTextFile* tFile, bool useNetX);
        void GenerateTestSteps(wxVector<PanelSensor*> panelSensor, wxTextFile* tFile, bool useNetX);
        void GenerateSettingsTable(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile);
        void GenerateTest(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile, bool useNetX, wxTextCtrl* txtCtrlLog);
        void FileLEDStimulation(wxVector<PanelSensor*> vectorSensorPanel);

        int  GetMaximumNumberOfTestsets(wxVector<PanelSensor*> vectorSensorPanel);
        int  GetLastEntry(wxVector<PanelSensor*> vectorSensorPanel);
        bool TestEntriesOK(wxVector<PanelSensor*> vectorSensorPanel, wxTextCtrl* txtCtrlLog, bool useNetX);

        /* Save and Open a Session */
        void SaveSessionAsIni(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile);
        bool OpenSessionAsIni(wxVector<PanelSensor*> vectorSensorPanel, wxFileConfig* tFileConfig);
        bool FillTestrowsWithContent(PanelSensor* sensorPanel, int iSensorCounter, wxFileConfig* tFileConfig);
};

#endif // CTESTGENERATION_H
