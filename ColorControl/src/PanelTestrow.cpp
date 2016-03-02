#include "PanelTestrow.h"
#include "PanelSensor.h"


///////////////////////////////////////////////////////////////////////////

PanelTestrow::PanelTestrow( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, bool useNetX ) : wxPanel( parent, id, pos, size, style )
{

	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	wxBoxSizer* bSizervectorSensorPanel;
	bSizervectorSensorPanel = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerNo;
	bSizerNo = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerButtons1;
	bSizerButtons1 = new wxBoxSizer( wxHORIZONTAL );
	bSizerButtons1->SetMinSize(wxSize(90, -1));

	//m_cbUseSet = new wxCheckBox( this, wxID_ANY, wxT("Use"), wxDefaultPosition, wxDefaultSize, 0 );
	//bSizerButtons1->Add( m_cbUseSet, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_bpButtonRemove = new wxBitmapButton( this, wxIdManager::ReserveId(1), wxArtProvider::GetBitmap( wxART_MINUS ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonRemove->SetMaxSize( wxSize( 20,20 ) );
	bSizerButtons1->Add( m_bpButtonRemove, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP , 2 );

    bSizerButtons1->Add( 0, 0, 1, wxEXPAND, 5 );


	m_bpButtonPaste = new wxBitmapButton( this, wxIdManager::ReserveId(1), wxArtProvider::GetBitmap( wxART_PASTE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPaste->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons1->Add( m_bpButtonPaste, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP, 2 );

	m_bpButtonClear = new wxBitmapButton( this, wxIdManager::ReserveId(1), wxArtProvider::GetBitmap( wxART_MISSING_IMAGE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonClear->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons1->Add( m_bpButtonClear, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL |wxTOP | wxRIGHT , 2 );


	bSizerNo->Add( bSizerButtons1, 1, wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerNo, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerName;
	bSizerName = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER  );
	m_txtCtrlSpName->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlSpName, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerName, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerWL;
	bSizerWL = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpWL = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlSpWL->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlSpWL, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerWL, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerSat;
	bSizerSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlSpSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlSpSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerSat, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerIllu;
	bSizerIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlSpIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlSpIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerIllu, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerColor;
	bSizerColor = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpColor = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlSpColor->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlSpColor, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerColor, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPintype;
	bSizerPintype = new wxBoxSizer( wxVERTICAL );

	wxString m_chSpPintype1Choices[] = { wxT("GPIO"), wxT("HIFPIO"), wxT("MMIO"), wxT("PIO"), wxT("RDYRUN"), wxT("RSTOUT"), wxT("XMIO") };
	int m_chSpPintype1NChoices = sizeof( m_chSpPintype1Choices ) / sizeof( wxString );
	m_chSpPintype = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpPintype1NChoices, m_chSpPintype1Choices, 0 );
	m_chSpPintype->SetSelection( 0 );
	bSizerPintype->Add( m_chSpPintype, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerPintype, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinNo;
	bSizerPinNo = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpPinNo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlSpPinNo->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlSpPinNo, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerPinNo, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinValue;
	bSizerPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_choiceSpPinValue1Choices[] = { wxT("Input"), wxT("High"), wxT("Low") };
	int m_choiceSpPinValue1NChoices = sizeof( m_choiceSpPinValue1Choices ) / sizeof( wxString );
	m_choiceSpPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSpPinValue1NChoices, m_choiceSpPinValue1Choices, 0 );
	m_choiceSpPinValue->SetSelection( 0 );
	bSizerPinValue->Add( m_choiceSpPinValue, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerPinValue, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerDefPinValue;
	bSizerDefPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chSpDefPinValue1Choices[] = { wxT("Input"), wxT("High"), wxT("Low") };
	int m_chSpDefPinValue1NChoices = sizeof( m_chSpDefPinValue1Choices ) / sizeof( wxString );
	m_chSpDefPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpDefPinValue1NChoices, m_chSpDefPinValue1Choices, 0 );
	m_chSpDefPinValue->SetSelection( 0 );
	bSizerDefPinValue->Add( m_chSpDefPinValue, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerDefPinValue, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolNm;
	bSizerTolNm = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpTolNm = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlSpTolNm->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlSpTolNm, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerTolNm, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolSat;
	bSizerTolSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpTolSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlSpTolSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlSpTolSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerTolSat, 0, 0, 5 );


	bSizervectorSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolIllu;
	bSizerTolIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpTolIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlSpTolIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlSpTolIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizervectorSensorPanel->Add( bSizerTolIllu, 0, 0, 5 );

    if(!useNetX)
    {
        m_chSpPintype->Hide();
        m_txtCtrlSpPinNo->Hide();
        m_choiceSpPinValue->Hide();
        m_chSpDefPinValue->Hide();
    }



	this->SetSizer( bSizervectorSensorPanel );
	this->Layout();
	bSizervectorSensorPanel->Fit( this );


	// Connect Events
	m_bpButtonRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnButtonRemove ), NULL, this->GetParent() );
	m_bpButtonPaste->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnPasteSet ), NULL, this->GetParent() );
	m_bpButtonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnClearSet ), NULL, this->GetParent() );
}

void PanelTestrow::UpdateTestrowView(bool useNetX)
{
    if(useNetX)
    {
        m_chSpPintype->Show();
        m_txtCtrlSpPinNo->Show();
        m_choiceSpPinValue->Show();
        m_chSpDefPinValue->Show();
    }
    else
    {
        m_chSpPintype->Hide();
        m_txtCtrlSpPinNo->Hide();
        m_choiceSpPinValue->Hide();
        m_chSpDefPinValue->Hide();
    }

    this->Layout();
}

void PanelTestrow::ClearRow()
{
    m_txtCtrlSpName->Clear();
    m_txtCtrlSpWL->Clear();
    m_txtCtrlSpSat->Clear();
    m_txtCtrlSpIllu->Clear();
    m_txtCtrlSpColor->SetBackgroundColour( wxColour(0xff,0xff,0xff) );
    m_txtCtrlSpColor->Clear(); // To update the color
    m_chSpPintype->SetSelection(0);
    m_txtCtrlSpPinNo->Clear(),
    m_choiceSpPinValue->SetSelection(0);
    m_chSpDefPinValue->SetSelection(0);
    m_txtCtrlSpTolNm->Clear();
    m_txtCtrlSpTolSat->Clear();
    m_txtCtrlSpTolIllu->Clear();
}


PanelTestrow::~PanelTestrow()
{
	// Disconnect Events
	/* Remove allocated IDs */


	m_bpButtonRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnButtonRemove ), NULL, this->GetParent() );
	m_bpButtonPaste->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnPasteSet ), NULL, this->GetParent() );
	m_bpButtonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnClearSet ), NULL, this->GetParent() );

    //wxIdManager::UnreserveId(m_bpButtonRemove->GetId(), 1);
}
