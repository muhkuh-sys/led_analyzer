/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif


#include "main.h"
// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 500,500 ), wxDefaultSize );
	
	menuBar_main = new wxMenuBar( 0 );
	menuFile = new wxMenu();
	wxMenuItem* menuItem_save;
	menuItem_save = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Save Configuration") ) + wxT('\t') + wxT("Strg-S"), wxT("Save window configuration"), wxITEM_NORMAL );
	menuFile->Append( menuItem_save );
	
	wxMenuItem* menuItem_open;
	menuItem_open = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Open Configuration") ) + wxT('\t') + wxT("Strg-O"), wxT("Open windows configuration"), wxITEM_NORMAL );
	menuFile->Append( menuItem_open );
	
	menuFile->AppendSeparator();
	
	wxMenuItem* menuItem_exit;
	menuItem_exit = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Exit") ) + wxT('\t') + wxT("Strg-Q"), wxT("Close app ..."), wxITEM_NORMAL );
	menuFile->Append( menuItem_exit );
	
	menuBar_main->Append( menuFile, wxT("File") ); 
	
	menuView = new wxMenu();
	wxMenuItem* menuItem_Log;
	menuItem_Log = new wxMenuItem( menuView, wxID_ANY, wxString( wxT("Show Log") ) + wxT('\t') + wxT("Strg-L"), wxT("Show extended output"), wxITEM_NORMAL );
	menuView->Append( menuItem_Log );
	
	wxMenuItem* menuItem_clearLog;
	menuItem_clearLog = new wxMenuItem( menuView, wxID_ANY, wxString( wxT("Clear Log") ) + wxT('\t') + wxT("Strg-P"), wxT("Flush output"), wxITEM_NORMAL );
	menuView->Append( menuItem_clearLog );
	
	wxMenuItem* menuItem_hideLog;
	menuItem_hideLog = new wxMenuItem( menuView, wxID_ANY, wxString( wxT("Hide Log") ) + wxT('\t') + wxT("Strg-H"), wxT("Hide extended output"), wxITEM_NORMAL );
	menuView->Append( menuItem_hideLog );
	
	menuView->AppendSeparator();
	
	wxMenuItem* menuDiagram;
	menuDiagram = new wxMenuItem( menuView, wxID_ANY, wxString( wxT("Show Chromaticity Diagram") ) + wxT('\t') + wxT("Strg-R"), wxT("Show CIE 1931 chromaticity curves"), wxITEM_NORMAL );
	menuView->Append( menuDiagram );
	
	menuBar_main->Append( menuView, wxT("View") ); 
	
	menuHelp = new wxMenu();
	wxMenuItem* menuItem_quickGuide;
	menuItem_quickGuide = new wxMenuItem( menuHelp, wxID_ANY, wxString( wxT("Quick Guide") ) + wxT('\t') + wxT("F1"), wxT("Open a quick tutorial for this app"), wxITEM_NORMAL );
	menuHelp->Append( menuItem_quickGuide );
	
	wxMenuItem* menuItem_about;
	menuItem_about = new wxMenuItem( menuHelp, wxID_ANY, wxString( wxT("About") ) + wxT('\t') + wxT("F2"), wxT("About this app"), wxITEM_NORMAL );
	menuHelp->Append( menuItem_about );
	
	menuBar_main->Append( menuHelp, wxT("Help") ); 
	
	this->SetMenuBar( menuBar_main );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	mainNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	mainNotebook->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	
	panelTestdefinition = new wxPanel( mainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	panelTestdefinition->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	panelTestdefinition->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	
	wxBoxSizer* calibrationSizer1;
	calibrationSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* calSizer12;
	calSizer12 = new wxBoxSizer( wxVERTICAL );
	
	calSizer12->SetMinSize( wxSize( 70,-1 ) ); 
	m_bitmap511 = new wxStaticBitmap( panelTestdefinition, wxID_ANY, wxBitmap( wxT("monkey-face-simple-violet.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 90,90 ), 0 );
	calSizer12->Add( m_bitmap511, 0, wxALIGN_CENTER|wxALL|wxTOP, 9 );
	
	wxStaticBoxSizer* calSizer113;
	calSizer113 = new wxStaticBoxSizer( new wxStaticBox( panelTestdefinition, wxID_ANY, wxT("Communication") ), wxVERTICAL );
	
	buttonScan1 = new wxButton( panelTestdefinition, wxID_ANY, wxT("SCAN"), wxDefaultPosition, wxDefaultSize, 0 );
	calSizer113->Add( buttonScan1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_dataViewListCtrl21 = new wxDataViewListCtrl( panelTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_dataViewListCtrl21->SetMinSize( wxSize( 90,120 ) );
	m_dataViewListCtrl21->SetMaxSize( wxSize( 90,100 ) );
	
	m_dataViewListColumn31 = m_dataViewListCtrl21->AppendTextColumn( wxT("Name") ); 
	m_dataViewListColumn41 = m_dataViewListCtrl21->AppendTextColumn( wxT("Name") ); 
	calSizer113->Add( m_dataViewListCtrl21, 2, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* calSizer1111;
	calSizer1111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bpButton21 = new wxBitmapButton( panelTestdefinition, wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_DOWN  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	calSizer1111->Add( m_bpButton21, 1, wxALIGN_LEFT|wxALL, 5 );
	
	m_bpButton31 = new wxBitmapButton( panelTestdefinition, wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_UP  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	calSizer1111->Add( m_bpButton31, 1, wxALIGN_RIGHT|wxALL, 5 );
	
	
	calSizer113->Add( calSizer1111, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	calSizer113->Add( 0, 0, 1, wxEXPAND, 5 );
	
	buttonConnect1 = new wxButton( panelTestdefinition, wxID_ANY, wxT("CONNECT"), wxDefaultPosition, wxDefaultSize, 0 );
	calSizer113->Add( buttonConnect1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* calSizer1121;
	calSizer1121 = new wxBoxSizer( wxHORIZONTAL );
	
	st_numb1 = new wxStaticText( panelTestdefinition, wxID_ANY, wxT("Connected: "), wxDefaultPosition, wxDefaultSize, 0 );
	st_numb1->Wrap( -1 );
	calSizer1121->Add( st_numb1, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrl21 = new wxTextCtrl( panelTestdefinition, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 30,20 ), 0 );
	m_textCtrl21->SetMaxSize( wxSize( 30,30 ) );
	
	calSizer1121->Add( m_textCtrl21, 0, wxALL, 5 );
	
	
	calSizer113->Add( calSizer1121, 1, wxALL|wxEXPAND, 10 );
	
	
	calSizer12->Add( calSizer113, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText7 = new wxStaticText( panelTestdefinition, wxID_ANY, wxT("Color Controller v 0.1\n  © Copyright 2015\n    Hilscher GmbH"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer20->Add( m_staticText7, 1, wxALIGN_CENTER, 5 );
	
	
	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	calSizer12->Add( bSizer20, 0, wxALIGN_CENTER|wxEXPAND, 5 );
	
	
	calibrationSizer1->Add( calSizer12, 0, wxBOTTOM|wxLEFT|wxTOP|wxEXPAND, 5 );
	
	wxBoxSizer* calSizer22;
	calSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* calSizer213;
	calSizer213 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* calSizer2113;
	calSizer2113 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString m_radioBox11Choices[] = { wxT("Single"), wxT("Continuous") };
	int m_radioBox11NChoices = sizeof( m_radioBox11Choices ) / sizeof( wxString );
	m_radioBox11 = new wxRadioBox( panelTestdefinition, wxID_ANY, wxT("Testmode"), wxDefaultPosition, wxDefaultSize, m_radioBox11NChoices, m_radioBox11Choices, 1, wxRA_SPECIFY_COLS );
	m_radioBox11->SetSelection( 1 );
	m_radioBox11->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	
	calSizer2113->Add( m_radioBox11, 0, wxEXPAND, 0 );
	
	wxStaticBoxSizer* calSizer21111;
	calSizer21111 = new wxStaticBoxSizer( new wxStaticBox( panelTestdefinition, wxID_ANY, wxT("Testinterval") ), wxHORIZONTAL );
	
	m_comboBox11 = new wxComboBox( panelTestdefinition, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	calSizer21111->Add( m_comboBox11, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText21 = new wxStaticText( panelTestdefinition, wxID_ANY, wxT("[sec]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	calSizer21111->Add( m_staticText21, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	calSizer2113->Add( calSizer21111, 0, wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	wxBoxSizer* calSizer21121;
	calSizer21121 = new wxBoxSizer( wxHORIZONTAL );
	
	m_toggleBtn2 = new wxToggleButton( panelTestdefinition, wxID_ANY, wxT("START"), wxDefaultPosition, wxDefaultSize, 0 );
	calSizer21121->Add( m_toggleBtn2, 0, wxALL|wxEXPAND, 5 );
	
	
	calSizer21121->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_toggleBtn21 = new wxToggleButton( panelTestdefinition, wxID_ANY, wxT("<<"), wxDefaultPosition, wxDefaultSize, 0 );
	calSizer21121->Add( m_toggleBtn21, 0, wxALIGN_CENTER|wxBOTTOM|wxLEFT|wxTOP, 5 );
	
	
	calSizer2113->Add( calSizer21121, 1, wxEXPAND, 5 );
	
	
	calSizer213->Add( calSizer2113, 0, wxEXPAND|wxTOP, 8 );
	
	wxBoxSizer* calSizer2121;
	calSizer2121 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook21 = new wxNotebook( panelTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	panelWavelength1 = new wxPanel( m_notebook21, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook21->AddPage( panelWavelength1, wxT("Wavelength"), true );
	panelSettings1 = new wxPanel( m_notebook21, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook21->AddPage( panelSettings1, wxT("Gain / Integration"), false );
	panelTolerance = new wxPanel( m_notebook21, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook21->AddPage( panelTolerance, wxT("Tolerance"), false );
	
	calSizer2121->Add( m_notebook21, 1, wxBOTTOM|wxEXPAND, 5 );
	
	
	calSizer213->Add( calSizer2121, 1, wxEXPAND|wxTOP, 10 );
	
	
	calSizer22->Add( calSizer213, 1, wxEXPAND, 5 );
	
	
	calibrationSizer1->Add( calSizer22, 1, wxBOTTOM|wxEXPAND|wxRIGHT|wxTOP, 5 );
	
	panelCollapsable = new wxPanel( panelTestdefinition, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	panelCollapsable->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	
	wxBoxSizer* calSizer31;
	calSizer31 = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap41 = new wxStaticBitmap( panelCollapsable, wxID_ANY, wxBitmap( wxT("../Downloads/PlanckianLocus.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 410,410 ), 0 );
	calSizer31->Add( m_bitmap41, 1, wxALIGN_BOTTOM|wxBOTTOM|wxRIGHT|wxTOP, 5 );
	
	
	calSizer31->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer891;
	bSizer891 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer241;
	sbSizer241 = new wxStaticBoxSizer( new wxStaticBox( panelCollapsable, wxID_ANY, wxT("Gain") ), wxVERTICAL );
	
	wxArrayString m_choice61Choices;
	m_choice61 = new wxChoice( panelCollapsable, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice61Choices, 0 );
	m_choice61->SetSelection( 0 );
	sbSizer241->Add( m_choice61, 0, wxALL, 5 );
	
	
	bSizer891->Add( sbSizer241, 1, wxALIGN_CENTER|wxRIGHT, 5 );
	
	wxStaticBoxSizer* sbSizer251;
	sbSizer251 = new wxStaticBoxSizer( new wxStaticBox( panelCollapsable, wxID_ANY, wxT("Integration Time") ), wxVERTICAL );
	
	wxArrayString m_choice71Choices;
	m_choice71 = new wxChoice( panelCollapsable, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice71Choices, 0 );
	m_choice71->SetSelection( 0 );
	sbSizer251->Add( m_choice71, 0, wxALL, 5 );
	
	
	bSizer891->Add( sbSizer251, 1, wxALIGN_CENTER|wxLEFT|wxRIGHT, 5 );
	
	butonQuickset1 = new wxButton( panelCollapsable, wxID_ANY, wxT("SET"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer891->Add( butonQuickset1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	calSizer31->Add( bSizer891, 0, wxEXPAND, 0 );
	
	wxBoxSizer* bSizer93;
	bSizer93 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer20;
	sbSizer20 = new wxStaticBoxSizer( new wxStaticBox( panelCollapsable, wxID_ANY, wxT("Tolerance Wavelength") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer94;
	bSizer94 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl17 = new wxTextCtrl( panelCollapsable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer94->Add( m_textCtrl17, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText211 = new wxStaticText( panelCollapsable, wxID_ANY, wxT("delta min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	bSizer94->Add( m_staticText211, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	sbSizer20->Add( bSizer94, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer96;
	bSizer96 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl18 = new wxTextCtrl( panelCollapsable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer96->Add( m_textCtrl18, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText22 = new wxStaticText( panelCollapsable, wxID_ANY, wxT("delta max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer96->Add( m_staticText22, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	sbSizer20->Add( bSizer96, 1, wxEXPAND, 5 );
	
	
	bSizer93->Add( sbSizer20, 1, wxALIGN_CENTER|wxRIGHT, 5 );
	
	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( panelCollapsable, wxID_ANY, wxT("Tolerance Saturation") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer95;
	bSizer95 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl19 = new wxTextCtrl( panelCollapsable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer95->Add( m_textCtrl19, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText23 = new wxStaticText( panelCollapsable, wxID_ANY, wxT("delta min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer95->Add( m_staticText23, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	sbSizer21->Add( bSizer95, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer97;
	bSizer97 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl20 = new wxTextCtrl( panelCollapsable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer97->Add( m_textCtrl20, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText24 = new wxStaticText( panelCollapsable, wxID_ANY, wxT("delta max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	bSizer97->Add( m_staticText24, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	sbSizer21->Add( bSizer97, 1, wxEXPAND, 5 );
	
	
	bSizer93->Add( sbSizer21, 1, wxALIGN_CENTER|wxLEFT|wxRIGHT, 5 );
	
	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxVERTICAL );
	
	buttonTolset = new wxButton( panelCollapsable, wxID_ANY, wxT("SET"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( buttonTolset, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_button38 = new wxButton( panelCollapsable, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( m_button38, 0, wxALL, 5 );
	
	
	bSizer93->Add( bSizer100, 0, wxALIGN_CENTER, 5 );
	
	
	calSizer31->Add( bSizer93, 0, wxALIGN_BOTTOM|wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	buttonGenerate = new wxButton( panelCollapsable, wxID_ANY, wxT("Save Testfile"), wxDefaultPosition, wxDefaultSize, 0 );
	calSizer31->Add( buttonGenerate, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxEXPAND|wxRIGHT|wxTOP, 5 );
	
	
	panelCollapsable->SetSizer( calSizer31 );
	panelCollapsable->Layout();
	calSizer31->Fit( panelCollapsable );
	calibrationSizer1->Add( panelCollapsable, 0, wxEXPAND | wxALL, 5 );
	
	
	panelTestdefinition->SetSizer( calibrationSizer1 );
	panelTestdefinition->Layout();
	calibrationSizer1->Fit( panelTestdefinition );
	mainNotebook->AddPage( panelTestdefinition, wxT("Testdefinition"), false );
	
	mainSizer->Add( mainNotebook, 3, wxALL|wxEXPAND, 0 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	statusBar_main = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}
