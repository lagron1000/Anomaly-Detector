

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class Data {
public:
    float time, altitude, speed, heading;
    Data(float t, float a, float s, float h) : time(t), altitude(a), speed(s), heading(h){}
};

class TimeSeries{

public:

	TimeSeries(const char* CSVfileName){
	}

};



#endif /* TIMESERIES_H_ */
