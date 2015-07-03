#include "PanelSensor.h"

PanelSensor::PanelSensor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, int sensornumber ) : wxPanel( parent, id, pos, size, style )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	wxBoxSizer* bSizerSensorPanel;
	bSizerSensorPanel = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerNo;
	bSizerNo = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerSensorNumber;
	bSizerSensorNumber = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSensorNo = new wxTextCtrl( this, wxID_ANY, wxString::Format(wxT("%i"), sensornumber), wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_READONLY | wxTE_CENTER );
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

	m_txtCtrlCurName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER );
	m_txtCtrlCurName->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlCurName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 2 );

	m_txtCtrlSpName1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER );
	m_txtCtrlSpName1->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlSpName1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpName2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER );
	m_txtCtrlSpName2->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlSpName2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpName3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER );
	m_txtCtrlSpName3->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlSpName3, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 2 );


	bSizerSensorPanel->Add( bSizerName, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerWL;
	bSizerWL = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurWL = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlCurWL->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlCurWL, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpWL1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpWL1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlSpWL1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpWL2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpWL2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlSpWL2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpWL3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpWL3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlSpWL3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerWL, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerSat;
	bSizerSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )  );
	m_txtCtrlCurSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlCurSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpSat1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )  );
	m_txtCtrlSpSat1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlSpSat1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpSat2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )  );
	m_txtCtrlSpSat2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlSpSat2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpSat3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )  );
	m_txtCtrlSpSat3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlSpSat3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerSat, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerIllu;
	bSizerIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )  );
	m_txtCtrlCurIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlCurIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpIllu1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )  );
	m_txtCtrlSpIllu1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlSpIllu1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpIllu2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpIllu2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlSpIllu2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpIllu3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpIllu3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlSpIllu3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerIllu, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerColor;
	bSizerColor = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurColor = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY );
	m_txtCtrlCurColor->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlCurColor->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlCurColor, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpColor1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY );
	m_txtCtrlSpColor1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlSpColor1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlSpColor1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpColor2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY );
	m_txtCtrlSpColor2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlSpColor2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlSpColor2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpColor3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY);
	m_txtCtrlSpColor3->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlSpColor3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlSpColor3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerColor, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPintype;
	bSizerPintype = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurPintypeChoices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO"), wxEmptyString };
	int m_chCurPintypeNChoices = sizeof( m_chCurPintypeChoices ) / sizeof( wxString );
	m_chCurPintype = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurPintypeNChoices, m_chCurPintypeChoices, 0 );
	m_chCurPintype->SetSelection( 4 );
	bSizerPintype->Add( m_chCurPintype, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	wxString m_chSpPintype1Choices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO"), wxEmptyString };
	int m_chSpPintype1NChoices = sizeof( m_chSpPintype1Choices ) / sizeof( wxString );
	m_chSpPintype1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpPintype1NChoices, m_chSpPintype1Choices, 0 );
	m_chSpPintype1->SetSelection( 4 );
	bSizerPintype->Add( m_chSpPintype1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_chSpPintype2Choices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO"), wxEmptyString };
	int m_chSpPintype2NChoices = sizeof( m_chSpPintype2Choices ) / sizeof( wxString );
	m_chSpPintype2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpPintype2NChoices, m_chSpPintype2Choices, 0 );
	m_chSpPintype2->SetSelection( 4 );
	bSizerPintype->Add( m_chSpPintype2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_chSpPintype3Choices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO"), wxEmptyString };
	int m_chSpPintype3NChoices = sizeof( m_chSpPintype3Choices ) / sizeof( wxString );
	m_chSpPintype3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpPintype3NChoices, m_chSpPintype3Choices, 0 );
	m_chSpPintype3->SetSelection( 4 );
	bSizerPintype->Add( m_chSpPintype3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPintype, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinNo;
	bSizerPinNo = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurPinNo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlCurPinNo->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlCurPinNo, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpPinNo1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpPinNo1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlSpPinNo1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpPinNo2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpPinNo2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlSpPinNo2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpPinNo3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpPinNo3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlSpPinNo3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPinNo, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinValue;
	bSizerPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurPinValueChoices[] = { wxT("Input"), wxT("0"), wxT("1"), wxEmptyString };
	int m_chCurPinValueNChoices = sizeof( m_chCurPinValueChoices ) / sizeof( wxString );
	m_chCurPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurPinValueNChoices, m_chCurPinValueChoices, 0);
	m_chCurPinValue->SetSelection( 3 );
	bSizerPinValue->Add( m_chCurPinValue, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	wxString m_choiceSpPinValue1Choices[] = { wxT("Input"), wxT("0"), wxT("1"), wxEmptyString  };
	int m_choiceSpPinValue1NChoices = sizeof( m_choiceSpPinValue1Choices ) / sizeof( wxString );
	m_choiceSpPinValue1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSpPinValue1NChoices, m_choiceSpPinValue1Choices, 0 );
	m_choiceSpPinValue1->SetSelection( 3 );
	bSizerPinValue->Add( m_choiceSpPinValue1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_choiceSpPinValue2Choices[] = { wxT("Input"), wxT("0"), wxT("1"), wxEmptyString  };
	int m_choiceSpPinValue2NChoices = sizeof( m_choiceSpPinValue2Choices ) / sizeof( wxString );
	m_choiceSpPinValue2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSpPinValue2NChoices, m_choiceSpPinValue2Choices, 0 );
	m_choiceSpPinValue2->SetSelection( 3 );
	bSizerPinValue->Add( m_choiceSpPinValue2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_choiceSpPinValue3Choices[] = { wxT("Input"), wxT("0"), wxT("1"), wxEmptyString  };
	int m_choiceSpPinValue3NChoices = sizeof( m_choiceSpPinValue3Choices ) / sizeof( wxString );
	m_choiceSpPinValue3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSpPinValue3NChoices, m_choiceSpPinValue3Choices, 0 );
	m_choiceSpPinValue3->SetSelection( 3 );
	bSizerPinValue->Add( m_choiceSpPinValue3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPinValue, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerDefPinValue;
	bSizerDefPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurDefPinValueChoices[] = { wxT("Input"), wxT("0"), wxT("1"), wxEmptyString  };
	int m_chCurDefPinValueNChoices = sizeof( m_chCurDefPinValueChoices ) / sizeof( wxString );
	m_chCurDefPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurDefPinValueNChoices, m_chCurDefPinValueChoices, 0 );
	m_chCurDefPinValue->SetSelection( 3 );
	bSizerDefPinValue->Add( m_chCurDefPinValue, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	wxString m_chSpDefPinValue1Choices[] = { wxT("Input"), wxT("0"), wxT("1"), wxEmptyString  };
	int m_chSpDefPinValue1NChoices = sizeof( m_chSpDefPinValue1Choices ) / sizeof( wxString );
	m_chSpDefPinValue1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpDefPinValue1NChoices, m_chSpDefPinValue1Choices, 0 );
	m_chSpDefPinValue1->SetSelection( 3 );
	bSizerDefPinValue->Add( m_chSpDefPinValue1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_chSpDefPinValue2Choices[] = { wxT("Input"), wxT("0"), wxT("1"), wxEmptyString  };
	int m_chSpDefPinValue2NChoices = sizeof( m_chSpDefPinValue2Choices ) / sizeof( wxString );
	m_chSpDefPinValue2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpDefPinValue2NChoices, m_chSpDefPinValue2Choices, 0 );
	m_chSpDefPinValue2->SetSelection( 3 );
	bSizerDefPinValue->Add( m_chSpDefPinValue2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );

	wxString m_chSpDefPinValue3Choices[] = { wxT("Input"), wxT("0"), wxT("1"), wxEmptyString  };
	int m_chSpDefPinValue3NChoices = sizeof( m_chSpDefPinValue3Choices ) / sizeof( wxString );
	m_chSpDefPinValue3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpDefPinValue3NChoices, m_chSpDefPinValue3Choices, 0 );
	m_chSpDefPinValue3->SetSelection( 3 );
	bSizerDefPinValue->Add( m_chSpDefPinValue3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerDefPinValue, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolNm;
	bSizerTolNm = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolNm = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )   );
	//m_txtCtrlTolNm->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolNm->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolNm->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlTolNm, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolNm1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpTolNm1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlSpTolNm1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolNm2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpTolNm2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlSpTolNm2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolNm3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpTolNm3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlSpTolNm3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerTolNm, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolSat;
	bSizerTolSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )   );
	//m_txtCtrlTolSat->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolSat->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlTolSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolSat1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpTolSat1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlSpTolSat1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolSat2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpTolSat2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlSpTolSat2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolSat3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpTolSat3->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlSpTolSat3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerTolSat, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolIllu;
	bSizerTolIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS )  );
	//m_txtCtrlTolIllu->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolIllu->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlTolIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolIllu1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpTolIllu1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlSpTolIllu1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolIllu2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
	m_txtCtrlSpTolIllu2->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlSpTolIllu2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );

	m_txtCtrlSpTolIllu3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTEXT_ALIGNMENT_CENTER | wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS ) );
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

