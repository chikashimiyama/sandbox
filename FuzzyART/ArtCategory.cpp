#include "ArtCategory.h"
#include <cmath>

ArtCategory::ArtCategory(int dim){   
    committed = false;
    if(dim > 0){
       weighting.resize(dim * 2); // because of complemented code
    }else{
    	weighting.clear();
	}
	// initialize all weighting to 1 and calculate sum of the weight    
    std::vector<double>::iterator it = weighting.begin();
    sum = 0.0;
    while(it != weighting.end()){
    	*it = 1.0;
    	sum+= *it;
    	it++;
    }
}

// calculate the mChoice match factor for this category and the given input
double ArtCategory::choose(std::vector<double> input, double mChoice){
    int i;
    double minTotal = 0;
    int size = input.size();

    for (i = 0; i < size; i++){
        // if the inputN is less than weightingN add inputN otherwise add weightingN
        minTotal += (input[i] < weighting[i] ? input[i] : weighting[i]);
    }
    return minTotal / (mChoice + sum); // average?
}

bool ArtCategory::mVigilance(const std::vector<double>input, double mVigilance){
    double minTotal = 0;
    double inputTotal = 0;
    int size = input.size();
    for (int i = 0; i < size; i++){
        minTotal += (input[i] < weighting[i] ? input[i] : weighting[i]);
        inputTotal += input[i];
    }
    // if the value is greater than the vigilance return true
    return (minTotal / inputTotal >= mVigilance);
}

double ArtCategory::getVigilance(const std::vector<double> input){
    double minTotal = 0;
    double inputTotal = 0;
    size_t dim = input.size();
    for (int i = 0; i < dim; i++){
        minTotal += (input[i] < weighting[i] ? input[i] : weighting[i]);
        inputTotal += input[i];
    }
    return minTotal / inputTotal;
}

double ArtCategory::learn(std::vector<double>input, double mLearnRate){
    if(!isSameSize(weighting, input)){
        return -1;
    }    
    size_t dim = input.size();
    std::vector<double> newWeighting(dim);
    double residual = 0;
    if (!committed){
        mLearnRate = 1;
        committed = true; // toggle flag
    }
    double inverseLearnRate = 1.0 - mLearnRate;
    for (int i = 0; i < dim; i++){
        // compare input and weighting one by one and take smaller one
        // then bias with "learnRate"
        // if the learnRate is low, the value in weighting retains more: like an old stubborn guy!
        newWeighting[i] = mLearnRate * (input[i] < weighting[i] ? input[i] : weighting[i]) 
        + inverseLearnRate * weighting[i];
    }
    // calculate residual
    // residual is sum of difference between new and old Weightings
    // if residual is big, many memories were rewritten 
    for (int i = 0; i < dim; i++){
        residual += weighting[i] - newWeighting[i];
        weighting[i] = newWeighting[i];
    }
    sum = 0;	
    // now update the total for this category
    for (int i = 0; i < dim; i++){
        sum += weighting[i];
    }
    // output average residual
    return residual / (dim * 0.5);

}

// return the amount of change in the category if this input was learned with LearnRate=1
double ArtCategory::getResidual(std::vector<double> input, double mLearnRate){

    if(!isSameSize(weighting, input)){
        return -1;
    }
    double residual = 0;
    size_t size = input.size();
    mLearnRate = 1;
    double inverseLearnRate = 1.0 - mLearnRate;
    for (int i = 0; i < size; i++){
        double min = (input[i] < weighting[i] ? input[i] : weighting[i]);
        residual += pow(weighting[i] - (mLearnRate * min + inverseLearnRate * weighting[i]), 2.0);
    }
    return residual / (size * 0.5);
}  


double ArtCategory::distance( std::vector<double> input){
    // take the not complemented part
    int featureLength = weighting.size() / 2;	// how many elements in the pre-complement coded std::vector?
    if(input.size() != featureLength){
        std::cout << "input length " << input.size() << " does not match" << std::endl;
        return -1.0;
    }
    std::vector<double> centerVector;
    for (int i = 0; i < featureLength; i++){	// find the 'center' of the category
        double center = (weighting[i] + (1.0 - weighting[i+featureLength])) * 0.5;
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
    int oldDim = weighting.size();
    if(newDim == oldDim){
        return;
    }
    std::cout << "resizing from " << weighting.size() << " to " << newDim << std::endl;
    weighting.resize(newDim);

    for(int i = oldDim; i < newDim; i++){
        weighting[i] = 1.0; // fill the gap
        sum += weighting[i]; // update sum
    }    
    committed = false;
}

void ArtCategory::dump(){
    size_t dims = weighting.size();
    std::cout << "dimensions:" << dims << std::endl;
    std::cout << "weighting:";
    std::vector<double>::iterator it = weighting.begin();
    while(it != weighting.end()){
        std::cout << *it;
        std::cout << " ";
        it++;
    }
    std::cout << std::endl;
    std::cout << "weight sum:" << sum << std::endl;
}
