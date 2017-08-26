files="main.cpp BlockingQueue.h ThreadPool.h geometry/Geometry.h geometry/Geometry.cpp figures/Figure.h rendering/RGB.h rendering/RGB.cpp figures/Sphere.h figures/Triangle.h rendering/Image.h rendering/Image.cpp scene/Scene.h scene/Camera.h scene/Camera.cpp scene/Screen.h scene/Screen.cpp scene/Light.h scene/Light.cpp scene/Scene.cpp scene/Spot.h scene/Spot.cpp rendering/Reader.h figures/Quadrangle.h"
g++ -std=c++11 -pthread $files -o run-main -I/usr/local/include/libpng12 -L/usr/local/lib -lpng -I/usr/local/include/png++
echo "compiled!"
