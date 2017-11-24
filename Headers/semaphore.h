

#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <mutex>
#include <condition_variable>


class Semaphore
{
public:
    Semaphore(unsigned count);
    
    void V();
    void P();
    
private:
    std::mutex mtx;
    std::condition_variable cv;
    unsigned count_;
};

#endif // SEMAPHORE_H

