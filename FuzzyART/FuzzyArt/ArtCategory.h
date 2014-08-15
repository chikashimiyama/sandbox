
#include <iostream>
#include <vector>
#include <cassert>

class ArtCategory{
private:
	// switch to true after the category is committed
	bool committed;	

	// the size of weightVector = dimensions
    std::vector<double> weightVector; 
    
    // sum of all elements in the weight Vector
    double sum;
    
    // utility function to check the size of vector A and B
    bool isSameSize(std::vector<double> &v1, std::vector<double> &v2 );
    
    void initWeightVector(const size_t dim, const double initValue = 1.0 );
    void updateSum();
    
public:

	// weight vector will be allocated based on the dim size (x2)
	// all weight will be initialized with 1.0
	// sum variable will be updated
    ArtCategory(int dim);
	
    //
	double choose(std::vector<double> input, double mChoice);

	// is the input vigilant or not
    bool evalVigilance(const std::vector<double>input, double mVigilance);
    
    //
	double getVigilance(const std::vector<double> input);

	// update vector of weightVector by the input vector
	double learn(std::vector<double>input, double mLearnRate);

	// similar to learn but does not overwrite the values of weightVector just simulate
	double getResidual(std::vector<double> input, double mLearnRate);

	double distance(std::vector<double> input); 

	// resize the vector. if the newSize is bigger than current size, fill new dimension with 1.0
	// and update sum
	void resize(int newSize); 
	void dump(); 

	// getter
	const std::vector<double> getWeights();
};


inline void ArtCategory::updateSum(){
    sum = 0.0;
    std::vector<double>::iterator it = weightVector.begin();
    while (it != weightVector.end()) {
        sum += *it;
        it++;
    }
}

inline bool ArtCategory::isSameSize(std::vector<double> &v1, std::vector<double> &v2 ){
 	return v1.size() == v2.size();
}

inline void ArtCategory::initWeightVector(const size_t dim, const double initValue){
    
    assert(dim > 0);
    weightVector.clear();
    weightVector.assign(dim * 2, initValue);
}

inline const std::vector<double> ArtCategory::getWeights(){
	return weightVector;
}


