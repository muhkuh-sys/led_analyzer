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

extern "C"
{
    #define  lua_c
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"

}



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
    wxLogMessage(wxT("Welcome to Color Control, where sugar grows on trees... \n"));


}

ColorControlFrame::~ColorControlFrame()
{

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
    lua_State *ptLuaState = lua_open();

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

      //m_numberOfDevices ...

    else wxLogMessage("Please Disconnect first");
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
        m_cocoDevices.at(i)->ConnectDevice(5);
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
    wxBoxSizer* bSizerTestDefinition;

    bSizerTestDefinition = new wxBoxSizer( wxVERTICAL );
    m_panelHeader = new PanelHeader(m_swTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALIGN_TOP);


    bSizerTestDefinition->Add(m_panelHeader, 0, wxEXPAND, 0);

    for (int i = 0; i< numberOfDevices; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            m_sensorPanels.push_back((new PanelSensor(m_swTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, i*16 + j)));
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
    m_swTestdefinition->Layout();
    bSizerTestDefinition->Fit(m_swTestdefinition);

}

void ColorControlFrame::ClearTestPanels()
{
    m_swTestdefinition->Hide();

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
