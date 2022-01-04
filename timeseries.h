/*
 * anomaly_detection_util.cpp
 *
 * Author:
 * Or Spiegel 318720067
 * Lior Agron 208250225
 */
#include <fstream>
#include <iosfwd>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include "string"
#include <list>

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries {
    const char* fileName;
    map<string, std :: vector<float>> flightData;
    vector<string> headers;
    int collumnSize = 0;
    int rowSize = 0;
public:
    explicit TimeSeries (const char* CSVfileName);
    // why explicit?
    vector<string> splitter(string givenString);
    vector<string> getHeaders() const;
    int getColSize() const;
    int getRowSize() const;
    map<string, std :: vector<float>> getMap() const;
};



#endif /* TIMESERIES_H_ */
