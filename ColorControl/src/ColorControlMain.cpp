/***************************************************************
 * Name:      ColorControlMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Subhan Waizi (swaizi@hilscher.com)
 * Created:   2015-06-16
 * Copyright: Subhan Waizi ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ColorControlMain.h"





//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


ColorControlFrame::ColorControlFrame(wxFrame *frame)
    : GUIFrame(frame)
{
    /* Initialize number of devices with 0 */
    m_numberOfDevices = 0;

    m_pLogTarget = new wxLogTextCtrl(m_text);
    m_pOldLogTarget = wxLog::SetActiveTarget(m_pLogTarget);
    // Redirect your std::cout to the same text
    wxStreamToTextRedirector redirect(m_text);

    if( m_pOldLogTarget !=  NULL)
    {
        delete m_pOldLogTarget;
    }

    wxLog::SetVerbose(true);
    wxLog::SetLogLevel(wxLOG_Debug );
    wxLogMessage(wxT("Welcome to Color Control...\n"));

    /* Set the working directory to the build folder if it is not already the build folder */
    if(!wxFileName::GetCwd().EndsWith("build"))
    {
        /* Set the working directory */
        wxFileName::SetCwd(wxFileName::GetCwd()+"\\build");
    }


    m_fileConfig = new wxFileConfig(wxEmptyString, wxEmptyString,
                                    wxFileName::GetCwd()+"/config.ini", wxEmptyString,
                                    wxCONFIG_USE_LOCAL_FILE);
    /* Allocate space for the array that will contain serial numbers */
    m_aStrSerials = new wxString[128];

    /* Initialize the timer */
    m_pTimer = new wxTimer(this, wxID_TIMER);

    /* Initialize Hash Tables */
    this->InitHashTables();

    /* Set Initial State */
    m_eState = IS_INITIAL;
}

ColorControlFrame::~ColorControlFrame()
{
    delete[] m_aStrSerials;
    if ( m_fileConfig ) delete m_fileConfig;
}

void ColorControlFrame::InitHashTables()
{
    /* Fill Hash Table String to gain or integration time*/
    m_str2Uc_gain[wxT("GAIN_1X")] =   TCS3472_GAIN_1X;
    m_str2Uc_gain[wxT("GAIN_4X")] =   TCS3472_GAIN_4X;
    m_str2Uc_gain[wxT("GAIN_16X")] =  TCS3472_GAIN_16X;
    m_str2Uc_gain[wxT("GAIN_60X")] =  TCS3472_GAIN_60X;

    m_str2Uc_integration[wxT("TIME_2_4ms")] = TCS3472_INTEGRATION_2_4ms;
    m_str2Uc_integration[wxT("TIME_24ms")]  = TCS3472_INTEGRATION_24ms;
    m_str2Uc_integration[wxT("TIME_100ms")] = TCS3472_INTEGRATION_100ms;
    m_str2Uc_integration[wxT("TIME_154ms")] = TCS3472_INTEGRATION_154ms;
    m_str2Uc_integration[wxT("TIME_200ms")] = TCS3472_INTEGRATION_200ms;
    m_str2Uc_integration[wxT("TIME_700ms")] = TCS3472_INTEGRATION_700ms;

    /* Hash table for register content to index of a choicebox */
    m_uc2strHash_gain[TCS3472_GAIN_1X]  = wxT("GAIN_1X");
    m_uc2strHash_gain[TCS3472_GAIN_4X]  = wxT("GAIN_4X");
    m_uc2strHash_gain[TCS3472_GAIN_16X] = wxT("GAIN_16X");
    m_uc2strHash_gain[TCS3472_GAIN_60X] = wxT("GAIN_60X");

    m_uc2strHash_integration[TCS3472_INTEGRATION_2_4ms] = wxT("TIME_2_4ms");
    m_uc2strHash_integration[TCS3472_INTEGRATION_24ms]  = wxT("TIME_24ms");
    m_uc2strHash_integration[TCS3472_INTEGRATION_100ms] = wxT("TIME_100ms");
    m_uc2strHash_integration[TCS3472_INTEGRATION_154ms] = wxT("TIME_154ms");
    m_uc2strHash_integration[TCS3472_INTEGRATION_200ms] = wxT("TIME_200ms");
    m_uc2strHash_integration[TCS3472_INTEGRATION_700ms] = wxT("TIME_700ms");
}

void ColorControlFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void ColorControlFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void ColorControlFrame::OnAbout(wxCommandEvent &event)
{

    wxString msg = "Color Control Application by\n          Subhan Waizi         \n   swaizi@hilscher.com  \n";
    wxMessageBox(msg, _("Welcome to..."));

}

void ColorControlFrame::OnQuickGuide(wxCommandEvent &event)
{
    wxMessageBox("Quick Guide in development.", _("Quick Guide"));

}

