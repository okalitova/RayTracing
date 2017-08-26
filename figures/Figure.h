//
// Created by okalitova on 14.04.16.
//

#ifndef RAYTRACING_FIGURE_H
#define RAYTRACING_FIGURE_H


#include "../geometry/Geometry.h"
#include "../rendering/RGB.h"

class Figure {
protected:
    constexpr double static NO_INTERSECT = 1e9;
    constexpr double static e = 20;
public:
    constexpr int static SPHERE = 1;
    constexpr int static TRIANGLE = 2;
    constexpr int static QUADRANGLE = 3;
    int id;
    Figure* fake;
    RGB color;
    double transparency;
    double reflectance;
    double transparencyKoef;
public:
    virtual Vector getIntersectionWithRay(Ray ray) = 0;
    virtual Vector getNormal(Vector intersection) = 0;
    virtual RGB getColor(Vector intersection) = 0;
    virtual Plane getPlane(Vector intersection) = 0;
    virtual Vector getPoint() = 0;
    virtual Figure* getReflection(Figure* figure) = 0;
};

#endif //RAYTRACING_FIGURE_H
