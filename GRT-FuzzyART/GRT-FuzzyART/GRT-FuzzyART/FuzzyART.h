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

namespace GRT {

class FuzzyART : public Clusterer{
    
public:
    FuzzyART();
    ~FuzzyART();
    virtual bool train_(MatrixDouble &data);
    //Tell the compiler we are using the following functions from the MLBase class to stop hidden virtual function warnings
    using MLBase::saveModelToFile;
    using MLBase::loadModelFromFile;
    using MLBase::train;
    using MLBase::train_;
    using MLBase::predict;
    using MLBase::predict_;
};


}


#endif /* defined(__GRT_FuzzyART__MGMFuzzyArt__) */
