#include "TextButton.h"

#include <wx/sizer.h>

TextButton::TextButton(wxWindow *parent, wxString const &label, wxSize const &size, const wxColour &buttonColour, const wxColour &textColour, float fontScale, bool bold)
 : wxStaticText(parent, wxID_ANY, label, wxDefaultPosition, size, wxALIGN_CENTRE_VERTICAL | wxALIGN_CENTRE_HORIZONTAL) {
	
	SetBackgroundColour(buttonColour);
	SetForegroundColour(textColour);

	wxFont font = GetFont().Scale(fontScale);
	if (bold) {
		font = font.Bold();
	}
	SetFont(font);
	Bind(wxEVT_ENTER_WINDOW, [this](wxMouseEvent &) {SetCursor(wxCURSOR_HAND); });
	Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent &) {SetCursor(wxCURSOR_ARROW); });

}