#pragma once

#include <thread>
#include <future>
#include <memory>
#include <mutex>
#include "scene/Scene.h"

class ThreadPool {
public:
    mutex mtx;
    ThreadPool();
    ThreadPool(int init_threadNumber, int init_height, int init_weight, Image* init_image, Scene* init_scene);

public:

    int threadsNumber;
    std::vector<std::thread> ourWorkers;
    int height, weight;
    Image* image;
    int i, j;
    void generate();
    Scene* scene;
};

void ThreadPool::generate() {
    while (true) {
        mtx.lock();
        int i_cur, j_cur;
        i_cur = i; j_cur = j;
        if (i < height - 1) {
            i++;
            mtx.unlock();
        } else {
            if (j < weight - 1) {
                i = 0; j++;
                mtx.unlock();
            } else {
                mtx.unlock();
                break;
            }
        }
        //cout << i_cur << " " << j_cur << "\n";
        image->setPixel(i_cur, j_cur, scene->getPixel(i_cur, j_cur));
    }
    return;
}


ThreadPool::ThreadPool(int init_threadNumber, int init_height, int init_weight, Image* init_image, Scene* init_scene) {
    threadsNumber = init_threadNumber;
    height = init_height;
    weight = init_weight;
    scene = init_scene;
    image = init_image;
    i = 0;
    j = 0;
    for (int i = 0; i < threadsNumber; ++i) {
        ourWorkers.push_back(thread(&ThreadPool::generate, this));
    }
    for (int i = 0; i < threadsNumber; ++i) {
        ourWorkers[i].join();
    }
}