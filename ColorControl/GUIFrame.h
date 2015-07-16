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
#include <wx/timer.h>
#include <wx/fileconf.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/textfile.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/tooltip.h>

#include "logo_hilscher.xpm"



#define COLOR_WARNING{210, 150, 0  }
#define COLOR_ERROR  {200, 0  , 0  }
#define COLOR_OK     {0,   200, 0  }

/* Macros for Log color */
#define LOG_WARNING(pText) pText->SetDefaultStyle(wxTextAttr(COLOR_WARNING))
#define LOG_ERROR(pText) pText->SetDefaultStyle(wxTextAttr(COLOR_ERROR))
#define LOG_SUCCESSFUL(pText) pText->SetDefaultStyle(wxTextAttr(COLOR_OK))
#define LOG_DEFAULT(pText) pText->SetDefaultStyle(wxTextAttr(*wxBLACK))

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

/// Class Chromaticity Frame

class FrameChromaticity : public wxFrame
{
private:
    wxStaticBitmap* m_bmChromaticity;

public:
    FrameChromaticity (wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize)
            : wxFrame(parent, id, title, pos, size, wxCLOSE_BOX | wxMINIMIZE_BOX | wxCLIP_CHILDREN | wxCAPTION )
        {
            this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );

            wxBoxSizer* bSizer;
            bSizer = new wxBoxSizer(wxVERTICAL),

            m_bmChromaticity = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("pic\\CIE1931.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
            bSizer->Add(m_bmChromaticity, 0, wxALL, 5);

            this->SetSizer(bSizer);
            this->Layout();
            bSizer->Fit(this);
        }

        ~FrameChromaticity(){if(m_bmChromaticity != NULL) delete m_bmChromaticity; };
};



// ----------------------------------------------------------------------------
// MyCustomChoiceRenderer for gain and integration time
// ----------------------------------------------------------------------------

class MyCustomChoiceRenderer: public wxDataViewChoiceRenderer
{
public:
        MyCustomChoiceRenderer(wxArrayString astrChoices)
            : wxDataViewChoiceRenderer(astrChoices,
                                       wxDATAVIEW_CELL_EDITABLE, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT
                                       )
        { }

        virtual wxString GetChoice(size_t WXUNUSED(index))
        {

        }


};


/*
class MyDataViewListModel: public wxDataViewModel
{
    public:
        MyDataViewListModel();

        ~MyDataViewListModel();

    virtual unsigned int GetColumnCount() const;

    virtual wxString GetColumnType( unsigned int col ) const;

    virtual void GetValueByRow( wxVariant &variant,
                                unsigned int row, unsigned int col ) const;
    virtual bool GetAttrByRow( unsigned int row, unsigned int col,
                               wxDataViewItemAttr &attr ) const;
    virtual bool SetValueByRow( const wxVariant &variant,
                                unsigned int row, unsigned int col );

    virtual unsigned int GetRow(const wxDataViewItem& children) const ;

    virtual unsigned int GetCount() const;

    virtual unsigned int GetChildren( const wxDataViewItem& item, wxDataViewItemArray& children) const;

    private:
        int m_test;
};
*/



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
			wxID_TESTMODE,
			wxID_TIMER,
			wxID_COLORS,
			wxID_USENETX,
			idStatusBar
		};

        wxTimer* m_pTimer;
        wxFileConfig* m_fileConfig;
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
		wxButton* m_buttonStimulation;
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
		wxDataViewColumn* m_cSensorState;
		MyCustomChoiceRenderer* m_mccrGain;
		MyCustomChoiceRenderer* m_mccrInt;
		wxScrolledWindow* m_swTestdefinition;
		wxScrolledWindow* m_swLog;
		wxTextCtrl* m_text;
		wxStatusBar* statusBar;
		wxLog* m_pOldLogTarget;
		wxCheckBox*    m_chUsenetx;
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
		virtual void OnStimulation ( wxCommandEvent& event) { event.Skip(); };
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTestmode (wxCommandEvent& event ) { event.Skip(); };
        virtual void OnTimeout( wxTimerEvent& event ) { event.Skip(); };
        virtual void OnShowLog( wxCommandEvent& event ) { event.Skip(); };
        virtual void OnHideLog( wxCommandEvent& event ) { event.Skip(); };
        virtual void OnClearLog( wxCommandEvent& event ) { event.Skip(); };
        virtual void OnShowChromaticity( wxCommandEvent& event ) { event.Skip(); };
        virtual void OnSensorSettingsChanged( wxDataViewEvent& event) {event.Skip(); };
        virtual void OnSystemSettings( wxCommandEvent& event) {event.Skip(); };
        virtual void OnSaveSession( wxCommandEvent & event ) { event.Skip(); };
        virtual void OnOpenSession( wxCommandEvent & event ) { event.Skip(); };
	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ColorControl"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 927,792 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUIFrame();

};


///////////////////////////////////////////////////////////////////////////////
/// Class DialogPropGrid
///////////////////////////////////////////////////////////////////////////////
class DialogPropGrid : public wxDialog
{
	private:
		wxPropertyGrid* m_propGrid;
		wxPGProperty* m_pgiTolnm;
		wxPGProperty* m_pgiTolsat;
		wxPGProperty* m_pgiTolillu;
		wxPGProperty* m_pgiNetxtype;
        wxButton* m_buttonSave;
		wxButton* m_buttonCancel;
		wxArrayString m_astrNetxTypes;
		wxFileConfig* m_pFileConfig;

		void OnSave( wxCommandEvent& event );
		void OnCancel( wxCommandEvent& event );

	protected:

	public:

		DialogPropGrid( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE, wxFileConfig* pFileConfig = NULL );
		~DialogPropGrid();

};

#endif //__GUIFRAME_H__
