#pragma once
#ifndef _IMAGE_MANAGER_H_
#define _IMAGE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "jpeglib.h"
#include "turbojpeg.h"

struct ImageData {
    uint8_t* data; // R,G,B
    uint32_t width;
    uint32_t height;
    uint32_t output_components;
};

class ImageManager {

    ImageData* images;
    size_t numberImages;

public:
    ImageManager() 
    {
        std::cout << "image manager constructor called" << std::endl;
        images = nullptr;
        numberImages = 0;
    };

    ~ImageManager() 
    {
        for (uint32_t i = 0; i < numberImages; i++)
        {
            freeImage(images[i]);
        }
        std::cout << "image manager deconstructor called" << std::endl;
        delete[] images;
    };

    ImageData getBackground() const;
    void freeImage(ImageData& image) const;

    size_t getNumberImages() const;
    void setNumberImages(size_t numberImages);

    ImageData& getImages() const;
    void setImages(ImageData* listPath);
};

#endif // !_IMAGE_H_
