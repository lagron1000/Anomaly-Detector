/*
 * anomaly_detection_util.cpp
 *
 * Author: 
 * Or Spiegel 318720067
 * Lior Agron 208250225
 */

#include <math.h>
#include <cmath>
#include "anomaly_detection_util.h"

/**
 * Or's sum func: new array SUM precise function
 * @param x
 * @param size
 * @return
 */
float summer(float *x, int size) {
    float finalSum = 0;
    //sum loop
    for (int i = 0; i < size; i++) {
        finalSum +=  x[i];
    }
    return finalSum;
}

/**
 * avg = avg Or's func: new FLOAT average precise function
 * @param x
 * @param size
 * @return
 */
float avg(float *x, int size) {
    if (!size) return 0;
    //sum
    float summing = summer(x, size);
    //quo for the average
    return summing/(float)size;
}

/**
 * the Var function = calculating the variance of X and Y by subtracting the squares average
 * by the regular average squared.
 * @param x
 * @param size
 * @return the variance.
 * used: Or's avg avg func
 */
float var(float *x, int size) {
    if (!size) return 0;
    float quo = 0;
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (x[i])*(x[i]);
    }
    quo = sum/(float)size;
    float eSqrt = avg(x, size) * avg(x, size);
    return quo - eSqrt;
}


/**
 * returns the covariance of X and Y by subtracting the average of the x*y mult by the mult of of both averages:
 * 𝑐𝑜𝑣(𝑋,𝑌)=𝐸(𝑋𝑌)−𝐸(𝑋)𝐸(𝑌)=𝐸((𝑋−𝐸(𝑋))(𝑌−𝐸(𝑌))
 * @param x - first array
 * @param y - second array
 * @param size
 * @return the cov.
 */
float cov(float *x, float *y, int size) {
    float cov = 0;
    float Ex = avg(x, size);
    float Ey = avg(y, size);
    float xy[size];
    for (int i = 0; i < size; i++) {
        xy[i] = x[i] * y[i];
    }
    cov = avg(xy, size) - (Ex * Ey);
    return cov;
}

/**
 * Measures the linear correlation between points by dividing the point's covariance by the standard deviation in the x
 * values and in the y values.
 */
float pearson(float* x, float* y, int size) {
    float coVar = cov(x, y, size);
    float standardDeviation = std::sqrt(var(x, size)) * std::sqrt(var(y, size));
    return coVar / standardDeviation;
}


/**
 * Using linear regression to form a linear line from an array of points. we find the slope by dividing the
 * x,y covariance by the x variance and we find the lines intersection with the Y axis by subtracting the x'es
 * average times the slope from the y'es average.
 */
Line linear_reg(Point **points, int size) {
    float xArr[size];
    float yArr[size];
    for (int i = 0; i < size; i++)
    {
        xArr[i] = points[i]->x;
        yArr[i] = points[i]->y;
    }
    float a = cov(xArr, yArr, size)/var(xArr, size);
    float b = avg(yArr, size) - a * avg(xArr, size);
    return Line(a,b);
}

/**
 * the deviation
 * @param p
 * @param points
 * @param size
 * @return
 */
float dev(Point p,Point** points, int size) {
    Line l = linear_reg(points, size);

    float dist =p.y - l.f(p.x);
    if (dist<0) {
        dist = -1*dist;
    }

    return dist;
}
/**
 *
 * @param p
 * @param l
 * @return
 */
float dev(Point p,Line l) {
    float dist = std::abs(p.y - l.f(p.x));
    if (dist<0) {
        dist = -1*dist;
    }
    return dist;
}