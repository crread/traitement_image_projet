#include "ImageManager.h"

void ImageManager::alloc_image(imageData* imageData) const
{
    imageData->data = NULL;
    imageData->data = (uint8_t*) malloc(sizeof(uint8_t*) * imageData->width * imageData->height * imageData->ch);
}

void ImageManager::free_image(imageData* imageData) const
{
    if (imageData->data != NULL) 
    {
        free(imageData->data);
    }
}

imageData& ImageManager::getImages() const
{
	return *images;
}

void ImageManager::setImages(std::vector<std::string>& listPath)
{

}