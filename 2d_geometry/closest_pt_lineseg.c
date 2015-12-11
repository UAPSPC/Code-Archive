/* 2D-Geometry: Closest Point on a Line Segment
   =================================================================
   Description: Given the end points of a line segment, A and B, and
                another point C, returns the point on the segment 
		closest to C.
		If a line perpendicular to A,B intersects A, B then
		intersection will be returned.  Otherwise the closer 
		endpoint will be returned.
		If the segment has a length of zero, an endpoint 
		will be returned.
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        Nov 9, 2002
   References:  0
   -----------------------------------------------------------------
   Reliability: 1 (Spain 10263 - Railway)
   Notes:       
*/

#include <stdio.h>
#include <math.h>
#define EPS 1E-8
#define SQR(x) ((x)*(x))

typedef struct {
  double x, y;
} Point;

Point closest_pt_lineseg(Point a, Point b, Point c) {
  Point p;
  double dp;

  b.x -= a.x;
  b.y -= a.y;
  if (fabs(b.x) < EPS && fabs(b.y) < EPS) return a;
  dp = (b.x*(c.x-a.x) + b.y*(c.y-a.y))/(SQR(b.x)+SQR(b.y));
  if (dp > 1) dp = 1;
  if (dp < 0) dp = 0;
  p.x = b.x*dp + a.x;
  p.y = b.y*dp + a.y;
  return p;
}

int main() {
  Point a, b, c, d;

  while (scanf("%lf %lf %lf %lf %lf %lf",
	       &a.x, &a.y, &b.x, &b.y, &c.x, &c.y)==6) {
    d = closest_pt_lineseg(a,b,c);
    printf("%g %g\n", d.x, d.y);
  }
  return 0;
}
