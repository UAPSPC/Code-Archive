/* 2D-Geometry: Reflect a point across a line
   =================================================================
   Description: Given a line defined by two points A and B, and 
                another point c, returns the reflection of point C
		across the line.
		
		Assumes that the A and B are different
		
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        Nov 9, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
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

Point reflect(Point a, Point b, Point c) {
  Point d, p;
  
  d = closest_pt_iline(a,b,c);
  p.x = 2.0*d.x - c.x;
  p.y = 2.0*d.y - c.y;
  return p;
}

int main() {
  Point a, b, c, d;
  while (scanf("%lf %lf %lf %lf %lf %lf",
	       &a.x, &a.y, &b.x, &b.y, &c.x, &c.y)==6) {
    d = reflect(a,b,c);
    printf("%g %g\n", d.x, d.y);
  }
  return 0;
}
