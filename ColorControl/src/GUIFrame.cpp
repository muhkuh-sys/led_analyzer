///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
//#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"


// ----------------------------------------------------------------------------
// MyCustomRenderer for Colours in wxDataViewListCtrl
// ----------------------------------------------------------------------------

class MyCustomRenderer: public wxDataViewCustomRenderer
{
public:
    MyCustomRenderer()
        : wxDataViewCustomRenderer("",
                                   wxDATAVIEW_CELL_ACTIVATABLE,
                                   wxALIGN_CENTER)
       { }

    virtual bool Render( wxRect rect, wxDC *dc, int state )
    {
        unsigned char r, g, b;
        r = wxAtoi(m_value.SubString(0,2));
        g = wxAtoi(m_value.SubString(3,5));
        b = wxAtoi(m_value.SubString(6,8));

        wxColour colour(r,g,b);

        dc->SetBrush( wxBrush(colour) );

        dc->DrawRoundedRectangle( rect, 5 );

        return true;
    }

    virtual wxSize GetSize() const
    {
        return wxSize(80,20);
    }

    virtual bool SetValue( const wxVariant &value )
    {
        m_value = value.GetString();
        return true;
    }

    virtual bool GetValue( wxVariant &WXUNUSED(value) ) const { return true; }

private:
    wxString m_value;
};


