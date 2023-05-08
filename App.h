#pragma once

#include <wx/app.h>

class App : public wxApp {
protected:
	virtual bool OnInit() override;
};

