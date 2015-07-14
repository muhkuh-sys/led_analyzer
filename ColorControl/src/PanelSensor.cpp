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
    bSizerNo->SetMinSize(wxSize(90, -1));

	wxBoxSizer* bSizerSensorNumber;
	bSizerSensorNumber = new wxBoxSizer( wxHORIZONTAL );

	m_txtCtrlSensorNo = new wxTextCtrl( this, wxID_ANY, wxString::Format(wxT("%i"), sensornumber), wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER | wxTE_READONLY );
	m_txtCtrlSensorNo->SetMaxSize( wxSize( 42,-1 ) );




	m_bpButtonPlus = new wxBitmapButton( this, wxID_ANY, wxArtProvider::GetBitmap( wxART_PLUS  ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPlus->SetMaxSize( wxSize( 20,20 ) );

	bSizerSensorNumber->Add( m_bpButtonPlus, 1, wxLEFT|wxALIGN_CENTER, 2 );
    bSizerSensorNumber->Add( 0, 0, 1,wxEXPAND, 5 );
    bSizerSensorNumber->Add( m_txtCtrlSensorNo, 0, wxALIGN_RIGHT | wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL, 2 );



	bSizerNo->Add( bSizerSensorNumber, 1, wxALIGN_CENTER_HORIZONTAL, 2 );
	bSizerCurSensor->Add( bSizerNo, 0, 0, 5 );
	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerName;
	bSizerName = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER );
	m_txtCtrlCurName->SetMaxSize( wxSize( 70,-1 ) );

	bSizerName->Add( m_txtCtrlCurName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 2 );


	bSizerCurSensor->Add( bSizerName, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerWL;
	bSizerWL = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurWL = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlCurWL->SetMaxSize( wxSize( 50,-1 ) );

	bSizerWL->Add( m_txtCtrlCurWL, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerWL, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerSat;
	bSizerSat = new wxBoxSizer( wxVERTICAL );



	m_txtCtrlCurSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS)  );
	m_txtCtrlCurSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerSat->Add( m_txtCtrlCurSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerSat, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerIllu;
	bSizerIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlCurIllu->SetMaxSize( wxSize( 50,-1 ) );

	bSizerIllu->Add( m_txtCtrlCurIllu, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerIllu, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerColor;
	bSizerColor = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlCurColor = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY );
	m_txtCtrlCurColor->SetMaxSize( wxSize( 50,-1 ) );
    m_txtCtrlCurColor->SetBackgroundColour( wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW ) );

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

	m_txtCtrlCurPinNo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER, wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlCurPinNo->SetMaxSize( wxSize( 50,-1 ) );

	bSizerPinNo->Add( m_txtCtrlCurPinNo, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerPinNo, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerPinValue;
	bSizerPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurPinValueChoices[] = { wxT("Input"), wxT("High"), wxT("Low") };
	int m_chCurPinValueNChoices = sizeof( m_chCurPinValueChoices ) / sizeof( wxString );
	m_chCurPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurPinValueNChoices, m_chCurPinValueChoices, 0 );
	m_chCurPinValue->SetSelection( 0 );
	bSizerPinValue->Add( m_chCurPinValue, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );


	bSizerCurSensor->Add( bSizerPinValue, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerDefPinValue;
	bSizerDefPinValue = new wxBoxSizer( wxVERTICAL );

	wxString m_chCurDefPinValueChoices[] = { wxT("Input"), wxT("High"), wxT("Low") };
	int m_chCurDefPinValueNChoices = sizeof( m_chCurDefPinValueChoices ) / sizeof( wxString );
	m_chCurDefPinValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chCurDefPinValueNChoices, m_chCurDefPinValueChoices, 0 );
	m_chCurDefPinValue->SetSelection( 0 );
	bSizerDefPinValue->Add( m_chCurDefPinValue, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );


	bSizerCurSensor->Add( bSizerDefPinValue, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolNm;
	bSizerTolNm = new wxBoxSizer( wxVERTICAL );
	m_txtCtrlTolNm = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER | wxTE_READONLY , wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlTolNm->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolNm->Add( m_txtCtrlTolNm, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerTolNm, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolSat;
	bSizerTolSat = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolSat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER | wxTE_READONLY , wxTextValidator(wxFILTER_DIGITS) );
	m_txtCtrlTolSat->SetMaxSize( wxSize( 50,-1 ) );

	bSizerTolSat->Add( m_txtCtrlTolSat, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 2 );


	bSizerCurSensor->Add( bSizerTolSat, 0, 0, 5 );


	bSizerCurSensor->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTolIllu;
	bSizerTolIllu = new wxBoxSizer( wxVERTICAL );

	m_txtCtrlTolIllu = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTER | wxTE_READONLY  , wxTextValidator(wxFILTER_DIGITS) );

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
    int iCurVectorSize;

    m_vectorTestrow.push_back(new PanelTestrow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL ));

    iCurVectorSize = m_vectorTestrow.size();

    bSizerRows->Add(m_vectorTestrow.at(iCurVectorSize-1), 1, wxEXPAND, 5);

    /* Hash the remove Button ID */
    m_hashRemove[m_vectorTestrow.back()->GetButtonRemoveID()] = (iCurVectorSize-1);
    /* Hash the clear button ID */
    m_hashClear[m_vectorTestrow.back()->GetButtonClearID()] = (iCurVectorSize-1);
    /* Hash the paste button ID */
    m_hashPaste[m_vectorTestrow.back()->GetButtonPasteID()] = (iCurVectorSize-1);

    this->GetParent()->FitInside();
    this->GetParent()->Layout();
    this->GetParent()->Show();
}

