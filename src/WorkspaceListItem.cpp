#include "WorkspaceListItem.h"
#include "WorkspaceListPanel.h"
#include "TextButton.h"
#include "def.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/log.h>
#include <wx/button.h>


WorkspaceListItem::WorkspaceListItem(wxWindow *parent, wxString const &workspaceName, wxString const &folderPath, std::function<void()> onRemove)
	: path_(folderPath), wxPanel(parent, wxID_ANY) {
	
	onRemove_ = onRemove;
	SetBackgroundColour(PANEL_ITEM_COLOUR);
	SetForegroundColour(*wxWHITE);
	Bind(wxEVT_ENTER_WINDOW, &WorkspaceListItem::onEnterWindow_, this);
	Bind(wxEVT_LEAVE_WINDOW, &WorkspaceListItem::onLeaveWindow_, this);
	Bind(wxEVT_LEFT_UP, &WorkspaceListItem::onClick_, this);


	wxStaticText *workspaceText = new wxStaticText(this, wxID_ANY, workspaceName, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_VERTICAL | wxALIGN_CENTRE_HORIZONTAL);
	workspaceText->SetFont(workspaceText->GetFont().Scale(1.5));
	workspaceText->Bind(wxEVT_ENTER_WINDOW, &WorkspaceListItem::onEnterWindow_, this);

	wxStaticText *folderPathText = new wxStaticText(this, wxID_ANY, path_);
	folderPathText->SetFont(folderPathText->GetFont().Scale(1.2f));
	folderPathText->Bind(wxEVT_ENTER_WINDOW, &WorkspaceListItem::onEnterWindow_, this);

	TextButton *removeButton = new TextButton(this, wxString(" Del "), wxSize(40, 30), *wxRED, *wxBLACK, 1.5f);
	removeButton->Bind(wxEVT_LEFT_UP, &WorkspaceListItem::remove_, this);

	wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *textSizer = new wxBoxSizer(wxVERTICAL);

	textSizer->Add(workspaceText, 1, wxLEFT, 10);
	textSizer->Add(folderPathText, 1, wxLEFT, 10);
	
	mainSizer->Add(textSizer, 1);
	mainSizer->Add(removeButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	
	SetSizer(mainSizer);
}

void WorkspaceListItem::onEnterWindow_(wxMouseEvent &event) {
	SetBackgroundColour(PANEL_ITEM_HOVER_COLOUR);
	SetCursor(wxCURSOR_HAND);
	Refresh();
}

void WorkspaceListItem::onLeaveWindow_(wxMouseEvent &) {
	SetBackgroundColour(PANEL_ITEM_COLOUR);
	SetCursor(wxCURSOR_ARROW);
	Refresh();
}

void WorkspaceListItem::onClick_(wxMouseEvent &) {
	std::system("code " + path_);
}

void WorkspaceListItem::remove_(wxMouseEvent &) {
	onRemove_();
}
