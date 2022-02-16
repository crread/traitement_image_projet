#include "FileReader.h"

bool FileReader::isDirectory(std::string& path) const
{
	return std::filesystem::is_directory(path);
}

std::vector<std::string> FileReader::getImagesPathList(std::string& path) const
{
	std::vector<std::string> imagePaths;

	const std::string extension = "jpeg";

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (entry.path().extension() == extension)
		{
			std::string path_string{ entry.path().u8string() };
			imagePaths.push_back(path_string);
		}
	}

	return imagePaths;
}