#include "MainPanel.h"
#include "WorkspacePanel.h"
#include "def.h"

#include <wx/sizer.h>

MainPanel::MainPanel(wxWindow *parent) 
	: wxPanel(parent) {

	SetBackgroundColour(BG_COLOUR);

	wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

	WorkspacePanel *workspacePanel = new WorkspacePanel(this);
	mainSizer->Add(workspacePanel, 1);

	SetSizerAndFit(mainSizer);
}

