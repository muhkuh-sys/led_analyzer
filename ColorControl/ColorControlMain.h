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
#include "CDevice.h"

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

        void UpdateData();
        void CreateRows(int numberOfDevices);
        void CreateTestPanels(int numberOfDevices);

        CDevice* m_device;
        wxLog *m_pLogTarget;
        //PanelSensor* m_sensorPanels;
        wxVector<PanelSensor*> m_sensorPanels;
        //PanelHeader m_panelHeader;


};


#endif // COLORCONTROLMAIN_H
