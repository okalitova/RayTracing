//
// Created by okalitova on 16.04.16.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "../geometry/Geometry.h"

class Camera {
private:
public:
    const Vector &getPosition() const {
        return position;
    }

    void setPosition(const Vector &position) {
        Camera::position = position;
    }

private:
    Vector position;
public:
    Camera();

    Camera(Vector init_position);
};

#endif //RAYTRACING_CAMERA_H
