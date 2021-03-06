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
#include "CTestGeneration.h"
#include "Config.h"




/* System States */
enum e_state_t
{
    IS_INITIAL,
    IS_SCANNED,
    IS_CONNECTED
};


WX_DECLARE_STRING_HASH_MAP(unsigned char /*value*/, MyStr2UcHash );
WX_DECLARE_HASH_MAP(unsigned char /* key */, wxString /* value */, wxIntegerHash, wxIntegerEqual, MyUc2StrHash );
WX_DECLARE_HASH_MAP(unsigned char /* key */, unsigned char /*value*/, wxIntegerHash, wxIntegerEqual, MyUc2UcHash );
class ColorControlFrame: public GUIFrame
{

    public:
        ColorControlFrame(wxFrame *frame);
        ~ColorControlFrame();
    private:

        MyStr2UcHash m_str2Uc_gain;
        MyStr2UcHash m_str2Uc_integration;
        MyUc2StrHash m_uc2strHash_gain;
        MyUc2StrHash m_uc2strHash_integration;
        MyUc2UcHash  m_uc2ucHash_waittimeselection;

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
        virtual void OnQuickGuide(wxCommandEvent& event);
        virtual void OnScan(wxCommandEvent& event);
        virtual void OnConnect(wxCommandEvent& event);
        virtual void OnDisconnect(wxCommandEvent& event);
        virtual void OnStart(wxCommandEvent& event);
        virtual void OnStimulation(wxCommandEvent& event);
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
        virtual void OnSaveSession( wxCommandEvent& event );
        virtual void OnOpenSession( wxCommandEvent& event );
        virtual void OnResize(  wxSizeEvent& event );
        //virtual void OnUseNetX ( wxCommandEvent& event);
        virtual void OnFastGain ( wxCommandEvent& event );
        virtual void OnFastIntTime( wxCommandEvent& event );

        wxString GetInterfaceSelection();
        void InitHashTables();
        void CreateRows();
        void CreateTestPanels(int numberOfDevices);
        void ClearTestPanels();
        void UpdateSerialList();
        void UpdateData();
        void UpdateConnectedField(wxColour colour);

        void GenerateColorTestTable(wxTextFile* tFile);
        void GenerateNetXTestTable(wxTextFile* tFile);
        void InsertHeaders(wxTextFile* tFile);
        void GenerateTestStepFunctions(wxTextFile* tFile);
        unsigned char GetSelectionMaxIntegrationTime();

        int  GetMaximumNumberOfTestsets();
        int  GetLastEntry();
        bool TestEntriesOK();

        int         m_numberOfDevices;
        wxLog       *m_pLogTarget;
        CLua        *m_pLua;
        wxString    *m_aStrSerials;
        e_state_t   m_eState;

        CTestGeneration m_testGeneration;


        /* vector contains panels for testfile generation */
        wxVector<PanelSensor*> m_vectorSensorPanels;
        /* vector contains entries for devices */
        wxVector<CColorController*> m_cocoDevices;

};


#endif // COLORCONTROLMAIN_H
