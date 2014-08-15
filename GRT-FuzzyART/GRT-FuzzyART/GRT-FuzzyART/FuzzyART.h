/**
 @file
 @author  Chikashi Miyama
 @version 1.0
 
 @brief This class implements the FuzzyArt clustering algorithm.
 
 */

#ifndef __GRT_FuzzyART__MGMFuzzyArt__
#define __GRT_FuzzyART__MGMFuzzyArt__

#include "CoreModules/Clusterer.h"
#include "Util/GRTCommon.h"
#include "CoreModules/Clusterer.h"
#include "DataStructures/ClassificationData.h"
#include "ArtCategory.h"
#include <string>
#include <vector>

namespace GRT {

class FuzzyART : public Clusterer{
    
protected:
    // vectors
    std::vector<ArtCategory> acVector;
    std::vector<double>inputVector; // input vector
    std::vector<double>choices; // vector of likelihood aginst each category
    std::vector<UINT> labels;
    
    // parameters
    UINT dimensions;
    UINT choice;
    double learnRate;
    double vigilance;

    UINT inputCount;
    UINT recentChoice; // the most recently chosen category

    double residual;    // how much the chosen category changed with the last input/learning step
    
private:
    static RegisterClustererModule< FuzzyART > registerModule;
    

public:
    
    FuzzyART(const UINT choice=0, const double learnRate=0.5, const double vigilance=0.85);
    ~FuzzyART();
    
    virtual bool train_(MatrixDouble &data);

    void setInput(std::vector<double> input);
    void normalizeInput();
    void complementCode();
    void fillCategoryChoice();
    int makeChoice(double vig);
    int getMax(std::vector<double> vec, double &max);
    
    
    bool reset();
    void setLearnRate(double l);
	void setChoice(double c);
	void setVigilance(double v);
    std::vector<double> getCategoryChoices();
    UINT getNumberOfCategories();
    UINT getChoosenCategory();

    UINT classify(std::vector<double> inv);
//  UINT increaseVigilance();
    void dump();};
    
inline void FuzzyART::setLearnRate(double l){
    learnRate = l;
}

inline void FuzzyART::setChoice(double c){
    choice = c;
}

inline void FuzzyART::setVigilance(double v){
    vigilance = v;
}

inline std::vector<double> FuzzyART::getCategoryChoices(){
    return choices;
}

inline UINT FuzzyART::getNumberOfCategories(){
    return acVector.size();
}

inline UINT FuzzyART::getChoosenCategory(){
    return recentChoice;
}

    
    
}


#endif /* defined(__GRT_FuzzyART__MGMFuzzyArt__) */
