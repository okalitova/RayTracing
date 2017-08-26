//
// Created by okalitova on 14.04.16.
//

#ifndef RAYTRACING_IMAGE_H
#define RAYTRACING_IMAGE_H

#include "RGB.h"
#include <vector>
#include <png++/png.hpp>

using namespace std;

class Image {
private:
    int width;
    int height;
    vector<vector<RGB>> matrix;
public:
    Image(int init_height, int init_width);
    void setPixel(int x, int y, RGB color);
    void write(const char *filename) {
        png::image< png::rgb_pixel > res(width, height);
        for (size_t y = 0; y < height; ++y)
        {
            for (size_t x = 0; x < width; ++x)
            {
                res[y][x] = png::rgb_pixel(matrix[y][x].r,
                matrix[y][x].g, matrix[y][x].b);
            }
        }
        res.write(filename);
    }
};

#endif //RAYTRACING_IMAGE_H
