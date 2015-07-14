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
            if(j%16 == 0) tFile->AddLine(wxString::Format(wxT(" [%2i] = {"), iDevCounter++));


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
                if( j == (sensorPanel.size() - 1)) tFile->AddLine(wxT("   }\n"));

                /* All other device entries need a comma */
                else tFile->AddLine(wxT("   },\n"));
            }
        }


        tFile->AddLine(wxT("}\n"));
        iDevCounter = 0;
    }

    wxString strTestSets;
    for(int i = 0; i < iNumberOfTestSets; i++)
    {
        if(i == 0) strTestSets += wxT("local atTestSets = { ");
        /* Last TestSet*/
        if(i == iNumberOfTestSets - 1) strTestSets += wxString::Format(wxT("tTestSet%d }\n"), i);
        /* Else */
        else strTestSets += wxString::Format(wxT("tTestSet%d, "), i);

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

        tFile->AddLine(wxT("}\n"));
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
    tFile->AddLine("require(\"color_control\")");

    if(useNetX)
    {
        tFile->AddLine("require(\"muhkuh_cli_init\")");
        tFile->AddLine("require(\"io_matrix\"\n)");
    }

    tFile->AddLine("-- be pessimistic ");
    tFile->AddLine("local retval = TEST_RESULT_FAIL\n");

}

