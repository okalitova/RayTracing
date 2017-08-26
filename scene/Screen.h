//
// Created by okalitova on 16.04.16.
//

#ifndef RAYTRACING_SCREEN_H
#define RAYTRACING_SCREEN_H

#include "../geometry/Geometry.h"

class Screen {
public:
    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        Screen::height = height;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        Screen::width = width;
    }

    const Vector &getLeft_down() const {
        return left_down;
    }

    void setLeft_down(const Vector &left_down) {
        Screen::left_down = left_down;
    }

    const Vector &getLeft_up() const {
        return left_up;
    }

    void setLeft_up(const Vector &left_up) {
        Screen::left_up = left_up;
    }

    const Vector &getRight_down() const {
        return right_down;
    }

    void setRight_down(const Vector &right_down) {
        Screen::right_down = right_down;
    }

    const Vector &getRight_up() const {
        return right_up;
    }

    void setRight_up(const Vector &right_up) {
        Screen::right_up = right_up;
    }

private:
    int height;
    int width;
    Vector left_down, left_up, right_down, right_up;
public:
    Screen();

    Screen(int init_width, int init_height, Vector init_left_down, Vector init_left_up,
    Vector init_right_down, Vector init_right_up);

    double getCellWidth() {
        return ((right_up - left_up).length() / width);
    }

    double getCellHeight() {
        return ((left_up - left_down).length() / height);
    }
};

#endif //RAYTRACING_SCREEN_H
