//
//  Person.cpp
//  ProjetoFinalLP3
//
//  Created by Pedro Figueirêdo on 17/11/2017.
//  Copyright © 2017 UFPB. All rights reserved.
//

#include "../Headers/Person.h"

Person::Person(Sex sex, const unsigned id, Bathroom& bathroom):id_(id),sex_(sex),bathroom_(bathroom){srand((unsigned)time(0));}

Person::~Person(){}

void Person::run(){
    
    this->bathroom_.print_->P();
    if(this->sex_ == Male)
        std::cout << "Man " << this->id_ << " arrived at the club" << std::endl;
    
    else
        std::cout << "Woman " << this->id_ << " arrived at the club" << std::endl;
    
    this->bathroom_.club_.nPeople_++;
    
    this->bathroom_.print_->V();
    
    while (!drinkIsOver()) {
        
        // Entry Protocol
        joinBathroomWaitingQueue_();
        
        // Critical Section
        usingBathroom_();
        
        // Leave Protocol
        leaveBathroomWaitingQueue_();
        
        // Non-critic section
        drinkBeverages_();
        
    }
    
    this->bathroom_.print_->P();
    if(this->sex_ == Male)
        std::cout << "Man " << this->id_ << " left the club" << std::endl;
        
    else
        std::cout << "Woman " << this->id_ << " left the club" << std::endl;
        
    this->bathroom_.club_.nPeople_--;
        
    this->bathroom_.print_->V();
}

inline bool Person::drinkIsOver(){
    return this->bathroom_.club_.nDrinks_ >= this->bathroom_.club_.MAX_DRINKS_;
}

inline void Person::joinBathroomWaitingQueue_(){
    this->bathroom_.lock_->P();
    
    if (this->sex_ == Male) {
        if (this->bathroom_.countFemaleExecuting_ > 0 || (this->bathroom_.countFemaleWaiting_ > 0 && this->bathroom_.countConsecutiveEntries_ >= 3)) {
            // Durmo
            this->bathroom_.countMaleWaiting_++;
            this->bathroom_.lock_->V();
            this->bathroom_.male_->P();
        }
        
        this->bathroom_.countMaleExecuting_++;
        
    }else{
        if (this->bathroom_.countMaleExecuting_ > 0 || (this->bathroom_.countMaleWaiting_ > 0 && this->bathroom_.countConsecutiveEntries_ >= 3)) {
            // Durmo
            this->bathroom_.countFemaleWaiting_++;
            this->bathroom_.lock_->V();
            this->bathroom_.female_->P();
        }
        
        this->bathroom_.countFemaleExecuting_++;
    }
    
    this->bathroom_.countConsecutiveEntries_++;
    this->bathroom_.lock_->V();
}

inline void Person::leaveBathroomWaitingQueue_(){
    this->bathroom_.lock_->P();
    
    if (this->sex_ == Sex::Male) {
        this->bathroom_.countMaleExecuting_--;
        
        if (!this->bathroom_.countMaleExecuting_ && this->bathroom_.countConsecutiveEntries_ >= 3 && this->bathroom_.countFemaleWaiting_ > 0) {
            this->bathroom_.countConsecutiveEntries_ = 0;
            int aux = 0;
            while(aux++ < 3 && this->bathroom_.countFemaleWaiting_){
                this->bathroom_.countFemaleWaiting_--;
                this->bathroom_.female_->V();
            }
        }else if (this->bathroom_.countMaleWaiting_ > 0 && !this->bathroom_.countFemaleWaiting_){
            this->bathroom_.countMaleWaiting_--;
            this->bathroom_.male_->V();
        }else if (!this->bathroom_.countMaleExecuting_ && !this->bathroom_.countMaleWaiting_ && this->bathroom_.countFemaleWaiting_){
            this->bathroom_.countConsecutiveEntries_ = 0;
            int aux = 0;
            while(aux++ < 3 && this->bathroom_.countFemaleWaiting_){
                this->bathroom_.countFemaleWaiting_--;
                this->bathroom_.female_->V();
            }
        }
        
    }else{ // Female
        this->bathroom_.countFemaleExecuting_--;
        
        if (!this->bathroom_.countFemaleExecuting_ && this->bathroom_.countConsecutiveEntries_ >= 3 && this->bathroom_.countMaleWaiting_ > 0) {
            this->bathroom_.countConsecutiveEntries_ = 0;
            int aux = 0;
            while(aux++ < 3 && this->bathroom_.countMaleWaiting_){
                this->bathroom_.countMaleWaiting_--;
                this->bathroom_.male_->V();
            }
        }else if (this->bathroom_.countFemaleWaiting_ > 0 && !this->bathroom_.countMaleWaiting_){
            this->bathroom_.countFemaleWaiting_--;
            this->bathroom_.female_->V();
        }else if (!this->bathroom_.countFemaleExecuting_ && !this->bathroom_.countFemaleWaiting_ && this->bathroom_.countMaleWaiting_){
            this->bathroom_.countConsecutiveEntries_ = 0;
            int aux = 0;
            while(aux++ < 3 && this->bathroom_.countMaleWaiting_){
                this->bathroom_.countMaleWaiting_--;
                this->bathroom_.male_->V();
            }
        }
    }
    this->bathroom_.lock_->V();
}

inline void Person::usingBathroom_(){
    
    if(!drinkIsOver()){
        this->bathroom_.print_->P();
        if (this->sex_ == Female)
            std::cout << "Woman " << this->id_ << " is in the bathroom" << std::endl;
        
        else
            std::cout << "Man " << this->id_ << " is in the bathroom" << std::endl;
        
        this->bathroom_.print_->V();
        
        std::this_thread::sleep_for(std::chrono::seconds(rand()%5 + 1));
        
    }
}

inline void Person::drinkBeverages_(){
    
    if (!drinkIsOver()) {
        this->bathroom_.print_->P();
        if (this->sex_ == Female)
            std::cout << "Woman " << this->id_ << " is drinking" << std::endl;
        
        else
            std::cout << "Man " << this->id_ << " is drinking" << std::endl;
        
        this->bathroom_.club_.nDrinks_++;
        
        this->bathroom_.print_->V();
        std::this_thread::sleep_for(std::chrono::seconds(rand()%20 + 1));
    }else{
        this->bathroom_.print_->P();
        if (this->sex_ == Female)
            std::cout << "Woman " << this->id_ << " tried to drink, but there were no drinks left." << std::endl;
        
        else
            std::cout << "Man " << this->id_ << " tried to drink, but there were no drinks left." << std::endl;
        this->bathroom_.print_->V();
    }
        
}

