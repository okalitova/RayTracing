//
// Created by okalitova on 16.04.16.
//

#ifndef RAYTRACING_LIGHT_H
#define RAYTRACING_LIGHT_H

#include "../rendering/RGB.h"
#include "../geometry/Geometry.h"
#include "../figures/Figure.h"

class Light {
private:
    Vector position;
    double power;
    RGB color;
public:
    vector<Figure *> getFiguresToIntersect() {
        return figuresToIntersect;
    }

    void setFiguresToIntersect(vector<Figure *> figuresToIntersect) {
        Light::figuresToIntersect = figuresToIntersect;
    }

private:
    vector<Figure*> figuresToIntersect;
public:
    double getPower() const {
        return power;
    }

    void setPower(double power) {
        Light::power = power;
    }

    const Vector &getPosition() const {
        return position;
    }

    void setPosition(const Vector &position) {
        Light::position = position;
    }

    const RGB &getColor() const {
        return color;
    }

    void setColor(const RGB &color) {
        Light::color = color;
    }
public:
    Light (Vector init_position, double init_power, vector<Figure*> init_figuresToIntersect);
};

#endif //RAYTRACING_LIGHT_H
