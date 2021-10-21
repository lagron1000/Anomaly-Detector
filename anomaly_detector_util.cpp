#include "anomaly_detection_util.h"

// // returns the variance of X and Y

// float var(float *x, int size);

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
Line::Line(float aa, float bb) {
    a = aa;
    b = bb;
}

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

// // returns the Pearson correlation coefficient of X and Y
// float pearson(float *x, float *y, int size);
// class Point
// {
// public:
//     float x, y;
//     Point(float x, float y) : x(x), y(x) {}
// };
// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size) {

}
// // returns the deviation between point p and the line equation of the points
// float dev(Point p, Point **points, int size);
// // returns the deviation between point p and the line
// float dev(Point p, Line l);