#include "WorkspacePanel.h"
#include "WorkspacePanelItem.h"
#include "TextButton.h"
#include "def.h"

#include <wx/stattext.h>
//#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/msgdlg.h>

#include <fstream>
#include <sstream>

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

	TextButton *addButton = new TextButton(this, wxString("Add"), wxSize(60, 30), BUTTON_COLOUR, *wxGREEN, 1.5f);
	addButton->Bind(wxEVT_LEFT_UP, &WorkspacePanel::onAddWorkspace, this);

	wxStaticText *title = new wxStaticText(this, wxID_ANY, wxString("Your Workspaces"));
	title->SetFont(title->GetFont().Scale(2).Bold());

	wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
	headerSizer->Add(title, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	headerSizer->Add(addButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	listSizer_ = new wxBoxSizer(wxVERTICAL);
	listPanel_ = new wxPanel(this);
	loadWorkspaces();
	listPanel_->SetSizer(listSizer_);

	mainSizer_->Add(headerSizer);
	mainSizer_->Add(listPanel_, 1, wxEXPAND);

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
	listSizer_->Add(new WorkspacePanelItem(listPanel_, workspaceName, path, [this, path] {
		removePanelItem(path);
		}), 1, wxEXPAND
	);
	GetParent()->Layout(); 
}

void WorkspacePanel::loadWorkspaces() {
	listSizer_->Clear(true);
	std::ifstream stream(FOLDER_LIST_PATH);

	if (!stream) {
		std::ofstream(FOLDER_LIST_PATH);
		return;
	}
	
	std::string path;
	while (std::getline(stream, path)) {
		if (!path.empty())
			addPanelItem(GetFolderNameFromPath(path), path);
	}
	//listPanel_->SetSizer(panelSizer_);
	GetParent()->Layout();
}

void WorkspacePanel::writeWorkspaceToFile(wxString const &path) {
	std::ofstream ofstream(FOLDER_LIST_PATH, std::ios_base::app);
	if(ofstream)
		ofstream << path << '\n';
}

void WorkspacePanel::removePanelItem(wxString const &path) {
	std::ifstream oldFile(FOLDER_LIST_PATH);
	std::ofstream newFile("temp.txt");
	if (!oldFile || !newFile)
		return;

	std::string line;
	while (std::getline(oldFile, line)) 
		if (line != path) 
			newFile << line << '\n';

	oldFile.close();
	newFile.close();

	remove(FOLDER_LIST_PATH);
	rename("temp.txt", FOLDER_LIST_PATH);
	loadWorkspaces();
}