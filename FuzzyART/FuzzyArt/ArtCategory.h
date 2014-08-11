
#include <iostream>
#include <vector>

class ArtCategory{
private:
	// switch to true after the category is committed
	bool committed;	

	// the size of weighting represents dimensions
    std::vector<double> weighting; 
    
    // sum of all weighting
    double sum; 
    bool isSameSize(std::vector<double> &v1, std::vector<double> &v2 );
public:

	// weight vector will be allocated based on the dim size (x2)
	// all weight will be initialized with 1.0, sum will be calculated
	ArtCategory(int dim); 
	
    //
	double choose(std::vector<double> input, double mChoice);

	
    bool mVigilance(const std::vector<double>input, double mVigilance);
	double getVigilance(const std::vector<double> input);

	// update vector of weighting by the input vector
	double learn(std::vector<double>input, double mLearnRate);

	// similar to learn but does not overwrite the values of weighting just simulate
	double getResidual(std::vector<double> input, double mLearnRate);

	double distance(std::vector<double> input); 

	// resize the vector. if the newSize is bigger than current size, fill new dimension with 1.0
	// and update sum
	void resize(int newSize); 
	void dump(); 

	// getter
	const std::vector<double> getWeights();
};

inline const std::vector<double> ArtCategory::getWeights(){
	return weighting;
}

inline bool ArtCategory::isSameSize(std::vector<double> &v1, std::vector<double> &v2 ){
 	return v1.size() == v2.size();
}
