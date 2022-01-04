/*
 * anomaly_detection_util.cpp
 *
 * Author:
 * Or Spiegel 318720067
 * Lior Agron 208250225
 */
#include "timeseries.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
//using namespace timeseries.h;
/**************************************************
 * constructor
 * @param CSVfileName
 **************************************************/
vector<string> TimeSeries :: splitter(string givenString) {
    vector<string> lineVector;
    // new Object from istringstream type. Class/Type doc: https://www.cplusplus.com/reference/sstream/istringstream/
    // that is the constructor, Iv'e did that so we can use "getLine" splitter for CSV content
    istringstream toSplit(givenString);
    // the split part:
    string substring;
    // istream & getline (char* s, streamsize n, char delim );
    // doc: https://www.cplusplus.com/reference/istream/istream/getline/
    while (getline(toSplit, substring, ',')) {
        // Adds a new element at the end of the vector, after its current last element.
        // https://www.cplusplus.com/reference/vector/vector/push_back/
        lineVector.push_back(substring);
    }
    return lineVector;
}

vector<string> TimeSeries :: getHeaders() const {
    return headers;
}

map<string, std :: vector<float>> TimeSeries ::getMap() const {
    return flightData;
}

int TimeSeries :: getColSize() const {
    return collumnSize;
}

int TimeSeries :: getRowSize() const {
    return rowSize;
}



/**************************************************
 * constructor, CSV file reader
 * @param CSVfileName
 **************************************************/
TimeSeries::TimeSeries(const char *CSVfileName) {
    collumnSize = 0;
    ifstream orAndLiorStream(CSVfileName);
    if (!orAndLiorStream.is_open()) {
        cout << "Didn't open! ERROR" << endl;
        return; // is it necessary? :O idk.

        // jajaja ¯\_(ツ)_/¯.
    }
    vector<string> split_line;
    // lineToStore = object where the extracted line is stored.
    string lineToStore;
    // or&lior stream = the object form which characters are extracted.
    //  Each extracted character is appended to the string as if its member push_back was called.
    getline(orAndLiorStream, lineToStore);
//    splittedLine = splitter(lineToStore);
    split_line = splitter(lineToStore);


    // updating the header vector - only the headers of the given data!
    for (int j = 0; j < split_line.size(); j++) {
        headers.push_back(split_line[j]);
        rowSize++;
    }
    // the features of the current header's flight!
    vector<float> data_content[headers.size()];
    // Reading the rest of the file for the data while there's more left to read.
    while (getline(orAndLiorStream, lineToStore)) {
         split_line = splitter(lineToStore);
         collumnSize++;
        for (int i = 0; i < split_line.size(); i++) {
            data_content[i].push_back(stof(split_line[i]));
        }
    }

    // adding the vectors to our main map!
    for (int k = 0; k < headers.size(); k++) {
        flightData.insert(pair<string, vector<float>>(headers[k], data_content[k]));
    }

orAndLiorStream.close();
}

