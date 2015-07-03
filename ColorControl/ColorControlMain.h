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
#include "PanelSensor.h"


#define MYGREEN {0, 200, 0}
#define MYRED   {255, 0, 0}




/* System States */
enum e_state_t
{
    IS_INITIAL,
    IS_SCANNED,
    IS_CONNECTED
};


// in the header file
DECLARE_VARIANT_OBJECT(wxChoice);

class ColorControlFrame: public GUIFrame
{

    public:
        ColorControlFrame(wxFrame *frame);
        ~ColorControlFrame();
    private:

        enum e_TIME_TESTMODE
        {
            TESTMODE_TIME_0_2SEC,
            TESTMODE_TIME_0_5SEC,
            TESTMODE_TIME_1SEC,
            TESTMODE_TIME_2SEC,
            TESTMODE_TIME_5SEC,
        };

        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnScan(wxCommandEvent& event);
        virtual void OnConnect(wxCommandEvent& event);
        virtual void OnDisconnect(wxCommandEvent& event);
        virtual void OnStart(wxCommandEvent& event);
        virtual void OnSerialUp  (wxCommandEvent& event);
        virtual void OnSerialDown(wxCommandEvent& event);
        virtual void OnTestmode (wxCommandEvent& event);
        virtual void OnTimeout(wxTimerEvent& event);
        virtual void OnShowLog(wxCommandEvent& event);
        virtual void OnHideLog(wxCommandEvent& event);
        virtual void OnClearLog(wxCommandEvent& event);
        virtual void OnShowChromaticity(wxCommandEvent& event);
        virtual void OnSensorSettingsChanged(wxDataViewEvent& event);
        virtual void OnSystemSettings( wxCommandEvent& event);
        virtual void OnGenerateTest( wxCommandEvent& event);
        virtual void OnUseTest( wxCommandEvent& event);



        void CreateRows(int numberOfDevices);
        void CreateTestPanels(int numberOfDevices);
        void ClearTestPanels();
        void UpdateSerialList();
        void UpdateRows(int iNumberOfDevices);
        void UpdateConnectedField(wxColour colour);
        int  IntegrationToIndex(tcs3472_intTime_t intTime);
        int  StrToRegisterContent(const wxString strSetting);
        void GenerateColorTestTable(wxTextFile* tFile);
        void GenerateNetXTestTable(wxTextFile* tFile);

        int         m_numberOfDevices;
        wxLog       *m_pLogTarget;
        CLua        *m_pLua;
        wxString    *m_aStrSerials;
        e_state_t   m_eState;




        /* vector contains panels for testfile generation */
        wxVector<PanelSensor*> m_sensorPanels;
        /* vector contains entries for devices */
        wxVector<CColorController*> m_cocoDevices;

};


#endif // COLORCONTROLMAIN_H
