#pragma once
#ifndef _IMAGE_MANAGER_H_
#define _IMAGE_H_

#include <iostream>
#include <string>
#include <vector>

#include "jpeglib.h"
#include "turbojpeg.h"

struct imageData {
    uint8_t* data;
    uint32_t width;
    uint32_t height;
    uint32_t output_components;
};

class ImageManager {

    imageData* images;
    uint32_t numberImages;

public:
    ImageManager() 
    {
        std::cout << "image manager constructor called" << std::endl;
        images = nullptr;
        numberImages = 0;
    };

    ~ImageManager() 
    {
        for (int i = 0; i < numberImages; i++)
        {
            delete[] images[i].data;
        }
        std::cout << "image manager deconstructor called" << std::endl;
        delete[] images;
    };

    imageData& getImages() const;
    void setImages(imageData* listPath);
};

#endif // !_IMAGE_H_
