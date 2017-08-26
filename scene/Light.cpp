//
// Created by okalitova on 16.04.16.
//

#include "Light.h"

Light::Light(Vector init_position, double init_power, vector<Figure*> init_figuresToIntersect) {
    position = init_position;
    power = init_power;
    figuresToIntersect = init_figuresToIntersect;
}