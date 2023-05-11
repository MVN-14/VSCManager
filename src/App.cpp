#include <wx/frame.h>

#include "App.h"
#include "MainPanel.h"

bool App::OnInit() {
	if (!wxApp::OnInit())
		return false;

	wxFrame *mainFrame = new wxFrame(nullptr,
								     wxID_ANY,
									 std::move(wxString("VSC Manager (0.0.1)")),
									 wxDefaultPosition,
									 std::move(wxSize(800, 600)));

	MainPanel *mainPanel = new MainPanel(mainFrame);
	mainFrame->Center(wxBOTH);
	mainFrame->Show();

	return true;
}

wxIMPLEMENT_APP(App);