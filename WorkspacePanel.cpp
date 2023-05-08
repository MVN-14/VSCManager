#include "WorkspacePanel.h"
#include "WorkspacePanelItem.h"
#include "TextButton.h"
#include "def.h"

#include <wx/stattext.h>
//#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/msgdlg.h>

#include <fstream>

namespace {
	wxString GetFolderNameFromPath(wxString const &path) {
		int lastSlashPosition = path.Last('\\');

		if (-1 != lastSlashPosition)
			return path.SubString(static_cast<size_t>(lastSlashPosition) + 1, path.Length());
		
		return path;
	}
}

WorkspacePanel::WorkspacePanel(wxWindow *parent) 
	: wxPanel(parent) {
	
	SetForegroundColour(*wxWHITE);

	mainSizer_ = new wxBoxSizer(wxVERTICAL);

	wxStaticText *addButton = new wxStaticText(this, wxID_ANY, wxString(" + "));
	addButton->SetBackgroundColour(BUTTON_COLOUR);
	addButton->SetForegroundColour(*wxBLACK);
	addButton->SetFont(addButton->GetFont().Bold().Scale(2.0f));
	addButton->SetSize(addButton->GetSize().GetWidth(), 40);
	addButton->Bind(wxEVT_LEFT_UP, &WorkspacePanel::onAddWorkspace, this);
	addButton->Bind(wxEVT_ENTER_WINDOW, [this](wxMouseEvent &) {SetCursor(wxCURSOR_HAND); });
	addButton->Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent &) {SetCursor(wxCURSOR_ARROW); });

	wxStaticText *title = new wxStaticText(this, wxID_ANY, wxString("Your Workspaces"));
	title->SetFont(title->GetFont().Scale(2).Bold());

	wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
	headerSizer->Add(title, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	headerSizer->Add(addButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	mainSizer_->Add(headerSizer);

	loadWorkspaces();

	SetSizer(mainSizer_);
}

void WorkspacePanel::onAddWorkspace(wxMouseEvent &) {
	wxDirDialog dialog(this, "Add workspace");
	int result = dialog.ShowModal();

	if (wxID_CANCEL == result)
		return;

	wxString path = dialog.GetPath();
	writeWorkspaceToFile(path);
	addPanelItem(GetFolderNameFromPath(path), path);
}

void WorkspacePanel::addPanelItem(wxString const &workspaceName, wxString const &path) {
	mainSizer_->Add(new WorkspacePanelItem(this, workspaceName, path), 1, wxEXPAND);
	GetParent()->Layout(); 
}

void WorkspacePanel::loadWorkspaces() {
	std::ifstream stream(FOLDER_LIST_PATH);

	if (!stream) {
		std::ofstream(FOLDER_LIST_PATH);
		return;
	}
	
	std::string path;
	while (std::getline(stream, path)) {
		if (path.empty())
			continue;
		addPanelItem(GetFolderNameFromPath(path), path);
	}
}

bool WorkspacePanel::writeWorkspaceToFile(wxString const &path) {
	std::ofstream ostream(FOLDER_LIST_PATH, std::ios_base::app);

	if (!ostream) 
		return false;

	ostream << path << '\n';
	return true;
}
