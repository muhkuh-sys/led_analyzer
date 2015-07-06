///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PanelSensor.h"

///////////////////////////////////////////////////////////////////////////

PanelSensor::PanelSensor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, int sensornumber ) : wxPanel( parent, id, pos, size, style )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

    m_sensorNumber = sensornumber;

	bSizerRows = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerCurSensor;
	bSizerCurSensor = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerNo;
	bSizerNo = new wxBoxSizer( wxVERTICAL );
    bSizerNo->SetMinSize(wxSize(80, -1));

	wxBoxSizer* bSizerSensorNumber;
	bSizerSensorNumber = new wxBoxSizer( wxHORIZONTAL );

	m_txtCtrlSensorNo = new wxTextCtrl( this, wxID_ANY, wxString::Format(wxT("%i"), sensornumber), wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER | wxTE_READONLY );
	m_txtCtrlSensorNo->SetMaxSize( wxSize( 32,-1 ) );

	bSizerSensorNumber->Add( m_txtCtrlSensorNo, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    bSizerSensorNumber->Add( 0, 0, 1, wxEXPAND, 5 );

	m_bpButtonPlus = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PLUS  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPlus->SetMaxSize( wxSize( 20,20 ) );

	bSizerSensorNumber->Add( m_bpButtonPlus, 1, wxLEFT|wxALIGN_CENTER, 5 );


	bSizerNo->Add( bSizerSensorNumber, 1, wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerNo, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerName;
	bSizerName = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurName->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlCurName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 2 );


	bSizerCurSensor->Add( bSizerName, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerWL;
	bSizerWL = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurWL = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurWL->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlCurWL, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerWL, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerSat;
	bSizerSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlCurSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerSat, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerIllu;
	bSizerIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlCurIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerIllu, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerColor;
	bSizerColor = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurColor = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurColor->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlCurColor, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerColor, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPintype;
	bSizerPintype = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurPintypeChoices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO") };
	int m_chCurPintypeNChoices = sizeof( m_chCurPintypeChoices ) / sizeof( wxString );
	m_chCurPintype = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurPintypeNChoices, m_chCurPintypeChoices, 0 );
	m_chCurPintype->SetSelection( 0 );
	bSizerPintype->Add( m_chCurPintype, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );


	bSizerCurSensor->Add( bSizerPintype, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinNo;
	bSizerPinNo = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurPinNo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlCurPinNo->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlCurPinNo, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerPinNo, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinValue;
	bSizerPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurPinValueChoices[] = { wxT("0"), wxT("1") };
	int m_chCurPinValueNChoices = sizeof( m_chCurPinValueChoices ) / sizeof( wxString );
	m_chCurPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurPinValueNChoices, m_chCurPinValueChoices, 0 );
	m_chCurPinValue->SetSelection( 0 );
	bSizerPinValue->Add( m_chCurPinValue, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );


	bSizerCurSensor->Add( bSizerPinValue, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerDefPinValue;
	bSizerDefPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurDefPinValueChoices[] = { wxT("0"), wxT("1") };
	int m_chCurDefPinValueNChoices = sizeof( m_chCurDefPinValueChoices ) / sizeof( wxString );
	m_chCurDefPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurDefPinValueNChoices, m_chCurDefPinValueChoices, 0 );
	m_chCurDefPinValue->SetSelection( 0 );
	bSizerDefPinValue->Add( m_chCurDefPinValue, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );


	bSizerCurSensor->Add( bSizerDefPinValue, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolNm;
	bSizerTolNm = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolNm = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlTolNm->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolNm->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolNm->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlTolNm, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerTolNm, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolSat;
	bSizerTolSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlTolSat->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolSat->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlTolSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerTolSat, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolIllu;
	bSizerTolIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlTolIllu->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_txtCtrlTolIllu->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_txtCtrlTolIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlTolIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerTolIllu, 0, 0, 5 );


	bSizerRows->Add( bSizerCurSensor, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerRows );
	this->Layout();
	bSizerRows->Fit( this );

	// Connect Events
	m_bpButtonPlus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnAddTestRow ), NULL, this );
}



PanelSensor::~PanelSensor()
{
	// Disconnect Events
	m_bpButtonPlus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnAddTestRow ), NULL, this );

}

void PanelSensor::OnAddTestRow(wxCommandEvent& event)
{
    this->GetParent()->Hide();

    int iCurVectorSize = m_vectorTestrow.size();
    m_vectorTestrow.push_back(new PanelTestrow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, m_sensorNumber, iCurVectorSize  ));
    bSizerRows->Add(m_vectorTestrow.at(m_vectorTestrow.size()-1), 1, wxEXPAND, 5);

    m_hashRemove[m_vectorTestrow.back()->GetButtonRemoveId()] = (m_vectorTestrow.size()-1);

    wxLogMessage("key id: %d", m_vectorTestrow.back()->GetButtonRemoveId());

    wxLogMessage("value: %d",  m_hashRemove[m_vectorTestrow.back()->GetButtonRemoveId()]);


// iterate over all the elements in the class
Hash_wxWindowID_UnsignedLong::iterator it;
int key, value;

for( it = m_hashRemove.begin(); it != m_hashRemove.end(); ++it )
{
    key = it->first;
    value = it->second;
    wxLogMessage("key: %d value: %d", key, value);

}

    this->GetParent()->FitInside();
    this->GetParent()->Layout();
    this->GetParent()->Show();
}

