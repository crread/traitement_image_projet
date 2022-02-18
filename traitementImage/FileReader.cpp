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

void FileReader::writeImage(const std::string& path, const imageData& image) const
{
	struct jpeg_error_mgr jerr;
	struct jpeg_compress_struct cinfo;

	jpeg_create_compress(&cinfo);

	cinfo.err = jpeg_std_error(&jerr);

	FILE* file = fopen(path.c_str(), "rb");

	if (file == NULL) {
		printf("Error: failed to open %s\n", path.c_str());
		exit(1);
	}

	jpeg_stdio_dest(&cinfo, file);

	cinfo.image_width = image.width;
	cinfo.image_height = image.height;
	cinfo.input_components = image.output_components;
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cinfo);

	jpeg_start_compress(&cinfo, true);

	uint8_t* row = image.data;
	const uint32_t stride = image.width * image.output_components;

	for (int y = 0; y < image.height; y++) {
		jpeg_write_scanlines(&cinfo, &row, 1);
		row += stride;
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(file);

	return;
}

imageData FileReader::readImage(const std::string& path) const
{
	imageData newImage;

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	FILE* file;

	if ((file = fopen(path.c_str(), "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", path.c_str());
		exit(1);
	}

	jpeg_stdio_src(&cinfo, file);
	jpeg_read_header(&cinfo, true);
	jpeg_start_decompress(&cinfo);

	newImage.width = cinfo.image_width;
	newImage.height = cinfo.image_height;
	newImage.output_components = cinfo.output_components;
	newImage.data = new uint8_t[newImage.width * newImage.height * newImage.output_components];

	uint8_t* row = newImage.data;
	const uint32_t stride = newImage.width * newImage.output_components;

	for (int y = 0; y < newImage.height; y++) {
		jpeg_read_scanlines(&cinfo, &row, 1);
		row += stride;
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	fclose(file);

	return newImage;
}

imageData* FileReader::loadImages(const std::vector<std::string>& paths) const
{
	imageData* images = new imageData[paths.size()];
	size_t size = 0;

	for (const auto& path : paths)
	{
		images[size] = readImage(path);
		size++;
	}

	return images;
}