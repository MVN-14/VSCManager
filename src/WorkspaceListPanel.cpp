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
	if (folderListPath.empty()) {
		wxDialog alert(this, wxID_ANY, "Error getting folder list path");
		alert.ShowModal();
	}

	std::ifstream oldFile(folderListPath);
	std::ofstream newFile(folderListPath + ".temp.txt");
	if (!newFile) {
		wxDialog alert(this, wxID_ANY, "Error creating temp index file");
		alert.ShowModal();
		return;
	}
	if (!oldFile) {
		wxDialog alert(this, wxID_ANY, "Error opening old index file");
		alert.ShowModal();
		return;
	}

	std::string line;
	while (std::getline(oldFile, line)) 
		if (line != path) 
			newFile << line << '\n';

	oldFile.close();
	newFile.close();

	if (0 != remove(folderListPath.c_str())) {
		wxDialog alert(this, wxID_ANY, "Error removing old index file.");
		alert.ShowModal();
		return;
	}
	if (0 != rename((folderListPath + ".temp.txt").c_str(), folderListPath.c_str())) {
		wxDialog alert(this, wxID_ANY, "Error renaming new index file.");
		alert.ShowModal();
		return;
	}

	loadWorkspaces_();
}

void WorkspaceListPanel::reloadWorkspaces() {
	loadWorkspaces_();
}