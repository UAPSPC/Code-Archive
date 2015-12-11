/* 2D-Geometry: Angle between three points (180 degrees or PI rads)
   =================================================================
   Description: Given 3 points A, B, C, it returns the magnitude of
                angle ABC in radians.
   
	        Will only return the angle 0 <= theta <= PI.

   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Scott Crosswhite
   Date:        October 19, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Uses the Cosine Law, c^2 = a^2 + b^2 - 2ab cos C.
                Presumes that d(A,B) and d(B,C) are non-zero.
*/

#include <iostream>
#include <cstdio>
#include <cmath>

#define SQR(x) ((x)*(x))

typedef struct {
  double x, y;
} Point;

double dist_2d (Point a, Point b) {
  return sqrt(SQR(a.x-b.x)+SQR(a.y-b.y));
}

double angle2d180 (Point A, Point B, Point C) {
  double a = dist_2d(A,B), b = dist_2d(B,C), c = dist_2d(A,C);
  return acos((SQR(c)-SQR(a)-SQR(b)) / (-2*a*b));
}

int main () {
  Point a, b, c;
  printf("Enter A, B, C:\n");
  while (scanf("%lf %lf %lf %lf %lf %lf",
	       &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6) {
    printf("Angle ABC in radians = %f\n", angle2d180(a,b,c));
  }
  return 0;
}
