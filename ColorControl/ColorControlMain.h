/***************************************************************
 * Name:      ColorControlMain.h
 * Purpose:   Defines Application Frame
 * Author:    Subhan Waizi (swaizi@hilscher.com)
 * Created:   2015-06-16
 * Copyright: Subhan Waizi ()
 * License:
 **************************************************************/

#ifndef COLORCONTROLMAIN_H
#define COLORCONTROLMAIN_H



#include "ColorControlApp.h"


#include "GUIFrame.h"
#include "CSensorData.h"

class ColorControlFrame: public GUIFrame
{
    public:
        ColorControlFrame(wxFrame *frame);
        ~ColorControlFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnScan(wxCommandEvent& event);
        virtual void OnConnect(wxCommandEvent& event);

        wxLog *m_pLogTarget;


};


#endif // COLORCONTROLMAIN_H
