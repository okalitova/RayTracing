//
// Created by okalitova on 16.04.16.
//

#include "../rendering/RGB.h"
#include "Spot.h"

Spot::Spot(RGB init_color, double init_colorPower, double init_lightPower) {
    color = init_color;
    colorPower = init_colorPower;
    lightPower = init_lightPower;
}