void ColorControlFrame::OnScan(wxCommandEvent& event)
{

    switch(m_eState)
    {
        case IS_INITIAL:
            /* If we're at initial state load and run the color_control file */
            m_pLua = new CLua("color_control_init.lua");

            /* If the txt_ctrl connected was red before because some error occured, we will set it to default now */
            this->UpdateConnectedField(wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ));
            this->UpdateSerialList();

            m_eState = IS_SCANNED;
            /* Don't break */

        case IS_SCANNED:

            /* Scan, if already scanned delete the lua state and scan for new devices */
            if (m_pLua)
            {
                m_pLua->CleanUp();
                delete m_pLua;
            }

            /* Run color_control.lua which initializes the needed modules */
            m_pLua = new CLua("color_control_init.lua");

            m_pLua->ScanDevices(m_numberOfDevices, m_aStrSerials);

            this->UpdateConnectedField(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));
            this->UpdateSerialList();

            if(!m_cocoDevices.empty()) m_cocoDevices.clear();

            if(m_numberOfDevices == 0)
            {
                wxLogMessage("No device detected ... please make sure the device is properly attached!");

                if (m_pLua)
                {
                    m_pLua->CleanUp();
                    delete m_pLua;
                }
                m_eState = IS_INITIAL;

            }
            else if(m_numberOfDevices < 0 )
            {
                wxLogMessage("Connection error ... please make sure the proper driver is installed!");
                if (m_pLua)
                {
                    m_pLua->CleanUp();
                    delete m_pLua;
                }
                m_eState = IS_INITIAL;
            }

            else
            {
                /* Get the default Tolerance Values from the Configuration files */
                int tol_nm, tol_sat, tol_illu;
                if(!m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_nm"), &tol_nm)) tol_nm = 10;
                if(!m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_sat"), &tol_sat)) tol_sat = 10;
                if(!m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_illu"), &tol_illu)) tol_illu = 50;

                for(int i = 0; i < m_numberOfDevices; i++)
                {
                    m_cocoDevices.push_back(new CColorController());
                    m_cocoDevices.at(i)->SetTolNm(tol_nm);
                    m_cocoDevices.at(i)->SetTolSat(tol_sat);
                    m_cocoDevices.at(i)->SetTolIllu(tol_illu);
                }

            }

            break;

        case IS_CONNECTED:
            wxLogMessage("Please disconnect first.");
            break;

        default:
            break;

    }

}

void ColorControlFrame::UpdateSerialList()
{
        /* Fill the serial list (clear before) */
        m_dataViewListSerials->DeleteAllItems();
        for(int i = 0; i < m_numberOfDevices; i++)
        {
            wxVector<wxVariant> rowData;
            rowData.push_back(i+1); // Serial Number
            rowData.push_back(m_aStrSerials[i]);
            m_dataViewListSerials->AppendItem(rowData);
        }
}

void ColorControlFrame::OnConnect(wxCommandEvent& event)
{

    switch(m_eState)
    {
        case IS_INITIAL:
            wxLogMessage("Please Scan for devices first.");
            break;

        case IS_SCANNED:

            int temp;
            m_pLua->ConnectDevices(temp);

            /* Compare number of Found devices to number of devices we connected to, must be equal or errors occured */
            if(temp == m_numberOfDevices)
            {
                wxLogMessage("Connecting..");
                for(int i = 0; i < m_numberOfDevices; i++)
                {
                    m_cocoDevices.at(i)->SetSerialNumber(m_aStrSerials[i]);
                    m_cocoDevices.at(i)->SetConnectivity(true);
                }

                /* Init the devices */
                m_pLua->InitDevices(m_cocoDevices);
                /* Create Rows for Colors*/
                CreateRows();
                /* Create Test Panels */
                CreateTestPanels(m_numberOfDevices);
                /* Update Data */
                this->UpdateData();

                /* Set System State to Connected */
                m_eState = IS_CONNECTED;
                /* Show It in the textCtrl for connected devices */
                this->UpdateConnectedField(COLOR_OK);

                wxLogMessage("Connected!");

            }
            /* Some Exception happened in the lua code (i2c/ftdi/led_analyzer functions in led_analyzer.dll) */
            if(temp < 0)
            {
                /* Show that something went wrong */
                m_numberOfDevices = 0;
                m_cocoDevices.clear();

                this->UpdateConnectedField(COLOR_ERROR);
                /* Reset the System State */
                m_eState = IS_INITIAL;
                LOG_ERROR(m_text);
                wxLogError("Ups! Something went wrong, please retry Scan and Connect!");
                LOG_DEFAULT(m_text);
            }

            break;

        case IS_CONNECTED:
            break;

        default:
            break;

    }

}

void ColorControlFrame::OnDisconnect(wxCommandEvent& event)
{
    switch(m_eState)
    {
        case IS_INITIAL:
            // Do nothing
            break;

        case IS_SCANNED:
            // Do nothing
            break;

        case IS_CONNECTED:

            // Clean up and clear everything
            wxLogMessage("Disconnecting ..");

            /* Remove color controller devices from vector */
            m_cocoDevices.clear();
            m_numberOfDevices = 0;

            /* Clear Serial Numbers */
            m_dataViewListSerials->DeleteAllItems();

            /* Clear Rows for Colors */
            m_dvlColors->DeleteAllItems();

            /* Clear Test Panels */
            this->ClearTestPanels();

            /* Flush and write zero */
            /* Reset the color of textctrl Connected */
            this->UpdateConnectedField(wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

            /* If the timer is Running Stop and transform Stop button into Start button It*/
            if(m_pTimer->IsRunning())
            {
                m_pTimer->Stop();
                m_buttonStart->SetLabel("START");
            }

            /* Clean up and close the current Lua State (color_control.lua) */
            if(m_pLua)
            {
                m_pLua->CleanUp();
                delete m_pLua;
            }
            /* Set Initial System State */
            m_eState = IS_INITIAL;

            /* Tell the world. ! */
            wxLogMessage("Disconnected!");
            break;

        default:
            break;

    }


}

void ColorControlFrame::OnStart(wxCommandEvent& event)
{
    switch(m_eState)
    {
        case IS_INITIAL:
            wxLogMessage("Please scan and connect first.");
            break;

        case IS_SCANNED:
            wxLogMessage("Please connect first.");
            break;

        case IS_CONNECTED:
            /* Now Check if we Make Single or Continuous Measurements */
            if(m_rbSingle->GetValue() == true)
            {
                if(m_pLua->StartMeasurements() == DEVICE_ERROR_FATAL)
                {
                    LOG_ERROR(m_text);
                    wxLogError("A fatal error has occured. Save your work, disconnect, re-scan and re-connect!");
                    LOG_DEFAULT(m_text);

                    /* Show that a fatal error has occured */
                    UpdateConnectedField(COLOR_ERROR);
                }

                m_pLua->ReadColours(m_cocoDevices);

                this->UpdateData();
            }

            if(m_rbContinuous->GetValue() == true)
            {
                /* STOP BUTTON CHANGES TO START BUTTON - TIMER STOPS */
                if(m_buttonStart->GetLabel().IsSameAs("STOP"))
                {
                    m_pTimer->Stop();
                    m_buttonStart->SetLabel("START");
                }

                else
                {
                    int iTimerValue;

                    switch(m_chTime->GetCurrentSelection())
                    {
                        case TESTMODE_TIME_0_2SEC:
                            iTimerValue = 200;
                            break;
                        case TESTMODE_TIME_0_5SEC:
                            iTimerValue = 500;
                            break;
                        case TESTMODE_TIME_1SEC:
                            iTimerValue = 1000;
                            break;
                        case TESTMODE_TIME_2SEC:
                            iTimerValue = 2000;
                            break;
                        case TESTMODE_TIME_5SEC:
                            iTimerValue = 5000;
                            break;
                        default:
                            iTimerValue = 1000;
                            break;
                    }

                    m_pTimer->Start(iTimerValue);
                    m_buttonStart->SetLabel("STOP");
                }
            }
    }

}

void ColorControlFrame::OnStimulation( wxCommandEvent& event )
{

    /* Set output to error as only error outputs follow */
    LOG_ERROR(m_text);

    /* Read if there's already a com port saved in the config file */
    wxString strPlugin;

    /* Check for any missing entries (name + pinnumber must be provided) */
    if(!m_testGeneration.CheckLEDStimulation(m_vectorSensorPanels ))
    {
        wxLogMessage("Stimulation unsuccessful.");
        wxLogMessage("Entries are missing, please provide.");
        LOG_DEFAULT(m_text);
        return;
    }

    /* Check if we successfully connected to an interface before, if so take that one,
        if there was no previous successful connection to an interface, let the user choose one
        of the available interfaces */
    if(m_fileConfig->Read("netXType/plugin", &strPlugin))
    {
        if(strPlugin == wxEmptyString) strPlugin = this->GetInterfaceSelection();
    }
    /* we could not read the config file */
    else
    {
        strPlugin = this->GetInterfaceSelection();
    }

    /* if the plugin is still empty we clicked on cancel */
    if(strPlugin == wxEmptyString)
    {
        LOG_DEFAULT(m_text);
        return;
    }

    if(!m_testGeneration.FileLEDStimulation(m_vectorSensorPanels, strPlugin))
    {
        wxLogMessage("Stimulation unsuccessful.");
        wxLogMessage("Stimulation file could not be generated.. abort.");

        LOG_DEFAULT(m_text);
        return;
    }

    /* Run the generated stimulation file */
    CLua stimulationfile("_tempscript_.lua");

    if(!stimulationfile.IsLoaded())
    {
        wxLogMessage("Stimulation unsuccessful.");
        wxLogMessage("Stimulation file could not be run on lua (errors) .. abort.");

        /* Empty the default plugin as it did not work */
        m_fileConfig->Write("netXType/plugin", "");

        LOG_DEFAULT(m_text);
        return;
    }

    /* LED Stimulation file could be run successfully, thus save the port as default */
    m_fileConfig->Write("netXType/plugin", strPlugin);
    LOG_SUCCESSFUL(m_text);
    wxLogMessage("Stimulation successful.");
    LOG_DEFAULT(m_text);
}

void ColorControlFrame::CreateRows()
{
    int iNumberOfDevices = m_cocoDevices.size();

    wxVariant test;

    for(int i = 0; i < iNumberOfDevices; i++)
    {
       for(int j = 0; j<16; j++)
       {
            wxVector<wxVariant> rowdata;
            rowdata.push_back(i*16 + (j + 1)); // sensorno
            rowdata.push_back(wxVariant(""));  // wavelength
            rowdata.push_back(wxVariant(""));  // saturation
            rowdata.push_back(wxVariant(""));  // illumination
            rowdata.push_back(wxVariant("0xffffff"));// m_cColor 255255255 is white
            rowdata.push_back(wxVariant(0));             // m_clearRatio;
            rowdata.push_back(wxVariant(m_uc2strHash_gain[m_cocoDevices.at(i)->GetGain(j)]));             // gain
            rowdata.push_back(wxVariant(m_uc2strHash_integration[m_cocoDevices.at(i)->GetIntTime(j)]));  // inttime
            rowdata.push_back(wxVariant(m_cocoDevices.at(i)->GetState(j))); // status

            m_dvlColors->AppendItem(rowdata);

       }
    }

}

void ColorControlFrame::UpdateData()
{
    wxVariant colorVariant;
    wxColour  colour;
    /* First Clear your Rows */
    m_dvlColors->DeleteAllItems();

    int iNumberOfDevices = m_cocoDevices.size();

    for(int i = 0; i < iNumberOfDevices; i++)
    {
       for(int j = 0; j<16; j++)
       {
            /* First Panel = Colors */
            wxVector<wxVariant> rowdata;
            rowdata.push_back(i*16 + (j + 1)); // sensorno
            rowdata.push_back(m_cocoDevices.at(i)->GetWavelength(j));    // wavelength
            rowdata.push_back(m_cocoDevices.at(i)->GetSaturation(j));    // saturation
            rowdata.push_back(m_cocoDevices.at(i)->GetIllumination(j));  // illumination
            rowdata.push_back((long)m_cocoDevices.at(i)->GetColour(j).GetRGB());                             // m_cColor
            rowdata.push_back(m_cocoDevices.at(i)->GetClearRatio(j));    // clearRatio
            rowdata.push_back(m_uc2strHash_gain[m_cocoDevices.at(i)->GetGain(j)]);                                     // gain
            rowdata.push_back(m_uc2strHash_integration[m_cocoDevices.at(i)->GetIntTime(j)]);                           // inttime
            rowdata.push_back(m_cocoDevices.at(i)->GetState(j));

            m_dvlColors->AppendItem(rowdata);

            /* Second Panel = Testdefinition */
            m_vectorSensorPanels.at(i*16 + j)->SetWavelength(m_cocoDevices.at(i)->GetWavelength(j));
            m_vectorSensorPanels.at(i*16 + j)->SetSaturation(m_cocoDevices.at(i)->GetSaturation(j));
            m_vectorSensorPanels.at(i*16 + j)->SetIllumination(m_cocoDevices.at(i)->GetIllumination(j));
            m_vectorSensorPanels.at(i*16 + j)->SetColour(m_cocoDevices.at(i)->GetColour(j));
            m_vectorSensorPanels.at(i*16 + j)->SetTolWavelength(m_cocoDevices.at(i)->GetTolNm());
            m_vectorSensorPanels.at(i*16 + j)->SetTolSaturation(m_cocoDevices.at(i)->GetTolSat());
            m_vectorSensorPanels.at(i*16 + j)->SetTolIllumination(m_cocoDevices.at(i)->GetTolIllu());
            m_vectorSensorPanels.at(i*16 + j)->SetIntegration(m_cocoDevices.at(i)->GetIntTime(j));
            m_vectorSensorPanels.at(i*16 + j)->SetGain(m_cocoDevices.at(i)->GetGain(j));
       }
    }

    if(m_nbData->GetSelection() == 1)  m_swTestdefinition->Show();
}

void ColorControlFrame::UpdateConnectedField(wxColour colour)
{
    m_textCtrlConnected->SetBackgroundColour( colour );
    m_textCtrlConnected->Clear();
    *m_textCtrlConnected << m_numberOfDevices;
}

void ColorControlFrame::CreateTestPanels(int numberOfDevices)
{

    m_swTestdefinition->Hide();
    m_swTestdefinition->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
    wxBoxSizer* bSizerTestDefinition;

    bSizerTestDefinition = new wxBoxSizer( wxVERTICAL );
    m_panelHeader = new PanelHeader(m_swTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALIGN_TOP);

    bSizerTestDefinition->Add(m_panelHeader, 0, wxEXPAND, 0);

    for (int i = 0; i< numberOfDevices; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            m_vectorSensorPanels.push_back(new PanelSensor(m_swTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, i*16 + j + 1));
            /* Fill it with the integration time and gain values so a tesgeneration without
            prior Measurement will have the settings as well */
            m_vectorSensorPanels.at(i*16 + j)->SetGain(m_cocoDevices.at(i)->GetGain(j));
            m_vectorSensorPanels.at(i*16 + j)->SetIntegration(m_cocoDevices.at(i)->GetIntTime(j));
        }
    }

    for(int i = 0; i < numberOfDevices; i++)
    {
        for(int j = 0; j < 16; j++)
        {
           bSizerTestDefinition->Add(m_vectorSensorPanels.at(i*16 + j), 0, wxEXPAND);
        }
    }

    m_swTestdefinition->SetSizer(bSizerTestDefinition);
    m_swTestdefinition->FitInside();
    m_swTestdefinition->Layout();

    if(m_nbData->GetSelection() == 1)m_swTestdefinition->Show();

}

void ColorControlFrame::ClearTestPanels()
{
    m_swTestdefinition->Hide();
    m_swTestdefinition->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

    if(m_panelHeader != NULL) m_panelHeader->Destroy();

    for(wxVector<PanelSensor*>::iterator it = m_vectorSensorPanels.begin(); it != m_vectorSensorPanels.end(); it++)
    {
        (*it)->Destroy();
    }

    m_vectorSensorPanels.clear();
    m_swTestdefinition->Show();
    m_swTestdefinition->Layout();
}

void ColorControlFrame::OnSerialUp(wxCommandEvent& event)
{
    int iRowIndex;

    switch(m_eState)
    {
        case IS_INITIAL:
            break;

        case IS_SCANNED:
            iRowIndex = m_dataViewListSerials->GetSelectedRow();
            if( iRowIndex == wxNOT_FOUND) return;
            m_pLua->SwapUp(m_aStrSerials, m_aStrSerials[iRowIndex], m_numberOfDevices );
            this->UpdateSerialList();
            break;

        case IS_CONNECTED:
            wxLogMessage("Cannot reorder - disconnect first.");
            break;

        default:
            break;
    }

}

void ColorControlFrame::OnSerialDown(wxCommandEvent& event)
{
    int iRowIndex;

    switch(m_eState)
    {
        case IS_INITIAL:
            break;

        case IS_SCANNED:
            iRowIndex = m_dataViewListSerials->GetSelectedRow();
            if( iRowIndex == wxNOT_FOUND) return;
            m_pLua->SwapDown(m_aStrSerials, m_aStrSerials[iRowIndex], m_numberOfDevices );
            this->UpdateSerialList();
            break;

        case IS_CONNECTED:
            wxLogMessage("Cannot reorder - disconnect first.");
            break;

        default:
            break;
    }
}

/* Only Gets Called when there's a change in the chosen radio button */
void ColorControlFrame::OnTestmode(wxCommandEvent& event)
{
    /* Prevent Switching Testmode while Timer is Running */
    if(m_pTimer->IsRunning())
    {
        wxBell();
        wxLogMessage("Can't change Testmode. Stop measurements first!");
        m_rbContinuous->SetValue(true);
    }

}



void ColorControlFrame::OnTimeout(wxTimerEvent& event)
{

    if(m_pLua->StartMeasurements() == DEVICE_ERROR_FATAL)
    {
        LOG_ERROR(m_text);
        wxLogError("A fatal error has occured. Save your work, disconnect, re-scan and re-connect!");
        LOG_DEFAULT(m_text);

        /* Show that a fatal error has occured */
        UpdateConnectedField(COLOR_ERROR);
    }

    /* If the result of readColours is not zero, something went wrong, but its not a fatal error
       thus just stop the measurements and update the status (reason why it stopped)*/
    if(m_pLua->ReadColours(m_cocoDevices) != 0)
    {
        m_pTimer->Stop();
        if(m_buttonStart->GetLabel().IsSameAs("STOP")) m_buttonStart->SetLabel("START");
    }
    /* Show the error*/
    this->UpdateData();
}


void ColorControlFrame::OnShowLog(wxCommandEvent& event)
{
    if(!m_swLog->IsShown())
    {
        m_swLog->Show();
        m_dataViewListSerials->SetMinSize(wxSize(-1, m_dataViewListSerials->GetMinSize().y - 50 ));
        this->Layout();
    }
}

void ColorControlFrame::OnHideLog(wxCommandEvent& event)
{
    if(m_swLog->IsShown())
    {
        m_swLog->Hide();
        m_dataViewListSerials->SetMinSize(wxSize(-1, m_dataViewListSerials->GetMinSize().y + 50 ));
        this->Layout();
    }
}


void ColorControlFrame::OnClearLog(wxCommandEvent& event)
{
    m_text->Clear();
}

void ColorControlFrame::OnShowChromaticity(wxCommandEvent& event)
{

    FrameChromaticity* chromaticityFrame = new FrameChromaticity(this, wxID_ANY, "CIE 1931 Chromaticity Diagram");
    chromaticityFrame->Show();
}


wxString ColorControlFrame::GetInterfaceSelection()
{
    wxString strDefaultInterface;

    if(!m_fileConfig->Read("netXType/plugin", &strDefaultInterface))
    {
        strDefaultInterface = wxEmptyString;
    }

    /* run the lua file to get the available interfaces */
    wxArrayString astrInterfaces;
    CLua hInterfaces("muhkuh_cli_init.lua");
    hInterfaces.GetInterfaces(astrInterfaces);

    /* check if the default interface is contained in the found interfaces, and if so set it as the initially selected one */
    wxSingleChoiceDialog chInterface(this, wxT("Select the plugin the netX is connected to."), wxT("Select the plugin"), astrInterfaces);

    int iSel;
    if((iSel = astrInterfaces.Index(strDefaultInterface)) != wxNOT_FOUND)
    {
        chInterface.SetSelection(iSel);
    }

    /* return an empty string */
    if(chInterface.ShowModal() == wxID_CANCEL)
    {
        return wxEmptyString;
    }
    /* we clicked ok */
    else
    {
        return chInterface.GetStringSelection();
    }
}

void ColorControlFrame::OnSensorSettingsChanged(wxDataViewEvent& event )
{
    int iIndex = m_dvlColors->ItemToRow(event.GetItem());

    int iDeviceIndex, iSensorIndex;

    iDeviceIndex = (int)(iIndex / 16);
    iSensorIndex = iIndex % 16;

    /* Event came because an item in gain column changed */
    if(m_cGain == event.GetDataViewColumn())
    {
        tcs3472_gain_t gain = (tcs3472_gain_t)m_str2Uc_gain[m_dvlColors->GetTextValue(iIndex, 6)];
        m_pLua->SetGainX(iDeviceIndex, iSensorIndex, gain);
    }

    /* Event came because an item in integration time column changed */
    if(m_cIntegration == event.GetDataViewColumn())
    {
        tcs3472_intTime_t intTime = (tcs3472_intTime_t)m_str2Uc_integration[m_dvlColors->GetTextValue(iIndex, 7)];
        m_pLua->SetIntTimeX(iDeviceIndex, iSensorIndex, intTime);
    }

}

void ColorControlFrame::OnFastGain( wxCommandEvent& event)
{
    switch(m_eState)
    {
        case IS_INITIAL:
        case IS_SCANNED:
            wxLogMessage("Please connect first.");
            break;
        case IS_CONNECTED:
            m_pLua->FastSettings(m_cocoDevices, m_str2Uc_gain[m_chGain->GetString(m_chGain->GetSelection())], 0);
            /* update the view */
            this->UpdateData();
            break;
    }
}

void ColorControlFrame::OnFastIntTime( wxCommandEvent& event)
{
    switch(m_eState)
    {
        case IS_INITIAL:
        case IS_SCANNED:
            wxLogMessage("No devices .. connect first.");
            break;
        case IS_CONNECTED:
            m_pLua->FastSettings(m_cocoDevices, m_str2Uc_integration[m_chIntTime->GetString(m_chIntTime->GetSelection())], 1);
            /* update the view */
            this->UpdateData();
            break;
    }

}

void ColorControlFrame::OnSystemSettings(wxCommandEvent& event)
{
    DialogPropGrid* myPropDialog = new DialogPropGrid(this, wxID_ANY, "Color Controller Settings", wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER| wxCLOSE_BOX | wxCAPTION, m_fileConfig);//, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL,  "bla");
    myPropDialog->ShowModal();

    /* Update System Settings if any occured, take defaults if for any reason the settings are corrupted */
    int tol_nm, tol_sat, tol_illu;
    if(!m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_nm"), &tol_nm)) tol_nm = 10;
    if(!m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_sat"), &tol_sat)) tol_sat = 10;
    if(!m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_illu"), &tol_illu)) tol_illu = 50;

    for(int i = 0; i < m_numberOfDevices; i++)
    {
        m_cocoDevices.at(i)->SetTolNm(tol_nm);
        m_cocoDevices.at(i)->SetTolSat(tol_sat);
        m_cocoDevices.at(i)->SetTolIllu(tol_illu);
    }

    /* Update it if we are connected */
    switch(m_eState)
    {
        case IS_INITIAL:
        case IS_SCANNED:
            break;
        case IS_CONNECTED:
            this->UpdateData();
            break;
    }
}


//void ColorControlFrame::OnGenerateTest(wxCommandEvent& event)
//{
//
//    MyGenerateDialog* GenDialog = new MyGenerateDialog(this, wxID_ANY, wxT("Select your settings for the testfile"), wxDefaultPosition, wxDefaultSize );
//    GenDialog->Show();
//
//    wxString strPath, strDefaultDir; // Full Path with dir + name
//
//    if(!m_fileConfig->Read("DEFAULT_PATHS/path_generate_testfile", &strDefaultDir))
//        strDefaultDir = wxEmptyString;
//
//    wxLogMessage("Generating Testfile.. ");
//
//
//    wxFileDialog save_fileDialog(this, "Choose output directory",
//                                 strDefaultDir,
//                                 "", "LUA files (*.lua) |*.lua",
//                                 wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
//
//    if(save_fileDialog.ShowModal() == wxID_CANCEL)
//    {
//        wxLogMessage("Abort.");
//        return;
//    }
//
//    /* Get the name and path */
//    strPath = save_fileDialog.GetPath();
//
//    /* Save the Directory as a default directory in the ini file */
//    m_fileConfig->Write("DEFAULT_PATHS/path_generate_testfile", save_fileDialog.GetDirectory());
//
//    /* the file either exists or must be created */
//    wxTextFile tFile(strPath);
//
//    /* Create the file if it doesn't exist yet */
//    if(!tFile.Exists()) tFile.Create();
//
//    if(!tFile.Open()) wxLogMessage("Couldn't open test file.");
//
//    /* Empty the file */
//    tFile.Clear();
//
//    LOG_ERROR(m_text);
//    if(!m_testGeneration.GenerateTest(m_vectorSensorPanels, &tFile, m_chUsenetx->GetValue())) return;
//    LOG_DEFAULT(m_text);
//
//    /* Write the testfile */
//    tFile.Write();
//
//    if(!tFile.Close()) wxLogMessage("Couldn't close test file.");
//    LOG_SUCCESSFUL(m_text);
//    wxLogMessage("Generated %s.", strPath);
//    LOG_DEFAULT(m_text);
//
//
//}


void ColorControlFrame::OnGenerateTest(wxCommandEvent& event)
{
    switch(m_eState)
    {
    case IS_INITIAL:
    case IS_SCANNED:
            wxLogMessage("Please connect first.");
            break;
    case IS_CONNECTED:

        wxLogMessage("Generating Testfile.. ");

        /* Get your output directory, and some test settings */
        MyGenerateDialog GenDialog(this, wxID_ANY, wxT("Select your settings for the testfile"), wxDefaultPosition, wxDefaultSize,  wxCAPTION , m_fileConfig );
        GenDialog.ShowModal();

        if (GenDialog.IsCancelled())
        {
            wxLogMessage("Abort.");
            return;
        }
        /* the file either exists or must be created */
        wxTextFile tFile(GenDialog.GetOutputDir());

        /* Create the file if it doesn't exist yet */
        if(!tFile.Exists()) tFile.Create();

        if(!tFile.Open()) wxLogMessage("Couldn't open test file.");

        /* Empty the file */
        tFile.Clear();

        LOG_ERROR(m_text);
        if(!m_testGeneration.GenerateTest(m_vectorSensorPanels, &tFile, GenDialog.UseNetX(), GenDialog.LuxCheckEnabled()))
        {
            /* Change log colour back */
            LOG_DEFAULT(m_text);
            return;
        }
        /* Write the testfile */
        tFile.Write();

        if(!tFile.Close()) wxLogMessage("Couldn't close test file.");
        LOG_SUCCESSFUL(m_text);
        wxLogMessage("Generated %s.", GenDialog.GetOutputDir());
        LOG_DEFAULT(m_text);

        break;
    }

}


void ColorControlFrame::OnUseTest(wxCommandEvent& event)
{
    wxFileDialog*  open_fileDialog;
    wxString       strDefaultDir;
    wxString       strPath;


    if(!m_fileConfig->Read("DEFAULT_PATHS/path_use_testfile", &strDefaultDir))
        strDefaultDir = wxEmptyString;

    open_fileDialog = new wxFileDialog(this, "Choose the input test file ..",
                                       strDefaultDir,
                                       "", "LUA files (*.lua) |*.lua",
                                       wxFD_DEFAULT_STYLE | wxFD_FILE_MUST_EXIST);

    if(open_fileDialog->ShowModal() == wxID_CANCEL)
    {
        wxLogMessage("Abort.");
        return;
    }

    strPath = open_fileDialog->GetPath();

    wxLogMessage("Using Testfile %s", strPath);

    /* Write the path as a default directory path into the config file */
    m_fileConfig->Write("DEFAULT_PATHS/path_use_testfile", open_fileDialog->GetDirectory());

    /* Let the user select the interface */
    wxString strInterface;

    /* If the user pressed cancel we abort */
    if((strInterface = GetInterfaceSelection()) == wxEmptyString)
    {
        wxLogMessage("Abort.");
        return;
    }

    wxString strLine;
    wxTextFile tFile(strPath);
    tFile.Open();

    /* Insert the Com port into the lua file ... there might be a better solution here */
    /* assumption: the generated file has the line in it */
    for(strLine = tFile.GetFirstLine(); !tFile.Eof(); strLine = tFile.GetNextLine())
    {
        if(strLine.StartsWith("-- INSERT INTERFACE NUMBER"))
        {
            /* Remove the line after "--INSERT INTERFACE NUMBER"*/
            /* We expect that line to be a empty line (newline) .. don't change that */
            tFile.RemoveLine(tFile.GetCurrentLine()+1);
            /* Replace it */
            tFile.InsertLine(wxString::Format(wxT("local strInterface = \"%s\""), strInterface), (tFile.GetCurrentLine()+1));
            break;
        }

    }

    tFile.Write();

    /* Insert code to use the test */
    CLua *useTest = new CLua(/*strPath*/);

    LOG_ERROR(m_text);
    int iTestResult = useTest->RunGeneratedTest(strPath);

    if(!useTest->IsLoaded())
    {
        wxLogMessage("Test file could not be run on lua (errors) .. abort.");

        /* Empty the default plugin as it did not work */
        m_fileConfig->Write("netXType/plugin", "");

        LOG_DEFAULT(m_text);
        return;
    }

    /* LED Stimulation file could be run successfully, thus save the plugin as default */
    m_fileConfig->Write("netXType/plugin", strInterface);

    /* Show result */
    if(iTestResult == 0)
    {
        LOG_SUCCESSFUL(m_text);
        wxLogMessage("LED Test successful.");
        LOG_DEFAULT(m_text);
    }
    else if(iTestResult == 1)
    {
        LOG_ERROR(m_text);
        wxLogMessage("LED Test failed!");
        LOG_DEFAULT(m_text);
    }
    else if(iTestResult == 2)
    {
        LOG_ERROR(m_text);
        wxLogMessage("Device error!");
        LOG_DEFAULT(m_text);
    }

}

void ColorControlFrame::OnSaveSession( wxCommandEvent& event )
{
    wxString strPath, strDefaultSaveDir;

    /* If the chosen save dir is not in the config file yet, write it into it */
    if(!m_fileConfig->Read("DEFAULT_PATHS/path_save_testsession", &strDefaultSaveDir))
        strDefaultSaveDir = wxEmptyString;


    wxFileDialog *save_sessionDialog;

    wxLogMessage("Saving Session.. ");

    save_sessionDialog = new wxFileDialog(this, "Choose output directory",
                                                strDefaultSaveDir,
                                                "", "ini files (*.ini) |*.ini",
                                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if( save_sessionDialog->ShowModal() == wxID_CANCEL )
    {
        wxLogMessage("Abort.");
        return;
    }

    /* Get full name + path */
    strPath = save_sessionDialog->GetPath();

    /* Save the directory as a default directory into the ini file */
    m_fileConfig->Write("DEFAULT_PATHS/path_save_testsession", save_sessionDialog->GetDirectory());


    /* the file either exists or must be created */
    wxTextFile tFile(strPath);

    /* Create the file if it doesn't exist yet */
    if(!tFile.Exists()) tFile.Create();

    if(!tFile.Open()) wxLogMessage("Couldn't open test file.");

    /* Clear It */
    tFile.Clear();

    /* Insert code here to fill it with template key tables and chapters */

    m_testGeneration.SaveSessionAsIni(m_vectorSensorPanels, &tFile);

    tFile.Write();

    if(!tFile.Close()) wxLogMessage("Couldn't close test file");

    wxLogMessage("Saved Session.");



}

void ColorControlFrame::OnOpenSession( wxCommandEvent& event )
{

    wxFileDialog*  open_fileDialog;
    wxString       strDefaultDir;
    wxString       strPath;


    if(!m_fileConfig->Read("DEFAULT_PATHS/path_open_testsession", &strDefaultDir))
        strDefaultDir = wxEmptyString;

    open_fileDialog = new wxFileDialog(this, "Choose the input test session file ..",
                                       strDefaultDir,
                                       "", "ini files (*.ini) |*.ini",
                                       wxFD_DEFAULT_STYLE | wxFD_FILE_MUST_EXIST);

    if(open_fileDialog->ShowModal() == wxID_CANCEL)
    {
        wxLogMessage("Abort.");
        return;
    }

    strPath = open_fileDialog->GetPath();

    wxLogMessage("Opening test session %s", strPath);

    m_fileConfig->Write("DEFAULT_PATHS/path_open_testsession", open_fileDialog->GetDirectory());

    wxFileConfig tFileConfig(wxEmptyString, wxEmptyString,
                             strPath, wxEmptyString,
                             wxCONFIG_USE_LOCAL_FILE);


    if(m_nbData->GetSelection() != 1)
    {
        m_nbData->SetSelection(1);
        m_swTestdefinition->Show();
    }

    if(m_testGeneration.OpenSessionAsIni(m_vectorSensorPanels, &tFileConfig))
    {
        wxLogMessage("Opened %s.", strPath);
    }
    else wxLogMessage("Abort.");

}

/*
void ColorControlFrame::OnUseNetX( wxCommandEvent& event )
{
    switch(m_eState)
    {
        case IS_INITIAL:
        case IS_SCANNED:
            break;
        case IS_CONNECTED:
            bool useNetX = m_chUsenetx->GetValue();
            for(wxVector<PanelSensor*>::iterator it =  m_vectorSensorPanels.begin(); it != m_vectorSensorPanels.end(); it++)
            {
                (*it)->UpdatePanelView(useNetX);
            }

            m_panelHeader->UpdateHeader(useNetX);

            if(m_nbData->GetSelection() == 1)
            {
                m_swTestdefinition->Layout();
                m_panelHeader->Layout();
                m_panelHeader->FitInside();
                m_swTestdefinition->FitInside();
            }

            break;

    }
}
*/

void ColorControlFrame::OnResize( wxSizeEvent& event )
{
    wxLogMessage("resizing");
}

