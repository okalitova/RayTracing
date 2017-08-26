//
// Created by okalitova on 14.04.16.
//

#include "Geometry.h"

const double e = 20;

double Vector::length() {
    return sqrt(x * x + y * y + z * z);
}

double Vector::length2() {
    return x * x + y * y + z * z;
}

void Vector::norm() {
    double l = this->length();
    if (x != 0)
        x = x / l;
    if (y != 0)
        y = y / l;
    if (z != 0)
        z = z / l;
}

bool operator == (const Vector &a, const Vector &b) {
    if ((a - b).length2() < e) {
        return true;
    } else {
        return false;
    }
}

Vector operator + (Vector a, Vector b) {
    Vector ab;
    ab.x = a.x + b.x;
    ab.y = a.y + b.y;
    ab.z = a.z + b.z;
    return ab;
}

Vector operator - (Vector b, Vector a) {
    Vector ab;
    if (a.x != 0)
        ab.x = b.x - a.x;
    else
        ab.x = b.x;
    if (a.y != 0)
        ab.y = b.y - a.y;
    else
        ab.y = b.y;
    if (a.z != 0)
        ab.z = b.z - a.z;
    else
        ab.z = b.z;
    return ab;
}

Vector operator * (double n, Vector a) {
    Vector an;
    if (a.x != 0)
        an.x = a.x * n;
    if (a.y != 0)
        an.y = a.y * n;
    if (a.z != 0)
        an.z = a.z * n;
    return an;
}

Vector operator / (Vector a, double n) {
    Vector an;
    if (a.x != 0)
        an.x = a.x / n;
    if (a.y != 0)
        an.y = a.y / n;
    if (a.z != 0)
        an.z = a.z / n;
    return an;
}

Vector operator * (Vector a, double n) {
    Vector an;
    if (a.x != 0)
        an.x = a.x * n;
    if (a.y != 0)
        an.y = a.y * n;
    if (a.z != 0)
        an.z = a.z * n;
    return an;
}

double scalar(Vector a, Vector b) {
    double res = 0;
    if (a.x != 0 && b.x != 0)
        res += a.x * b.x;
    if (a.y != 0 && b.y != 0)
        res += a.y * b.y;
    if (a.z != 0 && b.z != 0)
        res += a.z * b.z;
    return res;
}

double cross(Vector a, Vector b) {
    return sqrt((a.x * b.y - a.y * b.x) * (a.x * b.y - a.y * b.x) +
                        (a.x * b.z - a.z * b.x) * (a.x * b.z - a.z * b.x) +
                        (a.y * b.z - a.z * b.y) * (a.y * b.z - a.z * b.y));
}

Vector crossVector(Vector a, Vector b) {
    if ((a.x * b.z - a.z * b.x) != 0)
        return Vector((a.y * b.z - a.z * b.y), -1 * (a.x * b.z - a.z * b.x), (a.x * b.y - a.y * b.x));
    else
        return Vector((a.y * b.z - a.z * b.y), 0, (a.x * b.y - a.y * b.x));
}

double getCos(Vector a, Vector b) {
    return scalar(a, b) / a.length() / b.length();
}

Ray::Ray(Vector init_start, Vector init_direction) {
    start = init_start;
    direction = init_direction;
}
