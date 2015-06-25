///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

#include <iostream>
using namespace std;


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/dataview.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/scrolwin.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/dynlib.h>
#include <wx/radiobut.h> //
#include <wx/colordlg.h>
#include <wx/imaglist.h>
///////////////////////////////////////////////////////////////////////////////
/// Class PanelHeader
///////////////////////////////////////////////////////////////////////////////
class PanelHeader : public wxPanel
{
	private:

	protected:
		wxStaticText* m_stSensor;
		wxStaticText* m_stName;
		wxStaticText* m_stWavelength;
		wxStaticText* m_stSaturation;
		wxStaticText* m_stIllumination;
		wxStaticText* m_stColor;
		wxStaticText* m_stPintype;
		wxStaticText* m_stPinNo;
		wxStaticText* m_stPinvalue;
		wxStaticText* m_stPinDefValue;
		wxStaticText* m_tolWl;
		wxStaticText* m_tolSat;
		wxStaticText* m_tolLux;

	public:

		PanelHeader( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 932,35 ), long style = wxTAB_TRAVERSAL );
		~PanelHeader();

};




///////////////////////////////////////////////////////////////////////////////
/// Class PanelSensor
///////////////////////////////////////////////////////////////////////////////
class PanelSensor : public wxPanel
{
	private:

	protected:
		wxTextCtrl* m_txtCtrlSensorNo;
		wxCheckBox* m_cbUseSet1;
		wxBitmapButton* m_bpButtonPaste1;
		wxBitmapButton* m_bpButtonClear1;
		wxCheckBox* m_cbUseSet2;
		wxBitmapButton* m_bpButtonPaste2;
		wxBitmapButton* m_bmButtonClear2;
		wxCheckBox* m_cbUseSet3;
		wxBitmapButton* m_bmButtonPaste3;
		wxBitmapButton* m_bpButtonClear3;
		wxTextCtrl* m_txtCtrlCurName;
		wxTextCtrl* m_txtCtrlSpName1;
		wxTextCtrl* m_txtCtrlSpName2;
		wxTextCtrl* m_txtCtrlSpName3;
		wxTextCtrl* m_txtCtrlCurWL;
		wxTextCtrl* m_txtCtrlSpWL1;
		wxTextCtrl* m_txtCtrlSpWL2;
		wxTextCtrl* m_txtCtrlSpWL3;
		wxTextCtrl* m_txtCtrlCurSat;
		wxTextCtrl* m_txtCtrlSpSat1;
		wxTextCtrl* m_txtCtrlSpSat2;
		wxTextCtrl* m_txtCtrlSpSat3;
		wxTextCtrl* m_txtCtrlCurIllu;
		wxTextCtrl* m_txtCtrlSpIllu1;
		wxTextCtrl* m_txtCtrlSpIllu2;
		wxTextCtrl* m_txtCtrlSpIllu3;
		wxTextCtrl* m_txtCtrlCurColor;
		wxTextCtrl* m_txtCtrlSpColor1;
		wxTextCtrl* m_txtCtrlSpColor2;
		wxTextCtrl* m_txtCtrlSpColor3;
		wxChoice* m_chCurPintype;
		wxChoice* m_chSpPintype1;
		wxChoice* m_chSpPintype2;
		wxChoice* m_chSpPintype3;
		wxTextCtrl* m_txtCtrlCurPinNo;
		wxTextCtrl* m_txtCtrlSpPinNo1;
		wxTextCtrl* m_txtCtrlSpPinNo2;
		wxTextCtrl* m_txtCtrlSpPinNo3;
		wxChoice* m_chCurPinValue;
		wxChoice* m_choiceSpPinValue1;
		wxChoice* m_choiceSpPinValue2;
		wxChoice* m_choiceSpPinValue3;
		wxChoice* m_chCurDefPinValue;
		wxChoice* m_chSpDefPinValue1;
		wxChoice* m_chSpDefPinValue2;
		wxChoice* m_chSpDefPinValue3;
		wxTextCtrl* m_txtCtrlTolNm;
		wxTextCtrl* m_txtCtrlSpTolNm1;
		wxTextCtrl* m_txtCtrlSpTolNm2;
		wxTextCtrl* m_txtCtrlSpTolNm3;
		wxTextCtrl* m_txtCtrlTolSat;
		wxTextCtrl* m_txtCtrlSpTolSat1;
		wxTextCtrl* m_txtCtrlSpTolSat2;
		wxTextCtrl* m_txtCtrlSpTolSat3;
		wxTextCtrl* m_txtCtrlTolIllu;
		wxTextCtrl* m_txtCtrlSpTolIllu1;
		wxTextCtrl* m_txtCtrlSpTolIllu2;
		wxTextCtrl* m_txtCtrlSpTolIllu3;

