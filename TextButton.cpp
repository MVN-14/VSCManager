#include "TextButton.h"
#include <wx/sizer.h>

TextButton::TextButton(wxWindow *parent, wxString const &label, std::function<void()> callback, const wxColour &buttonColour, const wxColour &textColour)
 : wxStaticText(parent, wxID_ANY, label) {
	
	SetBackgroundColour(buttonColour);
	SetForegroundColour(textColour);

	Bind(wxEVT_LEFT_UP, [callback](wxMouseEvent &) {
		callback();
	});

	//wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText *text = new wxStaticText(this, wxID_ANY, label);
	text->SetFont(text->GetFont().Bold().Scale(1.2));

	//sizer->Add(text, 1, wxALL, 5);
	SetSize(GetBestSize());
	//SetSizer(sizer);
}