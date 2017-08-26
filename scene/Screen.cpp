//
// Created by okalitova on 16.04.16.
//

#include "Screen.h"

Screen::Screen(int init_width, int init_height, Vector init_left_down, Vector init_left_up, Vector init_right_down,
               Vector init_right_up) {
    width = init_width;
    height = init_height;
    left_down = init_left_down;
    left_up = init_left_up;
    right_down = init_right_down;
    right_up = init_right_up;
}

Screen::Screen() { }