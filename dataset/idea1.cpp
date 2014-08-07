
#include <iostream>
#include <vector>

using namespace std;

// super class with some common functions
class TimeStamp{
	// some useful funtions
};

// sub classes of Time Stamp
// instantiation of these classes are possible via Dataset class
// constructor is defined as private function.
class TimeStampDeltaTime: public TimeStamp{
private:
	friend class Dataset;
	double deltaTime;
	TimeStampDeltaTime(double dt):deltaTime(dt){}; // PRIVATE FUNCTION !
public:
	// some specific function with delta time
};

class TimeStampIndex: public TimeStamp{
private: 
	friend class Dataset;
	unsigned long index;
	TimeStampIndex(unsigned long id):index(id){}; // PRIVATE FUNCTION !
public:
	// some specific function with time index

};

// data class. skelton of Daniel's funcy class
class Data{
private:
	int someData;
public:
	Data(int d):someData(d){};
	// some more funcs
};

// event class which makes pair of data and timestamp
// if you want to associate multiple data with one timeStamp
// set deltaTime to 0.0

class Event{ // conbine data and timestamp, unchangeable! 
public:
	Event(TimeStamp t, Data d): ts(t), dt(d){};
	const Data dt;
	const TimeStamp ts; // actually keeps an instance of subclss
};


// Dataset maintains many Events, knows its timetype, and is able to create events
class Dataset{
public:
	enum TimeFormat{
		MGM_MODE_DELTA_TIME,
		MGM_MODE_TIME_INDEX
	};

	Dataset(const TimeFormat format): tf(format){}; 
	std::vector<Event> events;

	// overloaded for both type
	void addEvent(double deltaTime, Data dt); 
	void addEvent(unsigned long index, Data dt);
	// more event handling functions

private:
	const TimeFormat tf;
};

void Dataset::addEvent(double deltaTime, Data dt){
	if(tf != MGM_MODE_DELTA_TIME){
		cout << "time index should be unsigned long" << endl;
	}else{
		Event newEvent(TimeStampDeltaTime(deltaTime), dt);
		events.push_back(newEvent);
	}
}

inline void Dataset::addEvent(unsigned long timeIndex, Data dt){
	if(tf != MGM_MODE_TIME_INDEX){
		cout << "deltaTime should be double" << endl;
	}else{
		Event newEvent(TimeStampIndex(timeIndex), dt);
		events.push_back(newEvent);
	}
}

int main(){
	// we have to initialize time format of a data set when we instantiate
	Dataset deltaTimeDS = Dataset(Dataset::MGM_MODE_DELTA_TIME);
	Dataset indexTimeDS = Dataset(Dataset::MGM_MODE_TIME_INDEX);
	Data dummy(24);

	deltaTimeDS.addEvent(2.51, dummy);
	indexTimeDS.addEvent(30UL, dummy); // bit stupid


	return 0;
}