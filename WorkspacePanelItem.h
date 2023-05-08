#pragma once
#include <wx/panel.h>


class WorkspacePanelItem : public wxPanel {
public:
	WorkspacePanelItem(wxWindow *parent, wxString const &workspaceName, wxString const &folderPath);

private:
	wxString path_{};

	void onEnterWindow(wxMouseEvent &);
	void onLeaveWindow(wxMouseEvent &);
	void onClick(wxMouseEvent &);
};