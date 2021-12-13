/*
 * minCircle.h
 *
 * Author:
 * Or Spiegel 318720067
 * Lior Agron 208250225
 */
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_
#include "minCircle.h"


#include <algorithm>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
    Circle():center(Point(0,0)),radius(0){};
};
// --------------------------------------


/****************************************************************************************
 * Distance between 2 points, implemented by abs value
 * @param  p1 = 1st point
 *          p2 = 2nd point
 ****************************************************************************************/
float distBetween(Point p1, Point p2);
/****************************************************************************************
 * If the circle contains the point inside - return 1, else - 0.
 * @param c - Circle to check.
 * @param p - the point we are checking.
 * @return - 1 if the point inside the circle, else - 0.
****************************************************************************************/
bool isPointInCircle(Circle c, Point p);
/****************************************************************************************
 * Check if the given points are valid (Valid means - inside the circle.
 * @param c - A circle to check.
 * @param pointsVec - given points vector.
 * @return - 1 if all the vector content in the circle, otherwise - 0.
****************************************************************************************/
bool isValidCircle(Circle c, vector<Point> pointsVec);
/****************************************************************************************
 * Get circle from 2 points
 * @param p1 = 1st point
 * @param p2 = 2nd point
 * @return the smallest circle that contains 2 given points
 ****************************************************************************************/
Circle circleFrom2Points(Point p1, Point p2);
/****************************************************************************************
 * Get circle from 3 points helper function - find the center
 * @param  p1 = 1st point
 * @param  p2 = 2nd point
 * @param  p3 = 3rd point
 * @param  p4 = 4th point
 ****************************************************************************************/
Point get_circle_center(double bx, double by, double cx, double cy) ;
/****************************************************************************************
 * Get circle from 3 points
 * @param p1 = 1st point
 * @param p2 = 2nd point
 * @param p3 = 3rd point
 * @return the smallest circle that contains 3 given points
 ****************************************************************************************/
Circle circleFrom3Points(Point a, Point b, Point c);
/****************************************************************************************
 * For the recursion stop condition: if the size of the vector is <= 3.
 * @param points - given vector.
 * @return - a trivial circle.
 ****************************************************************************************/
Circle baseCase(vector<Point> points);
/****************************************************************************************
 * Using Welzl's recursive algorithm.
 * @param points - An array of pointers to points.
 * @param R - The points that are in the circle.
 * @param size - The size of the array.
 * @return - The minimum circle containing all points.
 ****************************************************************************************/
Circle welzl_algo(Point** points, vector<Point> R, int size);
/****************************************************************************************
 * @param points - An array of pointers to points. (vector)
 * @param size - Array length.
 * @return - The minimum enclosed circle, with the points from the vector.
 ****************************************************************************************/
Circle findMinCircle(Point** points,size_t size);

#endif /* MINCIRCLE_H_ */
