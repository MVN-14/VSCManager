#include "IOHelper.h"

#include <wx/string.h>

#include <fstream>
#include <filesystem>
#include <ostream>

#include <direct.h> // _mkdir

void writeWorkspaceToFile(wxString const &path)
{	
	std::ofstream ofstream(getFolderListPath(), std::ios_base::app);
	if (ofstream)
		ofstream << path << '\n';
}

std::string getFolderListPath() {
	char *path;
	size_t length;
	std::string dir{""};
	if (0 != _dupenv_s(&path, &length, "appdata")) {
		free(path);
		return dir;
	}

	if (path) {
		dir = std::string(path) + "\\VSCManager";
		free(path);
	}
	if (!std::filesystem::exists(dir)) {
		if (0 != _mkdir(dir.c_str()))
			return dir;
	}

#ifdef _DEBUG
	return dir + "\\folders-debug.txt";
#else
	return dir + "\\folders.txt";
#endif
}
