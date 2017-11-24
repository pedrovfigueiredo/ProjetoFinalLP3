//
//  main.cpp
//  ProjetoFinalLP3
//
//  Created by Pedro Figueirêdo on 17/11/2017.
//  Copyright © 2017 UFPB. All rights reserved.
//

#include <iostream>
#include <vector>
#include "../Headers/Person.h"
#include "../Headers/Club.h"
#include "../Headers/Sex.h"

int main(int argc, const char * argv[]) {
    const unsigned nPeople = 7;
    const unsigned MAX_DRINKS = 20;
    Club onTheRocks(MAX_DRINKS);
    Bathroom bathroom(onTheRocks);
    std::vector<std::unique_ptr<Person>> people;
    people.reserve(nPeople);
    
    for(unsigned i = 0, j = 0, k = 0; i < nPeople; i++){
        if (i%2 == 0)
            people.push_back(std::unique_ptr<Person>(new Person(Sex::Male, ++k , bathroom)));
        else
            people.push_back(std::unique_ptr<Person>(new Person(Sex::Female, ++j, bathroom)));
        people[i]->start();
    }
    
    for(auto& person: people)
        person->join();
    
    std::cout << "Drinks served: " << onTheRocks.nDrinks_ << std::endl;
    std::cout << "People in the Club: " << onTheRocks.nPeople_ << std::endl;
    std::cout << "Club is closed!"<< std::endl;
    
    return 0;
}
