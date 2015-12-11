/* 2D-Geometry - Infinite Line Intersection
   =================================================================
   Description: Given two infinite lines specified by two points,
                determines whether they intersect at one point,
                infinitely many points, or no points.  In the first 
                case, the point of intersection is also returned.
                The points of a line must be different (otherwise,
                the line is not define).
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Howard Cheng
   Date:        Nov 01, 2003
   References:  www.exaflop.org/docs/cgafaq/cga1.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - returns 1 if intersect at a point
                - returns 0 if no intersection
                - returns -1 if lines coincide
*/
#include <stdio.h>
#include <math.h>

typedef struct{
  double x, y;
} Point;

#define EPS 1e-8

int isect_iline(Point a, Point b, Point c, Point d, Point *p){
  double r, denom, num1;

  num1  = (a.y - c.y) * (d.x - c.x) - (a.x - c.x) * (d.y - c.y);
  denom = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);

  if (fabs(denom) >= EPS) {
    r = num1 / denom;
    p->x = a.x + r*(b.x - a.x);
    p->y = a.y + r*(b.y - a.y);
    return 1;
  } 
  if (fabs(num1) >= EPS) return 0;
  return -1;
}

int main(){
  Point a, b, c, d, p; int res;

  while (scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
         &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y) == 8) {
    res = isect_iline(a, b, c, d, &p);
    if (res == 1) {
      printf("Intersect at (%0.2f, %0.2f)\n", p.x, p.y);
    } else if (res == 0) {
      printf("Don't intersect\n");
    } else {
      printf("Infinite number of intersections\n");
    }
  }
  return 0;
}
