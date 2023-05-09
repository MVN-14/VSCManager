#pragma once

#include <wx/stattext.h>

#include "def.h"

class TextButton : public wxStaticText {
public:
	TextButton(wxWindow *parent, wxString const &label, wxSize const &size = wxDefaultSize, const wxColour &buttonColour = BUTTON_COLOUR, const wxColour &textColour = *wxBLACK, float fontScale = 1.0f, bool bold = true);
};

