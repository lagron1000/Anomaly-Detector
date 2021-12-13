
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

correlatedFeatures HybridAnomalyDetector::makeCF(string feat1, string feat2, float p, Line l, float t, Circle c) {
    correlatedFeatures cf = SimpleAnomalyDetector::makeCF(feat1, feat2, p, l, t);
    cf.minCirc = c;
    return cf;
}