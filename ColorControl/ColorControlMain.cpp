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
    m_text->AppendText(wxT("You just clicked on Scan button\n"));

}

void ColorControlFrame::OnConnect(wxCommandEvent& event)
{
    m_text->AppendText(wxT("You just clicked on Connect buton\n"));

}


