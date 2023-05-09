#pragma once
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/vscroll.h>

#include <map>

class WorkspacePanelItem;

class WorkspacePanel : public wxPanel {
public:
	WorkspacePanel(wxWindow *parent);
	void removePanelItem(wxString const &path);
private:
	wxBoxSizer *mainSizer_{nullptr};
	wxBoxSizer *listSizer_{nullptr};	
	wxPanel *listPanel_{nullptr};

	void onAddWorkspace(wxMouseEvent &);
	void addPanelItem(wxString const &workspaceName, wxString const &path);
	void loadWorkspaces();
	void writeWorkspaceToFile(wxString const &path);
};

