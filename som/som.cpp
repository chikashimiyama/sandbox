// Author:		John McCullock
// Date:		10-9-05
// Description:	Self-Organizing Map Network Example 1.

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int maxClusters = 2;
const int vectors = 4;
const int vecLen = 4;
const double decayRate = 0.96;
const double minAlpha = 0.01;

double alpha = 0.6;
double d[maxClusters];

double w[maxClusters][vecLen] = {{0.2, 0.6, 0.5, 0.9},
                                 {0.8, 0.4, 0.7, 0.3}};

int pattern[vectors][vecLen] = {{1, 1, 0, 0},
                                {0, 0, 0, 1},
                                {1, 0, 0, 0},
                                {0, 0, 1, 1}};

int tests[vectors][vecLen] = {{1, 0, 0, 1},
                              {0, 1, 1, 0},
                              {1, 0, 1, 0},
                              {0, 1, 0, 1}};

void training();
void testing();
void computeInput(int vectorNumber);
int minimum(double valueA, double valueB);

int main(){
    cout << fixed << setprecision(3) << endl;  //Format all the output.
    training();
    testing();

    return 0;
}

void training(){
    int iterations = 0;
    int dMin = 0;

    do {
        iterations += 1;
        cout << "iteration" << iterations << endl;
        for(int vecNum = 0; vecNum < vectors; vecNum++){ // 4 times
            computeInput(vecNum); // 

            dMin = minimum(d[0], d[1]);
            cout << "Closest is d(" << dMin << ")" << endl;

            //Update the weights on the winning unit.
            for(int i = 0; i <= (vectors - 1); i++){
                w[dMin][i] = w[dMin][i] + (alpha * (pattern[vecNum][i] - 
                                                            w[dMin][i]));
                //cout << " w(" << i << ")= " << w[dMin][i];
            } // i

        } // vecNum

        //Reduce the learning rate.
        alpha = decayRate * alpha; // decayRateは0.96固定なのでだんだん弱くなる

    } while(alpha > minAlpha); // アルファ(初期値 0.6)がminAlpha(0.01)より小さくなったら終了

    cout << "Iterations: " << iterations << "\n\n";
}

void testing(){
    int dMin;

//Print clusters created.
    cout << "Clusters for training input:" << endl;

    for(int vecNum = 0; vecNum <= (vectors - 1); vecNum++){

        //Compute input.
        computeInput(vecNum);

        //See which is smaller, d[0] or d[1]?
        dMin = minimum(d[0], d[1]);

        cout << "\nVector (";
        for(int i = 0; i <= (vectors - 1); i++){
            cout << pattern[vecNum][i] << ", ";
        } // i
        cout << ") fits into category " << dMin << endl;

    } // vecNum

//Print weight matrix.
    cout << "\n";
    for(int i = 0; i <= (maxClusters - 1); i++){
        cout << "Weights for Node " << i << " connections:" << endl;
        for(int j = 0; j <= (vecLen - 1); j++){
            cout << w[i][j] << ", ";
        } // j
        cout << "\n\n";
    } // i

//Print post-training tests.
    cout << "Categorized test input:" << endl;

    for(int vecNum = 0; vecNum <= (vectors - 1); vecNum++){
        //Compute input.
        computeInput(vecNum);

        //See which is smaller, d[0] or d[1]?
        dMin = minimum(d[0], d[1]);

        cout << "\nVector (";
        for(int i = 0; i <= (vectors - 1); i++){
            cout << tests[vecNum][i] << ", ";
        } // i
        cout << ") fits into category " << dMin << endl;

    } // vecNum
}

void computeInput(int vectorNumber){

//それぞれのクラスタとインプットの距離を求める

    d[0] = 0.0;
    d[1] = 0.0;
    
    for(int i = 0; i < maxClusters; i++){
        for(int j = 0; j < vectors; j++){
            // w .. 位置
            d[i] += pow((w[i][j] - tests[vectorNumber][j]), 2);
            cout << "D= " << d[i] << "\n";
        } // j
    } // i
}

int minimum(double valueA, double valueB){
    if(valueA > valueB){
        return 1;
    }else{
        return 0;
    }
}