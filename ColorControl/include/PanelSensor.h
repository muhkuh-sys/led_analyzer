#ifndef PANELSENSOR_H
#define PANELSENSOR_H


#include "../GUIFrame.h"

///////////////////////////////////////////////////////////////////////////////
/// Class PanelSensor
///////////////////////////////////////////////////////////////////////////////
class PanelSensor : public wxPanel
{
	private:
		wxTextCtrl* m_txtCtrlSensorNo;
		wxCheckBox* m_cbUseSet1;
		wxBitmapButton* m_bpButtonPaste1;
		wxBitmapButton* m_bpButtonClear1;
		wxCheckBox* m_cbUseSet2;
		wxBitmapButton* m_bpButtonPaste2;
		wxBitmapButton* m_bmButtonClear2;
		wxCheckBox* m_cbUseSet3;
		wxBitmapButton* m_bmButtonPaste3;
		wxBitmapButton* m_bpButtonClear3;
		wxTextCtrl* m_txtCtrlCurName;
		wxTextCtrl* m_txtCtrlSpName1;
		wxTextCtrl* m_txtCtrlSpName2;
		wxTextCtrl* m_txtCtrlSpName3;
		wxTextCtrl* m_txtCtrlCurWL;
		wxTextCtrl* m_txtCtrlSpWL1;
		wxTextCtrl* m_txtCtrlSpWL2;
		wxTextCtrl* m_txtCtrlSpWL3;
		wxTextCtrl* m_txtCtrlCurSat;
		wxTextCtrl* m_txtCtrlSpSat1;
		wxTextCtrl* m_txtCtrlSpSat2;
		wxTextCtrl* m_txtCtrlSpSat3;
		wxTextCtrl* m_txtCtrlCurIllu;
		wxTextCtrl* m_txtCtrlSpIllu1;
		wxTextCtrl* m_txtCtrlSpIllu2;
		wxTextCtrl* m_txtCtrlSpIllu3;
		wxTextCtrl* m_txtCtrlCurColor;
		wxTextCtrl* m_txtCtrlSpColor1;
		wxTextCtrl* m_txtCtrlSpColor2;
		wxTextCtrl* m_txtCtrlSpColor3;
		wxChoice* m_chCurPintype;
		wxChoice* m_chSpPintype1;
		wxChoice* m_chSpPintype2;
		wxChoice* m_chSpPintype3;
		wxTextCtrl* m_txtCtrlCurPinNo;
		wxTextCtrl* m_txtCtrlSpPinNo1;
		wxTextCtrl* m_txtCtrlSpPinNo2;
		wxTextCtrl* m_txtCtrlSpPinNo3;
		wxChoice* m_chCurPinValue;
		wxChoice* m_choiceSpPinValue1;
		wxChoice* m_choiceSpPinValue2;
		wxChoice* m_choiceSpPinValue3;
		wxChoice* m_chCurDefPinValue;
		wxChoice* m_chSpDefPinValue1;
		wxChoice* m_chSpDefPinValue2;
		wxChoice* m_chSpDefPinValue3;
		wxTextCtrl* m_txtCtrlTolNm;
		wxTextCtrl* m_txtCtrlSpTolNm1;
		wxTextCtrl* m_txtCtrlSpTolNm2;
		wxTextCtrl* m_txtCtrlSpTolNm3;
		wxTextCtrl* m_txtCtrlTolSat;
		wxTextCtrl* m_txtCtrlSpTolSat1;
		wxTextCtrl* m_txtCtrlSpTolSat2;
		wxTextCtrl* m_txtCtrlSpTolSat3;
		wxTextCtrl* m_txtCtrlTolIllu;
		wxTextCtrl* m_txtCtrlSpTolIllu1;
		wxTextCtrl* m_txtCtrlSpTolIllu2;
		wxTextCtrl* m_txtCtrlSpTolIllu3;


		void OnPasteSet1( wxCommandEvent& event );
		void OnClearSet1( wxCommandEvent& event );
		void OnPasteSet2( wxCommandEvent& event );
		void OnClearSet2( wxCommandEvent& event );
		void OnPasteSet3( wxCommandEvent& event );
		void OnClearSet3( wxCommandEvent& event );


