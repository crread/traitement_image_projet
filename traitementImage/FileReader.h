#pragma once
#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <filesystem>
#include <string>
#include <vector>

class FileReader
{
public:
	bool isDirectory(std::string& path) const;
	std::vector<std::string> getImagesPathList(std::string& path) const;
};

#endif //!_FILE_READER_H_