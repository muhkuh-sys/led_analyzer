#include "CTestGeneration.h"

CTestGeneration::CTestGeneration()
{
    //ctor
}

CTestGeneration::~CTestGeneration()
{
    //dtor
}


void CTestGeneration::GenerateColorTestTable(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile)
{
    unsigned int uiDevCounter = 0;
    unsigned int uiNumberOfTests = this->GetMaximumNumberOfTestsets(vectorSensorPanel);

    tFile->AddLine(" ---------------------- ColorControl LEDs under test ---------------------- ");

    for(unsigned int i = 0; i < uiNumberOfTests; i++)
    {
        tFile->AddLine(wxString::Format(wxT("-- LED Testset # %i --\n"), i));
        tFile->AddLine(wxString::Format(wxT("local tTestSet%i = {\n"), i));

        /* Iterate over Sensor Panels */
        for(unsigned int j = 0; j < vectorSensorPanel.size(); j++)
        {
            /* We reached a new device */
            if(j%16 == 0) tFile->AddLine(wxString::Format(wxT(" [%2i] = {"), uiDevCounter++));


            /* Get your rows in case the row really exists in the testrow vector */
            if((vectorSensorPanel.at(j)->GetVectorTestrow().size()) > i)
            {
                /* Add the testline */
                tFile->AddLine(vectorSensorPanel.at(j)->GetTestrow(j, i));

            }
            /* In case the row does not exist Generate a Empty Testrow */
            else  tFile->AddLine(vectorSensorPanel.at(j)->GetEmptyTestrow(j));



            /* Last Entry of a device */
            if(j%16 == 15)
            {
                /* The last device entry needs no comma */
                if( j == (vectorSensorPanel.size() - 1)) tFile->AddLine(wxT("   }\n"));

                /* All other device entries need a comma */
                else tFile->AddLine(wxT("   },\n"));
            }
        }


        tFile->AddLine(wxT("}\n"));
        uiDevCounter = 0;
    }

    wxString strTestSets;
    for(unsigned int i = 0; i < uiNumberOfTests; i++)
    {
        if(i == 0) strTestSets += wxT("local atTestSets = { ");
        /* Last TestSet*/
        if(i == uiNumberOfTests - 1) strTestSets += wxString::Format(wxT("tTestSet%d }\n"), i);
        /* Else */
        else strTestSets += wxString::Format(wxT("tTestSet%d, "), i);

    }

    tFile->AddLine(strTestSets);

}

int CTestGeneration::GetMaximumNumberOfTestsets(wxVector<PanelSensor*> vectorSensorPanel)
{
    /* Initialize the maximum number with zero */
    int iMaxNumber = 0;
    int iTemp;

    /* Search for the maximum amount of testsets we have */
    for(wxVector<PanelSensor*>::iterator it = vectorSensorPanel.begin(); it!= vectorSensorPanel.end(); it++)
    {
        if( (iTemp = (*it)->GetVectorTestrow().size()) > iMaxNumber) iMaxNumber = iTemp;
    }

    return iMaxNumber;
}

void CTestGeneration::GenerateNetXTestTable(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile, bool useNetX)
{
    if(useNetX == true)
    {
        tFile->AddLine(wxT(" --------------------------- netX I/O Table ---------------------------\n "));
        tFile->AddLine(wxT(" local atPinsUnderTest = {\n"));

        int iIndexLastEntry   = this->GetLastEntryWithVectors(vectorSensorPanel);

        for(int i = 0; (unsigned int)i < vectorSensorPanel.size(); i++)
        {

            if(vectorSensorPanel.at(i)->GetVectorTestrow().size() > 0)
            {
                if( i == iIndexLastEntry) tFile->AddLine(vectorSensorPanel.at(i)->GetAtPinsUnderTest(true));

                else  tFile->AddLine(vectorSensorPanel.at(i)->GetAtPinsUnderTest(false));
            }

        }

        tFile->AddLine(wxT("}\n"));
    }
}

