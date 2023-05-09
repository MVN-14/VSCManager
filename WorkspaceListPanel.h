#pragma once
#include <wx/vscroll.h>

class wxBoxSizer;
class WorkspaceListItem;

class WorkspaceListPanel : public wxScrolledWindow {
public:
	WorkspaceListPanel(wxWindow *parent);

	void reloadWorkspaces();

private:
	wxBoxSizer *mainSizer_{nullptr};

	void removePathFromFolderList_(wxString const &path);
	void addPanelItem_(wxString const &workspaceName, wxString const &path);
	void loadWorkspaces_();
};

