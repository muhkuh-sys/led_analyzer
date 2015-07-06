#ifndef PANELSENSOR_H
#define PANELSENSOR_H


#include "../GUIFrame.h"


WX_DECLARE_HASH_MAP( wxWindowID, unsigned int, wxIntegerHash, wxIntegerEqual, Hash_wxWindowID_UnsignedLong );

///////////////////////////////////////////////////////////////////////////////
/// Class PanelTestrow
///////////////////////////////////////////////////////////////////////////////
class PanelTestrow : public wxPanel
{
	private:
		wxCheckBox* m_cbUseSet1;
		wxBitmapButton* m_bpButtonRemove;
		wxBitmapButton* m_bpButtonPaste;
		wxBitmapButton* m_bpButtonClear;
		wxTextCtrl* m_txtCtrlSpName1;
		wxTextCtrl* m_txtCtrlSpWL1;
		wxTextCtrl* m_txtCtrlSpSat1;
		wxTextCtrl* m_txtCtrlSpIllu1;
		wxTextCtrl* m_txtCtrlSpColor1;
		wxChoice* m_chSpPintype1;
		wxTextCtrl* m_txtCtrlSpPinNo1;
		wxChoice* m_choiceSpPinValue1;
		wxChoice* m_chSpDefPinValue1;
		wxTextCtrl* m_txtCtrlSpTolNm1;
		wxTextCtrl* m_txtCtrlSpTolSat1;
		wxTextCtrl* m_txtCtrlSpTolIllu1;




		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPasteSet    ( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearSet    ( wxCommandEvent& event ) { event.Skip(); }


	public:

		PanelTestrow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL, unsigned int sensornumber = 0, unsigned int vectorsize = 0 );
        wxWindowID GetButtonRemoveId(){return m_bpButtonRemove->GetId();};

		~PanelTestrow();

};



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

		wxVector<PanelTestrow*> m_vectorTestrow;
		Hash_wxWindowID_UnsignedLong m_hashRemove;

    public:
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
        void SetPintype(int iSelection)    {m_chCurPintype->SetSelection(iSelection);};
        int GetPinNumber()                 {return wxAtoi(m_txtCtrlCurPinNo->GetValue());}
        void SetPinNumber(int iNumber)     {m_txtCtrlCurPinNo->SetValue(wxString::Format(wxT("%i"), iNumber));};
		int GetPinValue()                  {return m_chCurPinValue->GetSelection(); };
        void SetPinValue(int iValue)       {m_chCurPinValue->SetSelection(iValue);};
        int GetPinDefValue()                {return m_chCurDefPinValue->GetSelection(); };
        void SetPinDefValue(int iDefValue)  {m_chCurDefPinValue->SetSelection(iDefValue);};

		void OnAddTestRow( wxCommandEvent& event );
		void OnButtonRemove( wxCommandEvent& event );

	public:

		PanelSensor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL, int sensornumber = 0 );
		~PanelSensor();

};



#endif // PANELSENSOR_H