///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOTEXT ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );


	menuBarMain = new wxMenuBar( 0 );
	mMenuFile = new wxMenu();
	wxMenuItem* menuItem_save;
	menuItem_save = new wxMenuItem( mMenuFile, wxID_MENUSAVE, wxString( wxT("Save Session") ) + wxT('\t') + wxT("CTRL-S"), wxT("Save a session to work on it later"), wxITEM_NORMAL );
	mMenuFile->Append( menuItem_save );

	wxMenuItem* menuItem_open;
	menuItem_open = new wxMenuItem( mMenuFile, wxID_MENUOPEN, wxString( wxT("Open Session") ) + wxT('\t') + wxT("CTRL-O"), wxT("Open a session to continue working on it"), wxITEM_NORMAL );
	mMenuFile->Append( menuItem_open );

	mMenuFile->AppendSeparator();

	wxMenuItem* menuItem_exit;
	menuItem_exit = new wxMenuItem( mMenuFile, wxID_EXIT, wxString( wxT("Exit") ) + wxT('\t') + wxT("CTRL-Q"), wxT("Close app ..."), wxITEM_NORMAL );
	mMenuFile->Append( menuItem_exit );

	menuBarMain->Append( mMenuFile, wxT("File") );

	mMenuView = new wxMenu();
	wxMenuItem* menuItem_showLog;
	menuItem_showLog = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Show Log") ) + wxT('\t') + wxT("CTRL-L"), wxT("Show extended output"), wxITEM_NORMAL );
	mMenuView->Append( menuItem_showLog );

	wxMenuItem* menuItem_clearLog;
	menuItem_clearLog = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Clear Log") ) + wxT('\t') + wxT("CTRL-P"), wxT("Flush output"), wxITEM_NORMAL );
	mMenuView->Append( menuItem_clearLog );

	wxMenuItem* menuItem_hideLog;
	menuItem_hideLog = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Hide Log") ) + wxT('\t') + wxT("CTRL-H"), wxT("Hide extended output"), wxITEM_NORMAL );
	mMenuView->Append( menuItem_hideLog );

	mMenuView->AppendSeparator();

	wxMenuItem* menuDiagram;
	menuDiagram = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Show Chromaticity Diagram") ) + wxT('\t') + wxT("CTRL-E"), wxT("Show CIE 1931 chromaticity diagram"), wxITEM_NORMAL );
	mMenuView->Append( menuDiagram );

	menuBarMain->Append( mMenuView, wxT("View") );

	mMenuSettings = new wxMenu();
	wxMenuItem* menuItem_SystemSettings;
	menuItem_SystemSettings = new wxMenuItem( mMenuSettings, wxID_TOLERANCES, wxString( wxT("System Settings") ) , wxT("Change default tolerances and netX type"), wxITEM_NORMAL );
	mMenuSettings->Append( menuItem_SystemSettings );

	menuBarMain->Append( mMenuSettings, wxT("Settings") );

	mMenuHelp = new wxMenu();
	wxMenuItem* menuItem_quickGuide;
	menuItem_quickGuide = new wxMenuItem( mMenuHelp, wxID_QUICKGUIDE, wxString( wxT("Quick Guide") ) + wxT('\t') + wxT("F1"), wxT("Open a quick tutorial for this app"), wxITEM_NORMAL );
	mMenuHelp->Append( menuItem_quickGuide );

	menuItem_about = new wxMenuItem( mMenuHelp, wxID_ABOUT, wxString( wxT("About") ) + wxT('\t') + wxT("F2"), wxT("About this app"), wxITEM_NORMAL );
	mMenuHelp->Append( menuItem_about );

	menuBarMain->Append( mMenuHelp, wxT("Help") );

	this->SetMenuBar( menuBarMain );

	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerMainTop;
	bSizerMainTop = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerHW;
	bSizerHW = new wxBoxSizer( wxVERTICAL );


	bSizerHW->SetMinSize( wxSize( -1,-1 ) );
	m_bpCoco = new wxStaticBitmap( this, wxID_BPCOCO, wxBitmap( logo_hilscher_xpm , wxBITMAP_TYPE_XPM) , wxDefaultPosition, wxSize( 123,90 ), 0 );
	bSizerHW->Add( m_bpCoco, 0, wxALIGN_CENTER|wxALL|wxTOP, 9 );


	wxStaticBoxSizer* bSizerCommunication;
	bSizerCommunication = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Communication") ), wxVERTICAL );

	m_buttonScan = new wxButton( this, wxID_SCAN, wxT("&SCAN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerCommunication->Add( m_buttonScan, 0, wxEXPAND | wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_dataViewListSerials = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_HORIZ_RULES | wxDV_VERT_RULES );
	m_dataViewListSerials->SetMinSize( wxSize( -1,120 ) );

	m_dataViewListColumnNo = m_dataViewListSerials->AppendTextColumn( wxT("No."), wxDATAVIEW_CELL_INERT, 40, wxALIGN_CENTER);
	m_dataViewListColumnSerial = m_dataViewListSerials->AppendTextColumn( wxT("Serial"), wxDATAVIEW_CELL_INERT, 110 );
	bSizerCommunication->Add( m_dataViewListSerials, 2, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizerUpDown;
	bSizerUpDown = new wxBoxSizer( wxHORIZONTAL );

	m_bpButtonDown = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_DOWN  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerUpDown->Add( m_bpButtonDown, 1, wxALIGN_LEFT|wxALL, 5 );

	m_bpButtonUp = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_UP  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerUpDown->Add( m_bpButtonUp, 1, wxALIGN_RIGHT|wxALL, 5 );


	bSizerCommunication->Add( bSizerUpDown, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );


	bSizerCommunication->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonConnect   = new wxButton( this, wxID_CONNECT, wxT("&CONNECT"), wxDefaultPosition, wxDefaultSize, 0 );
    m_buttonDisconnect = new wxButton( this, wxID_DISCONNECT, wxT("&DISCONNECT"), wxDefaultPosition, wxDefaultSize, 0 );

	bSizerCommunication->Add( m_buttonConnect, 0, wxEXPAND | wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	bSizerCommunication->Add( m_buttonDisconnect, 0, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxBoxSizer* bSizerConnected;
	bSizerConnected = new wxBoxSizer( wxHORIZONTAL );

	m_stNumbConnected = new wxStaticText( this, wxID_ANY, wxT("Connected: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_stNumbConnected->Wrap( -1 );
	bSizerConnected->Add( m_stNumbConnected, 0, wxALL|wxEXPAND, 5 );

	m_textCtrlConnected = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 30,20 ), wxTE_CENTER | wxTE_READONLY );
	m_textCtrlConnected->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_textCtrlConnected->SetMaxSize( wxSize( 30,30 ) );

	bSizerConnected->Add( m_textCtrlConnected, 0, wxALL, 5 );


	bSizerCommunication->Add( bSizerConnected, 1, wxALL|wxEXPAND, 10 );


	bSizerHW->Add( bSizerCommunication, 1, wxBOTTOM|wxLEFT|wxRIGHT, 5 );


	bSizerHW->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerHilscher;
	bSizerHilscher = new wxBoxSizer( wxVERTICAL );


	bSizerHilscher->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stHilscher = new wxStaticText( this, wxID_ANY, wxT("Color Control v 0.0\n ©Copyright 2015\n   Hilscher GmbH"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stHilscher->Wrap( -1 );
	bSizerHilscher->Add( m_stHilscher, 1, wxALIGN_CENTER, 5 );


	bSizerHilscher->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizerHW->Add( bSizerHilscher, 0, wxALIGN_CENTER|wxEXPAND, 5 );


	bSizerMainTop->Add( bSizerHW, 0, wxBOTTOM|wxEXPAND|wxLEFT, 5 );

	wxBoxSizer* bSizerData;
	bSizerData = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizerTestfile;
	sbSizerTestfile = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Testfile") ), wxVERTICAL );

	m_buttonGenerate = new wxButton( this, wxID_GENERATE, wxT("Generate Tesfile"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTestfile->Add( m_buttonGenerate, 0, wxALL, 5 );

	m_buttonUseTestfile = new wxButton( this, wxID_USE, wxT("Use Testfile"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTestfile->Add( m_buttonUseTestfile, 0, wxALL|wxEXPAND, 5 );

    wxStaticBoxSizer* sbSizerTestmode;
    sbSizerTestmode = new wxStaticBoxSizer ( new wxStaticBox(this, wxID_ANY, wxT("Testmode" )  ), wxHORIZONTAL);

    wxBoxSizer* bSizerSingleCont;
    bSizerSingleCont = new wxBoxSizer(wxVERTICAL);


    m_chUsenetx = new wxCheckBox( this, wxID_USENETX, wxT("Use netX"), wxDefaultPosition, wxDefaultSize, 0);
    m_chUsenetx->SetValue(true);
    bSizerSingleCont->Add(m_chUsenetx, 0, wxALL, 5);


	m_rbSingle = new wxRadioButton( this, wxID_TESTMODE, wxT("Single"), wxDefaultPosition, wxDefaultSize, 0 );
	m_rbSingle->SetValue(true);
    bSizerSingleCont->Add(m_rbSingle, 0, wxALL, 5);

	m_rbContinuous = new wxRadioButton( this, wxID_TESTMODE, wxT("Continuous"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizerSingleCont->Add(m_rbContinuous, 0, wxALL, 5);


    sbSizerTestmode->Add(bSizerSingleCont);

    wxString m_chTimeChoices[] = { wxT("0.2 sec"), wxT("0.5 sec"), wxT("1 sec"), wxT("2 sec"), wxT("5 sec")};
	int m_chTimeNChoices = sizeof( m_chTimeChoices ) / sizeof( wxString );
	m_chTime = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chTimeNChoices, m_chTimeChoices, 0 );
	m_chTime->SetSelection( 0 );
	sbSizerTestmode->Add( m_chTime, 0, wxALL | wxALIGN_BOTTOM, 2 );

	wxStaticBoxSizer* sbSizerFastSetup;
	sbSizerFastSetup = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Fast Setup") ), wxVERTICAL );

	wxString m_chGainChoices[] = { wxT("GAIN_1X"), wxT("GAIN_4X"), wxT("GAIN_16X"), wxT("GAIN_60X") };
	int m_chGainNChoices = sizeof( m_chGainChoices ) / sizeof( wxString );
	m_chGain = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chGainNChoices, m_chGainChoices, 0 );
	m_chGain->SetSelection( 0 );
	sbSizerFastSetup->Add( m_chGain, 0, wxALL|wxEXPAND, 6 );

	wxString m_chIntTimeChoices[] = { wxT("TIME_2_4ms"), wxT("TIME_24ms"), wxT("TIME_100ms"), wxT("TIME_154ms"), wxT("TIME_200ms"), wxT("TIME_700ms") };
	int m_chIntTimeNChoices = sizeof( m_chIntTimeChoices ) / sizeof( wxString );
	m_chIntTime = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chIntTimeNChoices, m_chIntTimeChoices, 0 );
	m_chIntTime->SetSelection( 0 );
	sbSizerFastSetup->Add( m_chIntTime, 0, wxALL|wxEXPAND, 6 );


	bSizerButtons->Add(sbSizerTestfile, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
    bSizerButtons->Add(sbSizerFastSetup, 0, wxALL|wxEXPAND, 5 );
    bSizerButtons->Add(sbSizerTestmode, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);


	bSizerButtons->Add( 0, 0, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizerStartStimulate;
    bSizerStartStimulate = new wxBoxSizer(wxVERTICAL);

    m_buttonStart = new wxButton( this, wxID_START, wxT("S&TART"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStartStimulate->Add( m_buttonStart, 1, wxALIGN_CENTER|wxBOTTOM|wxRIGHT|wxTOP|wxEXPAND, 5 );

	m_buttonStimulation = new wxButton( this, wxID_START, wxT("Stimulate LEDs"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStartStimulate->Add( m_buttonStimulation, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5 );

	bSizerButtons->Add( bSizerStartStimulate, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerData->Add( bSizerButtons, 0, wxEXPAND, 5 );

	m_nbData = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_swColors = new wxScrolledWindow( m_nbData, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_swColors->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizerColors;
	bSizerColors = new wxBoxSizer( wxVERTICAL );

	m_dvlColors = new wxDataViewListCtrl( m_swColors, wxID_COLORS, wxDefaultPosition, wxDefaultSize, wxDV_HORIZ_RULES | wxDV_VERT_RULES );

	m_cSensorNo = m_dvlColors->AppendTextColumn( wxT("Sensor"), wxDATAVIEW_CELL_INERT, 50, wxALIGN_CENTER );
	m_cWavelength = m_dvlColors->AppendTextColumn( wxT("Wavelength"), wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER );
	m_cSaturation = m_dvlColors->AppendTextColumn( wxT("Saturation"), wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER );
	m_cIllumination = m_dvlColors->AppendTextColumn( wxT("Illumination"), wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER );

    m_cColor = new wxDataViewColumn("Color", new MyCustomRenderer, 4, wxDVC_DEFAULT_WIDTH, wxALIGN_CENTER, 0);
    m_dvlColors->AppendColumn(m_cColor);

    m_cExceededClear = m_dvlColors->AppendProgressColumn( wxT("Clear Level"), wxDATAVIEW_CELL_INERT, 100, wxALIGN_CENTER);


    wxArrayString astrGainchoices;
    astrGainchoices.Add("GAIN_1X");
    astrGainchoices.Add("GAIN_4X");
    astrGainchoices.Add("GAIN_16X");
    astrGainchoices.Add("GAIN_60X");

    wxArrayString astrIntchoices;
    astrIntchoices.Add("TIME_2_4ms");
    astrIntchoices.Add("TIME_24ms");
    astrIntchoices.Add("TIME_100ms");
    astrIntchoices.Add("TIME_154ms");
    astrIntchoices.Add("TIME_200ms");
    astrIntchoices.Add("TIME_700ms");

    m_mccrGain = new MyCustomChoiceRenderer(astrGainchoices);
    m_mccrInt  = new MyCustomChoiceRenderer(astrIntchoices);

	m_cGain = new wxDataViewColumn(wxT("Gain"), m_mccrGain, 6, wxDVC_DEFAULT_WIDTH, wxALIGN_CENTER, wxDATAVIEW_COL_RESIZABLE);
	m_cIntegration = new wxDataViewColumn(wxT("Integration Time"), m_mccrInt, 7, wxDVC_DEFAULT_WIDTH, wxALIGN_CENTER, wxDATAVIEW_COL_RESIZABLE);
    m_dvlColors->AppendColumn(m_cGain);
    m_dvlColors->AppendColumn(m_cIntegration);

   	m_cSensorState = m_dvlColors->AppendTextColumn( wxT("Status"), wxDATAVIEW_CELL_INERT, 100, wxALIGN_CENTER );



	bSizerColors->Add( m_dvlColors, 1, wxEXPAND, 5 );


	m_swColors->SetSizer( bSizerColors );
	m_swColors->Layout();
	bSizerColors->Fit( m_swColors );
	m_nbData->AddPage( m_swColors, wxT("Colors"), true );
	m_swTestdefinition = new wxScrolledWindow( m_nbData, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_swTestdefinition->SetScrollRate( 5, 20 );
	m_swTestdefinition->SetBackgroundColour ( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW));


	m_nbData->AddPage( m_swTestdefinition, wxT("Testdefinition"), false );

	bSizerData->Add( m_nbData, 1, wxEXPAND | wxALL, 5 );


	bSizerMainTop->Add( bSizerData, 1, wxEXPAND, 5 );


	bSizerMain->Add( bSizerMainTop, 1, wxEXPAND, 5 );

	m_swLog = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL );
	wxBoxSizer* bSizerLog;
	bSizerLog = new wxBoxSizer( wxVERTICAL );

	m_text = new wxTextCtrl( m_swLog, wxID_MYTEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH );
	m_text->SetMinSize( wxSize( -1,90 ) );

    m_pOldLogTarget = new wxLogTextCtrl(m_text);

	bSizerLog->Add( m_text, 0, wxEXPAND, 5 );


	m_swLog->SetSizer( bSizerLog );
	m_swLog->Layout();
	bSizerLog->Fit( m_swLog );
	bSizerMain->Add( m_swLog, 0, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, idStatusBar );

	this->Centre( wxBOTH );


    /* Accelerators */
    wxAcceleratorEntry entries[4];
    entries[0].Set(wxACCEL_ALT, (int) 'S', wxID_SCAN);
    entries[1].Set(wxACCEL_ALT, (int) 'C', wxID_CONNECT);
    entries[2].Set(wxACCEL_ALT, (int) 'D', wxID_DISCONNECT);
    entries[3].Set(wxACCEL_ALT, (int) 'T', wxID_START);

    wxAcceleratorTable accel(4, entries);
    this->SetAcceleratorTable(accel);

	// Connect Events
	m_buttonScan->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnScan ), NULL, this );
	m_bpButtonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialUp ), NULL, this );
	m_bpButtonDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialDown ), NULL, this );
	m_buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnConnect ), NULL, this );
    m_buttonDisconnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnDisconnect ), NULL, this );
	m_buttonGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnGenerateTest ), NULL, this );
	m_buttonUseTestfile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnUseTest ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnStart ), NULL, this );
	m_buttonStimulation->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler ( GUIFrame::OnStimulation ), NULL, this );
	this->Connect( m_chGain->GetId(), wxEVT_CHOICE, wxCommandEventHandler ( GUIFrame::OnFastGain ), NULL, this );
	this->Connect( m_chIntTime->GetId(), wxEVT_CHOICE, wxCommandEventHandler ( GUIFrame::OnFastIntTime), NULL, this );
	this->Connect( menuItem_about->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	this->Connect( menuItem_quickGuide->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuickGuide ) );
    this->Connect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
    this->Connect( wxID_TESTMODE, wxEVT_RADIOBUTTON, wxCommandEventHandler( GUIFrame::OnTestmode ) );
    this->Connect( wxID_TIMER, wxEVT_TIMER, wxTimerEventHandler ( GUIFrame::OnTimeout ) );
    this->Connect( menuItem_showLog->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( GUIFrame::OnShowLog ) );
    this->Connect( menuItem_hideLog->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( GUIFrame::OnHideLog ) );
    this->Connect( menuItem_clearLog->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( GUIFrame::OnClearLog ) );
    this->Connect( menuDiagram->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler (GUIFrame::OnShowChromaticity ) );
    this->Connect( m_dvlColors->GetId(), wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, wxDataViewEventHandler (GUIFrame::OnSensorSettingsChanged ) );
    this->Connect( menuItem_SystemSettings->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler (GUIFrame::OnSystemSettings ) );
    this->Connect(menuItem_save->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveSession ) );
    this->Connect(menuItem_open->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpenSession ) );
    this->Connect(m_chUsenetx->GetId(), wxEVT_CHECKBOX , wxCommandEventHandler ( GUIFrame::OnUseNetX ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	m_buttonScan->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnScan ), NULL, this );
	m_bpButtonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialUp ), NULL, this );
	m_bpButtonDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialDown ), NULL, this );
	m_buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnConnect ), NULL, this );
    m_buttonDisconnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnDisconnect ), NULL, this );
	m_buttonGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnGenerateTest ), NULL, this );
	m_buttonUseTestfile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnUseTest ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnStart ), NULL, this );
	m_buttonStimulation->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnStimulation ), NULL, this );

    this->Disconnect( wxEVT_RADIOBUTTON, wxCommandEventHandler( GUIFrame::OnTestmode ), NULL, this );
    this->Disconnect( wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), NULL, this );
    this->Disconnect( wxEVT_TIMER, wxTimerEventHandler (GUIFrame::OnTimeout ), NULL, this );
    this->Disconnect( wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnShowLog ), NULL, this);
    this->Disconnect( wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnClearLog ), NULL, this);
    this->Disconnect( wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnShowChromaticity ), NULL, this);
    this->Disconnect( wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, wxDataViewEventHandler ( GUIFrame::OnSensorSettingsChanged ), NULL, this);


}

