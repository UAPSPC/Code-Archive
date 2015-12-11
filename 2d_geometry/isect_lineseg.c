/* 2D Geometry: Line Segment Intersection
   =================================================================
   Description: Given two line segments specified by endpoints,
                determine whether they intersect at one point, 
		infinitely many points, or no points.  In the first
		case, the point of intersection is also returned.

   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Howard Cheng
   Date:        Nov 1, 2003
   References:  www.exaflop.org/docs/cgafaq/cga1.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - The endpoints of a line must be different.
                - Returns 1 if segments intersect at a point, 
                          0 if line segments don't intersect
                         -1 if the lines coincide 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1E-8

typedef struct {
  double x, y;
} Point;


int intersect_line(Point a, Point b, Point c, Point d, Point *p){
  Point t; double r, s, denom, num1, num2;

  num1  = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2  = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);

  if (fabs(denom) >= EPS) {
    r = num1 / denom;
    s = num2 / denom;
    if (0-EPS <= r && r <= 1+EPS && 
        0-EPS <= s && s <= 1+EPS) {
      p->x = a.x + r*(b.x - a.x);
      p->y = a.y + r*(b.y - a.y);
      return 1;
    }
    return 0;
  }
  if (fabs(num1) >= EPS) return 0;
  if (a.x > b.x || (a.x == b.x && a.y > b.y)) { t = a; a = b; b = t; }
  if (c.x > d.x || (c.x == d.x && c.y > d.y)) { t = c; c = d; d = t; }
  if (a.x == b.x) {
    if (b.y == c.y) {
      *p = b; return 1; 
    } else if (a.y == d.y) {
      *p = a; return 1;
    } else if (b.y < c.y || d.y < a.y)
      return 0;
  } else {
    if (b.x == c.x) {
      *p = b; return 1;
    } else if (a.x == d.x) {
      *p = a; return 1;
    } else if (b.x < c.x || d.x < a.x) 
      return 0;
  }
  return -1;
}

int main(){
  Point a, b, c, d, p; int res;
  
  while (scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
       &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y) == 8) {
    res = intersect_line(a, b, c, d, &p);
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
