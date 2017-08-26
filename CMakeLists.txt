cmake_minimum_required(VERSION 3.3)
project(RayTracing)

#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
set( LIBPNG_COMPILE_FLAGS "-I/usr/local/include/libpng12 -I/usr/local/include/png++ -std=c++11")
set( LIBPNG_LINK_FLAGS    "-L/usr/local/lib -lpng -lpng -pthread")

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${LIBPNG_COMPILE_FLAGS}" )
set( CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} ${LIBPNG_LINK_FLAGS}")

set(SOURCE_FILES main.cpp geometry/Geometry.h geometry/Geometry.cpp figures/Figure.h rendering/RGB.h rendering/RGB.cpp figures/Sphere.h figures/Triangle.h rendering/Image.h rendering/Image.cpp scene/Scene.h scene/Camera.h scene/Camera.cpp scene/Screen.h scene/Screen.cpp scene/Light.h scene/Light.cpp scene/Scene.cpp scene/Spot.h scene/Spot.cpp rendering/Reader.h figures/Quadrangle.h)
add_executable(RayTracing ${SOURCE_FILES})