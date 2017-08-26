//
// Created by okalitova on 16.04.16.
//

#ifndef RAYTRACING_SPOT_H
#define RAYTRACING_SPOT_H

#include "../rendering/RGB.h"

class Spot {
public:
    RGB getColor() const {
        return color;
    }

    void setColor(const RGB &color) {
        Spot::color = color;
    }

    double getColorPower() const {
        return colorPower;
    }

    void setColorPower(double colorPower) {
        Spot::colorPower = colorPower;
    }

    double getLightPower() const {
        return lightPower;
    }

    void setLightPower(double lightPower) {
        Spot::lightPower = lightPower;
    }

private:
    RGB color;
    double colorPower;
    double lightPower;
public:
    Spot(RGB init_color, double init_colorPower, double init_lightPower);
};

#endif //RAYTRACING_SPOT_H
