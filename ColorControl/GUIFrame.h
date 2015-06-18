///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

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
#include <wx/radiobox.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include <wx/msgdlg.h>
///////////////////////////////////////////////////////////////////////////

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
			wxID_SENSORS,
			wxID_NETX,
			wxID_QUICKGUIDE,
			wxID_BPCOCO,
			wxID_SCAN,
			wxID_CONNECT,
			wxID_MODE,
			wxID_GENERATE,
			wxID_USE,
			wxID_START,
			wxID_SCROLLEDPANEL,
			wxID_MYTEXT,
			idStatusBar
		};

		wxMenuBar* menuBarMain;
		wxMenu* mMenuFile;
		wxMenu* mMenuView;
		wxMenu* mMenuSettings;
		wxMenu* mMenuHelp;
		wxStaticBitmap* m_bpCoco;
		wxButton* m_buttonScan;
		wxDataViewListCtrl* m_dataViewListSerials;
		wxDataViewColumn* m_dataViewListColumnNo;
		wxDataViewColumn* m_dataViewListColumnSerial;
		wxBitmapButton* m_bpButtonUp;
		wxBitmapButton* m_bpButtonDown;
		wxButton* m_buttonConnect;
		wxStaticText* m_stNumbConnected;
		wxTextCtrl* m_textCtrlConnected;
		wxStaticText* m_stHilscher;
		wxRadioBox* m_rbHWType;
		wxButton* m_buttonGenerate;
		wxButton* m_buttonUseTestfile;
		wxButton* m_buttonStart;
		wxScrolledWindow* m_swData;
		wxPanel* m_panelLog;
		wxTextCtrl* m_text;
		wxStatusBar* statusBar;


		// Virtual event handlers, overide them in your derived class
		virtual void OnScan( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSerialUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSerialDown( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUseTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStart( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ColorControl"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 650,792 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUIFrame();

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
		wxStaticBitmap* m_bmSet1;
		wxStaticBitmap* m_bmClear1;
		wxCheckBox* m_cbUseSet11;
		wxStaticBitmap* m_bmSet11;
		wxStaticBitmap* m_bmClear11;
		wxCheckBox* m_cbUseSet12;
		wxStaticBitmap* m_bmSet12;
		wxStaticBitmap* m_bmClear12;
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

	public:

		PanelSensor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~PanelSensor();

};

#endif //__GUIFRAME_H__
