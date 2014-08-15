#include "ArtCategory.h"
#include <cmath>

ArtCategory::ArtCategory(int dim){
    committed = false;
    if(dim > 0){
        initWeightVector(dim);
        
    }else{
    	weightVector.clear();
	}
}

double ArtCategory::choose(const std::vector<double> &input, double mChoice){
    double minTotal = calcMinTotal(input, weightVector);
    return minTotal / (mChoice + sum);
}

bool ArtCategory::evalVigilance(const std::vector<double>&input, double vigilance) const{
    double vig = getVigilance(input);
    return (vig >= vigilance);
}

double ArtCategory::getVigilance(const std::vector<double> &input) const{
    double minTotal = calcMinTotal(input, weightVector);
    double inputTotal = calcInputTotal(input);
    return minTotal / inputTotal;
}

double ArtCategory::learn(const std::vector<double> &input, double mLearnRate){

    // 1. check the size
    if(!isSameSize(weightVector, input)){
        return -1;
    }
    
    // 2. allocate new weightVector vector
    size_t size = input.size();
    std::vector<double> newweightVector(size);
    if (!committed){ // if this is the first time learn purely from the input
        mLearnRate = 1;
        committed = true; // toggle flag
    }
    
    // 3. calculate new weighitng by comparing input and current weightVector
    double inverseLearnRate = 1.0 - mLearnRate;
    for (int i = 0; i < size; i++){
        // compare input and weightVector one by one and take smaller one
        // then bias with "learnRate"
        // if the learnRate is low, the value in weightVector retains more: like an old stubborn guy!
        newweightVector[i] =
        mLearnRate * (input[i] < weightVector[i] ? input[i] : weightVector[i])
        + inverseLearnRate * weightVector[i];
    }
    
    // 2. calculate residual and update weightVector
    // residual is sum of difference between new and old weightVectors
    // if residual is big, many memories were rewritten
    double residual = 0;
    for (int i = 0; i < size; i++){
        residual += weightVector[i] - newweightVector[i];
        weightVector[i] = newweightVector[i];
    }
    
    // 3. now update the sum for this category
    sum = 0;
    for (int i = 0; i < size; i++){
        sum += weightVector[i];
    }
    
    // 4. output average residual
    return residual / (size / 2);
}



void ArtCategory::resize(int dim){
    size_t newSize = dim * 2;
    size_t oldSize = weightVector.size();
    if(newSize == oldSize){
        return;
    }
    std::cout << "resizing from " << weightVector.size() << " to " << newSize << std::endl;
    
    weightVector.resize(newSize);
    for(int i = oldSize; i < newSize; i++){
        weightVector[i] = 1.0; // fill the gap
        sum += weightVector[i]; // update sum
    }    
    committed = false;
}

void ArtCategory::dump(){
    size_t dims = weightVector.size();
    std::cout << "dimensions:" << dims << std::endl;
    std::cout << "weightVector:";
    std::vector<double>::iterator it = weightVector.begin();
    while(it != weightVector.end()){
        std::cout << *it;
        std::cout << " ";
        it++;
    }
    std::cout << std::endl;
    std::cout << "weight sum:" << sum << std::endl;
}

/*
double ArtCategory::distance(const std::vector<double> &input) const{
    // calc dim from size
    int featureLength = static_cast<int>(weightVector.size()) / 2;

    std::vector<double> centerVector;

    // find the 'center' of the category
    for (int i = 0; i < featureLength; i++){
    double center = (weightVector[i] + (1.0 - weightVector[i+featureLength])) * 0.5;
    centerVector.push_back(center);
    }

    // calculate the distance to the input
    double dist = 0;
    double tmp;
    for (int i = 0; i < featureLength; i++){
    tmp = input[i]-centerVector[i];
    dist += tmp*tmp;
    }

    if (dist > 0){
    dist = sqrt(dist);
    }

    return dist;
}
 
double ArtCategory::getResidual(std::vector<double> input, double mLearnRate){

    if(!isSameSize(weightVector, input)){
        return -1;
    }
    double residual = 0;
    size_t size = input.size();
    mLearnRate = 1;
    double inverseLearnRate = 1.0 - mLearnRate;
    for (int i = 0; i < size; i++){
        double min = (input[i] < weightVector[i] ? input[i] : weightVector[i]);
        residual += pow(weightVector[i] - (mLearnRate * min + inverseLearnRate * weightVector[i]), 2.0);
    }
    return residual / (size * 0.5);
}
 */

