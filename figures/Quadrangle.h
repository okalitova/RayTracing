//
// Created by nimloth on 22.04.16.
//

#ifndef RAYTRACING_QUADRANGLE_H
#define RAYTRACING_QUADRANGLE_H

#include <png++/rgb_pixel.hpp>
#include <png++/image.hpp>
#include "Figure.h"

class Quadrangle : public Figure {
private:
    Vector a, b, c, d;
    Vector n;
    png::image< png::rgb_pixel > image;
    string imageName;
public:
    Quadrangle(Vector init_A, Vector init_B, Vector init_C, Vector init_D, RGB init_color, string init_imageName, double init_reflectance, Figure* init_fake, double init_transparencyKoef, double init_transparency) {
        transparency = init_transparency;
        transparencyKoef = init_transparencyKoef;
        fake = init_fake;
        color = init_color;
        reflectance = init_reflectance;
        a = init_A;
        b = init_B;
        c = init_C;
        d = init_D;
        n = crossVector(a - b, a - c);
        //cout << n.x << " " << n.y << " " << n.z << "\n";
        imageName = init_imageName;
        if (imageName != "none") {
            image.read(imageName);
        }
        id = QUADRANGLE;
    }

    void setOrientation(bool orientation) {
        if (orientation) n = -1 * n;
    }

    Vector getNormal(Vector intersection) {
        return n;
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
        double areaA = abs(cross(res - a, res - b));
        double areaB = abs(cross(res - b, res - c));
        double areaC = abs(cross(res - c, res - d));
        double areaD = abs(cross(res -d, res - a));
        double area = abs(cross(a - b, a - c)) + abs(cross(a - c, a - d));
        if (abs(areaA + areaB + areaC + areaD - area) > e) {
            res.x = NO_INTERSECT;
            res.y = NO_INTERSECT;
            res.z = NO_INTERSECT;
        }
        return res;
    }

    RGB getColor(Vector intersection) {
        if (imageName == "none") {
            return color;
        } else {
            double cellWidth = (b - a).length() / image.get_width();
            double cellHeight = (d - a).length() / image.get_height();
            int x = scalar((intersection - a), (b - a)) / (b - a).length() / cellWidth;
            int y = scalar((intersection - a), (d - a)) / (d - a).length() / cellHeight;
            if (y < image.get_height() && x < image.get_width()) {
                return RGB(image[y][x].red, image[y][x].green, image[y][x].blue);
            } else {
                return color;
            }
        }
    }

    Plane getPlane(Vector intersection) {
        return Plane(a, b, c);
    }

    Vector getPoint() {
        return a;
    }

    Quadrangle* getReflection(Figure* figure) {
        Vector pnt = figure->getPoint();
        Ray newRay = figure->getPlane(pnt).getReflection(pnt, a - pnt);
        Vector newA = newRay.start + newRay.direction;
        newRay = figure->getPlane(pnt).getReflection(pnt, b - pnt);
        Vector newB = newRay.start + newRay.direction;
        newRay = figure->getPlane(pnt).getReflection(pnt, c - pnt);
        Vector newC = newRay.start + newRay.direction;
        newRay = figure->getPlane(pnt).getReflection(pnt, d - pnt);
        Vector newD = newRay.start + newRay.direction;
        return new Quadrangle(a, b, c, d, color, "none", reflectance, figure, transparencyKoef, transparency);
    }
};

#endif //RAYTRACING_QUADRANGLE_H
