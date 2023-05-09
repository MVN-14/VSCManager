#include "MainPanel.h"
#include "WorkspaceListPanel.h"
#include "TextButton.h"
#include <wx/dirdlg.h>
#include "def.h"

#include <fstream>
#include <wx/sizer.h>

namespace {
	void writeWorkspaceToFile(wxString const &path) {
		std::ofstream ofstream(FOLDER_LIST_PATH, std::ios_base::app);
		if (ofstream)
			ofstream << path << '\n';
	}
}

MainPanel::MainPanel(wxWindow *parent) 
	: wxPanel(parent) {

	SetBackgroundColour(BG_COLOUR);
	SetForegroundColour(*wxWHITE);

	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText *title = new wxStaticText(this, wxID_ANY, wxString("Your Workspaces"));
	title->SetFont(title->GetFont().Scale(2).Bold());

	TextButton *addButton = new TextButton(this, wxString("Add"), wxSize(60, 30), BUTTON_COLOUR, *wxGREEN, 1.5f);
	addButton->Bind(wxEVT_LEFT_UP, &MainPanel::onAddWorkspace_, this);

	wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
	headerSizer->Add(title, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	headerSizer->Add(addButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	listPanel_ = new WorkspaceListPanel(this);
	
	mainSizer->Add(headerSizer, 0, wxEXPAND);
	mainSizer->Add(listPanel_, 1, wxEXPAND);

	SetSizerAndFit(mainSizer);
}

void MainPanel::onAddWorkspace_(wxMouseEvent &) {
	wxDirDialog dialog(this, "Add workspace");
	int result = dialog.ShowModal();

	if (wxID_CANCEL == result)
		return;

	wxString path = dialog.GetPath();
	writeWorkspaceToFile(path);
	listPanel_->reloadWorkspaces();
}