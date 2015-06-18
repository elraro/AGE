#include "AGE_OpenSave.h"

class AGE_OpenDialog: public AGE_OpenSave
{
public:
	AGE_OpenDialog(wxWindow *parent);

	/* Events */

	void OnDefaultAoE(wxCommandEvent &Event);
	void OnDefaultRoR(wxCommandEvent &Event);
	void OnDefaultAoK(wxCommandEvent &Event);
	void OnDefaultTC(wxCommandEvent &Event);
	void OnDefaultAoKHD(wxCommandEvent &Event);
	void OnDefaultFE(wxCommandEvent &Event);
	void OnDefaultSWGB(wxCommandEvent &Event);
	void OnDefaultCC(wxCommandEvent &Event);
	void OnChangeDatRadio(wxCommandEvent &Event);
	void OnSelectLang(wxCommandEvent &Event);
	void OnSelectLangX1(wxCommandEvent &Event);
	void OnSelectLangX1P1(wxCommandEvent &Event);
	void OnOK(wxCommandEvent &Event);
	void OnDecompress(wxCommandEvent &Event);

	/* Member Variables */

	wxStaticText *DriveText;
	wxStaticText *WindowCountText;
	wxTextCtrl *WindowCountBox;
	wxStaticText *LanguageText;
	wxBoxSizer *DriveLetterArea;
	wxCheckBox *Radio_DatFileLocation;
	wxCheckBox *CheckBox_LangWriteToLatest;
	wxButton *Button_RawDecompress;
	wxFilePickerCtrl *Path_RawDecompress;
	wxStaticText *TerrainsText;
	wxTextCtrl *TerrainsBox;
};
