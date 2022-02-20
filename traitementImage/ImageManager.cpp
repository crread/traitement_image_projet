#include "ImageManager.hpp"

void ImageManager::freeImage(ImageData& image) const
{
	delete[] image.data;
}

ImageData& ImageManager::getImages() const
{
	return *images;
}

ImageData& ImageManager::getImage(const int position) const
{
	return images[position];
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

bool ImageManager::pixelAreEquals(const ImageData& imageA, const ImageData& imageB,int position) const
{
	return imageA.data[position] == imageB.data[position] && imageA.data[position + 1] == imageB.data[position + 1] && imageA.data[position + 2] == imageB.data[position + 2];
}

ImageData ImageManager::getGrayScaleImage(const ImageData& image) const
{
	ImageData grayImage;

	grayImage.height = image.height;
	grayImage.width = image.width;
	grayImage.output_components = 1;
	grayImage.data = new uint8_t[grayImage.height * grayImage.width * grayImage.output_components];

	uint32_t size = grayImage.width * grayImage.height * grayImage.output_components;

	for (uint32_t i = 0; i < size; i++)
	{
		grayImage.data[i] = image.data[i * 3] / 3 + image.data[i * 3 + 1] / 3 + image.data[i * 3 + 2] / 3;
	}

	return grayImage;
}

void ImageManager::removeNoise(ImageData& grayImage, const int radius) const
{
	uint32_t size = grayImage.width * grayImage.height * grayImage.output_components;
	std::vector<uint8_t> list;

	for (uint32_t position = 0; position < size; position++)
	{
		for (int i = (radius / 2) * -1; i <= (radius / 2); i++)
		{
			for (int j = (radius / 2) * -1; j <= (radius / 2); j++)
			{
				uint32_t currentPosition = position + grayImage.width * i * + j;

				if (currentPosition >= 0 && currentPosition < size)
				{
					list.push_back(grayImage.data[currentPosition]);
				}
			}
		}
		std::sort(list.begin(), list.end());
		grayImage.data[position] = list[list.size() / 2];
		list.clear();
	}
}

ImageData ImageManager::getMask(const ImageData& background, ImageData& grayFrame) const
{
	ImageData mask;
	mask.height = background.height; 
	mask.width = background.width;
	mask.output_components = 1;

	uint32_t size = mask.height * mask.width;
	int radius = 5;
	mask.data = new uint8_t[size];

	int threshold = 30;

	for (uint32_t position = 0; position < size; position++)
	{
		mask.data[position] = std::abs(background.data[position] - grayFrame.data[position]) < threshold ? 0 : 255;
	}

	return mask;
}

void ImageManager::fusionImages(const ImageData& background, const ImageData& frame, const ImageData& mask) const
{
	uint32_t size = mask.width * mask.height * mask.output_components;

	for (uint32_t i = 0; i < size; i++)
	{
		if (mask.data[i] == 255)
		{
			background.data[i * 3] = frame.data[i * 3];
			background.data[i * 3 + 1] = frame.data[i * 3 + 1];
			background.data[i * 3 + 2] = frame.data[i * 3 + 2];
		}
	}
}

ImageData ImageManager::getBackground() const
{
	ImageData backgroundImage;
	backgroundImage.width = images[0].width;
	backgroundImage.height = images[0].height;
	backgroundImage.output_components = images[0].output_components;

	std::vector<uint8_t> color;

	uint32_t size = backgroundImage.width * backgroundImage.height * backgroundImage.output_components;

	backgroundImage.data = new uint8_t[size];
	
	for (uint32_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < numberImages; j++)
		{
			color.push_back(images[j].data[i]);
		}
		
		std::sort(color.begin(), color.end());
		backgroundImage.data[i] = color.at(color.size() / 2);
		color.clear();
	}

	std::cout << "background built..." << std::endl;

	return backgroundImage;
}