#pragma once

#include <wx/stattext.h>
#include <functional>

class TextButton : public wxStaticText {
public:
	TextButton(wxWindow *parent, wxString const &label, std::function<void()> callback, const wxColour &buttonColour = *wxGREEN, const wxColour &textColour = *wxBLACK);

};