	public:
	    /* First Block */
        bool IsActivated_1() {return m_cbUseSet1->GetValue();};
        bool IsActivated_2() {return m_cbUseSet2->GetValue();};
        bool IsActivated_3() {return m_cbUseSet3->GetValue();};


        /* Second Block - Name */
        wxString GetName()               {return m_txtCtrlCurName->GetValue();};
        void     SetName(wxString name)  {m_txtCtrlCurName->Clear();
                                          m_txtCtrlCurName->SetValue(name);};

        wxString Getname_1()             {return m_txtCtrlSpName1->GetValue();};
        void     SetName_1(wxString name){m_txtCtrlSpName1->Clear();
                                          m_txtCtrlSpName1->SetValue(name);};
        wxString Getname_2()             {return m_txtCtrlSpName2->GetValue();};
        void     SetName_2(wxString name){m_txtCtrlSpName2->Clear();
                                          m_txtCtrlSpName2->SetValue(name);};
        wxString Getname_3()             {return m_txtCtrlSpName3->GetValue();};
        void     SetName_3(wxString name){m_txtCtrlSpName3->Clear();
                                          m_txtCtrlSpName3->SetValue(name);};


        /* Third Block - Wavelength */
        int GetWavelength()           {return wxAtoi(m_txtCtrlCurWL->GetValue());};
        int GetWavelength_1()         {return wxAtoi(m_txtCtrlSpWL1->GetValue());};
        int GetWavelength_2()         {return wxAtoi(m_txtCtrlSpWL2->GetValue());};
        int GetWavelength_3()         {return wxAtoi(m_txtCtrlSpWL3->GetValue());};
        int GetTolWavelength()        {return wxAtoi(m_txtCtrlTolNm->GetValue());};
        int GetTolWavelength_1()      {return wxAtoi(m_txtCtrlSpTolNm1->GetValue());};
        int GetTolWavelength_2()      {return wxAtoi(m_txtCtrlSpTolNm2->GetValue());};
        int GetTolWavelength_3()      {return wxAtoi(m_txtCtrlSpTolNm3->GetValue());};

        void     SetWavelength(int wl)      {m_txtCtrlCurWL->SetValue(wxString::Format(wxT("%i"), wl));};
        void     SetWavelength_1(int wl)    {m_txtCtrlSpWL1->SetValue(wxString::Format(wxT("%i"), wl));};
        void     SetWavelength_2(int wl)    {m_txtCtrlSpWL2->SetValue(wxString::Format(wxT("%i"), wl));};
        void     SetWavelength_3(int wl)    {m_txtCtrlSpWL3->SetValue(wxString::Format(wxT("%i"), wl));};
        void     SetTolWavelength  (int tolnm){m_txtCtrlTolNm->SetValue(wxString::Format(wxT("%i"), tolnm));}
        void     SetTolWavelength_1(int tolnm){m_txtCtrlSpTolNm1->SetValue(wxString::Format(wxT("%i"), tolnm));}
        void     SetTolWavelength_2(int tolnm){m_txtCtrlSpTolNm2->SetValue(wxString::Format(wxT("%i"), tolnm));}
        void     SetTolWavelength_3(int tolnm){m_txtCtrlSpTolNm3->SetValue(wxString::Format(wxT("%i"), tolnm));}

        /* Fourth Block - Saturation */
        int GetSaturation()            {return wxAtoi(m_txtCtrlCurSat->GetValue()); };
        int GetSaturation_1()          {return wxAtoi(m_txtCtrlSpSat1->GetValue()); };
        int GetSaturation_2()          {return wxAtoi(m_txtCtrlSpSat2->GetValue()); };
        int GetSaturation_3()          {return wxAtoi(m_txtCtrlSpSat3->GetValue()); };
        int GetTolSaturation()         {return wxAtoi(m_txtCtrlTolSat->GetValue()); };
        int GetTolSaturation_1()       {return wxAtoi(m_txtCtrlSpTolSat1->GetValue()); };
        int GetTolSaturation_2()       {return wxAtoi(m_txtCtrlSpTolSat2->GetValue()); };
        int GetTolSaturation_3()       {return wxAtoi(m_txtCtrlSpTolSat3->GetValue()); };


