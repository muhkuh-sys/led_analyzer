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

	m_bpButtonUp = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_DOWN  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerUpDown->Add( m_bpButtonUp, 1, wxALIGN_LEFT|wxALL, 5 );

	m_bpButtonDown = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_UP  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
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

	wxStaticBoxSizer* sbSizerTestfile;
	sbSizerTestfile = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Testfile") ), wxVERTICAL );

	m_buttonGenerate = new wxButton( this, wxID_GENERATE, wxT("Generate Tesfile"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTestfile->Add( m_buttonGenerate, 0, wxALL, 5 );

	m_buttonUseTestfile = new wxButton( this, wxID_USE, wxT("Use Testfile"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTestfile->Add( m_buttonUseTestfile, 0, wxALL|wxEXPAND, 5 );


	bSizerButtons->Add( sbSizerTestfile, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerButtons->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonStart = new wxButton( this, wxID_START, wxT("START"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonStart, 0, wxALIGN_CENTER|wxBOTTOM|wxRIGHT|wxTOP|wxEXPAND, 5 );


	bSizerData->Add( bSizerButtons, 0, wxEXPAND, 5 );

	m_nbData = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_swColors = new wxScrolledWindow( m_nbData, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_swColors->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizerColors;
	bSizerColors = new wxBoxSizer( wxVERTICAL );

	m_dvlColors = new wxDataViewListCtrl( m_swColors, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_cSensorNo = m_dvlColors->AppendTextColumn( wxT("Sensor") );
	m_cWavelength = m_dvlColors->AppendTextColumn( wxT("Wavelength") );
	m_cSaturation = m_dvlColors->AppendTextColumn( wxT("Saturation") );
	m_cIllumination = m_dvlColors->AppendTextColumn( wxT("Illumination") );
	m_cColor = m_dvlColors->AppendTextColumn( wxT("Color") );
	m_cGain = m_dvlColors->AppendTextColumn( wxT("Gain") );
	m_cIntegration = m_dvlColors->AppendTextColumn( wxT("Integration Time") );
	bSizerColors->Add( m_dvlColors, 1, wxEXPAND, 5 );


	m_swColors->SetSizer( bSizerColors );
	m_swColors->Layout();
	bSizerColors->Fit( m_swColors );
	m_nbData->AddPage( m_swColors, wxT("Colors"), false );
	m_swTestdefinition = new wxScrolledWindow( m_nbData, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_swTestdefinition->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizerTestDefinition;
	bSizerTestDefinition = new wxBoxSizer( wxVERTICAL );


	m_swTestdefinition->SetSizer( bSizerTestDefinition );
	m_swTestdefinition->Layout();
	bSizerTestDefinition->Fit( m_swTestdefinition );
	m_nbData->AddPage( m_swTestdefinition, wxT("Testdefinition"), true );

	bSizerData->Add( m_nbData, 1, wxEXPAND | wxALL, 5 );


	bSizerMainTop->Add( bSizerData, 1, wxEXPAND, 5 );


	bSizerMain->Add( bSizerMainTop, 1, wxEXPAND, 5 );

	m_swLog = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL );
	wxBoxSizer* bSizerLog;
	bSizerLog = new wxBoxSizer( wxVERTICAL );

	m_text = new wxTextCtrl( m_swLog, wxID_MYTEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_text->SetMinSize( wxSize( -1,100 ) );

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

PanelHeader::PanelHeader( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );

	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxHORIZONTAL );

	m_stSensor = new wxStaticText( this, wxID_ANY, wxT("Sensor"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stSensor->Wrap( -1 );
	bSizer98->Add( m_stSensor, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stName = new wxStaticText( this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stName->Wrap( -1 );
	bSizer98->Add( m_stName, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stWavelength = new wxStaticText( this, wxID_ANY, wxT("Wavelength"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stWavelength->Wrap( -1 );
	bSizer98->Add( m_stWavelength, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stSaturation = new wxStaticText( this, wxID_ANY, wxT("Saturation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stSaturation->Wrap( -1 );
	bSizer98->Add( m_stSaturation, 0, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_stIllumination = new wxStaticText( this, wxID_ANY, wxT("Illumination"), wxDefaultPosition, wxDefaultSize, 0 );
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


	this->SetSizer( bSizer98 );
	this->Layout();
}

PanelHeader::~PanelHeader()
{
}

PanelSensor::PanelSensor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	wxBoxSizer* bSizerSensorPanel;
	bSizerSensorPanel = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerNo;
	bSizerNo = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerSensorNumber;
	bSizerSensorNumber = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSensorNo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSensorNo->SetMaxSize( wxSize( 30,-1 ) );

	bSizerSensorNumber->Add( m_txtCtrlSensorNo, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );


	bSizerNo->Add( bSizerSensorNumber, 1, wxALIGN_CENTER_HORIZONTAL, 2 );

	wxBoxSizer* bSizerButtons1;
	bSizerButtons1 = new wxBoxSizer( wxHORIZONTAL );

	m_cbUseSet1 = new wxCheckBox( this, wxID_ANY, wxT("Use"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons1->Add( m_cbUseSet1, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_bpButtonPaste1 = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PASTE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPaste1->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons1->Add( m_bpButtonPaste1, 1, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 2 );

	m_bpButtonClear1 = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_MISSING_IMAGE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonClear1->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons1->Add( m_bpButtonClear1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	bSizerNo->Add( bSizerButtons1, 1, wxALIGN_CENTER_HORIZONTAL, 2 );

	wxBoxSizer* bSizerButtons2;
	bSizerButtons2 = new wxBoxSizer( wxHORIZONTAL );

	m_cbUseSet2 = new wxCheckBox( this, wxID_ANY, wxT("Use"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons2->Add( m_cbUseSet2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_bpButtonPaste2 = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PASTE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPaste2->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons2->Add( m_bpButtonPaste2, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_bmButtonClear2 = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_MISSING_IMAGE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bmButtonClear2->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons2->Add( m_bmButtonClear2, 1, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	bSizerNo->Add( bSizerButtons2, 1, wxALIGN_CENTER_HORIZONTAL, 2 );

	wxBoxSizer* bSizerButtons3;
	bSizerButtons3 = new wxBoxSizer( wxHORIZONTAL );

	m_cbUseSet3 = new wxCheckBox( this, wxID_ANY, wxT("Use"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons3->Add( m_cbUseSet3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_bmButtonPaste3 = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PASTE  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bmButtonPaste3->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons3->Add( m_bmButtonPaste3, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_bpButtonClear3 = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_MISSING_IMAGE  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonClear3->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons3->Add( m_bpButtonClear3, 1, wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );


	bSizerNo->Add( bSizerButtons3, 1, wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerNo, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerName;
	bSizerName = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurName->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlCurName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 2 );

	m_txtCtrlSpName1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpName1->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlSpName1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpName2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpName2->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlSpName2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpName3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpName3->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlSpName3, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 2 );


	bSizerSensorPanel->Add( bSizerName, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerWL;
	bSizerWL = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurWL = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurWL->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlCurWL, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpWL1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpWL1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlSpWL1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpWL2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpWL2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlSpWL2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpWL3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpWL3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlSpWL3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerWL, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerSat;
	bSizerSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlCurSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpSat1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpSat1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlSpSat1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpSat2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpSat2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlSpSat2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpSat3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpSat3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlSpSat3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerSat, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerIllu;
	bSizerIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlCurIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpIllu1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpIllu1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlSpIllu1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpIllu2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpIllu2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlSpIllu2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpIllu3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpIllu3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlSpIllu3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerIllu, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerColor;
	bSizerColor = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurColor = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurColor->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlCurColor, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpColor1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpColor1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlSpColor1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpColor2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpColor2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlSpColor2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpColor3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpColor3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlSpColor3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerColor, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPintype;
	bSizerPintype = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurPintypeChoices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO") };
	int m_chCurPintypeNChoices = sizeof( m_chCurPintypeChoices ) / sizeof( wxString );
	m_chCurPintype = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurPintypeNChoices, m_chCurPintypeChoices, 0 );
	m_chCurPintype->SetSelection( 0 );
	bSizerPintype->Add( m_chCurPintype, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	wxString m_chSpPintype1Choices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO"), wxEmptyString };
	int m_chSpPintype1NChoices = sizeof( m_chSpPintype1Choices ) / sizeof( wxString );
	m_chSpPintype1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpPintype1NChoices, m_chSpPintype1Choices, 0 );
	m_chSpPintype1->SetSelection( 0 );
	bSizerPintype->Add( m_chSpPintype1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_chSpPintype2Choices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO") };
	int m_chSpPintype2NChoices = sizeof( m_chSpPintype2Choices ) / sizeof( wxString );
	m_chSpPintype2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpPintype2NChoices, m_chSpPintype2Choices, 0 );
	m_chSpPintype2->SetSelection( 0 );
	bSizerPintype->Add( m_chSpPintype2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_chSpPintype3Choices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO") };
	int m_chSpPintype3NChoices = sizeof( m_chSpPintype3Choices ) / sizeof( wxString );
	m_chSpPintype3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpPintype3NChoices, m_chSpPintype3Choices, 0 );
	m_chSpPintype3->SetSelection( 0 );
	bSizerPintype->Add( m_chSpPintype3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPintype, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinNo;
	bSizerPinNo = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurPinNo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurPinNo->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlCurPinNo, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpPinNo1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpPinNo1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlSpPinNo1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpPinNo2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpPinNo2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlSpPinNo2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpPinNo3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpPinNo3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlSpPinNo3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPinNo, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinValue;
	bSizerPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurPinValueChoices[] = { wxT("0"), wxT("1") };
	int m_chCurPinValueNChoices = sizeof( m_chCurPinValueChoices ) / sizeof( wxString );
	m_chCurPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurPinValueNChoices, m_chCurPinValueChoices, 0 );
	m_chCurPinValue->SetSelection( 0 );
	bSizerPinValue->Add( m_chCurPinValue, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	wxString m_choiceSpPinValue1Choices[] = { wxT("0"), wxT("1") };
	int m_choiceSpPinValue1NChoices = sizeof( m_choiceSpPinValue1Choices ) / sizeof( wxString );
	m_choiceSpPinValue1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSpPinValue1NChoices, m_choiceSpPinValue1Choices, 0 );
	m_choiceSpPinValue1->SetSelection( 0 );
	bSizerPinValue->Add( m_choiceSpPinValue1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_choiceSpPinValue2Choices[] = { wxT("0"), wxT("1") };
	int m_choiceSpPinValue2NChoices = sizeof( m_choiceSpPinValue2Choices ) / sizeof( wxString );
	m_choiceSpPinValue2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSpPinValue2NChoices, m_choiceSpPinValue2Choices, 0 );
	m_choiceSpPinValue2->SetSelection( 0 );
	bSizerPinValue->Add( m_choiceSpPinValue2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_choiceSpPinValue3Choices[] = { wxT("0"), wxT("1") };
	int m_choiceSpPinValue3NChoices = sizeof( m_choiceSpPinValue3Choices ) / sizeof( wxString );
	m_choiceSpPinValue3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSpPinValue3NChoices, m_choiceSpPinValue3Choices, 0 );
	m_choiceSpPinValue3->SetSelection( 0 );
	bSizerPinValue->Add( m_choiceSpPinValue3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPinValue, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerDefPinValue;
	bSizerDefPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurDefPinValueChoices[] = { wxT("0"), wxT("1") };
	int m_chCurDefPinValueNChoices = sizeof( m_chCurDefPinValueChoices ) / sizeof( wxString );
	m_chCurDefPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurDefPinValueNChoices, m_chCurDefPinValueChoices, 0 );
	m_chCurDefPinValue->SetSelection( 0 );
	bSizerDefPinValue->Add( m_chCurDefPinValue, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	wxString m_chSpDefPinValue1Choices[] = { wxT("0"), wxT("1") };
	int m_chSpDefPinValue1NChoices = sizeof( m_chSpDefPinValue1Choices ) / sizeof( wxString );
	m_chSpDefPinValue1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpDefPinValue1NChoices, m_chSpDefPinValue1Choices, 0 );
	m_chSpDefPinValue1->SetSelection( 0 );
	bSizerDefPinValue->Add( m_chSpDefPinValue1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_chSpDefPinValue2Choices[] = { wxT("0"), wxT("1") };
	int m_chSpDefPinValue2NChoices = sizeof( m_chSpDefPinValue2Choices ) / sizeof( wxString );
	m_chSpDefPinValue2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpDefPinValue2NChoices, m_chSpDefPinValue2Choices, 0 );
	m_chSpDefPinValue2->SetSelection( 0 );
	bSizerDefPinValue->Add( m_chSpDefPinValue2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_chSpDefPinValue3Choices[] = { wxT("0"), wxT("1") };
	int m_chSpDefPinValue3NChoices = sizeof( m_chSpDefPinValue3Choices ) / sizeof( wxString );
	m_chSpDefPinValue3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpDefPinValue3NChoices, m_chSpDefPinValue3Choices, 0 );
	m_chSpDefPinValue3->SetSelection( 0 );
	bSizerDefPinValue->Add( m_chSpDefPinValue3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerDefPinValue, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolNm;
	bSizerTolNm = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolNm = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlTolNm->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolNm->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolNm->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlTolNm, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolNm1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolNm1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlSpTolNm1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolNm2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolNm2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlSpTolNm2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolNm3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolNm3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlSpTolNm3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerTolNm, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolSat;
	bSizerTolSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlTolSat->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolSat->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlTolSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolSat1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolSat1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlSpTolSat1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolSat2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolSat2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlSpTolSat2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolSat3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolSat3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlSpTolSat3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerTolSat, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolIllu;
	bSizerTolIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlTolIllu->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolIllu->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlTolIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolIllu1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolIllu1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlSpTolIllu1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolIllu2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolIllu2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlSpTolIllu2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolIllu3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolIllu3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlSpTolIllu3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerTolIllu, 0, 0, 5 );


	this->SetSizer( bSizerSensorPanel );
	this->Layout();

	// Connect Events
	m_bpButtonPaste1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnPasteSet1 ), NULL, this );
	m_bpButtonClear1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnClearSet1 ), NULL, this );
	m_bpButtonPaste2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnPasteSet2 ), NULL, this );
	m_bmButtonClear2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnClearSet2 ), NULL, this );
	m_bmButtonPaste3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnPasteSet3 ), NULL, this );
	m_bpButtonClear3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnClearSet3 ), NULL, this );
}

PanelSensor::~PanelSensor()
{
	// Disconnect Events
	m_bpButtonPaste1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnPasteSet1 ), NULL, this );
	m_bpButtonClear1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnClearSet1 ), NULL, this );
	m_bpButtonPaste2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnPasteSet2 ), NULL, this );
	m_bmButtonClear2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnClearSet2 ), NULL, this );
	m_bmButtonPaste3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnPasteSet3 ), NULL, this );
	m_bpButtonClear3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnClearSet3 ), NULL, this );

}
