/*
 * anomaly_detection_util.cpp
 *
 * Author:
 * Or Spiegel 318720067
 * Lior Agron 208250225
 */

#include "SimpleAnomalyDetector.h"
//#include "anomaly_detection_util.h"
#include <string>

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void deletePoints(std::vector<Point*> points) {
    for (int i = 0; i < points.size(); i++) {
        delete points[i];
    }
}

std::vector<Point*> getPointsVector(float* a, float* b, int size) {
    std::vector<Point*> points;
    for (int t = 0; t <= size; t++) {
        Point* p = new Point(a[t], b[t]);
        points.push_back(p);
    }
    return points;
}

float getCFThreshold(std::vector<Point*> p, Line l, int size) {
    float largestDev = 0;
    for (int t = 0; t < size; t++) {
        float d = dev(*p[t], l);
        if (largestDev < d) largestDev = d;
    }
    return largestDev * 1.1;
}

int checkPairs(std::vector<string*> pairsChecked, string* newPair) {
    int pairFound = 0;
    for (string* n : pairsChecked) {
        if (!n[0].compare(newPair[0]) && !n[1].compare(newPair[1])) pairFound = 1;
    }
    return pairFound;
}

correlatedFeatures makeCF(string feat1, string feat2, float p, Line l, float t) {
    correlatedFeatures newCF;
    newCF.corrlation = p;
    newCF.feature1 = feat1;
    newCF.feature2 = feat2;
    // linear_reg() accepts an Array so we convert the vector to one
    // using the pointer to the first element.
    newCF.lin_reg = l;
    newCF.threshold = t;
    return newCF;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    std::vector<string*> pairsChecked;
    // correlated should probably be saved as a field
    std::vector<string*> correlated;
    map<string, std :: vector<float>> map = ts.getMap();
    // looping through all properties in map
    for (auto it = map.begin(); it != map.end(); ++it) {
        string feat1,feat2;  // names of the correlated features
        Line cfLine;
        float cfThresh;
        float p = 0;
        int j = 0;
        int index = 0;
        // m is the highest correlation recorded for this feature (Above the base threshold). base threshold is 0.9.
        float m = 0.9;
        string collumAName = it->first;
        float* valuesA = &it->second[0];
        int foundCorrelationFlag = 0;
        // looping again so that every property would be checked against all other properties.
        for (auto secIt = map.begin(); secIt != map.end(); ++secIt) {
            string collumBName = secIt->first;
            // since vectors are saved in memory sequentially like arrays - "converted" the vector into an array
            // by pointing at its first elements address for convince sake.
            float* valuesB = &secIt->second[0];
            // checking if pair was previously checked so we don't check the same pair twice.
            string* newPair = new string[2]{collumAName, collumBName};
            if (checkPairs(pairsChecked, newPair)) continue;
            // all columns are correlated to themselves.
            if (!collumAName.compare(collumBName)) continue;
            // adding both orientations as to avoid duplicate checks.
            string* pair1 = new string[2] {collumAName, collumBName};
            string* pair2 = new string[2]{collumBName, collumAName};
            pairsChecked.push_back(pair1);
            pairsChecked.push_back(pair2);
            int size = it->second.size();
            p = pearson(valuesA, valuesB, size);
            // if pearson is negative - multiply it by -1.
            if (p < 0 ) p = (-1) * p;
            if (p >= m) {
                foundCorrelationFlag = 1;
                j = index;
                // we want to couple this feat with its most correlative partner only, thus we up the local threshold
                // everytime we find a feat with witch featA is more correlative.
                m = p;
                std::vector<Point*> points = getPointsVector(valuesA, valuesB, size);
                feat1 = pair1[0];
                feat2 = pair1[1];
                // linear_reg() accepts an Array so we convert the vector to one
                // using the pointer to the first element.
                cfLine = linear_reg(&points[0], size);
                cfThresh = getCFThreshold(points, cfLine, size);
                // TODO: delete points
                deletePoints(points);
            }
            index++;
        }
        // only do the following if we found a correlating feature.
        if (foundCorrelationFlag) {
            correlatedFeatures newCF = makeCF(feat1, feat2, m, cfLine, cfThresh);
            cf.push_back(newCF);
        }
    }
}



vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> reports;
    int cSize = ts.getColSize();
//    correlatedFeatures* pairs = &cf[0];
    map<string, std :: vector<float>> map = ts.getMap();
    // i is the row num
    for (int i = 0; i <  cSize; i++) {
        // j is the j-th correlative pair/
        for (int j = 0; j < cf.size(); j++) {
            string feat1 = cf[j].feature1;
            string feat2 = cf[j].feature2;
            float x = map[feat1][i];
            float y = map[feat2][i];
            Point p = Point(x, y);
            float d = dev(p, cf[j].lin_reg);
            if (d > cf[j].threshold) {
                string desc = feat1 + "-" + feat2;
                AnomalyReport AR = AnomalyReport(desc,i + 1);
                reports.push_back(AR);
            }
        }
    }
    return reports;
}
