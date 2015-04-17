

#ifndef __MAIN_H__
#define __MAIN_H__

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
#include <wx/combobox.h>
#include <wx/tglbtn.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/choice.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* menuBar_main;
		wxMenu* menuFile;
		wxMenu* menuView;
		wxMenu* menuHelp;
		wxNotebook* mainNotebook;
		wxPanel* panelTestdefinition;
		wxStaticBitmap* m_bitmap511;
		wxButton* buttonScan1;
		wxDataViewListCtrl* m_dataViewListCtrl21;
		wxDataViewColumn* m_dataViewListColumn31;
		wxDataViewColumn* m_dataViewListColumn41;
		wxBitmapButton* m_bpButton21;
		wxBitmapButton* m_bpButton31;
		wxButton* buttonConnect1;
		wxStaticText* st_numb1;
		wxTextCtrl* m_textCtrl21;
		wxStaticText* m_staticText7;
		wxRadioBox* m_radioBox11;
		wxComboBox* m_comboBox11;
		wxStaticText* m_staticText21;
		wxToggleButton* m_toggleBtn2;
		wxToggleButton* m_toggleBtn21;
		wxNotebook* m_notebook21;
		wxPanel* panelWavelength1;
		wxPanel* panelSettings1;
		wxPanel* panelTolerance;
		wxPanel* panelCollapsable;
		wxStaticBitmap* m_bitmap41;
		wxChoice* m_choice61;
		wxChoice* m_choice71;
		wxButton* butonQuickset1;
		wxTextCtrl* m_textCtrl17;
		wxStaticText* m_staticText211;
		wxTextCtrl* m_textCtrl18;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textCtrl19;
		wxStaticText* m_staticText23;
		wxTextCtrl* m_textCtrl20;
		wxStaticText* m_staticText24;
		wxButton* buttonTolset;
		wxButton* m_button38;
		wxButton* buttonGenerate;
		wxStatusBar* statusBar_main;
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,730 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrame();
	
};

#endif //__MAIN_H__