void PanelSensor::OnPasteSet1(wxCommandEvent& event)
{
    /* Paste the name */
    if(!m_txtCtrlCurName->IsEmpty())
    {
        this->SetName_1(this->GetName());
    }
    /* Paste the wavelength */
    if(!m_txtCtrlCurWL->IsEmpty())
    {
        this->SetWavelength_1(this->GetWavelength());
    }
    /* Paste the current Saturation */
    if(!m_txtCtrlCurSat->IsEmpty())
    {
        this->SetSaturation_1(this->GetSaturation());
    }
    /* Paste the current illumination */
    if(!m_txtCtrlCurIllu->IsEmpty())
    {
        this->SetIllumination_1(this->GetIllumination());
    }
    /* Paste the default tolerances (Can be varied in Settings) */
    this->SetTolWavelength_1(this->GetTolWavelength());
    this->SetTolSaturation_1(this->GetTolSaturation());
    this->SetTolIllumination_1(this->GetTolIllumination());

    /* Paste the netX Data */
    this->SetPintype_1    (this->GetPintype());

    if(!m_txtCtrlCurPinNo->IsEmpty())
    {
        this->SetPinNumber_1  (this->GetPinNumber());
    }

    this->SetPinValue_1   (this->GetPinValue());
    this->SetPinDefValue_1(this->GetPinDefValue());


    /* Paste the current colour */
    this->SetColour_1(this->GetColour());



}

