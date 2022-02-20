#pragma once
#ifndef _IMAGE_MANAGER_H_
#define _IMAGE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

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

    bool pixelAreEquals(const ImageData& imageA, const ImageData& imageB, int position) const;

public:
    ImageManager() 
    {
        images = nullptr;
        numberImages = 0;
    };

    ~ImageManager() 
    {
        for (uint32_t i = 0; i < numberImages; i++)
        {
            freeImage(images[i]);
        }

        delete[] images;
    };

    void removeNoise(ImageData& grayImage, const int radius) const;
    ImageData getGrayScaleImage(const ImageData& image) const;
    uint8_t test(const ImageData& image, const int radius, const int position, const int f) const;
    std::vector<uint32_t> meanShift(const ImageData& image, const int threshold, const int radius, uint32_t position) const;
    void fusionImages(const ImageData& background, const ImageData& frame, const ImageData& mask) const;
    ImageData getMask(const ImageData& background, ImageData& frame) const;
    ImageData getBackground() const;
    void freeImage(ImageData& image) const;

    size_t getNumberImages() const;
    void setNumberImages(size_t numberImages);

    ImageData& getImages() const;
    ImageData& getImage(const int position) const;
    void setImages(ImageData* listPath);
};

#endif // !_IMAGE_H_
