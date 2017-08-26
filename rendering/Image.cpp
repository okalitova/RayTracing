//
// Created by okalitova on 14.04.16.
//

#include "Image.h"

Image::Image(int init_height, int init_width) {
    height = init_height;
    width = init_width;
    matrix.resize(height);
    for (int i = 0; i < height; ++i) {
        matrix[i].resize(width);
    }
}

void Image::setPixel(int x, int y, RGB color) {
    matrix[x][y] = color;
}