void PanelSensor::OnPasteSet2(wxCommandEvent& event)
{
    /* Paste the name */
    if(!m_txtCtrlCurName->IsEmpty())
    {
        this->SetName_2(this->GetName());
    }
    /* Paste the wavelength */
    if(!m_txtCtrlCurWL->IsEmpty())
    {
        this->SetWavelength_2(this->GetWavelength());
    }
    /* Paste the current Saturation */
    if(!m_txtCtrlCurSat->IsEmpty())
    {
        this->SetSaturation_2(this->GetSaturation());
    }
    /* Paste the current illumination */
    if(!m_txtCtrlCurIllu->IsEmpty())
    {
        this->SetIllumination_2(this->GetIllumination());
    }

    /* Paste the default tolerances (Can be varied in Settings) */
    this->SetTolWavelength_2(this->GetTolWavelength());
    this->SetTolSaturation_2(this->GetTolSaturation());
    this->SetTolIllumination_2(this->GetTolIllumination());

    /* Paste the netX Data */
    this->SetPintype_2    (this->GetPintype());

    if(!m_txtCtrlCurPinNo->IsEmpty())
    {
        this->SetPinNumber_2  (this->GetPinNumber());
    }

    this->SetPinValue_2   (this->GetPinValue());
    this->SetPinDefValue_2(this->GetPinDefValue());


    /* Paste the colour */
    this->SetColour_2(this->GetColour());

}