void CTestGeneration::GenerateTestStepFunctions(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile, bool useNetX)
{
    int iMaxNumber = this->GetMaximumNumberOfTestsets(sensorPanel);

    if(useNetX)
    {
        tFile->AddLine(wxT("-- Functions triggers the desired pin state for a testset"));
        /* Iterate over all Testsets and push the desired pin value onto the netX */
        for(int iTestIndex = 0; iTestIndex < iMaxNumber; iTestIndex++)
        {
            tFile->AddLine(wxString::Format(wxT("-- apply pin states for test set %d"), iTestIndex));
            tFile->AddLine(wxString::Format(wxT("local function applyPinState%d(aAttr)"), iTestIndex));

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



void CTestGeneration::GenerateInitialization(wxTextFile* tFile, bool useNetX)
{
    if(useNetX)
    {
        tFile->AddLine(wxT("-- Device connection ----------------------"));
        tFile->AddLine(wxT("-- netX"));
        tFile->AddLine(wxT("tPlugin = tester.getCommonPlugin()"));
        tFile->AddLine(wxT("if tPlugin==nil then"));
        tFile->AddLine(wxT("    error(\"No plugin selected, nothing to do!\")"));
        tFile->AddLine(wxT("end\n"));
    }

    tFile->AddLine(wxT("-- Color Controller"));
    tFile->AddLine(wxT("scanDevices()"));
    tFile->AddLine(wxT("local numberOfDevices = connectDevices()"));
    tFile->AddLine(wxT("if numberOfDevices <= 0 then"));
    tFile->AddLine(wxT("    error(\"No Color Controller detected, nothing to do!\")"));
    tFile->AddLine(wxT("end\n"));

    if(useNetX)
    {
        tFile->AddLine(wxT("-- Device initialization -------------------"));
        tFile->AddLine(wxT("-- netX"));
        tFile->AddLine(wxT("local aAttr = io_matrix.initialize(tPlugin, \"netx/iomatrix_netx%d.bin\")"));;
        tFile->AddLine(wxT("io_matrix.parse_pin_description(aAttr, atPinsUnderTest, ulVerbose)"));
    }

    if(useNetX)
    {
        tFile->AddLine(wxT("-- Turn off all LEDs"));
        tFile->AddLine(wxT("local uiCounter = 1"));
        tFile->AddLine(wxT("while(atPinsUnderTest[uiCounter] ~= nil) do"));
        tFile->AddLine(wxT("    io_matrix.set_pin(aAttr, atPinsUnderTest[uiCounter][1],2)"));
        tFile->AddLine(wxT("    uiCounter = uiCounter + 1"));
        tFile->AddLine(wxT("end\n"));
    }

    tFile->AddLine(wxT("-- Color Controller"));
    tFile->AddLine(wxT("initDevices(numberOfDevices, TCS3472_GAIN_1X, TCS3472_INTEGRATION_100ms)\n"));

}


void CTestGeneration::GenerateTestSteps(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile, bool useNetX)
{
    int iNumberOfTestSets = this->GetMaximumNumberOfTestsets(sensorPanel);

    tFile->AddLine(wxT("-- Actual Test -----------------------------"));
    /* Lua index for testtables start at 1 */
    for(int i = 1; i <= iNumberOfTestSets; i++)
    {

        if(useNetX)
        {
            tFile->AddLine(wxString::Format(wxT("-- Testset %d"), i));
            tFile->AddLine(wxString::Format(wxT("applyPinState%d(aAttr)"), i-1));
        }
        else
        {
            tFile->AddLine(wxString::Format(wxT("-- INSERT CODE TO TO STIMULATE THE LEDS OF TESTSET %d --"), i));
        }

        tFile->AddLine(wxT("led_analyzer.wait4Conversion(700)"));
        tFile->AddLine(wxT("startMeasurements(numberOfDevices)"));
        tFile->AddLine(wxString::Format(wxT("ret = validateLEDs(numberOfDevices, atTestSets[%d])\n"), i));
        tFile->AddLine(wxT("if ret ~= TEST_RESULT_OK then"));
        tFile->AddLine(wxT("    free()"));
        if(useNetX) tFile->AddLine("    ---- APPLY DEFAULT PINSTATES ---- ");
        tFile->AddLine(wxT("--    return  TEST_RESULT_FAIL"));
        tFile->AddLine(wxT("end\n"));
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
    this->GenerateTestStepFunctions(sensorPanel, tFile, useNetX);
    this->GenerateInitialization(tFile, useNetX);
    this->GenerateTestSteps(sensorPanel, tFile, useNetX);

}


void CTestGeneration::SaveSessionAsIni(wxVector<PanelSensor*> sensorPanel, wxTextFile* tFile)
{
    int iNumberOfSensors = sensorPanel.size();
    int rowCounter = 1;

    wxVector<PanelTestrow*> vectorTestrow;

    tFile->AddLine(wxT("[Testsession]"));
    tFile->AddLine(wxString::Format(wxT("numberOfSensors=%d\n"), iNumberOfSensors));

    /* Iterate over all Sensorpanels */
    for(wxVector<PanelSensor*>::iterator it = sensorPanel.begin(); it != sensorPanel.end(); it++)
    {
        tFile->AddLine(wxString::Format(wxT("[Sensor%d]"), (*it)->GetSensorNumber()));

        vectorTestrow = (*it)->GetVectorTestrow();
        tFile->AddLine(wxString::Format(wxT("numberOfTestrows=%d"), vectorTestrow.size()));

        /* Iterate over all testrows per sensor pannel */
        for(wxVector<PanelTestrow*>::iterator it_testrow = vectorTestrow.begin(); it_testrow!= vectorTestrow.end(); it_testrow++)
        {
            tFile->AddLine(wxString::Format(wxT("row%d_name=%s"), rowCounter, (*it_testrow)->GetName()));
            tFile->AddLine(wxString::Format(wxT("row%d_wavelength=%d"), rowCounter, (*it_testrow)->GetWavelength()));
            tFile->AddLine(wxString::Format(wxT("row%d_saturation=%d"), rowCounter, (*it_testrow)->GetSaturation()));
            tFile->AddLine(wxString::Format(wxT("row%d_illumination=%d"), rowCounter, (*it_testrow)->GetIllumination()));
            tFile->AddLine(wxString::Format(wxT("row%d_colour=%d"), rowCounter, (*it_testrow)->GetColour().GetRGB()));
            tFile->AddLine(wxString::Format(wxT("row%d_pintype=%d"), rowCounter, (*it_testrow)->GetPintype()));
            tFile->AddLine(wxString::Format(wxT("row%d_pinnumber=%d"), rowCounter, (*it_testrow)->GetPinNumber()));
            tFile->AddLine(wxString::Format(wxT("row%d_pinvalue=%d"), rowCounter, (*it_testrow)->GetPinValue()));
            tFile->AddLine(wxString::Format(wxT("row%d_pindefvalue=%d"), rowCounter, (*it_testrow)->GetPinDefValue()));
            tFile->AddLine(wxString::Format(wxT("row%d_tolnm=%d"), rowCounter, (*it_testrow)->GetTolWavelength()));
            tFile->AddLine(wxString::Format(wxT("row%d_tolsat=%d"), rowCounter, (*it_testrow)->GetTolSaturation()));
            tFile->AddLine(wxString::Format(wxT("row%d_tolillu=%d\n"), rowCounter, (*it_testrow)->GetTolIllumination()));

            rowCounter++;
        }
        /* Reset rowcounter */
        rowCounter = 0;
    }
}

bool CTestGeneration::OpenSessionAsIni(wxVector<PanelSensor*> sensorPanel, wxFileConfig* tFileConfig)
{
    int iCurSensorPanelSize = sensorPanel.size();
    int iSavedSensorPanelSize;

    if(iCurSensorPanelSize == 0)
    {
        wxLogMessage("Please connect first.");
        return false;
    }

    /* Return if you cannot read the number of sensors .. this is important as array exceedings
    might happen otherwise */
    if(!tFileConfig->Read("Testsession/numberOfSensors", &iSavedSensorPanelSize))
    {
        wxLogMessage("Test session file corrupted ..");
        return false;
    }


    /* Now iterate over all entries of the config file */

    int iCurNumberOfTestrows;
    int iSavedNumberOfTestrows;
    int iSensorCounter = 1;
    int iRowCounter = 1;
    int iTempRowCounter;

                    wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, (*it)->GetpButton()->GetId());
                    (*it)->GetpButton()->GetEventHandler()->ProcessEvent(evt);

    wxVector<PanelTestrow*> vectorTestrow;
    wxCommandEvent* evt;

    for(wxVector<PanelSensor*>::iterator it = sensorPanel.begin(); it != sensorPanel.end(); it++)
    {
        /* Only do it if the current sensor counter is smaller than the saved sensor counter*/

        if(iSensorCounter <= iSavedSensorPanelSize)
        {
            vectorTestrow = (*it)->GetVectorTestrow();
            iCurNumberOfTestrows = vectorTestrow.size();

            if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/numberOfTestrows"), iSensorCounter), &iSavedNumberOfTestrows))
               {
                   wxLogMessage("Test session file corrupted ..");
                   return false;
               }

             /* Fill if current number is smaller than saved number */
             if( (iTempRowCounter = iCurNumberOfTestrows) < iSavedNumberOfTestrows)
             {
                while( iTempRowCounter++ < iSavedNumberOfTestrows )
                {

                }
             }
             /* Delete if current number is bigger than saved number */
             else
             {
                while( iTempRowCounter-- > iSavedNumberOfTestrows)
                {
                    wxCommandEvent
                }
             }
        }

        iSensorCounter ++;


    }


}