PanelHeader::PanelHeader( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, bool useNetX ) : wxPanel( parent, id, pos, size, style )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );

	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxHORIZONTAL );

	m_stSensor = new wxStaticText( this, wxID_ANY, wxT("Sensor"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER );
	m_stSensor->SetMinSize(wxSize(80, -1));
	m_stSensor->Wrap( -1 );
	bSizer98->Add( m_stSensor, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stName = new wxStaticText( this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER );
	m_stName->Wrap( -1 );
	bSizer98->Add( m_stName, 0, wxALL, 5 );



	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stWavelength = new wxStaticText( this, wxID_ANY, wxT("Wavelength"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stWavelength->Wrap( -1 );
	bSizer98->Add( m_stWavelength, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stSaturation = new wxStaticText( this, wxID_ANY, wxT("Sat."), wxDefaultPosition, wxDefaultSize, 0 );
	m_stSaturation->Wrap( -1 );
	bSizer98->Add( m_stSaturation, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stIllumination = new wxStaticText( this, wxID_ANY, wxT("Illumin."), wxDefaultPosition, wxDefaultSize, 0 );
	m_stIllumination->Wrap( -1 );
	bSizer98->Add( m_stIllumination, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stColor = new wxStaticText( this, wxID_ANY, wxT("Color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stColor->Wrap( -1 );
	bSizer98->Add( m_stColor, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stPintype = new wxStaticText( this, wxID_ANY, wxT("Pintype"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stPintype->Wrap( -1 );
	bSizer98->Add( m_stPintype, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stPinNo = new wxStaticText( this, wxID_ANY, wxT("Pin #"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stPinNo->Wrap( -1 );
	bSizer98->Add( m_stPinNo, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stPinvalue = new wxStaticText( this, wxID_ANY, wxT("Pinvalue"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stPinvalue->Wrap( -1 );
	bSizer98->Add( m_stPinvalue, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stPinDefValue = new wxStaticText( this, wxID_ANY, wxT("Default"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stPinDefValue->Wrap( -1 );
	bSizer98->Add( m_stPinDefValue, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_tolWl = new wxStaticText( this, wxID_ANY, wxT("+/- nm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tolWl->Wrap( -1 );
	bSizer98->Add( m_tolWl, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_tolSat = new wxStaticText( this, wxID_ANY, wxT("+/- sat"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tolSat->Wrap( -1 );
	bSizer98->Add( m_tolSat, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_tolLux = new wxStaticText( this, wxID_ANY, wxT("+/- lux"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tolLux->Wrap( -1 );
	bSizer98->Add( m_tolLux, 0, wxALL, 5 );


    if(!useNetX)
    {
        m_stPintype->Hide();
        m_stPinNo->Hide();
        m_stPinvalue->Hide();
        m_stPinDefValue->Hide();
    }


	this->SetSizer( bSizer98 );
	this->Layout();
}

void PanelHeader::UpdateHeader(bool useNetX)
{
    if(useNetX)
    {
        m_stPintype->Show();
        m_stPinNo->Show();
        m_stPinvalue->Show();
        m_stPinDefValue->Show();
    }
    else
    {
        m_stPintype->Hide();
        m_stPinNo->Hide();
        m_stPinvalue->Hide();
        m_stPinDefValue->Hide();
    }

    this->Layout();
}

PanelHeader::~PanelHeader()
{
}


///////////////////////////////////////////////////////////////////////////

DialogPropGrid::DialogPropGrid( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, wxFileConfig* pFileConfig) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );


    /* Store the handle of the config file */
    m_pFileConfig = pFileConfig;

    /* Get the settings for default tolerances from the config.ini file */
    long tol_nm, tol_sat, tol_illu;
    wxString strNetX;

    if(!m_pFileConfig->Read("DEFAULT_TOLERANCES/tol_nm", &tol_nm)) tol_nm = 10;
    if(!m_pFileConfig->Read("DEFAULT_TOLERANCES/tol_sat", &tol_sat)) tol_sat = 10;
    if(!m_pFileConfig->Read("DEFAULT_TOLERANCES/tol_illu", &tol_illu)) tol_illu = 50;
    if(!m_pFileConfig->Read("netXType/type", &strNetX )) strNetX = m_astrNetxTypes.Item(0);


	wxBoxSizer* bSizerPropGrid;
	bSizerPropGrid = new wxBoxSizer( wxVERTICAL );

	m_propGrid = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxSize(300,-1), wxPG_DEFAULT_STYLE | wxPG_SPLITTER_AUTO_CENTER);
	m_propGrid->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);

    m_propGrid->Append( new wxPropertyCategory(wxT("Default Tolerances"), wxPG_LABEL) );
	m_pgiTolnm = m_propGrid->Append( new wxIntProperty( wxT("Wavelength +/-"), wxT("tol_nm"), tol_nm ) );
	m_pgiTolnm->SetValidator(wxTextValidator(wxFILTER_DIGITS));
	m_propGrid->SetPropertyHelpString( m_pgiTolnm, wxT("Default tolerance for wavelength (in nm)") );
	m_pgiTolsat = m_propGrid->Append( new wxIntProperty( wxT("Saturation    +/-"), wxT("tol_sat"), tol_sat ) );
	m_pgiTolsat->SetValidator(wxTextValidator(wxFILTER_DIGITS));
	m_propGrid->SetPropertyHelpString( m_pgiTolsat, wxT("Default tolerance for saturation  (in %)") );
	m_pgiTolillu = m_propGrid->Append( new wxIntProperty( wxT("Illumination +/-"), wxT("tol_illu"), tol_illu ) );
	m_pgiTolillu->SetValidator(wxTextValidator(wxFILTER_DIGITS));
	m_propGrid->SetPropertyHelpString( m_pgiTolillu, wxT("Default tolerance for illumination (in Lux)") );
    m_propGrid->Append( new wxPropertyCategory(wxT("Hardware Type"), wxPG_LABEL) );


	m_astrNetxTypes.Add("netX 10");
	m_astrNetxTypes.Add("netX 50");
	m_astrNetxTypes.Add("netX 51/52");
	m_astrNetxTypes.Add("netX 100/500");


	m_pgiNetxtype = m_propGrid->Append( new wxEnumProperty( wxT("netX Type"), wxPG_LABEL, m_astrNetxTypes  ) );
    m_pgiNetxtype->SetValueFromString(strNetX);
	m_propGrid->SetPropertyHelpString( m_pgiNetxtype, wxT("Connected netX type") );
	bSizerPropGrid->Add( m_propGrid, 1, wxEXPAND, 5 );

    bSizerPropGrid->Add(0, 0, 1, wxEXPAND, 5 );

    m_buttonSave = new wxButton( this, wxID_ANY, wxT("Save Settings"), wxDefaultPosition, wxDefaultSize, 0 );
    m_buttonCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);

    bSizerPropGrid->Add(m_buttonSave, 0, wxEXPAND, 0);
    bSizerPropGrid->Add(m_buttonCancel, 0, wxEXPAND, 0);

	this->SetSizer( bSizerPropGrid );
	m_propGrid->FitColumns();
	this->Layout();
    bSizerPropGrid->Fit( this );
	this->Centre( wxBOTH );


	/* Add save and cancel button */

	m_buttonSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogPropGrid::OnSave ), NULL, this);
    m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogPropGrid::OnCancel ), NULL, this);
}

void DialogPropGrid::OnSave( wxCommandEvent& event)
{
    /* Get your values to be saved into the ini file */

    unsigned int tol_nm, tol_sat, tol_illu, iIndex;

    tol_nm  = m_pgiTolnm->GetValue().GetInteger();
    tol_sat = m_pgiTolsat->GetValue().GetInteger();
    tol_illu = m_pgiTolillu->GetValue().GetInteger();
    iIndex = m_pgiNetxtype->GetValue().GetInteger();

    m_pFileConfig->Write("DEFAULT_TOLERANCES/tol_nm", tol_nm);
    m_pFileConfig->Write("DEFAULT_TOLERANCES/tol_sat", tol_sat);
    m_pFileConfig->Write("DEFAULT_TOLERANCES/tol_illu", tol_illu);
    if(iIndex <= m_astrNetxTypes.size())
    m_pFileConfig->Write("netXType/type", m_astrNetxTypes.Item(iIndex));


    wxLogMessage("Saved Settings");
    this->Destroy();

}

void DialogPropGrid::OnCancel( wxCommandEvent& event )
{
   this->Destroy();
}

DialogPropGrid::~DialogPropGrid()
{
    m_buttonSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogPropGrid::OnSave ), NULL, this);
    m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogPropGrid::OnCancel ), NULL, this);
}
