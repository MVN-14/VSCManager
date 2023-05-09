#pragma once

#include <wx/panel.h>

class WorkspaceListPanel;

class MainPanel : public wxPanel {
public:
	MainPanel(wxWindow *parent);

private:
	WorkspaceListPanel *listPanel_{nullptr};

	void onAddWorkspace_(wxMouseEvent &);
};

