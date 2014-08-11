

#include "ArtCategory.h"


class FuzzyArt {
private:
	std::vector<ArtCategory> acVector;
	int inputCount;  // how many inputs we have seen
    double maxRecency;
    
    // parameters
    double choice;
    double learnRate;
    double vigilance;

    std::vector<double>inputVector; // examined against stored data
    std::vector<double>choices; // vector of likelihood aginst each category

    int dimensions;
    int recentChoice; // the most recently chosen category
    int choiceSize;	// the size of the choices array
    double residual;    // how much the chosen category changed with the last input/learning step

    void setInput(std::vector<double> input);
    void normalizeInput();
    void complementCode();
    void fillCategoryChoice();
    int makeChoice(double vig);
    int getMax(std::vector<double> vec, double &max);

public:

    FuzzyArt(double c = 0.0, double l = 0.5, double v = 0.85):choice(c), learnRate(l), vigilance(v){
        reset();
    };
	
    void setLearnRate(double l);
	void setChoice(double c);
	void setVigilance(double v);
	void reset();
    int predict(std::vector<double> inv);
    int getChoosenCategory();
    int increaseVigilance(); //set the vigilance just high enough to reset the chosen category and look again.
    std::vector<double> getCategoryChoices();
    size_t getNumberOfCategories();
    void dump();
};


inline void FuzzyArt::setLearnRate(double l){
	learnRate = l;
}

inline void FuzzyArt::setChoice(double c){
	choice = c;
}

inline void FuzzyArt::setVigilance(double v){
	vigilance = v;
}

inline std::vector<double> FuzzyArt::getCategoryChoices(){
    return choices;
}

inline size_t FuzzyArt::getNumberOfCategories(){
    return acVector.size();
}

inline int FuzzyArt::getChoosenCategory(){
    return recentChoice;
}