void PanelSensor::OnButtonRemove( wxCommandEvent& event )
{
    /* Get the index of the vector to be deleted */
    int iVectorIndex = m_hashRemove[event.GetId()];

    /* Remove the item in the vector */
    /*
    wxMessageDialog MyRequestDialog(this, wxT("Do you really want to destroy the row? All entries will be lost."), wxT("Please Confirm"),
                                    wxOK | wxCANCEL);

    if(MyRequestDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    */

    /* Destroy the panel */
    m_vectorTestrow.at(iVectorIndex)->Destroy();

    /* Clear all hashes for this panel */
    m_hashClear.erase(m_vectorTestrow.at(iVectorIndex)->GetButtonClearID());

    m_hashPaste.erase(m_vectorTestrow.at(iVectorIndex)->GetButtonPasteID());

    m_hashRemove.erase(event.GetId());

    /* Remove the item from the vector */
    m_vectorTestrow.erase(iVectorIndex);

    /* First delete all existent hashes as the assignment to the vector index has changed */
    m_hashClear.clear();
    m_hashPaste.clear();
    m_hashRemove.clear();

    int iNewVectorIndex = 0;
    /* Refill the hash table with the right value for the new vector index */
    for(wxVector<PanelTestrow*>::iterator it=m_vectorTestrow.begin(); it != m_vectorTestrow.end(); it++)
    {
        m_hashRemove[(*it)->GetButtonRemoveID()] = iNewVectorIndex;
        m_hashClear[(*it)->GetButtonClearID()] = iNewVectorIndex;
        m_hashPaste[(*it)->GetButtonPasteID()] = iNewVectorIndex;
        iNewVectorIndex++;
    }

    /* Update the View */
    this->GetParent()->FitInside();
    this->GetParent()->Layout();

}

void PanelSensor::OnClearSet ( wxCommandEvent& event)
{
    /* Get the index of the vector to be deleted */
    int iVectorIndex = m_hashClear[event.GetId()];

    m_vectorTestrow.at(iVectorIndex)->ClearRow();

    /* Update the View */
    this->GetParent()->FitInside();
    this->GetParent()->Layout();
}


