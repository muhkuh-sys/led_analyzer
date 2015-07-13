#ifndef PANELTESTROW_H
#define PANELTESTROW_H

#include "../GUIFrame.h"

///////////////////////////////////////////////////////////////////////////////
/// Class PanelTestrow
///////////////////////////////////////////////////////////////////////////////

class PanelTestrow : public wxPanel
{
	private:
		wxCheckBox* m_cbUseSet;
		wxBitmapButton* m_bpButtonRemove;
		wxBitmapButton* m_bpButtonPaste;
		wxBitmapButton* m_bpButtonClear;
		wxTextCtrl* m_txtCtrlSpName;
		wxTextCtrl* m_txtCtrlSpWL;
		wxTextCtrl* m_txtCtrlSpSat;
		wxTextCtrl* m_txtCtrlSpIllu;
		wxTextCtrl* m_txtCtrlSpColor;
		wxChoice* m_chSpPintype;
		wxTextCtrl* m_txtCtrlSpPinNo;
		wxChoice* m_choiceSpPinValue;
		wxChoice* m_chSpDefPinValue;
		wxTextCtrl* m_txtCtrlSpTolNm;
		wxTextCtrl* m_txtCtrlSpTolSat;
		wxTextCtrl* m_txtCtrlSpTolIllu;


    protected:
		virtual void OnButtonRemove( wxCommandEvent& event ) { event.Skip(); };
		virtual void OnPasteSet    ( wxCommandEvent& event ) { event.Skip(); };
		virtual void OnClearSet    ( wxCommandEvent& event ) { event.Skip(); };


	public:

		PanelTestrow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );

        wxWindowID GetButtonRemoveID(){return m_bpButtonRemove->GetId();};
        wxWindowID GetButtonClearID(){return m_bpButtonClear->GetId();};
        wxWindowID GetButtonPasteID(){return m_bpButtonPaste->GetId(); };

        bool IsActivated()                  {return m_cbUseSet->GetValue();};
        wxString GetName()                  {return m_txtCtrlSpName->GetValue(); };
        bool     IsNameFieldEmpty()         {return m_txtCtrlSpName->IsEmpty();};
        void     SetName(wxString name)     {m_txtCtrlSpName->Clear();
                                              m_txtCtrlSpName->SetValue(name);};
        int GetWavelength()                 {return wxAtoi(m_txtCtrlSpWL->GetValue());};
        int GetTolWavelength()              {return wxAtoi(m_txtCtrlSpTolNm->GetValue());};
        void     SetWavelength(int wl)      {m_txtCtrlSpWL->SetValue(wxString::Format(wxT("%i"), wl));};
        void     SetTolWavelength(int tolnm){m_txtCtrlSpTolNm->SetValue(wxString::Format(wxT("%i"), tolnm));}
        int GetSaturation()                 {return wxAtoi(m_txtCtrlSpSat->GetValue()); };
        int GetTolSaturation()              {return wxAtoi(m_txtCtrlSpTolSat->GetValue()); };
        void SetSaturation(int sat)         {m_txtCtrlSpSat->SetValue(wxString::Format(wxT("%i"), sat));};
        void SetTolSaturation(int tolsat)   {m_txtCtrlSpTolSat->SetValue(wxString::Format(wxT("%i"), tolsat));};
        int GetIllumination()               {return wxAtoi(m_txtCtrlSpIllu->GetValue());};
        int GetTolIllumination()            {return wxAtoi(m_txtCtrlSpTolIllu->GetValue());};
        void SetIllumination(int illu)      {m_txtCtrlSpIllu->SetValue(wxString::Format(wxT("%i"), illu));};
        void SetTolIllumination(int tolillu){m_txtCtrlSpTolIllu->SetValue(wxString::Format(wxT("%i"), tolillu));};
        void SetColour(wxColour colour)     {m_txtCtrlSpColor->SetBackgroundColour(colour);
                                             m_txtCtrlSpColor->Clear();};
        wxColour GetColour()                {return m_txtCtrlSpColor->GetBackgroundColour();};
        void SetPintype(int iSelection)     {m_chSpPintype->SetSelection(iSelection); };
        int  GetPintype()                   {return m_chSpPintype->GetSelection();};
        wxString GetPintype(int iSelection) {return m_chSpPintype->GetString(iSelection);};
        void SetPinNumber(int iValue)       {iValue >= 0 ? m_txtCtrlSpPinNo->SetValue(wxString::Format(wxT("%i"), iValue)) :
                                                           m_txtCtrlSpPinNo->SetValue(wxString::Format(wxT("%i"), iValue));};
        int  GetPinNumber()                 {return wxAtoi(m_txtCtrlSpPinNo->GetValue());};
        void SetPinValue(int iSelection)    {m_choiceSpPinValue->SetSelection(iSelection);};
        bool IsPinNumberFieldEmpty()        {return m_txtCtrlSpPinNo->IsEmpty();};
        int  GetPinValue()                  {return m_choiceSpPinValue->GetSelection();};
        void SetPinDefValue(int iSelection) {m_chSpDefPinValue->SetSelection(iSelection);};
        int  GetPinDefValue()               {return m_chSpDefPinValue->GetSelection();};
        void ClearRow();
		~PanelTestrow();
};




#endif // PANELTESTROW_H
