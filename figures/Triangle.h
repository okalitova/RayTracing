//
// Created by okalitova on 14.04.16.
//

#ifndef RAYTRACING_TRIANGLE_H
#define RAYTRACING_TRIANGLE_H

#include "Figure.h"

class Triangle : public Figure {
public:
    Vector a, b, c;
    Vector n; //вектор нормали
    Triangle(Vector init_a, Vector init_b, Vector init_c, RGB init_color, double init_reflectance, Figure* init_fake, double init_transparencyKoef, double init_transparency) {
        transparency = init_transparency;
        transparencyKoef = init_transparencyKoef;
        fake = init_fake;
        reflectance = init_reflectance;
        a = init_a;
        b = init_b;
        c = init_c;
        n = crossVector(a - b, a - c);
        color = init_color;
        id = TRIANGLE;
    }
    void setOrientation(bool orientation) {
        if (orientation) n = -1 * n;
    }
    Vector getIntersectionWithRay(Ray ray) {
        Vector res;
        res.x = NO_INTERSECT;
        res.y = NO_INTERSECT;
        res.z = NO_INTERSECT;
        if (scalar(ray.direction, n) != 0) {
            double d = scalar(a - ray.start, n) / scalar(ray.direction, n);
            if (d >= 0) {
                res = ray.start + ray.direction * d;
            } else {
                res.x = NO_INTERSECT;
                res.y = NO_INTERSECT;
                res.z = NO_INTERSECT;
                return res;
            }
        }
        double areaA = abs(cross(res - b, res - c)) / 2;
        double areaB = abs(cross(res - a, res - c)) / 2;
        double areaC = abs(cross(res - a, res - b)) / 2;
        double area = abs(cross(a - b, a - c)) / 2;
        if (abs(areaA + areaB + areaC - area) > e) {
            res.x = NO_INTERSECT;
            res.y = NO_INTERSECT;
            res.z = NO_INTERSECT;
        }
        return res;
    }

    Vector getNormal(Vector intersection) {
        return n;
    }

    RGB getColor(Vector intersection) {
        return color;
    }

    Plane getPlane(Vector intersection) {
        return Plane(a, b, c);
    }

    Vector getPoint() {
        return a;
    }

    Triangle* getReflection(Figure* figure) {
        Vector pnt = figure->getPoint();
        Ray newRay = figure->getPlane(pnt).getReflection(pnt, a - pnt);
        Vector newA = newRay.start + newRay.direction;
        newRay = figure->getPlane(pnt).getReflection(pnt, b - pnt);
        Vector newB = newRay.start + newRay.direction;
        newRay = figure->getPlane(pnt).getReflection(pnt, c - pnt);
        Vector newC = newRay.start + newRay.direction;
        return new Triangle(a, b, c, color, reflectance, figure, transparencyKoef, transparency);
    }
};

#endif //RAYTRACING_TRIANGLE_H
