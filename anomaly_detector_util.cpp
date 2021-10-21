#include "anomaly_detector_util.h"
#include <cmath>

 float var(float *x, int size) {
     float ans = 0;
     float mu = E(x);
     for (int i = 0; i <= size; x++, i++) {
         ans += (*x - mu) * (*x - mu);
     }
     return ans / size;
 }

float pearson(float* x, float* y, int size) {
    float coVar = cov(x, y, size);
    float standartDeviation = sqrt(var(x, size)) * sqrt(var(y, size));
    return coVar / standartDeviation;
}

Point::Point(float x, float y) {
    x = x;
    y = y;

}

float dev(Point p,Point** points, int size) {
    Line l = linear_reg(points, size);
    float dist = abs(p.y - l.f(x));
    return dist;
}

float dev(Point p,Line l) {
    float dist = abs(p.y - l.f(x));
    return dist;
}
//
