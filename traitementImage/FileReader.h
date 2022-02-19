#pragma once
#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#define _CRT_SECURE_NO_DEPRECATE

#include <filesystem>
#include <string>
#include <vector>

#include <turbojpeg.h>

#include "ImageManager.h"

class FileReader
{

	bool isInExtension(const std::filesystem::path& path) const;

public:
	ImageData* loadImages(ImageManager& imageManager, const std::vector<std::string>& paths) const;
	ImageData readImage(const std::string& path) const;
	void writeImage(const std::string& path, const ImageData& image) const;
	bool isDirectory(std::string& path) const;
	std::vector<std::string> getImagesPathList(std::string& path) const;
};

#endif //!_FILE_READER_H_