int CTestGeneration::GetLastEntryWithVectors(wxVector<PanelSensor*> vectorSensorPanel)
{
    int iLastEntry = -1;

    /* Search for the last sensor entry which contains testrows */
    for(unsigned int i = 0; i<vectorSensorPanel.size(); i++)
    {
        if( vectorSensorPanel.at(i)->GetVectorTestrow().size() > 0) iLastEntry = i;
    }

    return iLastEntry;
}

bool CTestGeneration::CheckTestGeneration(wxVector<PanelSensor*> vectorSensorPanel, bool useNetX)
{

  int iSensorNumber;
  bool testEntriesOK = true;

  for(wxVector<PanelSensor*>::iterator it_sensor = vectorSensorPanel.begin(); it_sensor != vectorSensorPanel.end(); it_sensor++)
  {
     for(unsigned int i = 0; i < (*it_sensor)->GetVectorTestrow().size(); i++)
     {
         /* Names must be existent */
         if((*it_sensor)->GetVectorTestrow().at(i)->IsNameFieldEmpty())
         {
             iSensorNumber = (*it_sensor)->GetSensorNumber();
             wxLogMessage(wxString::Format(wxT("Name Entry for Sensor %d row %d missing!"), iSensorNumber, i+1));
             testEntriesOK =  false;

         }
         /* PinNumbers must be existent if Use netX is checked */
         if(useNetX)
         {
             if((*it_sensor)->GetVectorTestrow().at(i)->IsPinNumberFieldEmpty())
             {
                 iSensorNumber = (*it_sensor)->GetSensorNumber();
                 wxLogMessage(wxString::Format(wxT("Pin Number Entry for Sensor %d row %d missing!"), iSensorNumber, i+1));
                 testEntriesOK =  false;

             }
         }
     }
  }

  /* Further checks must follow here */
  return testEntriesOK;
}

void CTestGeneration::InsertHeaders(wxTextFile* tFile, bool useNetX)
{
    /* Get the right requires for the test */
    tFile->AddLine("require(\"color_control\")");

    if(useNetX)
    {
        tFile->AddLine("require(\"muhkuh_cli_init\")");
        tFile->AddLine("require(\"io_matrix\")\n\n");
        /* Dont change following line as the replace function will not work after*/
        tFile->AddLine("-- INSERT INTERFACE NUMBER\n");
    }

    tFile->AddLine("-- be pessimistic ");
    tFile->AddLine("local iRetval = TEST_RESULT_FAIL\n");
    tFile->AddLine("local strXmlResult");
    tFile->AddLine("local lux_check_enable = nil");

}

