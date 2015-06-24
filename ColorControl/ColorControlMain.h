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
#include "CLua.h"


#define MYGREEN {0, 200, 0}


/* System States */
typedef enum e_state_t
{
    IS_INITIAL,
    IS_SCANNED,
    IS_CONNECTED
};

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
        virtual void OnSerialUp  (wxCommandEvent& event);
        virtual void OnSerialDown(wxCommandEvent& event);

        void CreateRows(int numberOfDevices);
        void CreateTestPanels(int numberOfDevices);
        void ClearTestPanels();
        void UpdateSerialList();

        int         m_numberOfDevices;
        wxLog       *m_pLogTarget;
        CLua*       m_pLua;
        wxString*   m_aStrSerials;
        e_state_t   m_eState;



        /* vector contains panels for testfile generation */
        wxVector<PanelSensor*> m_sensorPanels;
        /* vector contains entries for devices */
        wxVector<CColorController*> m_cocoDevices;

};


#endif // COLORCONTROLMAIN_H
