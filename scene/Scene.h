//
// Created by okalitova on 16.04.16.
//

#pragma once

#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H

#include <vector>
#include "../figures/Figure.h"
#include "Camera.h"
#include "Screen.h"
#include "Light.h"
#include "../rendering/Image.h"
#include "Spot.h"
#include "../figures/Sphere.h"
#include <algorithm>
#include <thread>
//#include "../ThreadPool.h"


#include <thread>
#include <future>
#include <memory>

class Scene;

class Comparator {
public:
    Vector pnt;
    bool operator()(pair<Figure*, Vector> a, pair<Figure*, Vector> b) {
        if ((a.second - pnt).length() < (b.second - pnt).length()) {
            return true;
        }
        return false;
    }
};

class Scene {
public:
    Screen screen;
private:
    Camera camera;
    vector <Figure*> figures;
    vector <Light*> lights;
    constexpr double static NO_INTERSECT = 1e9;
    constexpr double static e = 20;
    Vector camDirection;
public:
    Scene(Camera init_camera, Screen init_screen, vector<Figure*> init_figures, vector<Light*> init_lights);

    /*void getScreen(Image &img, int i1, int i2, int j1, int j2) {
        for (int i = i1; i < i2; ++i) {
            for (int j = j1; j < j2; ++j) {
                img.setPixel(i, j, getPixel(i, j));
            }
        }
    }

    Image getScreenMultithread() {
        Image image(screen.getHeight(), screen.getWidth());
        thread thread1(&Scene::getScreen, this, std::ref(image), 0, screen.getHeight() / 2, 0, screen.getWidth() / 2);
        thread thread2(&Scene::getScreen, this, std::ref(image), screen.getHeight() / 2, screen.getHeight(), 0, screen.getWidth() / 2);
        thread thread3(&Scene::getScreen, this, std::ref(image), 0, screen.getHeight() / 2, screen.getWidth() / 2, screen.getWidth());
        thread thread4(&Scene::getScreen, this, std::ref(image), screen.getHeight() / 2, screen.getHeight(), screen.getWidth() / 2, screen.getWidth());
        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
        return image;
    }*/

    /*Image getScreen() {

        return image;
    }*/

    RGB getPixel(int x, int y) {
        Vector pixelPosition;
        Vector pixelPositionA = screen.getLeft_up() + (screen.getRight_up() - screen.getLeft_up()) * ((double)(y) / (double)screen.getWidth());
        Vector pixelPositionB = screen.getLeft_down() + (screen.getRight_down() - screen.getLeft_down()) * ((double)(y) / (double)screen.getWidth());
        pixelPosition = pixelPositionA + (pixelPositionB - pixelPositionA) * ((double) (x) / (double) screen.getHeight());
        Ray startRay(camera.getPosition(), pixelPosition - camera.getPosition());
        vector <Spot> spots;
        rayTrace(startRay, 4, 1, spots);
        return getPixelColor(spots);
    }

    void rayTrace(Ray ray, int depth, double colorPower, vector <Spot> &spots) {
        pair <Figure*, Vector> intersection = getIntersection(ray);
        camDirection = ray.direction;
        Spot spot = getSpot(intersection, colorPower);
        spots.push_back(spot);
        if (depth == 1) {
            return;
        } else {
            if (intersection.first == NULL) {
                return;
            }
            double colorPowerNew = intersection.first->reflectance * colorPower;
            if (colorPowerNew == 0) {
            } else {
                Ray newRay = intersection.first->getPlane(intersection.second).getReflection(intersection.second, ray.direction);
                rayTrace(newRay, depth - 1, colorPowerNew, spots);
            }
            colorPowerNew = intersection.first->transparency * colorPower;
            if (colorPowerNew == 0) {
            } else {
                Ray newRay = intersection.first->getPlane(intersection.second)
                        .getTransparencyRay(intersection.second, ray.direction, intersection.first->transparencyKoef);
                //cout << "direction: " << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z << "\n";
                //cout << "directionNew: " << newRay.direction.x << " " << newRay.direction.y << " " << newRay.direction.z << "\n";
                rayTrace(newRay, depth - 1, colorPowerNew, spots);
            }
        }
    }

    pair <Figure*, Vector> getIntersection(Ray ray) {
        Vector closest;
        closest.x = NO_INTERSECT;
        closest.y = NO_INTERSECT;
        double mmin = NO_INTERSECT;
        Figure* closestFigure = NULL;
        for (int i = 0; i < figures.size(); ++i) {
            if (figures[i]->fake ==  NULL) {
                Vector intersection = figures[i]->getIntersectionWithRay(ray);
                if (intersection.x != NO_INTERSECT || intersection.y != NO_INTERSECT ||
                    intersection.z != NO_INTERSECT) {
                    if (mmin > (intersection - ray.start).length() && (intersection - ray.start).length() > e) {
                        mmin = (intersection - ray.start).length();
                        closest = intersection;
                        closestFigure = figures[i];
                    }
                }
            }
        }
        return make_pair(closestFigure, closest);
    }

    Spot getSpot(pair <Figure*, Vector> intersection, double colorPower) {
        if (intersection.first == NULL) {
            return Spot(RGB(0, 0, 0), 1, 0);
        }
        Figure* figure = intersection.first;
        double spotColorPower = colorPower - figure->reflectance - figure->transparency;
        if (spotColorPower < 0) {
            spotColorPower = 0;
        }
        return Spot(figure->getColor(intersection.second), spotColorPower, getLight(intersection));
    }

