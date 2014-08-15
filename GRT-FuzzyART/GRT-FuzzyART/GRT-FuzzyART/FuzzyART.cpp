//
//  FuzztART.cpp
//  GRT-FuzzyART
//
//  Created by Chikashi Miyama on 11/08/14.
//  Copyright (c) 2014 ICST. All rights reserved.
//

#include "FuzzyART.h"

using namespace GRT;

RegisterClustererModule<FuzzyART> FuzzyART::registerModule("FuzzyART");

FuzzyART::FuzzyART(const UINT choice, double learnRate, double vigilance){
    
    this->choice = choice;
    this->learnRate = learnRate;
    this->vigilance = vigilance;
    
}

FuzzyART::~FuzzyART(){
    
}

bool FuzzyART::reset(){
    residual = 0;
    dimensions = 3;
    inputCount = 0;
    
    inputVector.clear();
    inputVector.resize(dimensions*2); // because of complemented code
    
    recentChoice = -1;
    acVector.clear();
    acVector.push_back(ArtCategory(dimensions));
    
    return true;
}

bool FuzzyART::train_(MatrixDouble &data){
    
    UINT numRows = data.getNumRows();
    labels.clear();
    
    for(int i = numRows; i < numRows; i++){
        std::vector<double> inv = data.getRowVector(i);
        setInput(inv); // copy input vector to the buffer, normalize, and prepare the complement code
        fillCategoryChoice(); // check the distance between input and each cateory
        makeChoice(vigilance); // make final prediction, update recent Choice, if the input is far from all existing AC make new one, depending on vigilance
    
        labels.push_back(recentChoice);
    }
    
    return true; // return result
}



// process input vector
void FuzzyART::setInput(std::vector<double> inv){ // input is without complemented code
    
    dimensions = static_cast<int>(inv.size()); // without complemented code
    
    // 1. resize the dimension of all ACs if necessary
    std::vector<ArtCategory>::iterator ait = acVector.begin();
    while(ait != acVector.end()){
        (*ait).resize(dimensions);
        ait++;
    }
    
    // 2. normalize inv and copy it to inputVector with complement code
    inputVector.clear();
    double max;
    getMax(inv, max);
    std::vector<double>::iterator it = inv.begin();
    while (it != inv.end()) {
        double normalized = (*it)/max;
        inputVector.push_back(normalized);
        inputVector.push_back(1.0-normalized);
        it++;
    }
}

// calculate the distances between each category and input vector and store the result in choices vector
void FuzzyART::fillCategoryChoice(){
    
    choices.clear();
    choices.resize(acVector.size()); // number of choices is depending on the number of ART Categories
    
    // check against all existing categories, and 1 empty one
    for(int i = 0; i < choices.size(); i++){
        choices[i] = acVector[i].choose(inputVector, choice);
    }
}

// search vector, return max index and put max value in the specified buffer
int FuzzyART::getMax(std::vector<double> vec, double &maxValue){
    int maxIndex = -1;
    double max = 0;
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] > max){
            max = vec[i];
            maxIndex = i;
        }
    }
    maxValue = max;
    return maxIndex;
}

int FuzzyART::makeChoice(double vig){
    int maxIndex = -1;
    bool chosen = false; // check mVigilance stuff here...
    while (!chosen){
        
        // 1. find largest match value in the vector of choices
        double max = 0;
        maxIndex = getMax(choices, max);
        
        // 2. if something is found
        if (maxIndex != -1){
            
            // 2-1 get a pointer to AC instance with the biggest match value (closest category)
            ArtCategory* ac = &acVector[maxIndex];
            
            // 2-2 if above vigilence (i.e. the closest one is not close enough)  or there is only one category, then learn
            
            if (ac->evalVigilance(inputVector, vig) || acVector.size() == 1){     // learn!
                residual = ac->learn(inputVector, learnRate); //learn
                while (maxIndex >= acVector.size()-1){  // committed the previous uncommitted category, so add a new blank one.
                    acVector.push_back(ArtCategory(dimensions));
                }
                chosen = true;
                recentChoice = maxIndex;
            }else{  // failed the mVigilance test.
                choices[maxIndex] = -1; // reset, try again
                maxIndex = -1;
            }
        } else {
            chosen = true;
        }
    } // otherwise look again.
    
    if (maxIndex > -1){
        inputCount++;
    }
    
    return maxIndex;
}



void FuzzyART::dump(){
    std::cout <<  "learnRate:" << learnRate << std::endl;
    std::cout <<  "vigilance:" << vigilance << std::endl;
    std::cout <<  "choice:" << choice << std::endl;
    std::cout <<  "input count:" << inputCount << std::endl;  // how many inputs we have seen
    
    std::vector<ArtCategory>::iterator it = acVector.begin();
    int index = 0;
    while(it != acVector.end()){
        std::cout <<  "======= category:" << index <<  "========" << std::endl;
        (*it).dump();
        it++;
        index++;
    }
}
//
//UINT FuzzyART::increaseVigilance(){
//    if (recentChoice > -1){
//        ArtCategory* ac = &acVector[recentChoice];
//        double higher_vig = ac->getVigilance(inputVector) + 0.01f;    // increase by a little bit.
//        recentChoice = makeChoice(higher_vig);
//    }
//    return recentChoice;
//}
