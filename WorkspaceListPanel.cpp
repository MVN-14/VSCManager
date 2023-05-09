#include "WorkspaceListPanel.h"
#include "WorkspaceListItem.h"
#include "TextButton.h"
#include "def.h"

#include <wx/stattext.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>

#include <fstream>

namespace {
	wxString GetFolderNameFromPath(wxString const &path) {
		int lastSlashPosition = path.Last('\\');

		if (-1 != lastSlashPosition)
			return path.SubString(static_cast<size_t>(lastSlashPosition) + 1, path.Length());
		
		return path;
	}
}

WorkspaceListPanel::WorkspaceListPanel(wxWindow *parent) 
	: wxScrolledWindow(parent) {

	mainSizer_ = new wxBoxSizer(wxVERTICAL);
	loadWorkspaces_();
	SetSizer(mainSizer_);
	SetScrollbars(1, 5, 50, 0);
}

void WorkspaceListPanel::addPanelItem_(wxString const &workspaceName, wxString const &path) {
	mainSizer_->Add(new WorkspaceListItem(this, workspaceName, path, [this, path] {
		removePathFromFolderList_(path);
		}), 0, wxEXPAND
	);
	GetParent()->Layout(); 
}

void WorkspaceListPanel::loadWorkspaces_() {
	mainSizer_->Clear(true);
	std::ifstream stream(FOLDER_LIST_PATH);

	if (!stream) {
		std::ofstream(FOLDER_LIST_PATH);
		return;
	}
	
	std::string path;
	while (std::getline(stream, path)) {
		if (!path.empty())
			addPanelItem_(GetFolderNameFromPath(path), path);
	}
	GetParent()->Layout();
}

void WorkspaceListPanel::removePathFromFolderList_(wxString const &path) {
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
	loadWorkspaces_();
}

void WorkspaceListPanel::reloadWorkspaces() {
	loadWorkspaces_();
}