void CTestGeneration::GenerateTestStepFunctions(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile, bool useNetX)
{
    unsigned int uiMaxNumber = this->GetMaximumNumberOfTestsets(vectorSensorPanel);

    if(useNetX)
    {
        tFile->AddLine(wxT("-- Functions triggers the desired pin state for a testset"));
        /* Iterate over all Testsets and push the desired pin value onto the netX */
        for(unsigned int uiTestIndex = 0; uiTestIndex < uiMaxNumber; uiTestIndex++)
        {
            tFile->AddLine(wxString::Format(wxT("-- apply pin states for test set %d"), uiTestIndex));
            tFile->AddLine(wxString::Format(wxT("local function applyPinState%d(aAttr)"), uiTestIndex));

            for(wxVector<PanelSensor*>::iterator it = vectorSensorPanel.begin(); it!= vectorSensorPanel.end(); it++)
            {
                if((*it)->GetVectorTestrow().size() > uiTestIndex)
                {
                    tFile->AddLine((*it)->GetPinStateTestSet(uiTestIndex));
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
        tFile->AddLine(this->GetFunctionAutomatedNetXConnection());
        tFile->AddLine("\n");
        tFile->AddLine(wxT("-- Device connection ----------------------"));
        tFile->AddLine(wxT("-- netX"));
        tFile->AddLine(wxT("open_netx_connection(strInterface)"));
        tFile->AddLine(wxT("tPlugin = tester.getCommonPlugin()"));
        tFile->AddLine(wxT("if tPlugin==nil then"));
        tFile->AddLine(wxT("    error(\"No plugin selected, nothing to do!\")"));
        tFile->AddLine(wxT("end\n"));
    }

    tFile->AddLine(wxT("-- Color Controller --> Scan"));
    tFile->AddLine(wxT("numberOfDevices, strXmlResult = scanDevices()"));
    tFile->AddLine(wxT("if numberOfDevices <= 0 then"));
    tFile->AddLine(wxT("    free()"));
    if(useNetX) tFile->AddLine(wxT("    tPlugin:Disconnect()"));
    tFile->AddLine(wxT("    return TEST_RESULT_DEVICE_ERROR, strXmlResult"));
    tFile->AddLine(wxT("end\n"));
    tFile->AddLine(wxT("-- Color Controller --> Connect"));
    tFile->AddLine(wxT("numberOfDevices, strXmlResult = connectDevices()"));
    tFile->AddLine(wxT("if numberOfDevices <= 0 then"));
    tFile->AddLine(wxT("    free()"));
    if(useNetX) tFile->AddLine(wxT("    tPlugin:Disconnect()"));
    tFile->AddLine(wxT("    return TEST_RESULT_DEVICE_ERROR, strXmlResult"));
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

    tFile->AddLine(wxT("-- Color Controller --> Init"));
    tFile->AddLine(wxT("initDevices(atSettings)\n"));

}



void CTestGeneration::GenerateTestSteps(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile, bool useNetX)
{
    int uiNumberOfTests = this->GetMaximumNumberOfTestsets(vectorSensorPanel);

    tFile->AddLine(wxT("-- Actual Test -----------------------------"));
    /* Lua index for testtables start at 1 */
    for(int i = 1; i <= uiNumberOfTests; i++)
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

        tFile->AddLine(wxT("led_analyzer.wait4Conversion(200)"));
        tFile->AddLine(wxT("startMeasurements()"));
        tFile->AddLine(wxString::Format(wxT("iRetval, strXmlResult = validateLEDs(atTestSets[%d], lux_check_enable)\n"), i));
        tFile->AddLine(wxT("if iRetval ~= TEST_RESULT_OK then"));
        tFile->AddLine(wxT("    free()"));
        if(useNetX)
        {
            tFile->AddLine("    ---- APPLY DEFAULT PINSTATES ---- ");
            tFile->AddLine("    --tPlugin:Disconnect()");
        }
        tFile->AddLine(wxT("    return  TEST_RESULT_FAIL, strXmlResult"));
        tFile->AddLine(wxT("end\n"));
    }

    tFile->AddLine(wxT("free()"));
    if(useNetX) tFile->AddLine(wxT("tPlugin:Disconnect()"));
    tFile->AddLine(wxT("return iRetval, strXmlResult"));
}

void CTestGeneration::GenerateSettingsTable(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile)
{
    int iDevCounter = 0;

    tFile->AddLine(wxT("-- Settings Table contains gain and integration time"));
    tFile->AddLine(wxT("atSettings = {"));

    /* Iterate over all elements of vectorsensorpanel */
    for(unsigned int i = 0; i < vectorSensorPanel.size(); i++)
    {
        /* We reached a new device */
        if(i%16 == 0) tFile->AddLine(wxString::Format(wxT(" [%2i] = {"), iDevCounter++));

        /* Get your settings row */
        tFile->AddLine(vectorSensorPanel.at(i)->GetSettingsrow(i));

            /* Last Entry of a device */
        if(i%16 == 15)
        {
            /* The last device entry needs no comma */
            if( i == (vectorSensorPanel.size() - 1)) tFile->AddLine(wxT("   }\n"));

            /* All other device entries need a comma */
            else tFile->AddLine(wxT("   },\n"));
        }

    }

    tFile->AddLine(wxT("}"));

}

bool CTestGeneration::GenerateTest(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile, bool useNetX)
{

    if(!this->CheckTestGeneration(vectorSensorPanel, useNetX))
    {
       if(!tFile->Close()) wxLogMessage("Couldn't close test file.");
       wxLogMessage("Errors occured ... abort.");
       return false;
    }

    /* Checks */

    this->InsertHeaders(tFile, useNetX);
    this->GenerateColorTestTable(vectorSensorPanel, tFile);
    this->GenerateSettingsTable(vectorSensorPanel, tFile);
    this->GenerateNetXTestTable(vectorSensorPanel, tFile, useNetX);
    this->GenerateTestStepFunctions(vectorSensorPanel, tFile, useNetX);
    this->GenerateInitialization(tFile, useNetX);
    this->GenerateTestSteps(vectorSensorPanel, tFile, useNetX);

    return true;

}


void CTestGeneration::SaveSessionAsIni(wxVector<PanelSensor*> vectorSensorPanel, wxTextFile* tFile)
{
    int iNumberOfSensors = vectorSensorPanel.size();
    int rowCounter = 1;

    wxVector<PanelTestrow*> vectorTestrow;

    tFile->AddLine(wxT("[Testsession]"));
    tFile->AddLine(wxString::Format(wxT("numberOfSensors=%d\n"), iNumberOfSensors));

    /* Iterate over all vectorSensorPanels */
    for(wxVector<PanelSensor*>::iterator it = vectorSensorPanel.begin(); it != vectorSensorPanel.end(); it++)
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
        rowCounter = 1;
    }
}

bool CTestGeneration::OpenSessionAsIni(wxVector<PanelSensor*> vectorSensorPanel, wxFileConfig* tFileConfig)
{
    int iCurvectorSensorPanelSize = vectorSensorPanel.size();
    int iSavedNumberOfSensors;

    if(iCurvectorSensorPanelSize == 0)
    {
        wxLogMessage("Please connect first.");
        return false;
    }

    /* Return if you cannot read the number of sensors .. this is important as array exceedings
    might happen otherwise */
    if(!tFileConfig->Read("Testsession/numberOfSensors", &iSavedNumberOfSensors))
    {
        wxLogMessage("Test session file corrupted ..");
        return false;
    }

    int iSensorcounter = 1;

    int iSavedNumberOfTesrows;
    int iCurNumberOfTesrows;

    wxVector<PanelTestrow*> vectorTestrow;

    /* Iterate over all entries of the config file */
    for(wxVector<PanelSensor*>::iterator it = vectorSensorPanel.begin(); it!= vectorSensorPanel.end(); it++)
    {

        /* Read the number of testrows for the sensor */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/numberOfTestrows"), iSensorcounter), &iSavedNumberOfTesrows ))
        {
            wxLogMessage("Test session file corrupted ..");
            wxLogMessage("blub");
            return false;
        }

        /* Get the current size of the testrow vector */
        vectorTestrow = (*it)->GetVectorTestrow();
        iCurNumberOfTesrows = vectorTestrow.size();

        /* Refill so we have the save number of testrows as in the config file*/
        while(iCurNumberOfTesrows != iSavedNumberOfTesrows)
        {
            /* Update current vector and its new size */
            vectorTestrow = (*it)->GetVectorTestrow();
            iCurNumberOfTesrows = vectorTestrow.size();

            /* Destroy rows if current number is bigger */
            if(iCurNumberOfTesrows > iSavedNumberOfTesrows)
            {
                /* Destroy last row */
                wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, vectorTestrow.back()->GetpButtonRemove()->GetId());
                vectorTestrow.back()->GetpButtonRemove()->GetEventHandler()->ProcessEvent(evt);

            }
            /* Add rows if current number is smaller then wanted number */
            if(iCurNumberOfTesrows < iSavedNumberOfTesrows)
            {
                wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, (*it)->GetpButtonAdd()->GetId());
                (*it)->GetpButtonAdd()->GetEventHandler()->ProcessEvent(evt);
            }
        }

        /* Now fill with content while iterating over sensors .. we assume that we have the correct
        numbers of testrows as in the testfile */
        if(this->FillTestrowsWithContent((*it), iSensorcounter, tFileConfig) == false)
        {
            wxLogMessage("Test session file corrupted ..");
            return false;
        }

        iSensorcounter++;

        /* Break if current SensorCounter is greater than the saved one as we would read
        invalid values for the testrows */

        if(iSensorcounter > iSavedNumberOfSensors) break;

    }

    return true;
}