		// Virtual event handlers, overide them in your derived class
		virtual void OnPasteSet1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearSet1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPasteSet2( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearSet2( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPasteSet3( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearSet3( wxCommandEvent& event ) { event.Skip(); }


	public:

		PanelSensor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 832,150 ), long style = wxTAB_TRAVERSAL, int sensornumber = 0 );
		~PanelSensor();
        wxTextCtrl* GetSensorNumber(){return m_txtCtrlSensorNo;};

};


///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		enum
		{
			wxID_MENUBAR = 1000,
			wxID_MENUSAVE,
			wxID_MENUOPEN,
			wxID_TOLERANCES,
			wxID_NETX,
			wxID_QUICKGUIDE,
			wxID_BPCOCO,
			wxID_SCAN,
			wxID_CONNECT,
			wxID_DISCONNECT,
			wxID_GENERATE,
			wxID_USE,
			wxID_START,
			wxID_MYTEXT,
			idStatusBar
		};

		wxMenuBar* menuBarMain;
		wxMenu* mMenuFile;
		wxMenu* mMenuView;
		wxMenu* mMenuSettings;
		wxMenu* mMenuHelp;
		wxMenuItem* menuItem_about;
		wxStaticBitmap* m_bpCoco;
		wxButton* m_buttonScan;
		wxDataViewListCtrl* m_dataViewListSerials;
		wxDataViewColumn* m_dataViewListColumnNo;
		wxDataViewColumn* m_dataViewListColumnSerial;
		wxBitmapButton* m_bpButtonUp;
		wxBitmapButton* m_bpButtonDown;
		wxButton* m_buttonConnect;
		wxButton* m_buttonDisconnect;
		wxStaticText* m_stNumbConnected;
		wxTextCtrl* m_textCtrlConnected;
		wxStaticText* m_stHilscher;
		wxButton* m_buttonGenerate;
		wxButton* m_buttonUseTestfile;
		wxButton* m_buttonStart;
		wxNotebook* m_nbData;
		wxScrolledWindow* m_swColors;
		wxDataViewListCtrl* m_dvlColors;
		wxDataViewColumn* m_cSensorNo;
		wxDataViewColumn* m_cWavelength;
		wxDataViewColumn* m_cSaturation;
		wxDataViewColumn* m_cIllumination;
		wxDataViewColumn* m_cColor;
		wxDataViewColumn* m_cGain;
		wxDataViewColumn* m_cIntegration;
		wxDataViewColumn* m_cExceededClear;
		wxDataViewChoiceRenderer* m_dvcrGain;
		wxDataViewChoiceRenderer* m_dvcrInt;
		wxScrolledWindow* m_swTestdefinition;
		wxScrolledWindow* m_swLog;
		wxTextCtrl* m_text;
		wxStatusBar* statusBar;
		wxLog* m_pOldLogTarget;
        wxRadioButton* m_rbSingle;
        wxRadioButton* m_rbContinuous;
        wxChoice* m_chTime;
        PanelHeader* m_panelHeader;

		// Virtual event handlers, overide them in your derived class
		virtual void OnScan( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSerialUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSerialDown( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisconnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUseTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ColorControl"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 927,792 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUIFrame();

};




#endif //__GUIFRAME_H__
