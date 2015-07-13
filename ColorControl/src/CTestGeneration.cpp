#include "CTestGeneration.h"

CTestGeneration::CTestGeneration()
{
    //ctor
}

CTestGeneration::~CTestGeneration()
{
    //dtor
}


void CTestGeneration::GenerateColorTestTable(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile)
{
    int iDevCounter = 0;
    int iNumberOfTestSets = this->GetMaximumNumberOfTestsets(sensorPanel);

    tFile->AddLine(" ---------------------- ColorControl LEDs under test ---------------------- ");

    for( int i = 0; i < iNumberOfTestSets; i++)
    {
        tFile->AddLine(wxString::Format(wxT("-- LED Testset # %i --\n"), i));
        tFile->AddLine(wxString::Format(wxT("local tTestSet%i = {\n"), i));

        /* Iterate over Sensor Panels */
        for(int j = 0; j < sensorPanel.size(); j++)
        {
            /* We reached a new device */
            if(j%16 == 0) tFile->AddLine(wxString::Format(wxT("[%2i] = {"), iDevCounter++));


            /* Get your rows in case the row really exists in the testrow vector */
            if((sensorPanel.at(j)->GetVectorTestrow().size()) > i)
            {
                /* Add the testline */
                tFile->AddLine(sensorPanel.at(j)->GetTestrow(j, i));

            }
            /* In case the row does not exist Generate a Empty Testrow */
            else  tFile->AddLine(sensorPanel.at(j)->GetEmptyTestrow(j));



            /* Last Entry of a device */
            if(j%16 == 15)
            {
                /* The last device entry needs no comma */
                if( j == (sensorPanel.size() - 1)) tFile->AddLine(wxT("}\n"));

                /* All other device entries need a comma */
                else tFile->AddLine(wxT("},\n"));
            }
        }


        tFile->AddLine(wxT("}"));
        iDevCounter = 0;
    }

    wxString strTestSets;
    for(int i = 0; i < iNumberOfTestSets; i++)
    {
        if(i == 0) strTestSets += wxT("local atTestSets = { ");
        /* Last TestSet*/
        if(i == iNumberOfTestSets - 1) strTestSets += wxString::Format(wxT("tTestSet%d }"), i);
        /* Else */
        else strTestSets += wxString::Format(wxT("tTestSet%d,"), i);

    }

    tFile->AddLine(strTestSets);

}

int CTestGeneration::GetMaximumNumberOfTestsets(wxVector<PanelSensor*> sensorPanel)
{
    /* Initialize the maximum number with zero */
    int iMaxNumber = 0;
    int iTemp;

    /* Search for the maximum amount of testsets we have */
    for(wxVector<PanelSensor*>::iterator it = sensorPanel.begin(); it!= sensorPanel.end(); it++)
    {
        if( (iTemp = (*it)->GetVectorTestrow().size()) > iMaxNumber) iMaxNumber = iTemp;
    }

    return iMaxNumber;
}

void CTestGeneration::GenerateNetXTestTable(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile, bool useNetX)
{
    if(useNetX == true)
    {
        tFile->AddLine(wxT(" --------------------------- netX I/O Table ---------------------------\n "));
        tFile->AddLine(wxT(" local atPinsUnderTest = {\n"));

        int iDevCounter = 0;
        int iIndexLastEntry   = this->GetLastEntry(sensorPanel);

        for(int i = 0; i < sensorPanel.size(); i++)
        {

            if(sensorPanel.at(i)->GetVectorTestrow().size() > 0)
            {
                if( i == iIndexLastEntry) tFile->AddLine(sensorPanel.at(i)->GetAtPinsUnderTest(true));

                else  tFile->AddLine(sensorPanel.at(i)->GetAtPinsUnderTest(false));
            }

        }

        tFile->AddLine(wxT("}"));
    }
}

int CTestGeneration::GetLastEntry(wxVector<PanelSensor*> sensorPanel)
{
    int iLastEntry = -1;

    /* Search for the last sensor entry which contains testrows */
    for(int i = 0; i<sensorPanel.size(); i++)
    {
        if( sensorPanel.at(i)->GetVectorTestrow().size() > 0) iLastEntry = i;
    }

    return iLastEntry;
}

