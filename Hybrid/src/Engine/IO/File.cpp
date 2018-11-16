#include "File.h"
#include <fstream>
#include <sstream>

FileLoadStatus loadFile(std::string file_path, std::string* out) {
	std::ifstream fileStream(file_path, std::ios::in);

	if (fileStream.is_open()) {
		std::stringstream sstr;
		sstr << fileStream.rdbuf();

		*out = sstr.str();

		fileStream.close();
		return FileLoadStatus::Success;
	}

	return FileLoadStatus::Error;
}
