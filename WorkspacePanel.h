#pragma once
#include <wx/panel.h>
#include <wx/sizer.h>


#include <vector>

class WorkspacePanelItem;

class WorkspacePanel : public wxPanel {
public:
	WorkspacePanel(wxWindow *parent);

private:
	wxBoxSizer *mainSizer_{nullptr};
	void onAddWorkspace(wxMouseEvent &);
	void addPanelItem(wxString const &workspaceName, wxString const &path);
	void loadWorkspaces();
	bool writeWorkspaceToFile(wxString const &path);
};

