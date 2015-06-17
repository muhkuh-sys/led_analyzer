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
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/msgdlg.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_MENUBAR 1000
#define wxID_MENUSAVE 1001
#define wxID_MENUOPEN 1002
#define wxID_QUICKGUIDE 1003
#define wxID_SCAN 1004
#define wxID_CONNECT 1005
#define wxID_START 1006
#define wxID_Data 1007
#define wxID_GENERATETEST 1008
#define wxID_USETEST 1009
#define wxID_SENDALL 1010
#define idStatusBar 1011

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* menuBarMain;
		wxMenu* mMenuFile;
		wxMenu* mMenuView;
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
		wxRadioBox* m_rbTestmode;
		wxButton* m_buttonStart;
		wxPanel* m_panelData;
		wxPanel* m_panelSettings;
		wxStaticBitmap* m_bpCIE;
		wxNotebook* m_nbTest;
		wxPanel* m_panelDefineTest;
		wxStaticText* m_stWavelength;
		wxTextCtrl* m_txtCtrlWavelength;
		wxStaticText* m_stSaturation;
		wxTextCtrl* m_txtCtrlSaturation;
		wxStaticText* m_stIllumination;
		wxTextCtrl* m_txtCtrlIllumination;
		wxButton* buttonGenerate;
		wxPanel* m_panelUseTest;
		wxStaticText* m_stInputTest;
		wxBitmapButton* m_bpButtonUP;
		wxTextCtrl* m_txtCtrlInputFile;
		wxButton* m_buttonUseTest;
		wxPanel* panelSensorSettings;
		wxChoice* m_choiceGain;
		wxChoice* m_choiceInt;
		wxButton* m_buttonSendAll;
		wxStatusBar* statusBar;

		// Virtual event handlers, overide them in your derived class
		virtual void OnScan( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSerialUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSerialDown( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUseTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSendAll( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ColorControl"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1020,700 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUIFrame();

};

#endif //__GUIFRAME_H__
