
#include <iostream>
#include <vector>
#include <cassert>

class ArtCategory{
private:
    
#pragma mark private variables
	// switch to true after the category is committed
	bool committed;
    
	// the size of weightVector = dimension * 2
    std::vector<double> weightVector;
    
    // sum of all elements in the weight Vector
    double sum;
    
#pragma mark private functions
    
    // sum of all weightVector
    bool isSameSize(const std::vector<double> &v1, const std::vector<double> &v2 ) const;
    
    // clear weightVector, resize it to dim * 2 and fill it with initValue
    void initWeightVector(const size_t dim, const double initValue = 1.0 );

    // calc the total value of the elements in init weight vector
    void updateSum();
    
    // compare inputA and inputB vector and accumlate the min values
	double calcMinTotal(const std::vector<double> &inputA, const std::vector<double> &inputB) const;
    
    // just sum up all elements in the vector
    double calcInputTotal(const std::vector<double> &input) const;
    
public:
#pragma mark constructor
    
	// weight vector will be allocated based on the dim size (x2)
	// all weight will be initialized with 1.0, sum will be calculated
	ArtCategory(int dim); 
	
    //calculate the mChoice match factor for this category and the given input
	double choose(const std::vector<double> &input, double mChoice);

    // calc minTotal / inputTotal and evaluate if it is above mVigilance of not
    bool evalVigilance(const std::vector<double> &input, double vigilance) const;
    
    // calc minTotal / inputTotal and return it
	double getVigilance(const std::vector<double> &input) const;

    
	// update vector of weightVector by the input vector
	double learn(const std::vector<double>& input, double mLearnRate);


	// resize the vector. if the newSize is bigger than current size, fill new dimension with 1.0
	// and update sum
	void resize(int dim);

	// getter
	const std::vector<double> getWeights();

#pragma mark utilities
	void dump();
    /*
	double getResidual(std::vector<double> input, double mLearnRate);
    double distance(const std::vector<double> &input) const;
     */
};


inline bool ArtCategory::isSameSize(const std::vector<double> &v1, const std::vector<double> &v2 )const{
 	return v1.size() == v2.size();
}

inline void ArtCategory::initWeightVector(const size_t dim, const double initValue){
    
    assert(dim > 0);
    weightVector.clear();
    weightVector.assign(dim * 2, initValue);
    updateSum();
}

inline void ArtCategory::updateSum(){
    sum = 0.0;
    std::vector<double>::iterator it = weightVector.begin();
    while (it != weightVector.end()) {
        sum += *it;
        it++;
    }
}

inline double ArtCategory::calcMinTotal(const std::vector<double> &inputA, const std::vector<double> &inputB ) const{

    assert(isSameSize(inputA, inputB)); // should be same size

    double minTotal = 0;
    size_t size = inputA.size();
    
    for(int i = 0; i < size; i++){
        // if the input[i] is less than weightVector[i] add input[i] to minTotal otherwise add weightVector[i]
        minTotal += (inputA[i] < inputB[i] ? inputA[i] : inputB[i]);
    }
    return minTotal;
}

inline double ArtCategory::calcInputTotal(const std::vector<double> &input) const{
    double sum = 0.0;
    std::vector<double>::const_iterator it = input.begin();
    while (it != input.end()) {
        sum += *it;
        it++;
    }
    return sum;
}

inline const std::vector<double> ArtCategory::getWeights(){
	return weightVector;
}



