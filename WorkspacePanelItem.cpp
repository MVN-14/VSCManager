#include "WorkspacePanelItem.h"
#include "def.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/log.h>
#include <windows.h>
#include <process.h>

WorkspacePanelItem::WorkspacePanelItem(wxWindow *parent, wxString const &workspaceName, wxString const &folderPath)
	: path_(folderPath), wxPanel(parent, wxID_ANY) {

	SetBackgroundColour(PANEL_ITEM_COLOUR);
	SetForegroundColour(*wxWHITE);
	Bind(wxEVT_ENTER_WINDOW, &WorkspacePanelItem::onEnterWindow, this);
	Bind(wxEVT_LEAVE_WINDOW, &WorkspacePanelItem::onLeaveWindow, this);
	Bind(wxEVT_LEFT_UP, &WorkspacePanelItem::onClick, this);

	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText *workspaceText = new wxStaticText(this, wxID_ANY, workspaceName);
	workspaceText->SetFont(workspaceText->GetFont().Scale(1.5));
	workspaceText->Bind(wxEVT_ENTER_WINDOW, &WorkspacePanelItem::onEnterWindow, this);

	wxStaticText *folderPathText = new wxStaticText(this, wxID_ANY, path_);
	folderPathText->SetFont(folderPathText->GetFont().Scale(1.2f));
	folderPathText->Bind(wxEVT_ENTER_WINDOW, &WorkspacePanelItem::onEnterWindow, this);

	mainSizer->Add(workspaceText, 1, wxLEFT, 10);
	mainSizer->Add(folderPathText, 1, wxLEFT, 10);
	
	SetSizer(mainSizer);
}

void WorkspacePanelItem::onEnterWindow(wxMouseEvent &) {
	SetBackgroundColour(PANEL_ITEM_HOVER_COLOUR);
	SetCursor(wxCURSOR_HAND);
	Refresh();
}

void WorkspacePanelItem::onLeaveWindow(wxMouseEvent &) {
	SetBackgroundColour(PANEL_ITEM_COLOUR);
	SetCursor(wxCURSOR_ARROW);
	Refresh();
}

void WorkspacePanelItem::onClick(wxMouseEvent &) {

	std::system("code " + path_);
	//STARTUPINFO startupInfo{0};
	//startupInfo.cb = sizeof(STARTUPINFO);
	//PROCESS_INFORMATION processInfo{0};
	//unsigned long const CP_MAX_COMMANDLINE = 32768;
	////std::wstring command = L"code \"" + path_.ToStdWstring() + L"\"";
	//std::wstring command = L"code .";


	//wchar_t *commandLine = new wchar_t[CP_MAX_COMMANDLINE];
	//wcsncpy_s(commandLine, CP_MAX_COMMANDLINE, command.c_str(), command.size() + 1);

	//auto res = CreateProcess(
	//	NULL,
	//	commandLine,
	//	NULL,
	//	NULL,
	//	false,
	//	0,
	//	NULL,
	//	NULL,
	//	&startupInfo,
	//	&processInfo
	//);

	//if (!res)
	//	auto error = GetLastError();

	//delete[] commandLine;
	//
	//CloseHandle(processInfo.hThread);
	//CloseHandle(processInfo.hProcess);
}
