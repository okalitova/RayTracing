//
// Created by okalitova on 14.04.16.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "Sphere.h"
#include "Figure.h"

class Sphere : public Figure {
public:
    double r;
    Vector center;
    Sphere(Vector init_center, double init_r, RGB init_color, double init_reflectance, Figure* init_fake, double init_transparencyKoef, double init_transparency) {
        transparency = init_transparency;
        transparencyKoef = init_transparencyKoef;
        fake = init_fake;
        center = init_center;
        r = init_r;
        color = init_color;
        reflectance = init_reflectance;
        id = SPHERE;
    }
    Vector getIntersectionWithRay(Ray ray) {
        Vector k = center - ray.start;
        ray.direction.norm();
        float b = scalar(k, ray.direction);
        float c = scalar(k, k) - r * r;
        float d = b * b - c;

        if (d >=0)
        {
            float sqrtfd = sqrtf(d);
            float t1 = b + sqrtfd;
            float t2 = b - sqrtfd;

            float min_t  = min(t1,t2);
            float max_t = max(t1,t2);

            float t;
            if (min_t < 0) t = max_t;
                else t = min_t;
            Vector ans = ray.start + ray.direction * t;
            if (t >= 0) {
                return ans;
            }
        }
        return Vector(NO_INTERSECT, NO_INTERSECT, NO_INTERSECT);
    }

    Vector getNormal(Vector intersection) {
        return (intersection - center);
    }

    RGB getColor(Vector intersection) {
        return color;
    }

    Plane getPlane(Vector intersection) {
        Vector p, q;
        p = crossVector(center - intersection, Vector(0, 0, 1));
        q = crossVector(center - intersection, Vector(0, 1, 0));
        return Plane(intersection, intersection + p, intersection + q, getNormal(intersection));
    }

    Vector getPoint() {
        return center + Vector(0, 0, r);
    }

    Sphere* getReflection(Figure* figure) {
        Vector pnt = figure->getPoint();
        Ray newRay = figure->getPlane(pnt).getReflection(pnt, center - pnt);
        Vector newCenter = newRay.start + newRay.direction;
        return new Sphere(newCenter, r, color, reflectance, figure, transparencyKoef, transparency);
    }
};

#endif //RAYTRACING_SPHERE_H