void PanelSensor::OnPasteSet3(wxCommandEvent& event)
{
    /* Paste the name */
    if(!m_txtCtrlCurName->IsEmpty())
    {
        this->SetName_3(this->GetName());
    }
    /* Paste the wavelength */
    if(!m_txtCtrlCurWL->IsEmpty())
    {
        this->SetWavelength_3(this->GetWavelength());
    }
    /* Paste the current Saturation */
    if(!m_txtCtrlCurSat->IsEmpty())
    {
        this->SetSaturation_3(this->GetSaturation());
    }
    /* Paste the current illumination */
    if(!m_txtCtrlCurIllu->IsEmpty())
    {
        this->SetIllumination_3(this->GetIllumination());
    }

    /* Paste the default tolerances (Can be varied in Settings) */
    this->SetTolWavelength_3(this->GetTolWavelength());
    this->SetTolSaturation_3(this->GetTolSaturation());
    this->SetTolIllumination_3(this->GetTolIllumination());

    /* Paste the netX Data */
    this->SetPintype_3    (this->GetPintype());


    if(!m_txtCtrlCurPinNo->IsEmpty())
    {
        this->SetPinNumber_3  (this->GetPinNumber());
    }

    this->SetPinValue_3   (this->GetPinValue());
    this->SetPinDefValue_3(this->GetPinDefValue());

    this->SetColour_3(this->GetColour());

}

void PanelSensor::OnClearSet1(wxCommandEvent& event)
{
    /* Empty all the entries in this row */
    m_txtCtrlSpName1->Clear();
    m_txtCtrlSpWL1->Clear();
    m_txtCtrlSpSat1->Clear();
    m_txtCtrlSpIllu1->Clear();
    this->SetColour_1(wxColour(0xff,0xff,0xff));
    m_chSpPintype1->SetSelection(4);
    m_choiceSpPinValue1->SetSelection(3);
    m_chSpDefPinValue1->SetSelection(3);
    m_txtCtrlSpTolNm1->Clear();
    m_txtCtrlSpTolSat1->Clear();
    m_txtCtrlSpTolIllu1->Clear();
    /* MISSING netX Data Defaults */
}

void PanelSensor::OnClearSet2(wxCommandEvent& event)
{
    /* Empty all the entries in this row */
    m_txtCtrlSpName2->Clear();
    m_txtCtrlSpWL2->Clear();
    m_txtCtrlSpSat2->Clear();
    m_txtCtrlSpIllu2->Clear();
    this->SetColour_2(wxColour(0xff,0xff,0xff));
    m_chSpPintype2->SetSelection(4);
    m_choiceSpPinValue2->SetSelection(3);
    m_chSpDefPinValue2->SetSelection(3);
    m_txtCtrlSpTolNm2->Clear();
    m_txtCtrlSpTolSat2->Clear();
    m_txtCtrlSpTolIllu2->Clear();
    /* MISSING netX Data Defaults */
}

void PanelSensor::OnClearSet3(wxCommandEvent& event)
{
    /* Empty all the entries in this row */
    m_txtCtrlSpName3->Clear();
    m_txtCtrlSpWL3->Clear();
    m_txtCtrlSpSat3->Clear();
    m_txtCtrlSpIllu3->Clear();
    this->SetColour_3(wxColour(0xff,0xff,0xff));
    m_chSpPintype3->SetSelection(4);
    m_choiceSpPinValue3->SetSelection(3);
    m_chSpDefPinValue3->SetSelection(3);
    m_txtCtrlSpTolNm2->Clear();
    m_txtCtrlSpTolSat2->Clear();
    m_txtCtrlSpTolIllu2->Clear();
    /* MISSING netX Data Defaults */
}

wxString PanelSensor::GetTestSet1(int iSensorIndex)
{
    int  iIndex = iSensorIndex % 16 + 1;
    bool komma = true;

    if(iIndex % 16 == 0) komma = false;

    wxString strTestSet1;

    if(komma)
    {
        if(m_txtCtrlSpName1->IsEmpty())
        {
            strTestSet1 = wxString::Format(wxT("[%2i] = { NO_TEST },"), iIndex);
        }
        else
        {
            strTestSet1 = wxString::Format(wxT("[%2i] = {name = \"%s\", nm = %3i, tol_nm = %2i, sat = %3i, tol_sat = %2i, lux = %5i, tol_lux = %4i},"),
                                           iIndex, this->Getname_1(), this->GetWavelength_1(), this->GetTolWavelength_1(),
                                           this->GetSaturation_1(), this->GetTolSaturation_1(), this->GetIllumination_1(),
                                           this->GetTolIllumination_1());
        }

    }

    if(!komma)
    {
        if(m_txtCtrlSpName1->IsEmpty())
        {
            strTestSet1 = wxString::Format(wxT("[%2i] = { NO_TEST }\n"), iIndex);
        }
        else
        {
            strTestSet1 = wxString::Format(wxT("[%2i] = {name = \"%s\", nm = %3i, tol_nm = %2i, sat = %3i, tol_sat = %2i, lux = %5i, tol_lux = %4i}\n"),
                                           this->Getname_1(), this->GetWavelength_1(), this->GetTolWavelength_1(),
                                           this->GetSaturation_1(), this->GetTolSaturation_1(), this->GetIllumination_1(),
                                           this->GetTolIllumination_1());
        }
    }

    return strTestSet1;

}

