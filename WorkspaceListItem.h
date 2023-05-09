#pragma once
#include <wx/panel.h>

#include <functional>

class WorkspaceListItem : public wxPanel {
public:
	WorkspaceListItem(wxWindow *parent, wxString const &workspaceName, wxString const &folderPath, std::function<void()> onRemove);

private:
	wxString path_{};
	std::function<void()> onRemove_;

	void onEnterWindow_(wxMouseEvent &event);
	void onLeaveWindow_(wxMouseEvent &);
	void onClick_(wxMouseEvent &);
	void remove_(wxMouseEvent &);
};