//
// Created by okalitova on 16.04.16.
//

#include "Scene.h"

Scene::Scene(Camera init_camera, Screen init_screen, vector <Figure*> init_figures, vector <Light*> init_lights) {
    camera = init_camera;
    screen = init_screen;
    figures = init_figures;
    lights = init_lights;
}
