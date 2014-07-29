#include <GRT.h>
#include <iostream>
using namespace GRT;
using namespace std;

int main(){

	GRT::SelfOrganizingMap mySom;

    // 4 cases with 4 attributes
    const double pattern[4][4] = {{1,1,0,0},{0,0,0,1},{1,0,0,1},{1,1,1,1}};

	// copy the 2D array onto GRT matrix
    GRT::MatrixDouble patternMatrix(4,4);
    for(int i = 0; i < patternMatrix.getNumRows(); i++ ){
        for(int j = 0; j < patternMatrix.getNumCols(); j++ ){
            patternMatrix[i][j] = pattern[i][j];
        }
    }
    // print matrix
    patternMatrix.print();
    
    // four neurons
    mySom.setNetworkSize(4);

    // training parameters
    mySom.setAlphaEnd(0.01);
    mySom.setMaxNumEpochs(100);
    mySom.setMinNumEpochs(10);

    // train
    mySom.train(patternMatrix);

    // print out the weights of trained neurons
    vector<GRT::GaussNeuron> neurons = mySom.getNeurons();
    cout << "numNeuron:" << neurons.size() << endl;
    for(int i = 0; i < neurons.size() ; i++){
        GRT::VectorDouble w = neurons[i].weights;
        cout << "neuron" << i << ": "<< w[0] << ' ' <<  w[1] << ' ' <<  w[2] << ' ' <<  w[3] << endl;
    }
    
    // test data
    GRT::VectorDouble test(4), result;
    test[0] = 0.5;
    test[1] = 0.5;
    test[2] = 0.5;
    test[3] = 0.5;

    // test the test data against all neurons in the SOM
    mySom.map(test);

    // get the result
    result = mySom.getMappedData();

    // check the liklihood
    int winner = 0;
    double biggest = 0.0;
    for(int i =0; i<4; i++){
    	if(biggest < result[i]){
    		biggest = result[i];
    		winner = i;
    	}
        cout << "likihood" << i  << ": " << result[i] << endl;
    }
    cout << "The test vector 0.5 0.5 0.5 0.5 belongs to category:" << winner << endl;
}