

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual correlatedFeatures makeCF(string feat1, string feat2, float p, Line l, float t, Circle c);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
