#include "FuzzyArt.h"
#include <iostream>
#include <fstream>

using namespace std;
void loadData();
void printData();
void printChoices(std::vector<double> choices);

std::vector<std::vector<double> > dataVector;

void loadData(){
	ifstream file("/Users/chikashi/Development/sandbox/FuzzyART/FuzzyART/iris.txt");
	std::string value;
	int counter  = 0;

	std::vector<double> vd;
	while ( file.good() ){

		getline(file, value, ',' );
		double dv = atof(value.c_str());
		vd.push_back(dv);
		counter++;
		counter %= 4;
		if(counter == 0){
			dataVector.push_back(vd);
			vd.clear();
		}
	}

	std::cout << dataVector.size() << " samples loaded" << std::endl;
	//printData();
}

void printData(){
	std::vector<std::vector<double> >::iterator it = dataVector.begin();
	int cnt = 0;
	while(it != dataVector.end()){
		std::vector<double> sampVector = *it;
		std::vector<double>::iterator iit = sampVector.begin();
		cout << "sample: " << cnt << " - ";
		while(iit != sampVector.end()){
			cout << *iit << " ";
			iit++;
		}
		cout << endl;
		cnt++;
		it++;
	}

}

int main(){
	FuzzyArt fa(0, 0.5, 0.5);
	loadData();

	// feed all data 
	std::vector<std::vector<double> >::iterator it = dataVector.begin();
	while(it != dataVector.end()){
		std::vector<double> sampVector = *it;
		fa.predict(sampVector);
		it++;
	}

	fa.dump();
	printChoices(fa.getCategoryChoices());
    
    //test
    
    cout << "===TEST===" << endl;
    double versicolor[] = {5.6, 2.9, 3.6, 1.3}; // cat 1
    double virginica[] = {7.9, 3.8, 6.4, 2.0}; // cat 2
    double setosa[] = {4.8, 3.4, 1.9, 0.2}; // cat 3
    std::vector<double> veriscolorVec(versicolor, versicolor+4);
    std::vector<double> virginicaVec(virginica, virginica+4);
    std::vector<double> setosaVec(setosa, setosa+4);

    cout << "5.6, 2.9, 3.6, 1.3 belongs to category:" << fa.predict(veriscolorVec) << endl;
    printChoices(fa.getCategoryChoices());
    cout << "7.9, 3.8, 6.4,	2.0 belongs to category:" << fa.predict(virginicaVec) << endl;
    printChoices(fa.getCategoryChoices());
    cout << "4.8, 3.4, 1.9, 0.2 belongs to category:" << fa.predict(setosaVec) << endl;
    printChoices(fa.getCategoryChoices());

	return 0;
}

void printChoices(std::vector<double> choices){

    size_t size = choices.size();

    std::cout << "Number of Choices:" << size << std::endl;
    std::cout << "choices: ";
    for(int i = 0; i < size; i++){
        std::cout << choices[i] << " ";
    }
    std::cout << std::endl;

}