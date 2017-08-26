//
// Created by okalitova on 14.04.16.
//

#include "RGB.h"

int mmin(int a, int b) {
    if (a < b) return a;
    else return b;
}

RGB::RGB(unsigned char init_r, unsigned char init_g, unsigned char init_b) {
    r = init_r;
    g = init_g;
    b = init_b;
}

RGB::RGB() {
    r = 0;
    g = 0;
    b = 0;
}

RGB RGB::operator+(RGB rgb) {
    RGB res;
    res.r = mmin(255, r + rgb.r);
    res.g = mmin(255, g + rgb.g);
    res.b = mmin(255, b + rgb.b);
    return res;
}

RGB RGB::operator*(double n) {
    RGB res;
    if (n > 1) n = 1;
    res.r = (int) (r * n);
    res.g = (int) (g * n);
    res.b = (int) (b * n);
    return res;
}
