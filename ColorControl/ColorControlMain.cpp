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
    // set new log target
    m_pLogTarget = new wxLogTextCtrl(m_text);
    m_pOldLogTarget = wxLog::SetActiveTarget(m_pLogTarget);

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
    delete[] m_device;
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

    wxLogMessage(wxT("You just clicked on Scan Button"));

}

void ColorControlFrame::OnConnect(wxCommandEvent& event)
{

   int number = 2;
   if(m_device == NULL)
   {
        m_device = new CDevice[number];
        this->CreateRows(number);
        this->CreateTestPanels(number);
   }

   else wxLogMessage("You are already connected");

}


void ColorControlFrame::UpdateData()
{

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
    wxBoxSizer* bSizerTestDefinition;


    bSizerTestDefinition = new wxBoxSizer( wxVERTICAL );

    for (int i = 0; i< numberOfDevices; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            m_sensorPanels.push_back((new PanelSensor(m_swTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER)));
        }
    }



    for(int i = 0; i < numberOfDevices; i++)
    {
        for(int j = 0; j < 16; j++)
        {
           bSizerTestDefinition->Add(m_sensorPanels.at(i*16 + j), 1, wxEXPAND);
        }
    }


    m_swTestdefinition->SetSizer(bSizerTestDefinition);
    bSizerTestDefinition->Fit(m_swTestdefinition);
    m_swTestdefinition->Layout();

}
