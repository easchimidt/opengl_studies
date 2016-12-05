//
// Created by Emanuel Schimidt on 21/11/16.
//

#include "Utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Utils::readImageFile(std::string filename, Image *image, bool greyscale) {
    int components = (greyscale ? 1 : 4); // # of components (rgba) desired from the image
    image->rgb = stbi_load( filename.c_str(), &(image->width), &image->height, &image->bpp, components );

    if (image->rgb == NULL) {
        std::ostringstream os;
        os << "Error reading file " << filename << ". Error: " << strerror(errno) << std::endl;
        throw std::invalid_argument(os.str());
    }
}

void Utils::freeStb(unsigned char *std_pointer) {
    stbi_image_free( std_pointer );
}
