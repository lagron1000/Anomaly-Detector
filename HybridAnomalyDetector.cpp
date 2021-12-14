
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

correlatedFeatures HybridAnomalyDetector::makeCF(string feat1, string feat2, float p, float threshold, Circle c) {
    correlatedFeatures newCF;
    newCF.corrlation = p;
    newCF.feature1 = feat1;
    newCF.feature2 = feat2;
    newCF.threshold = threshold;
    newCF.minCirc = c;
    return newCF;
}

void HybridAnomalyDetector :: addCF(TimeSeries ts, string firstFeat, string secondFeat, float m){
    if (m > 0.5 && m < 0.9) {
        map<string, std :: vector<float>> map = ts.getMap();
        int size = map[firstFeat].size();
        std::vector<Point*> points = getPointsVector(map[firstFeat].data(), map[secondFeat].data(), size);
        Circle minCirc = findMinCircle(&points[0], size);
        float threshold = minCirc.radius * 1.1;
        correlatedFeatures newCF = makeCF(firstFeat, secondFeat, m, threshold, minCirc);
        cf.push_back(newCF);
        return;
    }
    SimpleAnomalyDetector::addCF(ts, firstFeat, secondFeat, m);
}


void HybridAnomalyDetector :: considerAddingCF(float p, float* m, int* j, int* index, float* valuesA, float* valuesB,
                      int size, string* feat1, string* feat2, string* pair1,
                      Line* cfLine, float* cfThresh, int* f) {
    SimpleAnomalyDetector::considerAddingCF(p, m, j, index, valuesA, valuesB, size, feat1, feat2, pair1,
                                            cfLine, cfThresh, f);
    if (!(*f)) {
        if (p > 0.5) {
            std::vector<Point*> points = getPointsVector(valuesA, valuesB, size);
            Circle min = findMinCircle(&points[0], size);

        }
    }
}