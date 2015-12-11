/* 2D-Geometry: Parameter of circle from 3 points
   =================================================================
   Description: This routine computes the parameters of a circle
                (center and radius) from 3 points.
		Returns non-zero if successful, zero if the three
		points are collinear
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Howard Cheng
   Date:        Nov 13, 2002
   References:  www.exaflop.org/docs/cgafaq/
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* how close to call equal */
#define EPS 1E-8

typedef struct {
  double x, y;
} Point;

int circle(Point p1, Point p2, Point p3, Point *center, double *r)
{
  double a,b,c,d,e,f,g;

  a = p2.x - p1.x;  b = p2.y - p1.y;
  c = p3.x - p1.x;  d = p3.y - p1.y;
  e = a*(p1.x + p2.x) + b*(p1.y + p2.y);
  f = c*(p1.x + p3.x) + d*(p1.y + p3.y);
  g = 2.0*(a*(p3.y - p2.y) - b*(p3.x - p2.x));
  if (fabs(g) < EPS) return 0;
  center->x = (d*e - b*f) / g;
  center->y = (a*f - c*e) / g;
  *r = sqrt((p1.x-center->x)*(p1.x-center->x) +
	    (p1.y-center->y)*(p1.y-center->y));
  return 1;
}

int main(void)
{
  Point a, b, c, center;
  double r;
  
  while (scanf("%lf %lf %lf %lf %lf %lf", 
	       &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6) {
    if (circle(a, b, c, &center, &r)) {
      printf("center = (%5.3f, %5.3f)\n", center.x, center.y);
      printf("radius = %5.3f\n", r);
      printf("\n");
    } else {
      printf("colinear\n\n");
    }
  }
  return 0;
}
