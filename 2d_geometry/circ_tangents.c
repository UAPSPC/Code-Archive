/*  2D Geometry:  Circle tangents
   =================================================================
   Description: Given a circle (defined by a center point and radius) 
                and a point strictly outside the circle, returns the 
                two points of tangency.
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        Nov 19, 2002
   References:
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Assumes a non-zero distance between p and c.
*/

#include <stdio.h>
#include <math.h>
#define SQR(x) ((x)*(x))

typedef struct {
  double x, y;
} Point;

double dist2(Point a, Point b) {
  return SQR(a.x-b.x) + SQR(a.y-b.y);
}

Point a, b;

void circ_tangents(Point c, double r, Point p) {
  double perp, para, tmp = dist2(p,c);

  para = r*r/tmp;
  perp = r*sqrt(tmp-r*r)/tmp;
  
  a.x = c.x + (p.x-c.x)*para - (p.y-c.y)*perp;
  a.y = c.y + (p.y-c.y)*para + (p.x-c.x)*perp;
  b.x = c.x + (p.x-c.x)*para + (p.y-c.y)*perp;
  b.y = c.y + (p.y-c.y)*para - (p.x-c.x)*perp;
}

int main() {
  Point c, p;
  double rad;

  while (scanf("%lf %lf %lf", &c.x, &c.y, &rad)==3) {
    scanf("%lf %lf",&p.x,&p.y);
    circ_tangents(c, rad, p);
    printf("%g,%g %g,%g\n",a.x,a.y,b.x,b.y);
  }
  return 0;
}
