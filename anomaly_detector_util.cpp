/*
 * animaly_detection_util.cpp
 *
 * Author: 
 * Or Spiegel 
 * Lior Agron 208250225
 */

#include <math.h>
#include <cmath>
#include "anomaly_detector_util.h"

float avg(float* x, int size){
{
    float avarage = 0;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + arr[i];
    }

    avarage = sum / size;
    return avarage;
}

// returns the variance of X and Y
 float var(float *x, int size) {
     float ans = 0;
     float mu = avg(x);
     for (int i = 0; i <= size; x++, i++) {
         ans += (*x - mu) * (*x - mu);
     }
     return ans / size;
 }

// returns the covariance of X and Y
float cov(float *x, float *y, int size)
{
    float cov;
    float Ex = avg(x);
    float Ey = avg(y);
    // cov = avg(x - Ex)*(y-Ey);
    float *xy;
    for (int i = 0; i < size; i++) {
        xy[i] = x[i]*y[i];
    }
    cov = avg(xy) - avg(x)*avg(y);
    return cov;
}

float pearson(float* x, float* y, int size) {
    float coVar = cov(x, y, size);
    float standartDeviation = sqrt(var(x, size)) * sqrt(var(y, size));
    return coVar / standartDeviation;
}

Line linear_reg(Point **points, int size) {
    //Line l = new Linavg(float x,float y);
    float *xArr;
    float *yArr;
    for (int i = 0; i < size; i++)
    {
        xArr[i] = points[i]->x;
        yArr[i] = points[i]->y;
    }
    float a = cov(xArr, yArr, size)/var(xArr, size);
    float b = avg(yArr) - a * avg(xArr);
    return Line(a,b);
}


float dev(Point p,Point** points, int size) {
    Line l = linear_reg(points, size);
    float dist = abs(p.y - l.f(p.x));
    return dist;
}

float dev(Point p,Line l) {
    float dist = abs(p.y - l.f(p.x));
    return dist;
}