bool CTestGeneration::FillTestrowsWithContent(PanelSensor* sensorPanel, int iSensorCounter, wxFileConfig* tFileConfig)
{
    wxVector<PanelTestrow*> vectorTestrow = sensorPanel->GetVectorTestrow();
    int iTestrowCounter = 1;

    wxString     strName;
    int          iWavelength, iSaturation, iIllumination;
    int          iColor;
    wxColor      rowColor;
    int          iPinType, iPinNumber, iPinValue, iPinDefValue;
    int          iTolNm, iTolSat, iTolIllu;

    for(wxVector<PanelTestrow*>::iterator it = vectorTestrow.begin(); it != vectorTestrow.end(); it++)
    {
        /* Name */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_name"), iSensorCounter, iTestrowCounter), &strName))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetName(strName);
        /* Wavelength */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_wavelength"), iSensorCounter, iTestrowCounter), &iWavelength))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetWavelength(iWavelength);
        /* Saturation */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_saturation"), iSensorCounter, iTestrowCounter), &iSaturation))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            wxLogMessage("it's the saturation");
            return false;
        }
        (*it)->SetSaturation(iSaturation);
        /* Illumination */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_illumination"), iSensorCounter, iTestrowCounter), &iIllumination))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetIllumination(iIllumination);

        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_colour"), iSensorCounter, iTestrowCounter), &iColor))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetColour(wxColour((unsigned int)iColor));

        /* Pintype */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_pintype"), iSensorCounter, iTestrowCounter), &iPinType))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetPintype(iPinType);
        /* Pinnumber */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_pinnumber"), iSensorCounter, iTestrowCounter), &iPinNumber))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetPinNumber(iPinNumber);
        /* Pinvalue */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_pinvalue"), iSensorCounter, iTestrowCounter), &iPinValue))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetPinValue(iPinValue);
        /* Pin Default Value */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_pindefvalue"), iSensorCounter, iTestrowCounter), &iPinDefValue))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetPinDefValue(iPinDefValue);
        /* Tolerance Wavelength */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_tolnm"), iSensorCounter, iTestrowCounter), &iTolNm))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetTolWavelength(iTolNm);
        /* Tolerance Saturation */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_tolsat"), iSensorCounter, iTestrowCounter), &iTolSat))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..", iSensorCounter, iTestrowCounter);
            return false;
        }
        (*it)->SetTolSaturation(iTolSat);
        /* Tolerance Illumination */
        if(!tFileConfig->Read(wxString::Format(wxT("Sensor%d/row%d_tolillu"), iSensorCounter, iTestrowCounter), &iTolIllu))
        {
            wxLogMessage("Test session entry for sensor %d row %d corrupted ..");
            return false;
        }
        (*it)->SetTolIllumination(iTolIllu);

        iTestrowCounter++;
    }

    return true;
}

