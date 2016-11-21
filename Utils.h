//
// Created by Emanuel Schimidt on 20/11/16.
//

#ifndef ESTUDOSOPENGL_UTILS_H
#define ESTUDOSOPENGL_UTILS_H

#define STB_IMAGE_IMPLEMENTATION

#include <sstream>
#include "stb_image.h"

class Utils {
public:
    struct Image {
        unsigned char* rgb;
        int width;
        int height;
        int bpp;
    };

    static void readImageFile(std::string filename, Image *image) {
        image->rgb = stbi_load( filename.c_str(), &(image->width), &image->height, &image->bpp, 1 );

        if (image->rgb == NULL) {
            std::ostringstream os;
            os << "Error reading file " << filename << ". Error: " << strerror(errno) << std::endl;
            throw std::invalid_argument(os.str());
        }
    }
};





#endif //ESTUDOSOPENGL_UTILS_H