wxString PanelSensor::GetTestSet2(int iSensorIndex)
{
    int  iIndex = iSensorIndex % 16 + 1;
    bool komma = true;

    if(iIndex % 16 == 0) komma = false;

    wxString strTestSet2;

    if(komma)
    {
        if(m_txtCtrlSpName2->IsEmpty())
        {
            strTestSet2 = wxString::Format(wxT("[%2i] = { NO_TEST },"), iIndex);
        }
        else
        {
            strTestSet2 = wxString::Format(wxT("[%2i] = {name = \"%s\", nm = %3i, tol_nm = %2i, sat = %3i, tol_sat = %2i, lux = %5i, tol_lux = %4i},"),
                                           iIndex, this->Getname_2(), this->GetWavelength_2(), this->GetTolWavelength_2(),
                                           this->GetSaturation_2(), this->GetTolSaturation_2(), this->GetIllumination_2(),
                                           this->GetTolIllumination_2());
        }

    }

    if(!komma)
    {
        if(m_txtCtrlSpName2->IsEmpty())
        {
            strTestSet2 = wxString::Format(wxT("[%2i] = { NO_TEST }\n"), iIndex);
        }
        else
        {
            strTestSet2 = wxString::Format(wxT("[%2i] = {name = \"%s\", nm = %3i, tol_nm = %2i, sat = %3i, tol_sat = %2i, lux = %5i, tol_lux = %4i}"),
                                           iIndex, this->Getname_2(), this->GetWavelength_2(), this->GetTolWavelength_2(),
                                           this->GetSaturation_2(), this->GetTolSaturation_2(), this->GetIllumination_2(),
                                           this->GetTolIllumination_2());
        }
    }

    return strTestSet2;

}

wxString PanelSensor::GetTestSet3(int iSensorIndex)
{
    int  iIndex = iSensorIndex % 16 + 1;
    bool komma = true;

    if(iIndex % 16 == 0) komma = false;

    wxString strTestSet3;

    if(komma)
    {
        if(m_txtCtrlSpName3->IsEmpty())
        {
            strTestSet3 = wxString::Format(wxT("[%2i] = { NO_TEST },"), iIndex);
        }
        else
        {
            strTestSet3 = wxString::Format(wxT("[%2i] = {name = \"%s\", nm = %3i, tol_nm = %2i, sat = %3i, tol_sat = %2i, lux = %5i, tol_lux = %4i},"),
                                           iIndex, this->Getname_3(), this->GetWavelength_3(), this->GetTolWavelength_3(),
                                           this->GetSaturation_3(), this->GetTolSaturation_3(), this->GetIllumination_3(),
                                           this->GetTolIllumination_3());
        }

    }

    if(!komma)
    {
        if(m_txtCtrlSpName3->IsEmpty())
        {
            strTestSet3 = wxString::Format(wxT("[%2i] = { NO_TEST }\n"), iIndex);
        }
        else
        {
            strTestSet3 = wxString::Format(wxT("[%2i] = {name = \"%s\", nm = %3i, tol_nm = %2i, sat = %3i, tol_sat = %2i, lux = %5i, tol_lux = %4i}"),
                                           iIndex, this->Getname_3(), this->GetWavelength_3(), this->GetTolWavelength_3(),
                                           this->GetSaturation_3(), this->GetTolSaturation_3(), this->GetIllumination_3(),
                                           this->GetTolIllumination_3());
        }
    }

    return strTestSet3;

}

wxString PanelSensor::GetNetXData()
{

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
