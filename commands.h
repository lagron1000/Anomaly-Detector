

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
#include <sstream>
#include <sys/socket.h>

#define INT_A(aStart, aEnd, bStart, bEnd) ((aStart <= bEnd) && (aEnd >= bStart))
#define INT_B(aStart, aEnd, bStart, bEnd) ((bStart <= aEnd) && (bEnd >= aStart))
#define LINES_INT(aStart, aEnd, bStart, bEnd) (INT_A(aStart, aEnd, bStart, bEnd) || INT_B(aStart, aEnd, bStart, bEnd))
#define LINE_ENCAPS(aStart, aEnd, bStart, bEnd) ((aStart <= bStart) && (aEnd >= bEnd))
#define HAS_ENCAPS(aStart, aEnd, bStart, bEnd) (LINE_ENCAPS(aStart, aEnd, bStart, bEnd)||LINE_ENCAPS(bStart, bEnd, aStart, aEnd))

using namespace std;

struct Data {
    float threshold;
    int numOfRows;
    vector<AnomalyReport> reports;
    Data(){
        threshold=0.9;
        numOfRows = 0;
    }
};

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
};

class StandardIO : public DefaultIO {

public:
    StandardIO(){}
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

class SocketIO : public DefaultIO {
    int id;

public:
    SocketIO(int id) : id(id){}

    virtual string read() {
        char buf = 0;
        string input = "";
        while (buf != '\n') {
            recv(id, &buf, sizeof(char), 0);
            input += buf;
        }
        return input;
    }
    virtual void write(string text) {
        send(id, text.c_str(), text.size(), 0);
    }
    virtual void write(float f){
        ostringstream oss;
        oss << f;
        write (oss.str());
    }
    virtual void read(float* f){
        recv(id, f, sizeof(char), 0);
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
    UploadFile(DefaultIO* dio) : Command(dio, "upload a time series csv file\n"){}

    virtual void execute(Data* data) {
        dio->write("Please upload your local train CSV file.\n");
        dio->writeToFile("anomalyTrain.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->writeToFile("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }
};

/**
 * command 2
 */
class AlgorithmSettings : public Command {
    public:
    AlgorithmSettings(DefaultIO* dio) : Command(dio, "algorithm settings\n") {}
    virtual void execute(Data* data) {
        bool valid = false;
        dio->write("The current correlation threshold is ");
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
        data->numOfRows = ts2.getColSize();
        HybridAnomalyDetector hd;
        // learning
        hd.learnNormal(ts1);
        // detect test
        data->reports = hd.detect(ts2);
//        for (AnomalyReport r : reports) {
//            data->reports.push_back(r);
//        }
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
        //TODO: Command 3 didnt push reports to data->reports
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
    UploadAnomalies(DefaultIO* dio) : Command(dio, "upload anomalies and analyze results\n"){}

    void addAnomaly(string line, vector<Point>* p) {
        float x, y;
        string sX, sY;
        int commaI = line.find(',');
        sX = line.substr(0, commaI);
        sY = line.substr(commaI + 1);
        x = stof(sX);
        y = stof(sY);
        //TODO: check if this here below works
        p->push_back(Point(x, y));
    }

    vector<Point> getTimeIntervals(Data* data) {
        vector<Point> points;
        vector<AnomalyReport> reports = data->reports;
        int reportsSize = reports.size();
        float x = reports[0].timeStep;
        int count = 0;
        for (int i = 0; i < reportsSize; i++) {
            if (i == reportsSize-1) {
                float y = reports[i].timeStep;
                Point rep = Point(x, y);
                points.push_back(rep);
                break;
            }
            if (reports[i].description != reports[i+1].description || reports[i].timeStep+1 != reports[i+1].timeStep) {
                float y = reports[i].timeStep;
                Point rep = Point(x, y);
                points.push_back(rep);
                x = reports[i+1].timeStep;
            }
        }
        return points;
    }

    //todo:
    // supposed to be Data* data!!
    virtual void execute(Data* data) {
        dio->write("Please upload your local anomalies file.\n");
        vector<Point> anomaliesUploaded;
        string line = dio->read();
        float n = data->numOfRows;
        float p = 0;
        while (line != "done") {
            addAnomaly(line, &anomaliesUploaded);
            line = dio->read();
            p++;
        }
        dio->write("Upload complete.\n");
        float falsePosCount = 0;
        float truePosCount = 0;

        vector<Point> anomaliesDetected = getTimeIntervals(data);

        int sum = 0;
        for (Point p : anomaliesUploaded) {
            sum += p.y - p.x + 1;
        }

        for (Point detected : anomaliesDetected) {
            float aStart = detected.x;
            float aEnd = detected.y;
            bool gotTP;
            for (Point uploaded : anomaliesUploaded) {
                gotTP = false;
                float bStart = uploaded.x;
                float bEnd = uploaded.y;
                if (LINES_INT(aStart, aEnd, bStart, bEnd) || HAS_ENCAPS(aStart, aEnd, bStart, bEnd)) {
                    truePosCount++;
                    gotTP = true;
                    break;
                }
            }
            if (!gotTP) falsePosCount++;
        }

        int N = n - sum;
        dio->write("True Positive Rate: ");
        dio->write(((int)(1000.0*truePosCount / p))/1000.0f);
        dio->write("\nFalse Positive Rate: ");
        dio->write(((int)(1000.0*falsePosCount / N))/1000.0f);
        dio->write("\n");
    }
};




#endif /* COMMANDS_H_ */
