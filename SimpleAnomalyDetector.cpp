
#include "SimpleAnomalyDetector.h"
//#include "anomaly_detection_util.h"
#include <string>

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    float corThreshold = 0.9;
    float p = 0;
    std::vector<string*> pairsChecked;
    // correlated should probably be saved as a field
    std::vector<string*> correlated;
    map<string, std :: vector<float>> map = ts.getMap();
    // looping through all properties in map
    for (auto it = map.begin(); it != map.end(); ++it) {
        float m = corThreshold;
        int j = 0;
        int index = 0;
        string collumAName = it->first;
        float* valuesA = &it->second[0];
        // looping again so that every property would be checked against all other properties.
        for (auto secIt = map.begin(); secIt != map.end(); ++secIt) {
            string collumBName = secIt->first;
            // since vectors are saved in memory sequentially like arrays - "converted" the vector into an array
            // by pointing at its first elements address for convince sake.
            float* valuesB = &secIt->second[0];
            // checking if pair was previously checked so we don't check the same pair twice.
            string* newPair = new string[2]{collumAName, collumBName};
            for (string* n : pairsChecked) {
                if (!n[0].compare(newPair[0]) && !n[1].compare(newPair[1])) break;
            }
            // all columns are correlated to themselves.
            if (!collumAName.compare(collumBName)) break;
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
                j = index;
                // we want to couple this feat with its most correlative partner only, thus we up the local threshold
                // everytime we find a feat with witch featA is more correlative.
                m = p;
                std::vector<Point*> points;
                for (int t = 0; t <= size; t++) {
                    Point* p = new Point(valuesA[t], valuesB[t]);
                    points.push_back(p);
                }
                correlatedFeatures newCF;
                newCF.corrlation = p;
                newCF.feature1 = pair1[0];
                newCF.feature2 = pair1[1];
                // linear_reg() accepts an Array so we convert the vector to one
                // using the pointer to the first element.
                Line l = linear_reg(&points[0], size);
                newCF.lin_reg = l;
                float largestDev = 0;
                for (int t = 0; t <= size; t++) {
                    float d = dev(*points[t], l);
                    if (largestDev < d) largestDev = d;
                }
                newCF.threshold = largestDev * 1.1;
                cf.push_back(newCF);
            }
        }
        index++;
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
//    return vector<AnomalyReport> ();
}


float SimpleAnomalyDetector::getCorrelation(vector<float> feature_a, vector<float> feature_b) {
    return 0;
}
