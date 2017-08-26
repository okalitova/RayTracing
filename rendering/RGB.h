//
// Created by okalitova on 14.04.16.
//

#ifndef RAYTRACING_RGB_H
#define RAYTRACING_RGB_H

class RGB {
public:
    int r, g, b;
public:
    RGB(unsigned char init_r, unsigned char init_g, unsigned char init_b);
    RGB();
    RGB operator+ (RGB rgb);

    RGB operator* (double n);
};

#endif //RAYTRACING_RGB_H
