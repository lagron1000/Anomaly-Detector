#include "anomaly_detector_util.h"
#include <cmath>

float E(float *arr)
{
    float avarage;
    int lenght = sizeof(arr)/sizeof(*arr);
    int sum = 0;
    for (int i = 0; i < lenght; i++) {
        sum = sum + arr[i];
    }

    avarage = sum / lenght;
    return avarage;
}

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

//Point::Point(float x, float y) {
//    x = x;
//    y = y;
//
//}

float dev(Point p,Point** points, int size) {
    Line l = linear_reg(points, size);
    float dist = abs(p.y - l.f(p.x));
    return dist;
}

float dev(Point p,Line l) {
    float dist = abs(p.y - l.f(p.x));
    return dist;
}
// // returns the variance of X and Y

// float var(float *x, int size);



///////////////////////////////////////////////////////////////////////////////////////////////

// returns the covariance of X and Y
float cov(float *x, float *y, int size)
{
    float cov;
    float Ex = E(x);
    float Ey = E(y);
    // cov = E(x - Ex)*(y-Ey);
    float *xy;
    for (int i = 0; i < size; i++) {
        xy[i] = x[i]*y[i];
    }
    cov = E(xy) - E(x)*E(y);
    return cov;
}
//Line::Line(float aa, float bb) {
//    a = aa;
//    b = bb;
//}

Line linear_reg(Point **points, int size) {
    //Line l = new Line(float x,float y);
    float *xArr;
    float *yArr;
    for (int i = 0; i < size; i++)
    {
        xArr[i] = points[i]->x;
        yArr[i] = points[i]->y;
    }

    float a = cov(xArr, yArr, size)/var(xArr, size);
    float b = E(yArr) - a * E(xArr);
    Line y(a,b);
    return y;
}