void PanelSensor::OnPasteSet ( wxCommandEvent& event)
{
    /* Get the index of the vector to be deleted */
    int iVectorIndex = m_hashPaste[event.GetId()];

    /* Name */
    if(!this->GetName().IsEmpty())
    m_vectorTestrow.at(iVectorIndex)->SetName(this->GetName());
    /* Wavelength */
    m_vectorTestrow.at(iVectorIndex)->SetWavelength(this->GetWavelength());
    /* Saturation */
    m_vectorTestrow.at(iVectorIndex)->SetSaturation(this->GetSaturation());
    /* Illumination */
    m_vectorTestrow.at(iVectorIndex)->SetIllumination(this->GetIllumination());
    /* Colour */
    m_vectorTestrow.at(iVectorIndex)->SetColour(this->GetColour());
    /* Pintype */
    m_vectorTestrow.at(iVectorIndex)->SetPintype(this->GetPintype());
    /* Pin Number */
    if(!this->m_txtCtrlCurPinNo->IsEmpty())
    m_vectorTestrow.at(iVectorIndex)->SetPinNumber(this->GetPinNumber());
    /* Pin Value */
    m_vectorTestrow.at(iVectorIndex)->SetPinValue(this->GetPinValue());
    /* Pin Default Value */
    m_vectorTestrow.at(iVectorIndex)->SetPinDefValue(this->GetPinDefValue());
    /* Tolerance Wavelength */
    m_vectorTestrow.at(iVectorIndex)->SetTolWavelength(this->GetTolWavelength());
    /* Tolerance Saturation */
    m_vectorTestrow.at(iVectorIndex)->SetTolSaturation(this->GetTolSaturation());
    /* Tolerance Illumination */
    m_vectorTestrow.at(iVectorIndex)->SetTolIllumination(this->GetTolIllumination());


    /* Update the View */
    this->GetParent()->FitInside();
    this->GetParent()->Layout();
}


wxString PanelSensor::GetTestrow(int iSensorIndex, int iRowVectorIndex)
{
    int iIndex     = iSensorIndex % 16 +1;
    bool needKomma = true;

    wxString    strTestRow;

    /* The last sensor entry (sensor[16] doesnt need a komma) */
    if(iIndex % 16 == 0) needKomma = false;


    if(needKomma)
    {
            strTestRow = wxString::Format(wxT("     [%2i] = {name = \"%s\", nm = %3i, tol_nm = %2i, sat = %3i, tol_sat = %2i, lux = %5i, tol_lux = %4i},"),
                                           iIndex, m_vectorTestrow.at(iRowVectorIndex)->GetName() , m_vectorTestrow.at(iRowVectorIndex)->GetWavelength(),
                                           m_vectorTestrow.at(iRowVectorIndex)->GetTolWavelength(), m_vectorTestrow.at(iRowVectorIndex)->GetSaturation(),
                                           m_vectorTestrow.at(iRowVectorIndex)->GetTolSaturation(), m_vectorTestrow.at(iRowVectorIndex)->GetIllumination(),
                                           m_vectorTestrow.at(iRowVectorIndex)->GetTolIllumination());
    }

    else
    {
            strTestRow = wxString::Format(wxT("     [%2i] = {name = \"%s\", nm = %3i, tol_nm = %2i, sat = %3i, tol_sat = %2i, lux = %5i, tol_lux = %4i}"),
                                           iIndex, m_vectorTestrow.at(iRowVectorIndex)->GetName() , m_vectorTestrow.at(iRowVectorIndex)->GetWavelength(),
                                           m_vectorTestrow.at(iRowVectorIndex)->GetTolWavelength(), m_vectorTestrow.at(iRowVectorIndex)->GetSaturation(),
                                           m_vectorTestrow.at(iRowVectorIndex)->GetTolSaturation(), m_vectorTestrow.at(iRowVectorIndex)->GetIllumination(),
                                           m_vectorTestrow.at(iRowVectorIndex)->GetTolIllumination());
    }

    return strTestRow;
}


wxString PanelSensor::GetEmptyTestrow(int iSensorIndex)
{
    int iIndex     = iSensorIndex % 16 + 1;
    bool needKomma = true;

    wxString    strTestRow;

    /* The last sensor entry (sensor[16] doesnt need a komma) */
    if(iIndex % 16 == 0) needKomma = false;

    if(needKomma)
    {
            strTestRow = wxString::Format(wxT("     [%2i] =  nil , -- NO TEST ! NO TEST ! NO TEST ! -- "), iIndex);
    }

    else
    {
            strTestRow = wxString::Format(wxT("     [%2i] =  nil   -- NO TEST ! NO TEST ! NO TEST ! -- "), iIndex);
    }

    return strTestRow;
}

