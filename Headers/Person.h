//
//  Person.h
//  ProjetoFinalLP3
//
//  Created by Pedro Figueirêdo on 17/11/2017.
//  Copyright © 2017 UFPB. All rights reserved.
//

#ifndef Person_h
#define Person_h
#include "Thread.h"
#include "Bathroom.h"
#include "Sex.h"
#include <iostream>
#include <chrono>
#include <thread>

class Person : public Thread {
public:
    
    Person(const Sex sex, const unsigned id, Bathroom& bathroom);
    ~Person();
    
    void run();

    
private:
    inline void joinBathroomWaitingQueue_();
    inline void leaveBathroomWaitingQueue_();
    inline void usingBathroom_();
    inline void drinkBeverages_();
    inline bool drinkIsOver();
    
    Bathroom& bathroom_;
    const Sex sex_;
    const unsigned id_;
};


#endif /* Person_h */

