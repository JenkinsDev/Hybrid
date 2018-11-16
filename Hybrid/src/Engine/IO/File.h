#ifndef __JINX_FILE_H_
#define __JINX_FILE_H_

#include <string>

enum class FileLoadStatus { Error, Success };

FileLoadStatus loadFile(std::string file_path, std::string* out);

#endif