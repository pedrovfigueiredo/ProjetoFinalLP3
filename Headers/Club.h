//
//  Club.h
//  ProjetoFinalLP3
//
//  Created by Pedro Figueirêdo on 17/11/2017.
//  Copyright © 2017 UFPB. All rights reserved.
//

#ifndef Club_h
#define Club_h

class Club {
public:
    Club(const unsigned MAX_DRINKS);
    ~Club();
    
    unsigned nDrinks_;
    unsigned nPeople_;
    const unsigned MAX_DRINKS_;
};


#endif /* Club_h */
