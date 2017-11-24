//
//  Bathroom.cpp
//  ProjetoFinalLP3
//
//  Created by Pedro Figueirêdo on 17/11/2017.
//  Copyright © 2017 UFPB. All rights reserved.
//

#include "../Headers/Bathroom.h"

Bathroom::Bathroom(Club& club):
    club_(club),
    lock_(new Semaphore(1)),
    male_(new Semaphore(0)),
    female_(new Semaphore(0)),
    print_(new Semaphore(1)),
    countConsecutiveEntries_(0),
    countMaleWaiting_(0),
    countFemaleWaiting_(0),
    countMaleExecuting_(0),
    countFemaleExecuting_(0)
{}

Bathroom::~Bathroom()
{}

