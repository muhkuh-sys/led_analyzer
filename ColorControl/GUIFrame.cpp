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
	this->SetSizeHints( wxSize(-1,-1 ), wxDefaultSize );
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
	wxMenuItem* menuItem_Log;
	menuItem_Log = new wxMenuItem( mMenuView, wxID_ANY, wxString( wxT("Show Log") ) + wxT('\t') + wxT("Strg-L"), wxT("Show extended output"), wxITEM_NORMAL );
	mMenuView->Append( menuItem_Log );

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
	bSizerMain = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerHW;
	bSizerHW = new wxBoxSizer( wxVERTICAL );

	bSizerHW->SetMinSize( wxSize( 70,-1 ) );
	m_bpCoco = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("pic/logo_hilscher.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 90,90 ), 0 );
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


	bSizerHW->Add( bSizerCommunication, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );


	bSizerHW->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerHilscher;
	bSizerHilscher = new wxBoxSizer( wxVERTICAL );


	bSizerHilscher->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stHilscher = new wxStaticText( this, wxID_ANY, wxT("Color Control v 0.1\n© Copyright 2015\nHilscher GmbH"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stHilscher->Wrap( -1 );
	bSizerHilscher->Add( m_stHilscher, 1, wxALIGN_CENTER, 5 );


	bSizerHilscher->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizerHW->Add( bSizerHilscher, 0, wxALIGN_CENTER|wxEXPAND, 5 );


	bSizerMain->Add( bSizerHW, 0, wxBOTTOM|wxEXPAND|wxLEFT, 5 );

	wxBoxSizer* bSizerMainRight;
	bSizerMainRight = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerControl;
	bSizerControl = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerControl1;
	bSizerControl1 = new wxBoxSizer( wxHORIZONTAL );

	wxString m_rbTestmodeChoices[] = { wxT("Color Controller"), wxT("Color Controller + netX 56") };
	int m_rbTestmodeNChoices = sizeof( m_rbTestmodeChoices ) / sizeof( wxString );
	m_rbTestmode = new wxRadioBox( this, wxID_ANY, wxT("Testmode"), wxDefaultPosition, wxDefaultSize, m_rbTestmodeNChoices, m_rbTestmodeChoices, 1, wxRA_SPECIFY_COLS );
	m_rbTestmode->SetSelection( 0 );
	m_rbTestmode->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	bSizerControl1->Add( m_rbTestmode, 0, wxEXPAND, 0 );


	bSizerControl1->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonStart = new wxButton( this, wxID_START, wxT("START"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerControl1->Add( m_buttonStart, 0, wxALIGN_CENTER|wxEXPAND, 5 );


	bSizerControl->Add( bSizerControl1, 0, wxALL|wxEXPAND|wxTOP, 5 );

	m_panelData = new wxPanel( this, wxID_Data, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizerControl->Add( m_panelData, 1, wxEXPAND | wxALL, 5 );


	bSizerMainRight->Add( bSizerControl, 1, wxEXPAND, 5 );

	m_panelSettings = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelSettings->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	wxBoxSizer* bSizerSettings;
	bSizerSettings = new wxBoxSizer( wxVERTICAL );

	m_bpCIE = new wxStaticBitmap( m_panelSettings, wxID_ANY, wxBitmap( wxT("pic/CIE1931.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 420,410 ), 0 );
	bSizerSettings->Add( m_bpCIE, 1, wxALIGN_BOTTOM|wxBOTTOM|wxTOP, 8 );


	bSizerSettings->Add( 0, 0, 1, wxEXPAND, 5 );

	m_nbTest = new wxNotebook( m_panelSettings, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelDefineTest = new wxPanel( m_nbTest, wxID_GENERATETEST, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelDefineTest->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOTEXT ) );
	m_panelDefineTest->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	wxBoxSizer* bSizerDefineTest;
	bSizerDefineTest = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerTol;
	bSizerTol = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizerWavelength;
	sbSizerWavelength = new wxStaticBoxSizer( new wxStaticBox( m_panelDefineTest, wxID_ANY, wxT("Wavelength [nm]") ), wxHORIZONTAL );

	m_stWavelength = new wxStaticText( m_panelDefineTest, wxID_ANY, wxT("+/-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stWavelength->Wrap( -1 );
	sbSizerWavelength->Add( m_stWavelength, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtCtrlWavelength = new wxTextCtrl( m_panelDefineTest, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	sbSizerWavelength->Add( m_txtCtrlWavelength, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizerTol->Add( sbSizerWavelength, 1, wxALIGN_CENTER|wxRIGHT, 5 );

	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( m_panelDefineTest, wxID_ANY, wxT("Saturation [%]") ), wxHORIZONTAL );

	m_stSaturation = new wxStaticText( m_panelDefineTest, wxID_ANY, wxT("+/-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stSaturation->Wrap( -1 );
	sbSizer21->Add( m_stSaturation, 0, wxALL, 5 );

	m_txtCtrlSaturation = new wxTextCtrl( m_panelDefineTest, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	sbSizer21->Add( m_txtCtrlSaturation, 0, wxALL, 5 );


	bSizerTol->Add( sbSizer21, 1, wxALIGN_CENTER|wxRIGHT, 5 );

	wxStaticBoxSizer* sbSizerIllumination;
	sbSizerIllumination = new wxStaticBoxSizer( new wxStaticBox( m_panelDefineTest, wxID_ANY, wxT("Illumination [Lux]") ), wxHORIZONTAL );

	m_stIllumination = new wxStaticText( m_panelDefineTest, wxID_ANY, wxT("+/-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stIllumination->Wrap( -1 );
	sbSizerIllumination->Add( m_stIllumination, 0, wxALL, 5 );

	m_txtCtrlIllumination = new wxTextCtrl( m_panelDefineTest, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	sbSizerIllumination->Add( m_txtCtrlIllumination, 0, wxALL, 5 );


	bSizerTol->Add( sbSizerIllumination, 1, wxALIGN_CENTER, 5 );


	bSizerDefineTest->Add( bSizerTol, 1, wxALIGN_CENTER|wxALL|wxEXPAND|wxTOP, 10 );

	buttonGenerate = new wxButton( m_panelDefineTest, wxID_ANY, wxT("Generate Testfile"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDefineTest->Add( buttonGenerate, 0, wxALIGN_BOTTOM|wxALL|wxEXPAND, 10 );


	m_panelDefineTest->SetSizer( bSizerDefineTest );
	m_panelDefineTest->Layout();
	bSizerDefineTest->Fit( m_panelDefineTest );
	m_nbTest->AddPage( m_panelDefineTest, wxT("Define Test"), true );
	m_panelUseTest = new wxPanel( m_nbTest, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerUseTest;
	bSizerUseTest = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerTestInput;
	bSizerTestInput = new wxBoxSizer( wxHORIZONTAL );

	m_stInputTest = new wxStaticText( m_panelUseTest, wxID_ANY, wxT("Select Input Test File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stInputTest->Wrap( -1 );
	bSizerTestInput->Add( m_stInputTest, 0, wxALIGN_CENTER|wxRIGHT, 5 );

	m_bpButtonUP = new wxBitmapButton( m_panelUseTest, wxID_ANY, wxArtProvider::GetBitmap( wxART_FILE_OPEN ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerTestInput->Add( m_bpButtonUP, 0, wxALIGN_CENTER_VERTICAL, 5 );

	m_txtCtrlInputFile = new wxTextCtrl( m_panelUseTest, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTestInput->Add( m_txtCtrlInputFile, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizerUseTest->Add( bSizerTestInput, 1, wxALIGN_CENTER|wxALL|wxEXPAND, 10 );

	m_buttonUseTest = new wxButton( m_panelUseTest, wxID_USETEST, wxT("Use Testfile"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerUseTest->Add( m_buttonUseTest, 0, wxALIGN_BOTTOM|wxALL|wxEXPAND, 10 );


	m_panelUseTest->SetSizer( bSizerUseTest );
	m_panelUseTest->Layout();
	bSizerUseTest->Fit( m_panelUseTest );
	m_nbTest->AddPage( m_panelUseTest, wxT("Use Test"), false );
	panelSensorSettings = new wxPanel( m_nbTest, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerGainIntButton;
	bSizerGainIntButton = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerGainInt;
	bSizerGainInt = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizerGain;
	sbSizerGain = new wxStaticBoxSizer( new wxStaticBox( panelSensorSettings, wxID_ANY, wxT("Gain") ), wxVERTICAL );

	wxString m_choiceGainChoices[] = { wxT("GAIN_1X"), wxT("GAIN_4X"), wxT("GAIN_16X"), wxT("GAIN_60X") };
	int m_choiceGainNChoices = sizeof( m_choiceGainChoices ) / sizeof( wxString );
	m_choiceGain = new wxChoice( panelSensorSettings, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceGainNChoices, m_choiceGainChoices, 0 );
	m_choiceGain->SetSelection( 2 );
	sbSizerGain->Add( m_choiceGain, 0, wxALL, 5 );


	bSizerGainInt->Add( sbSizerGain, 1, wxALIGN_CENTER|wxRIGHT, 5 );

	wxStaticBoxSizer* sbSizerInt;
	sbSizerInt = new wxStaticBoxSizer( new wxStaticBox( panelSensorSettings, wxID_ANY, wxT("Integration Time") ), wxVERTICAL );

	wxString m_choiceIntChoices[] = { wxT("2_4ms"), wxT("24ms"), wxT("100ms"), wxT("154ms"), wxT("200ms"), wxT("700ms") };
	int m_choiceIntNChoices = sizeof( m_choiceIntChoices ) / sizeof( wxString );
	m_choiceInt = new wxChoice( panelSensorSettings, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceIntNChoices, m_choiceIntChoices, 0 );
	m_choiceInt->SetSelection( 0 );
	sbSizerInt->Add( m_choiceInt, 0, wxALL, 5 );


	bSizerGainInt->Add( sbSizerInt, 1, wxALIGN_CENTER|wxRIGHT, 5 );


	bSizerGainIntButton->Add( bSizerGainInt, 1, wxALIGN_CENTER|wxALL|wxEXPAND, 10 );

	m_buttonSendAll = new wxButton( panelSensorSettings, wxID_SENDALL, wxT("Send All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerGainIntButton->Add( m_buttonSendAll, 0, wxALIGN_BOTTOM|wxALL|wxEXPAND, 10 );


	panelSensorSettings->SetSizer( bSizerGainIntButton );
	panelSensorSettings->Layout();
	bSizerGainIntButton->Fit( panelSensorSettings );
	m_nbTest->AddPage( panelSensorSettings, wxT("Settings"), false );

	bSizerSettings->Add( m_nbTest, 0, wxBOTTOM|wxEXPAND, 5 );


	m_panelSettings->SetSizer( bSizerSettings );
	m_panelSettings->Layout();
	bSizerSettings->Fit( m_panelSettings );
	bSizerMainRight->Add( m_panelSettings, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );


	bSizerMain->Add( bSizerMainRight, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, idStatusBar );

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonScan->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnScan ), NULL, this );
	m_bpButtonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialUp ), NULL, this );
	m_bpButtonDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialDown ), NULL, this );
	m_buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnConnect ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnStart ), NULL, this );
	buttonGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnGenerateTest ), NULL, this );
	m_buttonUseTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnUseTest ), NULL, this );
	m_buttonSendAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSendAll ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	m_buttonScan->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnScan ), NULL, this );
	m_bpButtonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialUp ), NULL, this );
	m_bpButtonDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSerialDown ), NULL, this );
	m_buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnConnect ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnStart ), NULL, this );
	buttonGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnGenerateTest ), NULL, this );
	m_buttonUseTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnUseTest ), NULL, this );
	m_buttonSendAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnSendAll ), NULL, this );

}
