#include "ArtCategory.h"
#include <cmath>

ArtCategory::ArtCategory(int dim){
    
    committed = false; // wait for initialization
    
    
    if(dim > 0){
        initWeightVector(dim);
        updateSum();
    }else{
    	weightVector.clear();
	}
}

// calculate the mChoice match factor for this category and the given input
double ArtCategory::choose(std::vector<double> input, double mChoice){
    double minTotal = 0;
    size_t size = input.size(); // dim * 2

    for (int i = 0; i < size; i++){
        // if the inputN is less than weightVectorN add inputN otherwise add weightVectorN
        minTotal += (input[i] < weightVector[i] ? input[i] : weightVector[i]);
    }
    return minTotal / (mChoice + sum); // average?
}

bool ArtCategory::evalVigilance(const std::vector<double>input, double mVigilance){
    double minTotal = 0;
    double inputTotal = 0;
    size_t size = input.size();

    // compare input vector and weightVector vector and accumalate the smaller values
    for(int i = 0; i < size; i++){
        minTotal += (input[i] < weightVector[i] ? input[i] : weightVector[i]);
        inputTotal += input[i];
    }
    return (minTotal / inputTotal >= mVigilance);
}

// get vigilance against input vector
double ArtCategory::getVigilance(const std::vector<double> input){
    double minTotal = 0;
    double inputTotal = 0;
    size_t cnt = input.size();
    
    // compare input vector and weightVector vector and accumalate the smaller value
    for (int i = 0; i < cnt; i++){
        minTotal += (input[i] < weightVector[i] ? input[i] : weightVector[i]);
        inputTotal += input[i];
    }
    
    // divide mintotal by input total
    return minTotal / inputTotal;
}

double ArtCategory::learn(std::vector<double>input, double mLearnRate){

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

// return the amount of change in the category if this input was learned with LearnRate=1
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


double ArtCategory::distance( std::vector<double> input){
    // take the not complemented part
    int featureLength = static_cast<int>(weightVector.size()) / 2;	// how many elements in the pre-complement coded std::vector?
    if(input.size() != featureLength){
        std::cout << "input length " << input.size() << " does not match" << std::endl;
        return -1.0;
    }
    std::vector<double> centerVector;
    for (int i = 0; i < featureLength; i++){	// find the 'center' of the category
        double center = (weightVector[i] + (1.0 - weightVector[i+featureLength])) * 0.5;
        centerVector.push_back(center);
    }
    double dist = 0;
    for (int i = 0; i < featureLength; i++){	// calculate the distance to the input
        dist += pow(input[i]-centerVector[i],2);
    }
    if (dist > 0){
        dist = sqrt(dist);
    }
    return dist;
}

void ArtCategory::resize(int newSize){
    int newDim = newSize * 2;
    int oldDim = static_cast<int>(weightVector.size());
    if(newDim == oldDim){
        return;
    }
    std::cout << "resizing from " << weightVector.size() << " to " << newDim << std::endl;
    weightVector.resize(newDim);

    for(int i = oldDim; i < newDim; i++){
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
