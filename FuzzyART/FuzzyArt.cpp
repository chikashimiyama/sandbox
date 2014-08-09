#include "FuzzyArt.h"

void FuzzyArt::reset(){
    residual = 0;
    dimensions = 3;
    maxRecency = 0;
    inputCount = 0;

    inputVector.clear();
    inputVector.resize(dimensions*2); // because of complemented code

    choiceSize = 1;
    recentChoice = -1;
    acVector.clear();
    acVector.push_back(ArtCategory(dimensions));
}

int FuzzyArt::predict(std::vector<double> inv){
    setInput(inv);
    normalizeInput();
    complementCode();
    fillCategoryChoice();    
    makeChoice(vigilance);
    return recentChoice;
}

void FuzzyArt::setInput(std::vector<double> in){ // input is without complemented code

    dimensions = in.size(); // without complemented code
    inputVector.resize(dimensions * 2); // because of complemented code

    //resize the dimension of all ACs if necessary
    std::vector<ArtCategory>::iterator it = acVector.begin();
    while(it != acVector.end()){
        (*it).resize(dimensions);
        it++;
    }

    for(int i = 0; i < dimensions; i++){
        inputVector[i*2] = in[i];
        inputVector[i*2+1] = 1.0 - in[i];
    }
}

void FuzzyArt::normalizeInput(){

    double max = 0;
    //search for max value in the input vector
    for(int i = 0; i < dimensions; i++){
        max = (inputVector[i] > max ? inputVector[i] : max);
    }

    //normalize with max value; make all input less than 1.0
    if (max > 1){
        for (int i = 0; i < dimensions; i++){
            inputVector[i] /= max;
        }
    }
}

void FuzzyArt::complementCode(){

    for (int i = 0; i < dimensions*2; i+=2){
        inputVector[i+1] = 1.0 - inputVector[i];
    } 
    // create complement of input - complement coding
    // e.g. 0.3 0.7 0.5 0.5 0.25 0.75 etc..
}

void FuzzyArt::fillCategoryChoice(){
    choices.clear();

    choices.resize(acVector.size());
    choiceSize = acVector.size();
    // check against all existing categories, and 1 empty one
    if(dimensions > 0){
        for(int i = 0; i < choiceSize; i++){
            choices[i] = acVector[i].choose(inputVector, choice);
        }
    }
}

// search vector, return max index and put max value in the specified buffer
int FuzzyArt::getMax(std::vector<double> vec, double &maxValue){
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

int FuzzyArt::makeChoice(double vig){ 
    int maxIndex = -1;
    bool chosen = false; // check mVigilance stuff here...
    while (!chosen){
        // find largest match value
        double max = 0;    
        maxIndex = getMax(choices, max);

        if (maxIndex != -1){          
            //search for the closest category            
            ArtCategory* ac = &acVector[maxIndex];
            
            // if above vigilence then learn from it
            if (ac->mVigilance(inputVector, vig) || acVector.size() == 1){     // learn!

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

int FuzzyArt::increaseVigilance(){
    if (recentChoice > -1){
        ArtCategory* ac = &acVector[recentChoice];
        double higher_vig = ac->getVigilance(inputVector) + 0.01f;    // increase by a little bit.
        recentChoice = makeChoice(higher_vig);
    }
    return recentChoice;
}

void FuzzyArt::dump(){
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

