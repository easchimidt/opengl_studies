//
// Created by Emanuel Schimidt on 20/11/16.
//

#ifndef ESTUDOSOPENGL_UTILS_H
#define ESTUDOSOPENGL_UTILS_H

#include <sstream>
#include <math.h>
#include "stb_image.h"

class Utils {
public:
    struct Image {
        unsigned char* rgb;
        int width;
        int height;
        int bpp;
    };

    static void readImageFile(std::string filename, Image *image, bool greyscale);
    static void freeStb(unsigned char *std_pointer);

    static inline float toRadians(float angle) {
        return (float)(angle * M_PI / 180.0f);
    }

    static inline float toDegree(float radians) {
        return (float)(180.0f * radians / M_PI);
    }
};

#endif //ESTUDOSOPENGL_UTILS_H