        void SetSaturation(int sat)      {m_txtCtrlCurSat->SetValue(wxString::Format(wxT("%i"), sat));};
        void SetSaturation_1(int sat)    {m_txtCtrlSpSat1->SetValue(wxString::Format(wxT("%i"), sat));};
        void SetSaturation_2(int sat)    {m_txtCtrlSpSat2->SetValue(wxString::Format(wxT("%i"), sat));};
        void SetSaturation_3(int sat)    {m_txtCtrlSpSat3->SetValue(wxString::Format(wxT("%i"), sat));};
        void SetTolSaturation  (int tolsat){m_txtCtrlTolSat->SetValue(wxString::Format(wxT("%i"), tolsat));};
        void SetTolSaturation_1(int tolsat){m_txtCtrlSpTolSat1->SetValue(wxString::Format(wxT("%i"), tolsat));};
        void SetTolSaturation_2(int tolsat){m_txtCtrlSpTolSat2->SetValue(wxString::Format(wxT("%i"), tolsat));};
        void SetTolSaturation_3(int tolsat){m_txtCtrlSpTolSat3->SetValue(wxString::Format(wxT("%i"), tolsat));};



        /* Fifth Block Illumination */
        int GetIllumination()              {return wxAtoi(m_txtCtrlCurIllu->GetValue());};
        int GetIllumination_1()            {return wxAtoi(m_txtCtrlSpIllu1->GetValue());};
        int GetIllumination_2()            {return wxAtoi(m_txtCtrlSpIllu2->GetValue());};
        int GetIllumination_3()            {return wxAtoi(m_txtCtrlSpIllu3->GetValue());};
        int GetTolIllumination()           {return wxAtoi(m_txtCtrlTolIllu->GetValue());};
        int GetTolIllumination_1()         {return wxAtoi(m_txtCtrlSpTolIllu1->GetValue());};
        int GetTolIllumination_2()         {return wxAtoi(m_txtCtrlSpTolIllu2->GetValue());};
        int GetTolIllumination_3()         {return wxAtoi(m_txtCtrlSpTolIllu3->GetValue());};

        void SetIllumination(int illu)     {m_txtCtrlCurIllu->SetValue(wxString::Format(wxT("%i"), illu));};
        void SetIllumination_1(int illu)   {m_txtCtrlSpIllu1->SetValue(wxString::Format(wxT("%i"), illu));};
        void SetIllumination_2(int illu)   {m_txtCtrlSpIllu2->SetValue(wxString::Format(wxT("%i"), illu));};
        void SetIllumination_3(int illu)   {m_txtCtrlSpIllu3->SetValue(wxString::Format(wxT("%i"), illu));};
        void SetTolIllumination  (int tolillu){m_txtCtrlTolIllu->SetValue(wxString::Format(wxT("%i"), tolillu));};
        void SetTolIllumination_1(int tolillu){m_txtCtrlSpTolIllu1->SetValue(wxString::Format(wxT("%i"), tolillu));};
        void SetTolIllumination_2(int tolillu){m_txtCtrlSpTolIllu2->SetValue(wxString::Format(wxT("%i"), tolillu));};
        void SetTolIllumination_3(int tolillu){m_txtCtrlSpTolIllu3->SetValue(wxString::Format(wxT("%i"), tolillu));};


        /* Sixth Block Colour */
        void SetColour(wxColour colour)    {m_txtCtrlCurColor->SetBackgroundColour(colour);
                                            m_txtCtrlCurColor->Clear();};
        void SetColour_1(wxColour colour)  {m_txtCtrlSpColor1->SetBackgroundColour(colour);
                                            m_txtCtrlSpColor1->Clear();};
        void SetColour_2(wxColour colour)  {m_txtCtrlSpColor2->SetBackgroundColour(colour);
                                            m_txtCtrlSpColor2->Clear();};
        void SetColour_3(wxColour colour)  {m_txtCtrlSpColor3->SetBackgroundColour(colour);
                                            m_txtCtrlSpColor3->Clear();};

        wxColour GetColour()               {return m_txtCtrlCurColor->GetBackgroundColour();};
        wxColour GetColour_1()             {return m_txtCtrlSpColor1->GetBackgroundColour();};
        wxColour GetColour_2()             {return m_txtCtrlSpColor2->GetBackgroundColour();};
        wxColour GetColour_3()             {return m_txtCtrlSpColor3->GetBackgroundColour();};


