#pragma once
#include <wx/panel.h>

#include <functional>

class WorkspacePanelItem : public wxPanel {
public:
	WorkspacePanelItem(wxWindow *parent, wxString const &workspaceName, wxString const &folderPath, std::function<void()> onRemove);

private:
	wxString path_{};

	std::function<void()> onRemove_;
	void onEnterWindow(wxMouseEvent &event);
	void onLeaveWindow(wxMouseEvent &);
	void onClick(wxMouseEvent &);
	void onRemove(wxMouseEvent &);
};