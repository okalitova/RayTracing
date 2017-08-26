//
// Created by okalitova on 14.04.16.
//

#ifndef RAYTRACING_GEOMETRY_H
#define RAYTRACING_GEOMETRY_H

#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Vector {
public:
    double x;
    double y;
    double z;
    double length();

    Vector() {
        x = 0;
        y = 0;
        z = 0;
    };
    Vector(double init_x, double init_y, double init_z) {
        x = init_x;
        y = init_y;
        z = init_z;
    }
    double length2();

    Vector turn90();

    void norm();
};

bool operator == (const Vector &a, const Vector &b);

Vector operator + (Vector a, Vector b);

Vector operator - (Vector b, Vector a);

Vector operator * (double n, Vector a);

Vector operator / (Vector a, double n);

Vector operator * (Vector a, double n);

double scalar(Vector a, Vector b);

double cross(Vector a, Vector b);

Vector crossVector(Vector a, Vector b);

double getCos(Vector a, Vector b);

double area(vector<Vector> polygon);

bool sortByX(Vector a, Vector b);

vector<Vector> convex(vector<Vector> polygon);

bool isBigAngle(Vector a, Vector b, Vector c);

vector<Vector> getTriangle(Vector a, Vector b, Vector c);

class Line {
public:
    double a, b, c;
    Line() {}
    Line(double a_init, double b_init, double c_init) : a(a_init), b(b_init), c(c_init) {}
};

Vector intersectLines(Line line1, Line line2);

Line getLine(Vector a, Vector b);

bool isParallel(Line line1, Line line2);

bool isTheSameLine(Line line1, Line line2);

bool isInInterval(Vector x, Vector a, Vector b);

class Ray {
public:
    Vector start;
    Vector direction;
    Ray(Vector init_start, Vector init_direction);
};

class Plane {
private:
    Vector q, p;
    Vector n;
public:
    Plane(Vector init_a, Vector init_b, Vector init_c) {
        q = init_a - init_b;
        p = init_a - init_c;
        n = crossVector(q, p);
        n = n / n.length();
    }

    Plane(Vector init_a, Vector init_b, Vector init_c, Vector init_n) {
        q = init_a - init_b;
        p = init_a - init_c;
        n = init_n;
        n = n / n.length();
    }

    Vector getNormal() {
        return n;
    }

    Ray getReflection(Vector intersection, Vector direction) {
        Vector norm = n;
        double cos = scalar(n, direction);
        if (cos > 0) {
            norm =  -1 * n;
        }
        double h = scalar(direction, -1 * norm);
        return Ray(intersection, direction + norm * 2 * h);
    }

    Ray getTransparencyRay(Vector intersection, Vector direction, double transparencyKoef) {
        Vector norm = n;
        double cos = scalar(n, direction);
        if (cos < 0) {
            norm =  -1 * n;
            transparencyKoef = 1 / transparencyKoef;
        }
        Vector newDirection = norm * 1000 + ((direction - norm * 1000) * transparencyKoef);
        return Ray(intersection, newDirection);
    }
};

#endif //RAYTRACING_GEOMETRY_H