        /* Pintype */
        //const wxString GetPintype(){return m_chCurPintype->GetString(m_chCurPintype->GetSelection()); };
        int            GetPintype(){return m_chCurPintype->GetSelection();};
        const wxString GetPintype_1(){return m_chSpPintype1->GetString(m_chSpPintype1->GetSelection()); };
        const wxString GetPintype_2(){return m_chSpPintype2->GetString(m_chSpPintype2->GetSelection()); };
        const wxString GetPintype_3(){return m_chSpPintype3->GetString(m_chSpPintype3->GetSelection()); };

        void SetPintype(int iSelection){m_chCurPintype->SetSelection(iSelection);};
        void SetPintype_1(int iSelection){m_chSpPintype1->SetSelection(iSelection);};
        void SetPintype_2(int iSelection){m_chSpPintype2->SetSelection(iSelection);};
        void SetPintype_3(int iSelection){m_chSpPintype3->SetSelection(iSelection);};

        /* Pin Number */
        int GetPinNumber()  {return wxAtoi(m_txtCtrlCurPinNo->GetValue());}
        int GetPinNumber_1(){return wxAtoi(m_txtCtrlSpPinNo1->GetValue());};
        int GetPinNumber_2(){return wxAtoi(m_txtCtrlSpPinNo2->GetValue());};
        int GetPinNumber_3(){return wxAtoi(m_txtCtrlSpPinNo3->GetValue());};

        void SetPinNumber  (int iNumber){m_txtCtrlCurPinNo->SetValue(wxString::Format(wxT("%i"), iNumber));};
        void SetPinNumber_1(int iNumber){m_txtCtrlSpPinNo1->SetValue(wxString::Format(wxT("%i"), iNumber)); };
        void SetPinNumber_2(int iNumber){m_txtCtrlSpPinNo2->SetValue(wxString::Format(wxT("%i"), iNumber)); };
        void SetPinNumber_3(int iNumber){m_txtCtrlSpPinNo3->SetValue(wxString::Format(wxT("%i"), iNumber)); };

		/* Pin Value */
		int GetPinValue()  {return m_chCurPinValue->GetSelection(); };
		int GetPinValue_1(){return m_choiceSpPinValue1->GetSelection(); };
		int GetPinValue_2(){return m_choiceSpPinValue2->GetSelection(); };
		int GetPinValue_3(){return m_choiceSpPinValue3->GetSelection(); };

        void SetPinValue(int iValue) {m_chCurPinValue->SetSelection(iValue);};
        void SetPinValue_1(int iValue) {m_choiceSpPinValue1->SetSelection(iValue); };
        void SetPinValue_2(int iValue) {m_choiceSpPinValue2->SetSelection(iValue); };
        void SetPinValue_3(int iValue) {m_choiceSpPinValue3->SetSelection(iValue); };

        /* Pin Default Value */
        int GetPinDefValue()   {return m_chCurDefPinValue->GetSelection(); };
        int GetPinDefValue_1() {return m_chSpDefPinValue1->GetSelection(); };
        int GetPinDefValue_2() {return m_chSpDefPinValue2->GetSelection(); };
        int GetPinDefValue_3() {return m_chSpDefPinValue3->GetSelection(); };

        void SetPinDefValue(int iDefValue)  {m_chCurDefPinValue->SetSelection(iDefValue);};
        void SetPinDefValue_1(int iDefValue){m_chSpDefPinValue1->SetSelection(iDefValue);};
        void SetPinDefValue_2(int iDefValue){m_chSpDefPinValue2->SetSelection(iDefValue);};
        void SetPinDefValue_3(int iDefValue){m_chSpDefPinValue3->SetSelection(iDefValue);};


        wxString GetTestSet1(int iSensorIndex);
        wxString GetTestSet2(int iSensorIndex);
        wxString GetTestSet3(int iSensorIndex);

        wxString GetNetXData();


		PanelSensor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 832,150 ), long style = wxSTATIC_BORDER, int sensornumber = 0 );
		~PanelSensor();


};

#endif // PANELSENSOR_H