int CTestGeneration::GetLastEntryWithPinnumber(wxVector<PanelSensor*> vectorSensorPanel)
{
    int iIndex = -1;

    for(unsigned int i = 0; i < vectorSensorPanel.size(); i ++)
    {
        /* The pinnumber field is not empty */
        if(!vectorSensorPanel.at(i)->IsPinnumberEmpty()) iIndex = i;
    }

    return iIndex;
}

wxString CTestGeneration::GetFunctionAutomatedNetXConnection()
{
    wxString strFunction;
    strFunction += wxT("-- Open a netx connection without user input\n");
    strFunction += wxT("local function open_netx_connection(strInterfacePattern)\n");
    strFunction += wxT("\n");
    strFunction += wxT("    -- Open the connection to the netX.\n");
    strFunction += wxT("    if string.upper(strInterfacePattern)~=\"ASK\" then\n");
    strFunction += wxT("        -- No interface detected yet.\n");
    strFunction += wxT("        local tPlugin = nil\n");
    strFunction += wxT("\n");
    strFunction += wxT("        -- Detect all interfaces.\n");
    strFunction += wxT("        local aDetectedInterfaces = {}\n");
    strFunction += wxT("        for iCnt,tPlugin in ipairs(__MUHKUH_PLUGINS) do\n");
    strFunction += wxT("            tPlugin:DetectInterfaces(aDetectedInterfaces)\n");
    strFunction += wxT("        end\n");
    strFunction += wxT("\n");
    strFunction += wxT("        -- Search all detected interfaces for the pattern.\n");
    strFunction += wxT("        for iInterfaceIdx,tInterface in ipairs(aDetectedInterfaces) do\n");
    strFunction += wxT("            local strName = tInterface:GetName()\n");
    strFunction += wxT("            if string.match(strName, strInterfacePattern)~=nil then\n");
    strFunction += wxT("                tPlugin = aDetectedInterfaces[iInterfaceIdx]:Create()\n");
    strFunction += wxT("\n");
    strFunction += wxT("                -- Connect the plugin.\n");
    strFunction += wxT("                tPlugin:Connect()\n");
    strFunction += wxT("                break\n");
    strFunction += wxT("            end\n");
    strFunction += wxT("        end\n");
    strFunction += wxT("\n");
    strFunction += wxT("        -- Found the interface?\n");
    strFunction += wxT("        if tPlugin==nil then\n");
    strFunction += wxT("            error(string.format(\"No interface matched the pattern '%s'!\", strInterfacePattern))\n");
    strFunction += wxT("        end\n");
    strFunction += wxT("\n");
    strFunction += wxT("        tester.setCommonPlugin(tPlugin)\n\n");
    strFunction += wxT("    end\n");
    strFunction += wxT("\n");
    strFunction += wxT("end\n");

    return strFunction;
}