void PanelSensor::OnButtonRemove( wxCommandEvent& event)
{
    //wxLogMessage("event.GetId(): %d", event.GetId());

    Hash_wxWindowID_UnsignedLong::iterator it;
    int key, value;
    for( it = m_hashRemove.begin(); it != m_hashRemove.end(); ++it )
    {
        key = it->first;
        value = it->second;
        wxLogMessage("key: %d value: %d", key, value);

    }

}

///////////////////////////////////////////////////////////////////////////

PanelTestrow::PanelTestrow( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, unsigned int sensor, unsigned int vectorsize ) : wxPanel( parent, id, pos, size, style )
{
	Hash_wxWindowID_UnsignedLong myHashRemove;

	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );

	wxBoxSizer* bSizerSensorPanel;
	bSizerSensorPanel = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerNo;
	bSizerNo = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerButtons1;
	bSizerButtons1 = new wxBoxSizer( wxHORIZONTAL );

	m_cbUseSet1 = new wxCheckBox( this, wxID_ANY, wxT("Use"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons1->Add( m_cbUseSet1, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_bpButtonPaste = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PASTE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPaste->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons1->Add( m_bpButtonPaste, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP, 2 );

	m_bpButtonClear = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_MISSING_IMAGE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonClear->SetMaxSize( wxSize( 20,20 ) );

	bSizerButtons1->Add( m_bpButtonClear, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL |wxTOP, 2 );

	m_bpButtonRemove = new wxBitmapButton( this, wxIdManager::ReserveId(1), wxArtProvider::GetBitmap( wxART_MINUS ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonRemove->SetMaxSize( wxSize( 20,20 ) );



	bSizerButtons1->Add( m_bpButtonRemove, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL | wxLEFT|wxTOP, 2 );


	bSizerNo->Add( bSizerButtons1, 1, wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerNo, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerName;
	bSizerName = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpName1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpName1->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlSpName1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerName, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerWL;
	bSizerWL = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpWL1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpWL1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlSpWL1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerWL, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerSat;
	bSizerSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpSat1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpSat1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlSpSat1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerSat, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerIllu;
	bSizerIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpIllu1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpIllu1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlSpIllu1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerIllu, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerColor;
	bSizerColor = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpColor1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpColor1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerColor->Add( m_txtCtrlSpColor1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerColor, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPintype;
	bSizerPintype = new wxBoxSizer( wxVERTICAL );

	wxString m_chSpPintype1Choices[] = { wxT("MMIO"), wxT("XMIO"), wxT("GPIO"), wxT("PIO"), wxEmptyString };
	int m_chSpPintype1NChoices = sizeof( m_chSpPintype1Choices ) / sizeof( wxString );
	m_chSpPintype1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpPintype1NChoices, m_chSpPintype1Choices, 0 );
	m_chSpPintype1->SetSelection( 0 );
	bSizerPintype->Add( m_chSpPintype1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPintype, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinNo;
	bSizerPinNo = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpPinNo1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpPinNo1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlSpPinNo1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPinNo, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinValue;
	bSizerPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_choiceSpPinValue1Choices[] = { wxT("0"), wxT("1") };
	int m_choiceSpPinValue1NChoices = sizeof( m_choiceSpPinValue1Choices ) / sizeof( wxString );
	m_choiceSpPinValue1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSpPinValue1NChoices, m_choiceSpPinValue1Choices, 0 );
	m_choiceSpPinValue1->SetSelection( 0 );
	bSizerPinValue->Add( m_choiceSpPinValue1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerPinValue, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerDefPinValue;
	bSizerDefPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chSpDefPinValue1Choices[] = { wxT("0"), wxT("1") };
	int m_chSpDefPinValue1NChoices = sizeof( m_chSpDefPinValue1Choices ) / sizeof( wxString );
	m_chSpDefPinValue1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chSpDefPinValue1NChoices, m_chSpDefPinValue1Choices, 0 );
	m_chSpDefPinValue1->SetSelection( 0 );
	bSizerDefPinValue->Add( m_chSpDefPinValue1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerDefPinValue, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolNm;
	bSizerTolNm = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpTolNm1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolNm1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlSpTolNm1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerTolNm, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolSat;
	bSizerTolSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpTolSat1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolSat1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlSpTolSat1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerTolSat, 0, 0, 5 );


	bSizerSensorPanel->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolIllu;
	bSizerTolIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlSpTolIllu1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCtrlSpTolIllu1->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolIllu->Add( m_txtCtrlSpTolIllu1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerSensorPanel->Add( bSizerTolIllu, 0, 0, 5 );



	this->SetSizer( bSizerSensorPanel );
	this->Layout();
	bSizerSensorPanel->Fit( this );


	// Connect Events
	m_bpButtonRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnButtonRemove ), NULL, this );
	m_bpButtonPaste->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelTestrow::OnPasteSet ), NULL, this );
	m_bpButtonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelTestrow::OnClearSet ), NULL, this );
}

PanelTestrow::~PanelTestrow()
{
	// Disconnect Events
	/* Remove allocated IDs */
    //wxIdManager::UnreserveId(m_bpButtonRemove->GetId(), 1);

	m_bpButtonRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSensor::OnButtonRemove ), NULL, this );
	m_bpButtonPaste->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelTestrow::OnPasteSet ), NULL, this );
	m_bpButtonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelTestrow::OnClearSet ), NULL, this );

}



