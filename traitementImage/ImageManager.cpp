#include "ImageManager.h"

imageData& ImageManager::getImages() const
{
	return *images;
}

void ImageManager::setImages(imageData* images)
{
    this->images = images;
}