bool CTestGeneration::FileLEDStimulation(wxVector<PanelSensor*> vectorSensorPanel, wxString strPlugin)
{

    wxTextFile tFile(wxFileName::GetCwd()+"\\_tempscript_.lua");

    if(!tFile.Exists()) tFile.Create();

    if(!tFile.Open())
    {
        wxLogMessage("Couldn't open file.");
        return false;
    }

    tFile.Clear();

    tFile.AddLine("require(\"muhkuh_cli_init\")");
    tFile.AddLine("require(\"io_matrix\")\n");

    tFile.AddLine(this->GetFunctionAutomatedNetXConnection());

    tFile.AddLine(wxT(" --------------------------- netX I/O Table ---------------------------\n "));
    tFile.AddLine(wxT(" local atPinsUnderTest = {\n"));

    if(this->GetLastEntryWithPinnumber(vectorSensorPanel) == -1)
    {
        tFile.AddLine(wxT("}"));
        return false;
    }
    /* Fill atPinsUnderTest */
    for(int i = 0; (unsigned int)i < vectorSensorPanel.size(); i++)
    {
        /*  */
        if(!vectorSensorPanel.at(i)->IsPinnumberEmpty())
        {
            if(!(i == this->GetLastEntryWithPinnumber(vectorSensorPanel)))
                        tFile.AddLine(wxString::Format(wxT("    { \"%s\", io_matrix.PINTYPE_%s, %3d, %2d, io_matrix.PINFLAG_IOZ },\n"),
                        vectorSensorPanel.at(i)->GetName(),
                        vectorSensorPanel.at(i)->GetPintype(vectorSensorPanel.at(i)->GetPintype()),
                        vectorSensorPanel.at(i)->GetPinNumber(), vectorSensorPanel.at(i)->GetPinDefValue()));
            /* last entry needs no comma */
            else
                        tFile.AddLine(wxString::Format(wxT("    { \"%s\", io_matrix.PINTYPE_%s, %3d, %2d, io_matrix.PINFLAG_IOZ }\n"),
                        vectorSensorPanel.at(i)->GetName(),
                        vectorSensorPanel.at(i)->GetPintype(vectorSensorPanel.at(i)->GetPintype()),
                        vectorSensorPanel.at(i)->GetPinNumber(), vectorSensorPanel.at(i)->GetPinDefValue()));
        }
    }

    tFile.AddLine(wxT("}"));

    tFile.AddLine(wxT(" --------------------------- netX I/O Table values -----------------------\n "));
    tFile.AddLine(wxT(" local atPinsUnderTestValues = {\n"));
    /* Fill value table */
    for(int i = 0; (unsigned int)i < vectorSensorPanel.size(); i++)
    {
        if(!vectorSensorPanel.at(i)->IsPinnumberEmpty())
        {
            if(!(i == this->GetLastEntryWithPinnumber(vectorSensorPanel)))
                tFile.AddLine(wxString::Format(wxT("    { %d },"), vectorSensorPanel.at(i)->GetPinValue()));
            /* last entry needs no comma */
            else
                tFile.AddLine(wxString::Format(wxT("    { %d }"), vectorSensorPanel.at(i)->GetPinValue()));
        }
    }

    tFile.AddLine(wxT("}"));


    tFile.AddLine(wxT("-- Device connection ----------------------"));
    tFile.AddLine(wxT("-- netX"));
    tFile.AddLine(wxString::Format(wxT("open_netx_connection(\"%s\")"), strPlugin ));
    tFile.AddLine(wxT("tPlugin = tester.getCommonPlugin()"));
    tFile.AddLine(wxT("if tPlugin==nil then"));
    tFile.AddLine(wxT("    error(\"No plugin selected, nothing to do!\")"));
    tFile.AddLine(wxT("end\n"));

    tFile.AddLine(wxT("-- Device initialization -------------------"));
    tFile.AddLine(wxT("-- netX"));
    tFile.AddLine(wxT("local aAttr = io_matrix.initialize(tPlugin, \"netx/iomatrix_netx%d.bin\")"));;
    tFile.AddLine(wxT("io_matrix.parse_pin_description(aAttr, atPinsUnderTest, ulVerbose)"));

    tFile.AddLine(wxT("-- Turn on all LEDs"));
    tFile.AddLine(wxT("local uiCounter = 1"));
    tFile.AddLine(wxT("while(atPinsUnderTest[uiCounter] ~= nil) do"));
    tFile.AddLine(wxT("    io_matrix.set_pin(aAttr, atPinsUnderTest[uiCounter][1], atPinsUnderTestValues[uiCounter][1])"));
    tFile.AddLine(wxT("    uiCounter = uiCounter + 1"));
    tFile.AddLine(wxT("end\n\n"));

    tFile.AddLine(wxT("tPlugin:Disconnect()"));

    tFile.Write();

    if(!tFile.Close())
    {
        wxLogMessage("Couldn't close file");
        return false;
    }

    return true;

}


bool CTestGeneration::CheckLEDStimulation(wxVector<PanelSensor*> vectorSensorPanel)
{
    /* If Pinnumbers are provided names must be provided as well, as the io_matrix test lua
    requires the name as a neccessary parameter */
    bool retVal = true;

    /* check if entries which contain a pinnumber also have a name */
    for(wxVector<PanelSensor*>::iterator it = vectorSensorPanel.begin(); it != vectorSensorPanel.end(); it++ )
    {
        if(!(*it)->IsPinnumberEmpty() && (*it)->IsNameEmpty())
        {
            wxLogMessage("Name entry for sensor %d is missing.", (*it)->GetSensorNumber());
            retVal = false;
        }
    }

    if(!retVal) return retVal;

    /* if there's no entry at all with a pinnumber, return */
    if(GetLastEntryWithPinnumber(vectorSensorPanel) == -1)
        retVal = false;

    return retVal;
}
