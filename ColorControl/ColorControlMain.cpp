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
    char buff[256];
    char filename[] = "device_test.lua";
    int error;
    int number = 0;
    m_numberOfDevices = 2;
    // View Class which updates refreshes and takes care about data to be shown
    // set new log target
    m_pLogTarget = new wxLogTextCtrl(m_text);
    m_pOldLogTarget = wxLog::SetActiveTarget(m_pLogTarget);
    // Redirect your std::cout to the same text


    if( m_pOldLogTarget !=  NULL)
    {
        delete m_pOldLogTarget;
    }


    wxLog::SetVerbose(true);
    wxLog::SetLogLevel(wxLOG_Debug );
    wxLogMessage(wxT("Welcome to Color Control...\n"));

    wxStreamToTextRedirector redirect(m_text);

    /* Open your main lua file where functions are stored */
    L = lua_open();
    luaL_openlibs(L);

    if (luaL_loadfile(L, "lua/color_control.lua") || lua_pcall(L, 0, 0, 0))
    {
        wxLogMessage("Cannot open the main lua file");
    }

}

ColorControlFrame::~ColorControlFrame()
{
 lua_close(L);
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

    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));

}

void ColorControlFrame::OnScan(wxCommandEvent& event)
{

    if(m_cocoDevices.empty())
      {
        for(int i = 0; i < m_numberOfDevices; i++)
        {
            m_cocoDevices.push_back(new CColorController);
        }
      }
    else wxLogMessage("Please Disconnect first");


    lua_getglobal(L, "connectDevices");
    if(lua_pcall(L, 0, 2, 0) != 0) cout << "error" << endl;


    if(lua_isnumber(L, -1) != 0) cout << "error" << endl;
    int test = lua_tonumber(L, -1);
    //lua_pop(L, -1);

    wxString** astrSerial = (wxString** )lua_touserdata(L, -2);
    cout << astrSerial[0] << endl;








      //m_numberOfDevices ...


}

void ColorControlFrame::OnConnect(wxCommandEvent& event)
{


  if(m_cocoDevices.empty())
  {
    wxLogMessage("Please Scan for devices first");
  }
  else
  {
    wxLogMessage("Connecting ..");

    for(int i = 0; i < m_numberOfDevices; i++)
    {
        //m_cocoDevices.at(i)->ConnectDevice(5);
    }
    CreateRows(m_numberOfDevices);
    CreateTestPanels(m_numberOfDevices);
  }

}


void ColorControlFrame::OnDisconnect(wxCommandEvent& event)
{
    wxLogMessage("you clicked on disconnet");


    // Clear your Color Controller List
    if(!m_cocoDevices.empty()) m_cocoDevices.clear();

    // Delete the rows in the table
    m_dvlColors->DeleteAllItems();

    // Delete all the test panels
    if(!m_sensorPanels.empty())
    {
        this->ClearTestPanels();
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
            rowdata.push_back(wxVariant(""));  // gain
            rowdata.push_back(wxVariant(""));  // inttime

            m_dvlColors->AppendItem(rowdata);
       }
    }

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
            m_sensorPanels.push_back((new PanelSensor(m_swTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, i*16 + j + 1)));
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

    for(int i = 0; i < 2; i++)
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
