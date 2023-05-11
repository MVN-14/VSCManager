#include "WorkspaceListPanel.h"
#include "WorkspaceListItem.h"
#include "TextButton.h"
#include "ioHelper.h"
#include "def.h"

#include <wx/stattext.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>

#include <fstream>

namespace {
	wxString getFolderNameFromPath(wxString const &path) {
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
	std::string folderPath = getFolderListPath();
	mainSizer_->Clear(true);
	std::ifstream stream(folderPath);

	if (!stream) {
		std::ofstream(folderPath);
		return;
	}
	
	std::string path;
	while (std::getline(stream, path)) {
		if (!path.empty())
			addPanelItem_(getFolderNameFromPath(path), path);
	}
	GetParent()->Layout();
}

void WorkspaceListPanel::removePathFromFolderList_(wxString const &path) {
	std::string folderListPath = getFolderListPath();
	std::ifstream oldFile(folderListPath);
	std::ofstream newFile("temp.txt");
	if (!oldFile || !newFile)
		return;

	std::string line;
	while (std::getline(oldFile, line)) 
		if (line != path) 
			newFile << line << '\n';

	oldFile.close();
	newFile.close();

	remove(folderListPath.c_str());
	rename("temp.txt", folderListPath.c_str());
	loadWorkspaces_();
}

void WorkspaceListPanel::reloadWorkspaces() {
	loadWorkspaces_();
}