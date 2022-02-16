#pragma once
#ifndef _IMAGE_MANAGER_H_
#define _IMAGE_H_

#include <iostream>
#include <string>
#include <vector>

#include "jpeglib.h"
#include "turbojpeg.h"

struct imageData {
    uint8_t* data;   // raw data
    uint32_t width;
    uint32_t height;
    uint32_t ch;     // color channels
};

class ImageManager {

    imageData* images;

    void alloc_image(imageData* imageData) const;
    void free_image(imageData* imageData) const;

public:
    imageData& getImages() const;
    void setImages(std::vector<std::string>& listPath);
};

#endif // !_IMAGE_H_
