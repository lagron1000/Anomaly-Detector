/*
 * minCircle.cpp
 *
 * Author:
 * Or Spiegel 318720067
 * Lior Agron 208250225
 */

#include "minCircle.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
/****************************************************************************************
 * Distance between 2 points, implemented by abs value
 * @param  p1 = 1st point
 *          p2 = 2nd point
 ****************************************************************************************/
float distBetween(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/****************************************************************************************
 * If the circle contains the point inside - return 1, else - 0.
 * @param c - Circle to check.
 * @param p - the point we are checking.
 * @return - 1 if the point inside the circle, else - 0.
****************************************************************************************/
bool isPointInCircle(Circle c, Point p) {
    return distBetween(c.center, p) <= c.radius;
}

/****************************************************************************************
 * Check if the given points are valid (Valid means - inside the circle.
 * @param c - A circle to check.
 * @param pointsVec - given points vector.
 * @return - 1 if all the vector content in the circle, otherwise - 0.
****************************************************************************************/
bool isValidCircle(Circle c, vector<Point> pointsVec) {
    for (auto currPoint: pointsVec) { // iterating the given vector
        if (isPointInCircle(c, currPoint) == 0) {
            return false;
        }
    }
    return true;
}

/****************************************************************************************
 * Get circle from 2 points
 * @param p1 = 1st point
 * @param p2 = 2nd point
 * @return the smallest circle that contains 2 given points
 ****************************************************************************************/
Circle circleFrom2Points(Point p1, Point p2) {
    float r = distBetween(p1,p2) / 2.0; // radius for the new circle!
    float centerDX = (p1.x + p2.x) / 2.0; // new circle center x value
    float centerDY = (p1.y + p2.y) / 2.0; // new circle center y value
    Point newCenter = {centerDX, centerDY}; // new point for the circle center
    return {newCenter, r}; // return new circle using the new center and radius.
}

/****************************************************************************************
 * Get circle from 3 points helper function - find the center
 * @param  p1 = 1st point
 * @param  p2 = 2nd point
 * @param  p3 = 3rd point
 * @param  p4 = 4th point
 ****************************************************************************************/
Point get_circle_center(float bx, float by, float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return { (cy * B - by * C) / (2 * D),
             (bx * C - cx * B) / (2 * D) };
}

/****************************************************************************************
 * Get circle from 3 points
 * @param p1 = 1st point
 * @param p2 = 2nd point
 * @param p3 = 3rd point
 * @return the smallest circle that contains 3 given points
 ****************************************************************************************/
Circle circleFrom3Points(Point p1, Point p2, Point p3) {
    Point center = get_circle_center(p2.x - p1.x, p2.y - p1.y, p3.x - p1.x, p3.y - p1.y);
    center.x = center.x + p1.x;
    center.y = center.y + p1.y;
    float radius = distBetween(center, p1);
    return {center, radius}; // the new circle
}

/****************************************************************************************
 * For the recursion stop condition: if the size of the vector is <= 3.
 * @param points - given vector.
 * @return - a trivial circle.
 ****************************************************************************************/
Circle baseCase(vector<Point> points) {
    if (points.size() == 0) {
        Circle tmp = {{0, 0}, 0};
        return tmp;
    }
    else if (points.size() == 1) {
        return {points[0], 0};
    }
    else if(points.size() == 2) {
        return circleFrom2Points(points[0], points[1]);
    }

    // check if we can enclose MEC from 2 points
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle tempCircle = circleFrom2Points(points[i], points[j]);
            if (isValidCircle(tempCircle, points)) {
                return tempCircle; // return a circle from the points.
            }
        }
    }
    return circleFrom3Points(points[0], points[1], points[2]);
}



/****************************************************************************************
 * Using Welzl's recursive algorithm.
 * @param points - An array of pointers to points.
 * @param R - The points that are in the circle.
 * @param size - The size of the array.
 * @return - The minimum circle containing all points.
 ****************************************************************************************/
Circle welzl_algo(Point** points, vector<Point> R, int size) {
    if (size == 0 || R.size() == 3) {
        return baseCase(R);
    }
    Point p = *points[size - 1];
    Circle temp = welzl_algo(points, R, size - 1);
    if (isPointInCircle(temp, p)) {
        return temp;
    }

    R.push_back(p);
    return welzl_algo(points, R, size - 1);
}

/****************************************************************************************
 * @param points - An array of pointers to points. (vector)
 * @param size - Array length.
 * @return - The minimum enclosed circle, with the points from the vector.
 ****************************************************************************************/
Circle findMinCircle(Point** points,size_t size){
    vector<Point> temp;
    return welzl_algo(points, temp, size);
}