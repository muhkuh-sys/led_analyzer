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
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GuiFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOTEXT ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	menuBarMain = new wxMenuBar( 0 );
	mMenuFile = new wxMenu();
	wxMenuItem* menuItem_save;
	menuItem_save = new wxMenuItem( mMenuFile, wxID_MENUSAVE, wxString( wxT("Save Session") ) + wxT('\t') + wxT("Strg-S"), wxT("Save a session to work on it later"), wxITEM_NORMAL );
	mMenuFile->Append( menuItem_save );

	wxMenuItem* menuItem_open;
	menuItem_open = new wxMenuItem( mMenuFile, wxID_MENUOPEN, wxString( wxT("Open Session") ) + wxT('\t') + wxT("Strg-O"), wxT("Open a session to continue working on it"), wxITEM_NORMAL );
	mMenuFile->Append( menuItem_open );

	mMenuFile->AppendSeparator();

	wxMenuItem* menuItem_exit;
	menuItem_exit = new wxMenuItem( mMenuFile, wxID_EXIT, wxString( wxT("Exit") ) + wxT('\t') + wxT("Strg-Q"), wxT("Close app ..."), wxITEM_NORMAL );
	mMenuFile->Append( menuItem_exit );

	menuBarMain->Append( mMenuFile, wxT("File") );

	mMenuView = new wxMenu();
	wxMenuItem* menuItem_showLog;
	menuItem_showLog = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Show Log") ) + wxT('\t') + wxT("Strg-L"), wxT("Show extended output"), wxITEM_NORMAL );
	mMenuView->Append( menuItem_showLog );

	wxMenuItem* menuItem_clearLog;
	menuItem_clearLog = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Clear Log") ) + wxT('\t') + wxT("Strg-P"), wxT("Flush output"), wxITEM_NORMAL );
	mMenuView->Append( menuItem_clearLog );

	wxMenuItem* menuItem_hideLog;
	menuItem_hideLog = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Hide Log") ) + wxT('\t') + wxT("Strg-H"), wxT("Hide extended output"), wxITEM_NORMAL );
	mMenuView->Append( menuItem_hideLog );

	mMenuView->AppendSeparator();

	wxMenuItem* menuDiagram;
	menuDiagram = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Show Chromaticity Diagram") ) + wxT('\t') + wxT("Strg-R"), wxT("Show CIE 1931 chromaticity curves"), wxITEM_NORMAL );
	mMenuView->Append( menuDiagram );

	menuBarMain->Append( mMenuView, wxT("View") );

	mMenuSettings = new wxMenu();
	wxMenuItem* menuItem_tolerances;
	menuItem_tolerances = new wxMenuItem( mMenuSettings, wxID_TOLERANCES, wxString( wxT("Tolerances") ) , wxEmptyString, wxITEM_NORMAL );
	mMenuSettings->Append( menuItem_tolerances );

	wxMenuItem* menuItem_sensorSettings;
	menuItem_sensorSettings = new wxMenuItem( mMenuSettings, wxID_SENSORS, wxString( wxT("Sensors") ) , wxEmptyString, wxITEM_NORMAL );
	mMenuSettings->Append( menuItem_sensorSettings );

	wxMenuItem* menuItem_netXType;
	menuItem_netXType = new wxMenuItem( mMenuSettings, wxID_NETX, wxString( wxT("netX Type") ) , wxEmptyString, wxITEM_NORMAL );
	mMenuSettings->Append( menuItem_netXType );

	menuBarMain->Append( mMenuSettings, wxT("Settings") );

	mMenuHelp = new wxMenu();
	wxMenuItem* menuItem_quickGuide;
	menuItem_quickGuide = new wxMenuItem( mMenuHelp, wxID_QUICKGUIDE, wxString( wxT("Quick Guide") ) + wxT('\t') + wxT("F1"), wxT("Open a quick tutorial for this app"), wxITEM_NORMAL );
	mMenuHelp->Append( menuItem_quickGuide );

	wxMenuItem* menuItem_about;
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

	bSizerHW->SetMinSize( wxSize( 70,-1 ) );
	m_bpCoco = new wxStaticBitmap( this, wxID_BPCOCO, wxBitmap( wxT("pic/logo_hilscher.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 90,90 ), 0 );
	bSizerHW->Add( m_bpCoco, 0, wxALIGN_CENTER|wxALL|wxTOP, 9 );

	wxStaticBoxSizer* bSizerCommunication;
	bSizerCommunication = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Communication") ), wxVERTICAL );

	m_buttonScan = new wxButton( this, wxID_SCAN, wxT("SCAN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerCommunication->Add( m_buttonScan, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_dataViewListSerials = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_dataViewListSerials->SetMinSize( wxSize( -1,150 ) );

	m_dataViewListColumnNo = m_dataViewListSerials->AppendTextColumn( wxT("No.") );
	m_dataViewListColumnSerial = m_dataViewListSerials->AppendTextColumn( wxT("Serial") );
	bSizerCommunication->Add( m_dataViewListSerials, 2, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizerUpDown;
	bSizerUpDown = new wxBoxSizer( wxHORIZONTAL );

	m_bpButtonUp = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_DOWN ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerUpDown->Add( m_bpButtonUp, 1, wxALIGN_LEFT|wxALL, 5 );

	m_bpButtonDown = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_UP ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerUpDown->Add( m_bpButtonDown, 1, wxALIGN_RIGHT|wxALL, 5 );


	bSizerCommunication->Add( bSizerUpDown, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );


	bSizerCommunication->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonConnect = new wxButton( this, wxID_CONNECT, wxT("CONNECT"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerCommunication->Add( m_buttonConnect, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	wxBoxSizer* bSizerConnected;
	bSizerConnected = new wxBoxSizer( wxHORIZONTAL );

	m_stNumbConnected = new wxStaticText( this, wxID_ANY, wxT("Connected: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_stNumbConnected->Wrap( -1 );
	bSizerConnected->Add( m_stNumbConnected, 0, wxALL|wxEXPAND, 5 );

	m_textCtrlConnected = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 30,20 ), 0 );
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

	wxString m_rbHWTypeChoices[] = { wxT("Measurement"), wxT("Stimulation"), wxT("Both") };
	int m_rbHWTypeNChoices = sizeof( m_rbHWTypeChoices ) / sizeof( wxString );
	m_rbHWType = new wxRadioBox( this, wxID_MODE, wxT("Mode"), wxDefaultPosition, wxDefaultSize, m_rbHWTypeNChoices, m_rbHWTypeChoices, 1, wxRA_SPECIFY_COLS );
	m_rbHWType->SetSelection( 0 );
	bSizerButtons->Add( m_rbHWType, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizerTestfile;
	sbSizerTestfile = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Testfile") ), wxVERTICAL );

	m_buttonGenerate = new wxButton( this, wxID_GENERATE, wxT("Generate Tesfile"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTestfile->Add( m_buttonGenerate, 0, wxALL, 5 );

	m_buttonUseTestfile = new wxButton( this, wxID_USE, wxT("Use Testfile"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTestfile->Add( m_buttonUseTestfile, 0, wxALL|wxEXPAND, 5 );


	bSizerButtons->Add( sbSizerTestfile, 0, wxALL|wxEXPAND, 5 );


	bSizerButtons->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonStart = new wxButton( this, wxID_START, wxT("START"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonStart, 0, wxALIGN_CENTER|wxBOTTOM|wxRIGHT|wxTOP, 5 );


	bSizerData->Add( bSizerButtons, 0, wxEXPAND, 5 );

    wxBoxSizer* bTestSizer;

    PanelSensor* testpanel;
    testpanel = new PanelSensor(this);

    bTestSizer->Add(testpanel, 1, wxEXPAND | wxALL, 5);



	m_swData = new wxScrolledWindow( this, wxID_SCROLLEDPANEL, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_swData->SetScrollRate( 5, 5 );
	bSizerData->Add( m_swData, 1, wxEXPAND | wxALL, 5 );






	bSizerMainTop->Add( bSizerData, 1, wxEXPAND, 5 );


	bSizerMain->Add( bSizerMainTop, 1, wxEXPAND, 5 );

	m_panelLog = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerLog;
	bSizerLog = new wxBoxSizer( wxVERTICAL );

	m_text = new wxTextCtrl( m_panelLog, wxID_MYTEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_text->SetMinSize( wxSize( -1,100 ) );

	bSizerLog->Add( m_text, 0, wxEXPAND, 5 );


	m_panelLog->SetSizer( bSizerLog );
	m_panelLog->Layout();
	bSizerLog->Fit( m_panelLog );
	bSizerMain->Add( m_panelLog, 0, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, idStatusBar );

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonScan->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnScan ), NULL, this );
	m_bpButtonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialUp ), NULL, this );
	m_bpButtonDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialDown ), NULL, this );
	m_buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnConnect ), NULL, this );
	m_buttonGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnGenerateTest ), NULL, this );
	m_buttonUseTestfile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnUseTest ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnStart ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	m_buttonScan->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnScan ), NULL, this );
	m_bpButtonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialUp ), NULL, this );
	m_bpButtonDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialDown ), NULL, this );
	m_buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnConnect ), NULL, this );
	m_buttonGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnGenerateTest ), NULL, this );
	m_buttonUseTestfile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnUseTest ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnStart ), NULL, this );

}

