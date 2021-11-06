#include "timeseries.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std:

/**************************************************
 * constructor
 * @param CSVfileName
 **************************************************/
vector<string> TimeSeries::splitter(string givenString) {
    vector<string> lineVector;
    // new Object from istringstream type. Class/Type doc: https://www.cplusplus.com/reference/sstream/istringstream/
    // that is the constructor, Iv'e did that so we can use "getLine" splitter for CSV content
    istringstream toSplit(givenString);
    // the split part:
    string substring;
    // istream & getline (char* s, streamsize n, char delim );
    // doc: https://www.cplusplus.com/reference/istream/istream/getline/
    while (getline(toSplit, substring, ',') == 1) {
        // Adds a new element at the end of the vector, after its current last element.
        // https://www.cplusplus.com/reference/vector/vector/push_back/
        lineVector.push_back(substring);
    }
    return lineVector;
}

/**************************************************
 * constructor, CSV file reader
 * @param CSVfileName
 **************************************************/
TimeSeries::TimeSeries(const char *CSVfileName) {
    ifstream orAndLiorStream(CSVfileName);
    if (!orAndLiorStream.is_open()) {
        cout << "Didn't opened well! ERROR" << endl;
        return; // is it necessary? :O idk.
    }
    vector<sring> split_line;
    // lineToStore = object where the extracted line is stored.
    string lineToStore;
    // or&lior stream = the object form which characters are extracted.
    //  Each extracted character is appended to the string as if its member push_back was called.
    getline(orAndLiorStream, lineToStore);
    splittedLine = splitter(lineToStore);

    // updating the header vector - only the headers of the given data!
    for (int j = 0; j < split_line.size(); j++) {
        headers.push_back(split_line[j]);
    }
    // the features of the current header's flight!
    vector<float> data_content[headers.size()];
    // Reading the rest of the file for the data while there's more left to read.
    while (getline(orAndLiorStream, lineToStore)) {
        splittedLine = splitter(lineToStore);
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
