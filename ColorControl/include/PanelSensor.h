#ifndef PANELSENSOR_H
#define PANELSENSOR_H


#include "../GUIFrame.h"
#include "PanelTestrow.h"


WX_DECLARE_HASH_MAP( wxWindowID, unsigned int, wxIntegerHash, wxIntegerEqual, Hash_wxWindowID_UnsignedLong );


///////////////////////////////////////////////////////////////////////////////
/// Class PanelSensor
///////////////////////////////////////////////////////////////////////////////
class PanelSensor : public wxPanel
{
	private:
	    int m_sensorNumber;
        wxBoxSizer* bSizerRows;
		wxTextCtrl* m_txtCtrlSensorNo;
		wxBitmapButton* m_bpButtonPlus;
		wxTextCtrl* m_txtCtrlCurName;
		wxTextCtrl* m_txtCtrlCurWL;
		wxTextCtrl* m_txtCtrlCurSat;
		wxTextCtrl* m_txtCtrlCurIllu;
		wxTextCtrl* m_txtCtrlCurColor;
		wxChoice* m_chCurPintype;
		wxTextCtrl* m_txtCtrlCurPinNo;
		wxChoice* m_chCurPinValue;
		wxChoice* m_chCurDefPinValue;
		wxTextCtrl* m_txtCtrlTolNm;
		wxTextCtrl* m_txtCtrlTolSat;
		wxTextCtrl* m_txtCtrlTolIllu;

		unsigned char m_integration;
		unsigned char m_gain;

		wxVector<PanelTestrow*> m_vectorTestrow;
		Hash_wxWindowID_UnsignedLong m_hashRemove;
		Hash_wxWindowID_UnsignedLong m_hashClear;
		Hash_wxWindowID_UnsignedLong m_hashPaste;


    public:
        wxBitmapButton* GetpButtonAdd() {return m_bpButtonPlus;};
        wxVector<PanelTestrow*> GetVectorTestrow(){return m_vectorTestrow; };

        int      GetSensorNumber()      {return wxAtoi(m_txtCtrlSensorNo->GetValue());};
        wxString GetName()              {return m_txtCtrlCurName->GetValue();};
        void SetName(wxString name)     {m_txtCtrlCurName->Clear();
                                         m_txtCtrlCurName->SetValue(name);};
        int GetWavelength()             {return wxAtoi(m_txtCtrlCurWL->GetValue());};
        int GetTolWavelength()          {return wxAtoi(m_txtCtrlTolNm->GetValue());};
        void SetWavelength(int wl)      {m_txtCtrlCurWL->SetValue(wxString::Format(wxT("%i"), wl));};
        void SetTolWavelength(int tolnm){m_txtCtrlTolNm->SetValue(wxString::Format(wxT("%i"), tolnm));}
        int GetSaturation()             {return wxAtoi(m_txtCtrlCurSat->GetValue()); };
        int GetTolSaturation()          {return wxAtoi(m_txtCtrlTolSat->GetValue()); };
        void SetSaturation(int sat)      {m_txtCtrlCurSat->SetValue(wxString::Format(wxT("%i"), sat));};
        void SetTolSaturation(int tolsat){m_txtCtrlTolSat->SetValue(wxString::Format(wxT("%i"), tolsat));};
        int GetIllumination()              {return wxAtoi(m_txtCtrlCurIllu->GetValue());};
        int GetTolIllumination()           {return wxAtoi(m_txtCtrlTolIllu->GetValue());};
        void SetIllumination(int illu)     {m_txtCtrlCurIllu->SetValue(wxString::Format(wxT("%i"), illu));};
        void SetTolIllumination(int tolillu){m_txtCtrlTolIllu->SetValue(wxString::Format(wxT("%i"), tolillu));};
        void SetColour(wxColour colour)    {m_txtCtrlCurColor->SetBackgroundColour(colour);
                                            m_txtCtrlCurColor->Clear();};
        wxColour GetColour()               {return m_txtCtrlCurColor->GetBackgroundColour();};
        int GetPintype()                   {return m_chCurPintype->GetSelection();};
        wxString GetPintype(int iIndex)    {return m_chCurPintype->GetString(iIndex);};
        void SetPintype(int iSelection)    {m_chCurPintype->SetSelection(iSelection);};
        int GetPinNumber()                 {return wxAtoi(m_txtCtrlCurPinNo->GetValue());}
        void SetPinNumber(int iNumber)     {m_txtCtrlCurPinNo->SetValue(wxString::Format(wxT("%i"), iNumber));};
        bool IsPinnumberEmpty()            {return m_txtCtrlCurPinNo->IsEmpty();};
		int GetPinValue()                  {return m_chCurPinValue->GetSelection(); };
        void SetPinValue(int iValue)       {m_chCurPinValue->SetSelection(iValue);};
        int GetPinDefValue()                {return m_chCurDefPinValue->GetSelection(); };
        void SetPinDefValue(int iDefValue)  {m_chCurDefPinValue->SetSelection(iDefValue);};

        void SetIntegration(unsigned char ucIntegration){m_integration = ucIntegration;};
        void SetGain(unsigned char ucGain) {m_gain = ucGain;};
        unsigned char  GetIntegration()       {return m_integration;};
        unsigned char  GetGain()              {return m_gain;};

        /* Test Generation */
        wxString GetTestrow(int iSensorIndex, int iRowVectorIndex);
        wxString GetEmptyTestrow(int iSensorIndex);
        wxString GetAtPinsUnderTest(bool lastEntry);
        wxString GetPinStateTestSet(int iIndexTestSet);
        wxString GetSettingsrow(int iSensorIndex);
        bool NameMoreThanTwice(const wxArrayString astrCurName, const wxString strCurName);
        bool IsLastNameEntryWithoutRepetition(int iCurIndex);


        void OnAddTestRow( wxCommandEvent& event );
		void OnButtonRemove( wxCommandEvent& event );
        void OnClearSet( wxCommandEvent& event);
        void OnPasteSet( wxCommandEvent& event);




		PanelSensor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL, int sensornumber = 0 );
		~PanelSensor();

};



#endif // PANELSENSOR_H
