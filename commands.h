

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command{
	DefaultIO* dio;
public:
    public string desc;
    Command(DefaultIO* dio):dio(dio){}
    virtual std::string getDesc(){return desc};
	virtual void execute()=0;
	virtual ~Command(){}
};

struct Data {
    float threshold;
    vector<AnomalyReport> reports;
    Data() {
        threshold = 0.9;
    }
};

/**
 * command 2
 */
class AlgorithmSettings : public Command {
    public:
    AlgorithmSettings(DefaultIO* io) : Command(io, "algorithm settings") {}
    virtual void execute(Data* data) {
        bool valid = false;
        io->write("The current threshold is ");
        io->write("%f", data->threshold);
        io->write("\nType a new threshold\n");

        float inputVal;
        io->read(&inputVal);

        while (!valid) {
            if (inputVal > 0 && inputVal <= 1) {
                data->threshold = inputVal;
                valid = true;
            } else {
                io->write("please choose a value between 0 and 1.\n")
            }
        }
    }
};

/**
 * command 3
 */
class DetectAnomalies : public Command {
public:
    DetectAnomalies(DefaultIO* io) : Command(io, "detect anomalies\n") {}
    virtual void execute(Data* data) {
        TimeSeries ts1("anomalyTrain.csv");
        TimeSeries ts2("anomalyTest.csv");
        HybridAnomalyDetector hd;
        // learning
        hd.learnNormal(ts1);
        // detect test
        data->reports = hd.detect(ts2);
        io->write("anomaly detection complete.\n");
    }
};
/**
 * command 4
 */
class DisplayResults : public Command {
public:
    DisplayResults(DefaultIO* io) : Command(io, "display results\n") {}
    virtual void execute(Data* data) {
       for (int i = 0; i < data->reports.size(); i++) {
           this->io->write(std::to_string(data->reports[i].timeStep ) + "\t" + data->reports[i].description + "\n");
       } io.write("Done.\n");
    }
};

// implement here your command classes



#endif /* COMMANDS_H_ */
