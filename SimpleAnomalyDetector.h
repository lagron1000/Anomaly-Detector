/*
 * SimpleAnomalyDetector.h
 *
 * Author:
 * Or Spiegel 318720067
 * Lior Agron 208250225
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

//#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "minCircle.h"

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
    // a line made from all points (feat1[i], feat2[i]);
	Line lin_reg;
    //largest distance of a point from the line (multiplied by 1.1);
	float threshold;
    // circle enclosing all points within normal range
    Circle minCirc;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
protected:
    vector<correlatedFeatures> cf;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();
	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    virtual correlatedFeatures makeCF(string feat1, string feat2, float p, Line l, float t);
    std::vector<Point*> getPointsVector(float* a, float* b, int size);
    virtual void addCF(TimeSeries ts, string firstFeat, string secondFeat, float m);
    virtual bool checkAnomaly(Point p, correlatedFeatures cf);
	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
