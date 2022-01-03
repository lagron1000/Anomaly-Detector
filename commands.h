

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

#define INT_A(aStart, aEnd, bStart, bEnd) ((aStart <= bEnd) && (aEnd >= bStart))
#define INT_B(aStart, aEnd, bStart, bEnd) ((bStart <= aEnd) && (bEnd >= aStart))
#define LINES_INT(aStart, aEnd, bStart, bEnd) (INT_A(aStart, aEnd, bStart, bEnd) || INT_B(aStart, aEnd, bStart, bEnd))

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

    void writeToFile(string newFileName) {
        ofstream out(newFileName);
        string line = "";
        while ((line = read()) != "done") {
            out<<line<<endl;
        }
        out.close();
    }
	// you may add additional methods here
};

// you may add here helper classes

class StandardIO : DefaultIO {

public:
    virtual string read(){
        string s;
        cin>>s;
        return s;
    }
    virtual void write(string text){
        cout<<text;
    }

    virtual void write(float f){
        cout<<f;
    }

    virtual void read(float* f){
        cin>>*f;
    }

};

struct Data {
    float threshold;
    vector<AnomalyReport> reports;
    Data(){
        threshold=0.9;
    }
};


class Command{
protected:
    DefaultIO* dio;
public:
  string desc;
	Command(DefaultIO* dio, string desc):dio(dio), desc(desc){}
  virtual std::string getDesc(){return desc;}
	virtual void execute(Data* data)=0;
	virtual ~Command(){}
};


/**
 * command 1
 */
class UploadFile : public Command {
public:
    UploadFile(DefaultIO* dio) : Command(dio, "upload a time series csv file"){}

    virtual void execute(Data* data) {
        dio->write("Please upload your local train CSV file.\n");
        dio->writeToFile("anomalyTrain.csv");
        dio->write("Upload complete\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->writeToFile("anomalyTest.csv");
        dio->write("Upload complete\n");
    }
};

/**
 * command 2
 */
class AlgorithmSettings : public Command {
    public:
    AlgorithmSettings(DefaultIO* dio) : Command(dio, "algorithm settings") {}
    virtual void execute(Data* data) {
        bool valid = false;
        dio->write("The current threshold is ");
        dio->write(data->threshold);
        dio->write("\nType a new threshold\n");

        float inputVal;
        dio->read(&inputVal);

        while (!valid) {
            if (inputVal > 0 && inputVal <= 1) {
                data->threshold = inputVal;
                valid = true;
            } else {
                dio->write("please choose a value between 0 and 1.\n");
            }
        }
    }
};

/**
 * command 3
 */
class DetectAnomalies : public Command {
public:
    DetectAnomalies(DefaultIO* dio) : Command(dio, "detect anomalies\n") {}
    virtual void execute(Data* data) {
        TimeSeries ts1("anomalyTrain.csv");
        TimeSeries ts2("anomalyTest.csv");
        HybridAnomalyDetector hd;
        // learning
        hd.learnNormal(ts1);
        // detect test
        data->reports = hd.detect(ts2);
        dio->write("anomaly detection complete.\n");
    }
};

/**
 * command 4
 */
class DisplayResults : public Command {
public:
    DisplayResults(DefaultIO* dio) : Command(dio, "display results\n") {}
    virtual void execute(Data* data) {
       for (int i = 0; i < data->reports.size(); i++) {
           dio->write(std::to_string(data->reports[i].timeStep ) + "\t" + data->reports[i].description + "\n");
       }
       dio->write("Done.\n");
    }
};

/**
 * command 5
 */
class UploadAnomalies : public Command {
public:
    UploadAnomalies(DefaultIO* dio) : Command(dio, "upload anomalies and analyze results"){}

    void addAnomaly(string line, vector<Point>* p) {
        float x, y;
        string sX, sY;
        int commaI = line.find(',');
        sX = line.substr(0, commaI);
        sY = line.substr(commaI + 1);
        x = stoi(sX);
        y = stoi(sY);
        //TODO: check if this here below works
        p->push_back(Point(x, y));
    }

    vector<Point> getTimeIntervals(Data data) {
        vector<Point> points;
        vector<AnomalyReport> reports = data.reports;
        int reportsSize = reports.size();
        float x = reports[0].timeStep;
        int count = 0;
        for (int i = 0; i <= reportsSize; i++) {
            if (reports[i].timeStep != x || i == reportsSize) {
                float y = x + count;
                Point rep = Point(x, y);
                points.push_back(rep);
                x = reports[i].timeStep;
                count = 0;
                break;
            }
            count++;
        }
        return points;
    }

    //todo:
    // supposed to be Data* data!!
    virtual void execute(Data data) {
        dio->write("Please upload your local anomalies file.");
        vector<Point> anomaliesUploaded;
        string line = dio->read();
        int n = 0;
        while (line != "done") {
            addAnomaly(line, &anomaliesUploaded);
            line = dio->read();
            n++;
        }
        dio->write("Upload Complete.");
        int falsePosCount = 0;
        int truePosCount = 0;

        vector<Point> anomaliesDetected = getTimeIntervals(data);

        int p = anomaliesDetected.size();

        for (Point uploaded : anomaliesUploaded) {
            float aStart = uploaded.x;
            float aEnd = uploaded.y;
            for (Point detected : anomaliesDetected) {
                float bStart = detected.x;
                float bEnd = detected.y;
                if (LINES_INT(aStart, aEnd, bStart, bEnd)) truePosCount++;
                else falsePosCount++;
            }
        }

        dio->write("True Positive Rate: ");
        dio->write(truePosCount / p);
        dio->write("False Positive Rate: ");
        dio->write(falsePosCount / n);
    }
};




#endif /* COMMANDS_H_ */