wxString PanelSensor::GetAtPinsUnderTest(bool isLastEntry)
{
    wxString      strPinsUnderTest;
    wxArrayString astrCurNames;
    wxString      strCurName;

    strPinsUnderTest += wxString::Format(wxT("  --- Sensor %2d ---\n"), this->GetSensorNumber());

    if(isLastEntry)
    {
        for(int i = 0; i < m_vectorTestrow.size(); i++)
        {
            strCurName = m_vectorTestrow.at(i)->GetName();
            if(!this->NameMoreThanTwice(astrCurNames, strCurName ))
            {
                astrCurNames.Add(strCurName);

                /* If we have the last testentry or all following entries have the same name we need no comma */

                if(i ==  (m_vectorTestrow.size() - 1))
                {
                    strPinsUnderTest += wxString::Format(wxT("  { \"%s\", io_matrix.PINTYPE_%s, %3d, %2d, io_matrix.PINFLAG_IOZ }\n"),
                                            strCurName, m_vectorTestrow.at(i)->GetPintype(m_vectorTestrow.at(i)->GetPintype()),
                                            m_vectorTestrow.at(i)->GetPinNumber(), m_vectorTestrow.at(i)->GetPinDefValue());
                }
                else
                {
                    if(this->IsLastNameEntryWithoutRepetition(i))
                    {
                        strPinsUnderTest += wxString::Format(wxT("  { \"%s\", io_matrix.PINTYPE_%s, %3d, %2d, io_matrix.PINFLAG_IOZ }\n"),
                                                strCurName, m_vectorTestrow.at(i)->GetPintype(m_vectorTestrow.at(i)->GetPintype()),
                                                m_vectorTestrow.at(i)->GetPinNumber(), m_vectorTestrow.at(i)->GetPinDefValue());
                    }
                    else
                    {
                        strPinsUnderTest += wxString::Format(wxT("  { \"%s\", io_matrix.PINTYPE_%s, %3d, %2d, io_matrix.PINFLAG_IOZ },\n"),
                                                strCurName, m_vectorTestrow.at(i)->GetPintype(m_vectorTestrow.at(i)->GetPintype()),
                                                m_vectorTestrow.at(i)->GetPinNumber(), m_vectorTestrow.at(i)->GetPinDefValue());
                    }
                }

            }

        }
    }

    else
    {
        for(int i = 0; i < m_vectorTestrow.size(); i++)
        {
            strCurName = m_vectorTestrow.at(i)->GetName();
            if(!this->NameMoreThanTwice(astrCurNames, strCurName ))
            {
                astrCurNames.Add(strCurName);
                strPinsUnderTest += wxString::Format(wxT("  { \"%s\", io_matrix.PINTYPE_%s, %3d, %2d, io_matrix.PINFLAG_IOZ },\n"),
                                        strCurName, m_vectorTestrow.at(i)->GetPintype(m_vectorTestrow.at(i)->GetPintype()),
                                        m_vectorTestrow.at(i)->GetPinNumber(), m_vectorTestrow.at(i)->GetPinDefValue());
            }

        }
    }


    return strPinsUnderTest;
}

bool PanelSensor::NameMoreThanTwice(const wxArrayString astrstrCurNames, const wxString strCurName)
{
    for(int i = 0; i < astrstrCurNames.GetCount(); i++)
    {
        if (astrstrCurNames.Item(i).IsSameAs(strCurName)) return true;
    }
    return false;
}

bool PanelSensor::IsLastNameEntryWithoutRepetition(int iCurIndex)
{
    wxString strCurName = m_vectorTestrow.at(iCurIndex)->GetName();

    for(int i = iCurIndex+1; i < m_vectorTestrow.size(); i++)
    {
        if (!m_vectorTestrow.at(i)->GetName().IsSameAs(strCurName)) return false;
    }

    return true;

}

wxString PanelSensor::GetPinStateTestSet(int iIndexTestSet)
{

    return wxString::Format(wxT("   io_matrix.set_pin(aAttr, \"%s\", %d)"),
                                m_vectorTestrow.at(iIndexTestSet)->GetName(),
                                m_vectorTestrow.at(iIndexTestSet)->GetPinValue());

}
