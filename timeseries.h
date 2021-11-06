#include <fstream>
#include <iosfwd>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include "string"

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <list>

//using namespace std;
using namespace std;
using namespace timeseries.h;
class TimeSeries {

public:
    const char* fileName;
    map<string, std::vector<float>> flightData;
    vector<string> headers;
    explicit TimeSeries (const char* CSVfileName);
     // why explicit?



}



#endif /* TIMESERIES_H_ */
