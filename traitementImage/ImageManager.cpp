#include "ImageManager.h"

void ImageManager::freeImage(ImageData& image) const
{
	delete[] image.data;
}

ImageData& ImageManager::getImages() const
{
	return *images;
}

void ImageManager::setImages(ImageData* images)
{
    this->images = images;
}

size_t ImageManager::getNumberImages() const
{
	return this->numberImages;
}

void ImageManager::setNumberImages(size_t numberImages)
{
	this->numberImages = numberImages;
}

ImageData ImageManager::getBackground() const
{
	ImageData backgroundImage;

	backgroundImage.width = images[0].width;
	backgroundImage.height = images[0].height;
	backgroundImage.output_components = images[0].output_components;

	backgroundImage.data = new uint8_t[backgroundImage.width * backgroundImage.height * backgroundImage.output_components];

	std::vector<uint8_t> color;
	
	uint32_t size = backgroundImage.width * backgroundImage.height * backgroundImage.output_components;

	unsigned short coef = 9;

	for (uint32_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < coef; j++)
		{
			color.push_back(images[j * (numberImages / coef)].data[i]);
		}
		
		color.push_back(images[numberImages - 1].data[i]);
		std::sort(color.begin(), color.end());
		backgroundImage.data[i] = color.at(color.size() / 2);
		color.clear();
	}

	return backgroundImage;
}