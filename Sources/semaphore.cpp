#include "../Headers/semaphore.h"

Semaphore::Semaphore(unsigned count):
count_(count)
{}

void Semaphore::V(){
    ++count_;
    cv.notify_one();
}

void Semaphore::P(){
    std::unique_lock<std::mutex> lck(mtx);
    
    while(count_ == 0)
        cv.wait(lck);
    
    --count_;
}


