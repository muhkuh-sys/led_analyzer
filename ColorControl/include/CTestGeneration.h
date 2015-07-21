#ifndef CTESTGENERATION_H
#define CTESTGENERATION_H

#include "GUIFrame.h"
#include "PanelSensor.h"



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
        bool GenerateTest(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile, bool useNetX);
        wxString GetFunctionAutomatedNetXConnection();
        bool FileLEDStimulation(wxVector<PanelSensor*> vectorSensorPanel, wxString strPlugin);

        int  GetMaximumNumberOfTestsets(wxVector<PanelSensor*> vectorSensorPanel);
        int  GetLastEntryWithVectors(wxVector<PanelSensor*> vectorSensorPanel);
        int  GetLastEntryWithPinnumber(wxVector<PanelSensor*> vectorSensorPanel);

        /* Check the entries for led stimulation */
        bool CheckLEDStimulation(wxVector<PanelSensor*> vectorSensorPanel);
        /* check the entries for testfile generation */
        bool CheckTestGeneration(wxVector<PanelSensor*> vectorSensorPanel, bool useNetX);
        /* Save and Open a Session */
        void SaveSessionAsIni(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile);
        bool OpenSessionAsIni(wxVector<PanelSensor*> vectorSensorPanel, wxFileConfig* tFileConfig);
        bool FillTestrowsWithContent(PanelSensor* sensorPanel, int iSensorCounter, wxFileConfig* tFileConfig);
};

#endif // CTESTGENERATION_H
