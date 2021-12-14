

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual correlatedFeatures makeCF(string feat1, string feat2, float p, float threshold, Circle c);
    virtual void considerAddingCF(float p, float* m, int* j, int* index, float* valuesA, float* valuesB,
                                  int size, string* feat1, string* feat2, string* pair1,
                                  Line* cfLine, float* cfThresh, int* f);
    virtual void addCF(TimeSeries ts, string firstFeat, string secondFeat, float m);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
