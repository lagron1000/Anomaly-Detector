#include "anomaly_detector_util.h"
 float var(float *x, int size) {
     float ans = 0;
     float mu = E(x);
     for (int i = 0; i <= size; x++, i++) {
         ans += (*x - mu) * (*x - mu);
     }
     return ans / size;
 }