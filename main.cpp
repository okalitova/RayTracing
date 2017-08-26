#include <iostream>
#include "rendering/Image.h"
#include "scene/Scene.h"
#include "rendering/Reader.h"
#include "ThreadPool.h"

using namespace std;

int main() {
    Reader reader("input.txt");
    cout << "read\n";
    Scene scene = reader.getScene();
    cout << "get scene\n";
    Image image(scene.screen.getHeight(), scene.screen.getWidth());
    cout << "here\n";
    ThreadPool (4, scene.screen.getHeight(), scene.screen.getWidth(), &image, &scene);
    cout << "get screen\n";
    image.write("output.png");
    return 0;
}