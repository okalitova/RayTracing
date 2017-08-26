//#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>


template <class T>
class BlockingQueue {
public:
    BlockingQueue();
    void push(const T& item);
    void pop(T& item);
    T pop();
    ~BlockingQueue();
private:
    std::queue<T> que;
    std::mutex mtx;
    std::condition_variable someonePushed;
};


template <class T>
void BlockingQueue<T>::push(const T& item) {
    std::unique_lock<std::mutex> ourLock(mtx);

    que.push(item);

    someonePushed.notify_one();
}


template<class T>
T BlockingQueue<T>::pop() {
    std::unique_lock<std::mutex> ourLock(mtx);

    while(que.size() == 0) {
        someonePushed.wait(ourLock);
    }
    T item = que.front();
    que.pop();

    return item;
}


template <class T>
void BlockingQueue<T>::pop(T& item) {
    item = pop();
}


template<class T>
BlockingQueue<T>::~BlockingQueue() {
    std::unique_lock<std::mutex> ourLock(mtx);
    someonePushed.notify_all();
}
