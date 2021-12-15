/*
 * HybridAnomalyDetector.h
 *
 * Author:
 * Or Spiegel 318720067
 * Lior Agron 208250225
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual correlatedFeatures makeCF(string feat1, string feat2, float p, float threshold, Circle c);
    virtual void addCF(TimeSeries ts, string firstFeat, string secondFeat, float m);
    virtual bool checkAnomaly(Point p, correlatedFeatures cf);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
