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
    // View Class which updates refreshes and takes care about data to be shown
    // set new log target
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


    wxFileName::SetCwd(wxFileName::GetCwd()+"\\build");




    m_fileConfig = new wxFileConfig(wxEmptyString, wxEmptyString,
                                    wxFileName::GetCwd()+"/config.ini", wxEmptyString,
                                    wxCONFIG_USE_LOCAL_FILE);


    //wxLogMessage("%s", m_fileConfig->GetLocalFileName(NULL, 0));

    /* Allocate space for the array that will contain serial numbers */
    m_aStrSerials = new wxString[128];

    /* Initialize the timer */
    m_pTimer = new wxTimer(this, wxID_TIMER);
    //m_pTimer->Start(1000);

    /* Set Initial State */
    m_eState = IS_INITIAL;
}

ColorControlFrame::~ColorControlFrame()
{
    delete[] m_aStrSerials;
    delete m_fileConfig;
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

    wxString msg = "Subhan Waizi - Bachelorarbeit. BOOYA.";
    wxMessageBox(msg, _("Welcome to..."));

}

void ColorControlFrame::OnScan(wxCommandEvent& event)
{

    switch(m_eState)
    {
        case IS_INITIAL:
            /* If we're at initial state load and run the color_control file */
            m_pLua = new CLua("color_control.lua");

            /* If the txt_ctrl connected was red before because some error occured, we will set it to default now */

            m_textCtrlConnected->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
            m_textCtrlConnected->Clear();
            *m_textCtrlConnected << m_numberOfDevices;
            m_dataViewListSerials->DeleteAllItems();

            m_eState = IS_SCANNED;

            /* Don't break */

        case IS_SCANNED:
            /* Scan */
            m_pLua->ScanDevices(m_numberOfDevices, m_aStrSerials);
            if(m_numberOfDevices == 0)
            {
                wxLogMessage("No device detected ... please make sure the device is properly attached!");

                if(!m_cocoDevices.empty()) m_cocoDevices.clear();

                m_eState = IS_INITIAL;

                delete m_pLua;
            }
            else
            {
                /* Get the default Tolerance Values from the Configuration files */
                int tol_nm, tol_sat, tol_illu;
                m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_nm"), &tol_nm);
                m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_sat"), &tol_sat);
                m_fileConfig->Read(wxT("DEFAULT_TOLERANCES/tol_illu"), &tol_illu);

                for(int i = 0; i < m_numberOfDevices; i++)
                {
                    m_cocoDevices.push_back(new CColorController());
                    m_cocoDevices.at(i)->SetTolNm(tol_nm);
                    m_cocoDevices.at(i)->SetTolSat(tol_sat);
                    m_cocoDevices.at(i)->SetTolIllu(tol_illu);
                }
                this->UpdateSerialList();
                m_eState = IS_SCANNED;
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
    /* There are known Color Controllers until now */
        /* Fill the serial gui list (clear before) */
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
                    m_cocoDevices.at(i)->SetSerialNumber(m_aStrSerials[0]);
                    m_cocoDevices.at(i)->SetConnectivity(true);
                }

                /* Create Rows for Colors*/
                CreateRows(m_numberOfDevices);
                /* Create Test Panels */
                CreateTestPanels(m_numberOfDevices);


                /* Set System State to Connected */
                m_eState = IS_CONNECTED;

                /* Init the devices */
                m_pLua->InitDevices(m_numberOfDevices);

                /* Show It in the textCtrl for connected devices */
                this->UpdateConnectedField(MYGREEN);
                wxLogMessage("Connected!");

            }

            /* Some Exception happened in the lua code (i2c/ftdi/led_analyzer functions in led_analyzer.dll) */
            if(temp < 0)
            {
                /* Show that something went wrong */
                m_numberOfDevices = 0;
                this->UpdateConnectedField(MYRED);
                /* Reset the System State */
                m_eState = IS_INITIAL;
                wxLogError("Ups! Something went wrong, please retry Scan and Connect!");
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

            /* Clear Serial Numbers */
            m_dataViewListSerials->DeleteAllItems();

            /* Clear Rows for Colors */
            m_dvlColors->DeleteAllItems();

            /* Clear Test Panels */
            this->ClearTestPanels();
            m_swColors->Layout();

            /* Set number of devices to zero -- ONLY AT THE END OF A BLOCK */
            m_numberOfDevices = 0;

            /* Flush and write zero */
            /* Reset the color of textctrl Connected */
            this->UpdateConnectedField(wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

            /* If the timer is Running Stop and transform Stop button into Start button It*/
            if(m_pTimer->IsRunning())
            {
                m_pTimer->Stop();
                m_buttonStart->SetLabel("START");
            }

            /* Close the current Lua State (color_control.lua) */
            delete m_pLua;

            /* Set Initial System State */
            m_eState = IS_INITIAL;

            /* Say you're disconnected ! */
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
            wxLogMessage("Please Scan and Connect first.");
            break;

        case IS_SCANNED:
            wxLogMessage("Please Connect first.");
            break;

        case IS_CONNECTED:
            /* Now Check if we Make Single or Continuous Measurements */

            if(m_rbSingle->GetValue() == true)
            {
                m_pLua->StartMeasurements(m_numberOfDevices);

                m_pLua->ReadColours(m_numberOfDevices, m_cocoDevices);

                this->UpdateRows(m_numberOfDevices);
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
                        case TESTMODE_TIME_10SEC:
                            iTimerValue = 10000;
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

void ColorControlFrame::CreateRows(int numberOfDevices)
{

    for(int i = 0; i < numberOfDevices; i++)
    {
       for(int j = 0; j<16; j++)
       {
            wxVector<wxVariant> rowdata;
            rowdata.push_back(i*16 + (j + 1)); // sensorno
            rowdata.push_back(wxVariant(""));  // wavelength
            rowdata.push_back(wxVariant(""));  // saturation
            rowdata.push_back(wxVariant(""));  // illumination
            rowdata.push_back(wxVariant(""));  // m_cColor
            rowdata.push_back("");// m_clearRatio;
            rowdata.push_back("");  // gain
            rowdata.push_back(wxVariant(""));  // inttime

            m_dvlColors->AppendItem(rowdata);

       }
    }

}

void ColorControlFrame::UpdateRows(int iNumberOfDevices)
{
    /* First Clear your Rows */
    m_dvlColors->DeleteAllItems();
    //this->CreateRows(iNumberOfDevices);


    for(int i = 0; i < iNumberOfDevices; i++)
    {
       for(int j = 0; j<16; j++)
       {

            /* First Panel = Colors */
            wxVector<wxVariant> rowdata;
            rowdata.push_back(i*16 + (j + 1)); // sensorno
            rowdata.push_back(m_cocoDevices.at(i)->GetWavelength(j));  // wavelength
            rowdata.push_back(m_cocoDevices.at(i)->GetSaturation(j));   // saturation
            rowdata.push_back(m_cocoDevices.at(i)->GetIllumination(j));  // illumination
            rowdata.push_back("");          // m_cColor
            rowdata.push_back(m_cocoDevices.at(i)->GetClearRatio(j)); // clearRatio
            rowdata.push_back(astrGainchoices.Item(m_cocoDevices.at(i)->GetGain(j)));                                     // gain
            rowdata.push_back(astrIntchoices.Item(IntegrationToIndex(m_cocoDevices.at(i)->GetIntTime(j))));                           // inttime

            m_dvlColors->AppendItem(rowdata);

            /* Second Panel = Testdefinition */
            m_sensorPanels.at(i*16 + j)->SetName("");
            m_sensorPanels.at(i*16 + j)->SetWavelength(m_cocoDevices.at(i)->GetWavelength(j));
            m_sensorPanels.at(i*16 + j)->SetSaturation(m_cocoDevices.at(i)->GetSaturation(j));
            m_sensorPanels.at(i*16 + j)->SetIllumination(m_cocoDevices.at(i)->GetIllumination(j));
            m_sensorPanels.at(i*16 + j)->SetColour(m_cocoDevices.at(i)->GetColour(j));
            m_sensorPanels.at(i*16 + j)->SetTolWavelength(m_cocoDevices.at(i)->GetTolNm());
            m_sensorPanels.at(i*16 + j)->SetTolSaturation(m_cocoDevices.at(i)->GetTolSat());
            m_sensorPanels.at(i*16 + j)->SetTolIllumination(m_cocoDevices.at(i)->GetTolIllu());
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
            m_sensorPanels.push_back(new PanelSensor(m_swTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, i*16 + j + 1));
        }
    }


    for(int i = 0; i < numberOfDevices; i++)
    {
        for(int j = 0; j < 16; j++)
        {
           bSizerTestDefinition->Add(m_sensorPanels.at(i*16 + j), 0, wxEXPAND);
        }
    }



    m_swTestdefinition->SetSizer(bSizerTestDefinition);
    /* this will make the scroll bars show up right away */
    m_swTestdefinition->FitInside();
    m_swTestdefinition->Layout();

    //wxLogMessage("Currently selected page: %i", m_nbData->GetSelection());
    if(m_nbData->GetSelection() == 1)m_swTestdefinition->Show();


}

void ColorControlFrame::ClearTestPanels()
{
    m_swTestdefinition->Hide();
    m_swTestdefinition->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

    if(m_panelHeader != NULL) m_panelHeader->Destroy();

    for(int i = 0; i < m_numberOfDevices; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            m_sensorPanels.at(i*16 + j)->Destroy();
        }
    }
    m_sensorPanels.clear();
    m_swTestdefinition->Show();
    m_swTestdefinition->Layout();
}

void ColorControlFrame::OnSerialUp(wxCommandEvent& event)
{
    int iRowIndex = m_dataViewListSerials->GetSelectedRow();
    if( iRowIndex == wxNOT_FOUND) return;
    m_pLua->SwapUp(m_aStrSerials, m_aStrSerials[iRowIndex], m_numberOfDevices );
    this->UpdateSerialList();
}

void ColorControlFrame::OnSerialDown(wxCommandEvent& event)
{
    int iRowIndex = m_dataViewListSerials->GetSelectedRow();
    if( iRowIndex == wxNOT_FOUND) return;
    m_pLua->SwapDown(m_aStrSerials, m_aStrSerials[iRowIndex], m_numberOfDevices );
    this->UpdateSerialList();
}

/* Only Gets Called when there's a change in the chosen radio button */
void ColorControlFrame::OnTestmode(wxCommandEvent& event)
{
    /* Prevent Switching Testmode while Timer is Running */
    if(m_pTimer->IsRunning())
    {
        wxBell();
        wxLogMessage("Can't change Testmode. Stop First!");
        m_rbContinuous->SetValue(true);
    }

}


void ColorControlFrame::OnTimeout(wxTimerEvent& event)
{

    m_pLua->StartMeasurements(m_numberOfDevices);
    m_pLua->ReadColours(m_numberOfDevices, m_cocoDevices);
    this->UpdateRows(m_numberOfDevices);

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
        tcs3472_gain_t gain = (tcs3472_gain_t)StrToRegisterContent(m_dvlColors->GetTextValue(iIndex, 6));
        m_pLua->SetGainX(iDeviceIndex, iSensorIndex, gain);
    }

    /* Event came because an item in integration time column changed */
    if(m_cIntegration == event.GetDataViewColumn())
    {
        tcs3472_intTime_t intTime = (tcs3472_intTime_t)StrToRegisterContent(m_dvlColors->GetTextValue(iIndex, 7));
        m_pLua->SetIntTimeX(iDeviceIndex, iSensorIndex, intTime);
    }


}


int ColorControlFrame::IntegrationToIndex(tcs3472_intTime_t intTime)
{
    switch(intTime)
    {
    case TCS3472_INTEGRATION_2_4ms:
        return 0;
        break;
    case TCS3472_INTEGRATION_24ms:
        return 1;
        break;
    case TCS3472_INTEGRATION_100ms:
        return 2;
        break;
    case TCS3472_INTEGRATION_154ms:
        return 3;
        break;
    case TCS3472_INTEGRATION_200ms:
        return 4;
        break;
    case TCS3472_INTEGRATION_700ms:
        return 5;
        break;
    default:
        wxLogMessage("Cannot return Int Time Index, Int Time not found!");
        break;
    }

    /* Shouldn't arrive here */
    return -1;
}


int ColorControlFrame::StrToRegisterContent(const wxString strSetting)
{
    if(strSetting.Left(4).IsSameAs("GAIN"))
    {
        if(strSetting.IsSameAs("GAIN_1X"))  return TCS3472_GAIN_1X;
        if(strSetting.IsSameAs("GAIN_4X"))  return TCS3472_GAIN_4X;
        if(strSetting.IsSameAs("GAIN_16X")) return TCS3472_GAIN_16X;
        if(strSetting.IsSameAs("GAIN_60X")) return TCS3472_GAIN_60X;

    }

    if(strSetting.Left(4).IsSameAs("TIME"))
    {
        if(strSetting.IsSameAs("TIME_2_4ms")) return TCS3472_INTEGRATION_2_4ms;
        if(strSetting.IsSameAs("TIME_24ms"))  return TCS3472_INTEGRATION_24ms;
        if(strSetting.IsSameAs("TIME_100ms")) return TCS3472_INTEGRATION_100ms;
        if(strSetting.IsSameAs("TIME_154ms")) return TCS3472_INTEGRATION_154ms;
        if(strSetting.IsSameAs("TIME_200ms")) return TCS3472_INTEGRATION_200ms;
        if(strSetting.IsSameAs("TIME_700ms")) return TCS3472_INTEGRATION_700ms;

    }

    /* Should Not arrive here */
    return -1;
}