    double getLight(pair <Figure*, Vector> intersection) {
        double light = 0;
        for (int i = 0; i < lights.size(); ++i) {
            //check side
            /*Vector norm = intersection.first->getNormal(intersection.second);
            if (scalar(norm, camDirection) > 0) {
                norm = (-1) * norm;
            }
            Vector lightDirection = lights[i]->getPosition() - intersection.second;*/
            //cout << lights[i]->getFiguresToIntersect().size() << "\n";
            /*if (lights[i]->getFiguresToIntersect().size() != 0) {
                cout << norm.x << " " << norm.y << " " << norm.z << "\n";
                cout << "light: " << lightDirection.x << " " << lightDirection.y << " " << lightDirection.z << "\n";
                cout << scalar(norm, lights[i]->getPosition() - intersection.second) << "\n";
            }*/
            /*double cosN = scalar(norm, lightDirection) / norm.length() / lightDirection.length();
            if (cosN < -0.1) {
                if (intersection.first->id == Figure::SPHERE && norm.z < 0 && lightDirection.z < 0) {
                    cout << "scalar: " << cosN << "\n";
                    cout << norm.x << " " << norm.y << " " << norm.z << "\n";
                    cout << "light: " << lightDirection.x << " " << lightDirection.y << " " << lightDirection.z << "\n";

                }
                //cout << norm.x << " " << norm.y << " " << norm.z << "\n";
                //cout << "light: " << lightDirection.x << " " << lightDirection.y << " " << lightDirection.z << "\n";
                continue;
            }
            //if (lights[i]->getFiguresToIntersect().size() != 0) continue;
            /*Ray ray(lights[i]->getPosition(), intersection.second - lights[i]->getPosition());
            pair <Figure*, Vector> lightIntersection = getIntersection(ray);
            if (intersection.second == lightIntersection.second) {
                Vector n = intersection.first->getNormal(intersection.second);
                Vector dist = lights[i]->getPosition() - intersection.second;
                double cos = getCos(dist, n);
                if (cos < 0) cos = -cos;
                light += lights[i]->getPower() * cos / dist.length2();
            }*/
            Ray ray(lights[i]->getPosition(), intersection.second - lights[i]->getPosition());
            vector <pair<Figure*, Vector>> intersectedFigures;
            Comparator cmp;
            cmp.pnt = ray.start;
            for (int j = 0; j < figures.size(); ++j) {
                Vector inter = figures[j] -> getIntersectionWithRay(ray);
                if (inter.x != NO_INTERSECT || inter.y != NO_INTERSECT || inter.z != NO_INTERSECT) {
                    intersectedFigures.push_back(make_pair(figures[j], inter));
                }
            }
            sort(intersectedFigures.begin(), intersectedFigures.end(), cmp);
            vector <Figure*> figuresToIntersect = lights[i]->getFiguresToIntersect();
            figuresToIntersect.push_back(intersection.first);
            /*cout << "figuresToIntersect" << "\n";
            for (int z = 0; z < figuresToIntersect.size(); z++) {
                RGB color =  figuresToIntersect[z]->color;
                cout << color.r << " " << color.g << " " << color.b << "\n";
            }*/
            int cur = 0;
            bool flag = false;
            Vector finalIntersection;
            double koef = 1;
            for (int z = 0; z < figuresToIntersect.size(); ++z) {
                if (cur == intersectedFigures.size() || flag) {
                    flag = true;
                    break;
                }
                for (int j = cur; j < intersectedFigures.size(); ++j) {
                    if (intersectedFigures[j].first == figuresToIntersect[z]) {
                        if (z == figuresToIntersect.size() - 1) {
                            finalIntersection = intersectedFigures[j].second;
                        } else {
                            cur = j + 1;
                            koef *= intersectedFigures[j].first->reflectance;
                        }
                        break;
                    } else {
                        if (z == figuresToIntersect.size() - 1) {
                            if (intersectedFigures[j].first->fake == NULL) {
                                koef *= intersectedFigures[j].first->transparency;
                            } else {
                                continue;
                            }
                        } else {
                            if (intersectedFigures[j].first->fake == figuresToIntersect[z]) {
                                koef *= intersectedFigures[j].first->transparency;
                            } else {
                                continue;
                            }
                        }
                    }
                }
            }
            if (!flag && intersection.second == finalIntersection) {
                Vector n = intersection.first->getNormal(intersection.second);
                Vector dist = lights[i]->getPosition() - intersection.second;
                double cos = getCos(dist, n);
                if (cos < 0) cos = -cos;
                light += lights[i]->getPower() * cos / dist.length2() * koef;
            }
            /*int num = figuresToIntersect.size();
            if (num <= intersectedFigures.size()) {
                int flag = 0;
                for (int j = 0; j < num; ++j) {
                    if (intersectedFigures[j].first == figuresToIntersect[j]) {
                        flag++;
                    }
                }
                if (flag == num && intersection.second == intersectedFigures[num - 1].second) {
                    Vector n = intersection.first->getNormal(intersection.second);
                    Vector dist = lights[i]->getPosition() - intersection.second;
                    double cos = getCos(dist, n);
                    if (cos < 0) cos = -cos;
                    light += lights[i]->getPower() * cos / dist.length2();
                }
            }*/
        }
        return light;
    }

    RGB getPixelColor(vector <Spot> spots) {
        RGB sum;
        bool flag = false;
        for (int i = 0; i < spots.size(); ++i) {
            RGB color = spots[i].getColor();
            sum = sum + (color * spots[i].getColorPower()) * spots[i].getLightPower();
            if ((color.b != 0 || color.g != 0 || color.r != 0) && (!flag)) {
                flag = true;
                sum = sum + color * 0.02;
            }
        }
        return sum;
    }
};

#endif //RAYTRACING_SCENE_H
