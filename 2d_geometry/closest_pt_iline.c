/* 2D-Geometry: Closest Point on Infinite Line
   =================================================================
   Description: Given a point C, and an infinite line represented by
                points A and B, returns the point P on the line 
		closest to C. (i.e. CP is orthogonal to AB)

   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        Nov 9, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Assumes that points A and B are not the same.
*/

#include <stdio.h>
#define SQR(x) ((x)*(x))

typedef struct{
  double x, y;
} Point;

Point closest_pt_iline(Point a, Point b, Point c) {
  Point p;
  double dp;

  b.x -= a.x;
  b.y -= a.y;
  dp = (b.x*(c.x-a.x) + b.y*(c.y-a.y)) / (SQR(b.x)+SQR(b.y));
  p.x = b.x*dp + a.x;
  p.y = b.y*dp + a.y;
  return p;
}  

int main() {
  Point a, b, c, p;

  while (scanf("%lf %lf %lf %lf %lf %lf",
	       &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6){
    p = closest_pt_iline(a,b,c);
    printf("%g %g\n", p.x, p.y);
  }
  return 0;
}
