
#include <iostream>
#include <vector>

using namespace std;

// data class
class Data{
private:
	int someData;
public:
	Data(int d):someData(d){};
	// some more funcs
};

// event class which makes pair of data and timestamp

template<typename TT> class Event{ // conbine data and timestamp, unchangeable! 
public:
	Event(TT t, Data d): timeData(t), dt(d){};
	const Data dt;
	TT timeData;// this could be deltaTime or timeIndex
};


// Dataset maintains many Events, knows its time type, and is able to create event
template<typename TT> class Dataset{
public:

	std::vector<Event<TT> > events; // vector of uint or double
	void addEvent(TT timeData, Data dt); 
	// more event handling functions follows...

};

template<typename TT> 
void Dataset<TT>::addEvent(TT timeData, Data dt){

	Event<TT> newEvent(timeData, dt);
	events.push_back(newEvent);
}

int main(){

	Dataset<double> deltaTimeDS;
	Dataset<unsigned long> indexTimeDS;
	// This is semantically not so ellegant but we can make it cleaner
	// using factory design pattern for example.

	Data dummy(24);

	deltaTimeDS.addEvent(2.51, dummy);
	indexTimeDS.addEvent(30UL, dummy); 


	return 0;
}