PanelSensor::PanelSensor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	wxBoxSizer* bSizerSensor;
	bSizerSensor = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerNo;
	bSizerNo = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSensorNo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 30,-1 ), 0 );
	bSizerNo->Add( m_txtCtrlSensorNo, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 2 );

	wxBoxSizer* bSizerButtons1;
	bSizerButtons1 = new wxBoxSizer( wxHORIZONTAL );

	m_cbUseSet1 = new wxCheckBox( this, wxID_ANY, wxT("Use"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons1->Add( m_cbUseSet1, 1, 0, 5 );

	m_bmSet1 = new wxStaticBitmap( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PASTE  ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons1->Add( m_bmSet1, 1, 0, 5 );

	m_bmClear1 = new wxStaticBitmap( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_MISSING_IMAGE  ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons1->Add( m_bmClear1, 1, 0, 5 );


	bSizerNo->Add( bSizerButtons1, 0, wxALL|wxEXPAND, 2 );

	wxBoxSizer* bSizerButtons2;
	bSizerButtons2 = new wxBoxSizer( wxHORIZONTAL );

	m_cbUseSet11 = new wxCheckBox( this, wxID_ANY, wxT("Use"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons2->Add( m_cbUseSet11, 1, 0, 5 );

	m_bmSet11 = new wxStaticBitmap( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PASTE  ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons2->Add( m_bmSet11, 1, 0, 5 );

	m_bmClear11 = new wxStaticBitmap( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_MISSING_IMAGE  ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons2->Add( m_bmClear11, 1, 0, 5 );


	bSizerNo->Add( bSizerButtons2, 0, wxALL|wxEXPAND, 2 );

	wxBoxSizer* bSizerButtons3;
	bSizerButtons3 = new wxBoxSizer( wxHORIZONTAL );

	m_cbUseSet12 = new wxCheckBox( this, wxID_ANY, wxT("Use"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons3->Add( m_cbUseSet12, 1, 0, 5 );

	m_bmSet12 = new wxStaticBitmap( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PASTE ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons3->Add( m_bmSet12, 1, 0, 5 );

	m_bmClear12 = new wxStaticBitmap( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_MISSING_IMAGE ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons3->Add( m_bmClear12, 1, 0, 5 );


	bSizerNo->Add( bSizerButtons3, 0, wxALL|wxEXPAND, 2 );


	bSizerSensor->Add( bSizerNo, 1, 0, 5 );

	wxBoxSizer* bSizerName;
	bSizerName = new wxBoxSizer( wxVERTICAL );

	bSizerName->SetMinSize( wxSize( 70,-1 ) );
	m_txtCtrlCurName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerName->Add( m_txtCtrlCurName, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpName1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerName->Add( m_txtCtrlSpName1, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpName2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerName->Add( m_txtCtrlSpName2, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpName3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerName->Add( m_txtCtrlSpName3, 0, wxALL|wxEXPAND, 2 );


	bSizerSensor->Add( bSizerName, 1, 0, 5 );

	wxBoxSizer* bSizerWL;
	bSizerWL = new wxBoxSizer( wxVERTICAL );

	bSizerWL->SetMinSize( wxSize( -70,-1 ) );
	m_txtCtrlCurWL = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerWL->Add( m_txtCtrlCurWL, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpWL1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerWL->Add( m_txtCtrlSpWL1, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpWL2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerWL->Add( m_txtCtrlSpWL2, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpWL3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerWL->Add( m_txtCtrlSpWL3, 0, wxALL|wxEXPAND, 2 );


	bSizerSensor->Add( bSizerWL, 1, 0, 5 );

	wxBoxSizer* bSizerSat;
	bSizerSat = new wxBoxSizer( wxVERTICAL );

	bSizerSat->SetMinSize( wxSize( 70,-1 ) );
	m_txtCtrlCurSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerSat->Add( m_txtCtrlCurSat, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpSat1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerSat->Add( m_txtCtrlSpSat1, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpSat2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerSat->Add( m_txtCtrlSpSat2, 0, wxALL|wxEXPAND, 2 );

	m_txtCtrlSpSat3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizerSat->Add( m_txtCtrlSpSat3, 0, wxALL|wxEXPAND, 2 );


	bSizerSensor->Add( bSizerSat, 1, 0, 5 );


	this->SetSizer( bSizerSensor );
	this->Layout();
	bSizerSensor->Fit( this );
}

PanelSensor::~PanelSensor()
{
}
