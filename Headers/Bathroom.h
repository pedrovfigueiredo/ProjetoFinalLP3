//
//  Bathroom.h
//  ProjetoFinalLP3
//
//  Created by Pedro Figueirêdo on 17/11/2017.
//  Copyright © 2017 UFPB. All rights reserved.
//

#ifndef Bathroom_h
#define Bathroom_h
#include "Club.h"
#include "Sex.h"
#include "semaphore.h"

class Bathroom{
public:
    Bathroom(Club& club);
    ~Bathroom();
    
    unsigned countConsecutiveEntries_;
    std::unique_ptr<Semaphore> lock_, male_, female_, print_;
    Club& club_;
    
    // Contadores de Sexo
    unsigned countMaleWaiting_;
    unsigned countFemaleWaiting_;
    unsigned countMaleExecuting_;
    unsigned countFemaleExecuting_;
};


#endif /* Bathroom_h */

