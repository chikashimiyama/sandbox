#include <iostream>
using namespace std;
template<typename Tn> class Example{
public:
	Tn data;	
	Tn getData(){return data;};
	void setData(Tn d){data = d;};
};


template<typename T>
T multi(T a, T b){
	return a * b;
}


class sdInterpolation{

public:
    template <typename T>
    T interpolate(T valueA, T valueB, double weight);

};

template <typename T>
T sdInterpolation::interpolate(T valueA, T valueB, double weight){
    return (valueB - valueA)  * weight + valueA;
}




int main(){
	float x = multi(2.3 , 3.1);
	int  y = multi(2.3, 3.1);
	int  z = multi<float>(2.3, 3.1);

	cout << x << endl;
	cout << y << endl;
	cout << z << endl;

	Example<float> ex;
	ex.setData(20.3);
	cout << ex.getData() << endl;

	sdInterpolation intp;
	cout <<  "intp: " << intp.interpolate(300, 900, 0.3) << endl;

	return 0;
}