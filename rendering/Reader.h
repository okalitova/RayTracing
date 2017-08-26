//
// Created by okalitova on 20.04.16.
//

#ifndef RAYTRACING_READER_H
#define RAYTRACING_READER_H

#include "../scene/Scene.h"
#include "../figures/Triangle.h"
#include "../figures/Sphere.h"
#include "../figures/Quadrangle.h"
#include <fstream>
#include <string>

class Reader {
    std::ifstream fin;
private:
    Vector getVector() {
        Vector ans;
        fin >> ans.x >> ans.y >> ans.z;
        return ans;
    }
    RGB getRGB() {
        RGB ans;
        fin >> ans.r >> ans.g >> ans.b;
        return ans;
    }
public:

    Reader(string filename) {
        fin.open (filename, std::ifstream::in);
    }
    Scene getScene () {
        Camera camera(getVector());
        int height, width;
        fin >> height >> width;
        Vector left_up, left_down, right_up, right_down;
        left_up = getVector();
        right_up = getVector();
        right_down = getVector();
        left_down = getVector();
        Screen screen(width, height, left_down, left_up, right_down, right_up);
        vector <Figure*> figures;
        int n;
        fin >> n;
        for (int i = 0; i < n; ++i) {
            string s;
            fin >> s;
            if (s == "triangle") {
                Vector A, B, C, n;
                A = getVector();
                B = getVector();
                C = getVector();
                RGB color = getRGB();
                double reflectance;
                fin >> reflectance;
                double transparency, transparencyKoef;
                fin >> transparency >> transparencyKoef;
                figures.push_back(new Triangle(A, B, C, color, reflectance, NULL, transparencyKoef, transparency));
            }
            if (s == "sphere") {
                Vector center;
                double r;
                center = getVector();
                fin >> r;
                RGB color = getRGB();
                double reflectance;
                fin >> reflectance;
                double transparency, transparencyKoef;
                fin >> transparency >> transparencyKoef;
                figures.push_back(new Sphere(center, r, color, reflectance, NULL, transparencyKoef, transparency));
            }
            if (s == "quadrangle") {
                Vector A, B, C, D;
                A = getVector();
                B = getVector();
                C = getVector();
                D = getVector();
                RGB color = getRGB();
                double reflectance;
                fin >> reflectance;
                double transparency, transparencyKoef;
                fin >> transparency >> transparencyKoef;
                string imageName;
                fin >> imageName >> imageName;
                if (imageName != "none") {
                    cout << imageName << "\n";
                }
                figures.push_back(new Quadrangle(A, B, C, D, color, imageName, reflectance, NULL, transparencyKoef, transparency));
            }
        }
        vector <Light*> lights;
        vector <Figure*> figuresToIntersect;
        int m;
        fin >> m;
        for (int i = 0; i < m; ++i) {
            Vector start = getVector();
            double power;
            fin >> power;
            lights.push_back(new Light(start, power, figuresToIntersect));
        }
        int num_figures = figures.size();
        int num_lights = lights.size();
        for (int i = 0; i < num_figures; ++i) {
            if (figures[i]->reflectance > 0 && (figures[i]->id == Figure::TRIANGLE || figures[i]->id == Figure::QUADRANGLE)) {
                double power = figures[i]->reflectance * 500000;
                for (int j = 0; j < num_lights; ++j) {
                    figuresToIntersect = lights[j]->getFiguresToIntersect();
                    Vector pnt = figures[i]->getPoint();
                    Ray newRay = figures[i]->getPlane(pnt).getReflection(pnt, lights[j]->getPosition() - pnt);
                    Vector newPosition = newRay.start + newRay.direction;
                    figuresToIntersect.push_back(figures[i]);
                    lights.push_back(new Light(newPosition, power, figuresToIntersect));
                }
                for (int j = 0; j < num_figures; ++j) {
                    Figure* figure = figures[j];
                    if (figure != figures[i]) {
                        figures.push_back(figure->getReflection(figures[i]));
                    }
                }
            }
        }
        return Scene(camera, screen, figures, lights);
    }
};

#endif //RAYTRACING_READER_H
