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

extern "C"
{
    #define  lua_c
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"

}

#include "ColorControlApp.h"
#include "GUIFrame.h"
#include "CSensorData.h"
#include "CDevice.h"

#include <iostream>
using namespace std;



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
        virtual void OnDisconnect(wxCommandEvent& event);

        void CreateRows(int numberOfDevices);
        void CreateTestPanels(int numberOfDevices);
        void ClearTestPanels();

        int         m_numberOfDevices;
        wxLog       *m_pLogTarget;
        lua_State   *L;

        /* vector contains panels for testfile generation */
        wxVector<PanelSensor*> m_sensorPanels;
        /* vector contains entries for devices */
        wxVector<CColorController*> m_cocoDevices;

};


#endif // COLORCONTROLMAIN_H