bool CTestGeneration::TestEntriesOK(wxVector<PanelSensor*> sensorPanel, wxTextCtrl* txtCtrlLog, bool useNetX)
{

  int iSensorNumber;
  bool testEntriesOK = true;

  /* As this function only emits warning messages we can change the text colour attribute to orange */
  txtCtrlLog->SetDefaultStyle(wxTextAttr(COLOR_WARNING));

  for(wxVector<PanelSensor*>::iterator it_sensor = sensorPanel.begin(); it_sensor != sensorPanel.end(); it_sensor++)
  {
     for(int i = 0; i < (*it_sensor)->GetVectorTestrow().size(); i++)
     {
         /* Names must be existent */
         if((*it_sensor)->GetVectorTestrow().at(i)->IsNameFieldEmpty())
         {
             iSensorNumber = (*it_sensor)->GetSensorNumber();
             wxLogWarning(wxString::Format(wxT("Name Entry for Sensor %d row %d missing!"), iSensorNumber, i+1));
             testEntriesOK =  false;

         }
         /* PinNumbers must be existent if Use netX is checked */
         if(useNetX)
         {
             if((*it_sensor)->GetVectorTestrow().at(i)->IsPinNumberFieldEmpty())
             {
                 iSensorNumber = (*it_sensor)->GetSensorNumber();
                 wxLogWarning(wxString::Format(wxT("Pin Number Entry for Sensor %d row %d missing!"), iSensorNumber, i+1));
                 testEntriesOK =  false;

             }
         }
     }
  }
  /* Change the text colour back to normal */
  txtCtrlLog->SetDefaultStyle(wxTextAttr(*wxBLACK));

  return testEntriesOK;
}

void CTestGeneration::InsertHeaders(wxTextFile* tFile, bool useNetX)
{
    /* Get the right requires for the test */
    tFile->AddLine("require(\"color_control.lua\"");

    if(useNetX)
    {
        tFile->AddLine("require(\"muhkuh_cli_init.lua\")");
        tFile->AddLine("require(\"io_marix.lua\")\n");
    }

}

void CTestGeneration::GenerateTestStepFunctions(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile, bool useNetX)
{
    int iMaxNumber = this->GetMaximumNumberOfTestsets(sensorPanel);

    if(useNetX)
    {
        tFile->AddLine(wxT("-- Iterate over all devices and its testsets"));
        /* Iterate over all Testsets and push the desired pin value onto the netX */
        for(int iTestIndex = 0; iTestIndex < iMaxNumber; iTestIndex++)
        {
            tFile->AddLine(wxString::Format(wxT("-- apply pin states for test set %d"), iTestIndex));
            tFile->AddLine(wxString::Format(wxT("local function applyPinState%d()"), iTestIndex));

            for(wxVector<PanelSensor*>::iterator it = sensorPanel.begin(); it!= sensorPanel.end(); it++)
            {
                if((*it)->GetVectorTestrow().size() > iTestIndex)
                {
                    tFile->AddLine((*it)->GetPinStateTestSet(iTestIndex));
                }
            }

            tFile->AddLine(wxT("end"));
        }
    }

}

void CTestGeneration::GenerateTest(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile, bool useNetX, wxTextCtrl* txtCtrlLog)
{

    if(!this->TestEntriesOK(sensorPanel, txtCtrlLog, useNetX))
    {
       if(!tFile->Close()) wxLogMessage("Couldn't close test file.");
       txtCtrlLog->SetDefaultStyle(wxTextAttr(*wxRED));
       wxLogMessage("Errors occured ... abort.");
       txtCtrlLog->SetDefaultStyle(wxTextAttr(*wxBLACK));
       return;
    }

    this->InsertHeaders(tFile, useNetX);
    this->GenerateColorTestTable(sensorPanel, tFile);
    this->GenerateNetXTestTable(sensorPanel, tFile, useNetX);
    this->GenerateTestStepFunctions(sensorPanel, tFile);

}
