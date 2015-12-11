/* 2D Geometry: Point in Polygon Test
   =================================================================
   Description: Determines if a point is strictly inside, outside,
		or on the boundary of a simple polygon.

   Complexity:	O(N)
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	March 12, 2003
   References:  This is more or less taken from Randolph Franklin's
		http://www.ecse.rpi.edu/Homepages/wrf/geom/pnpoly.html
   -----------------------------------------------------------------
   Reliability: 1 (Spain 634)
   Notes: 	If your points are guaranteed not to be on the
		boundary, remove that check.  You could also return
		a third value, neither 0 nor 1, for boundary cases.
*/

#include <stdio.h>
#include <math.h>
#define BOUNDARY 1
#define EPS 1E-8
#define SQR(x) ((x)*(x))

typedef struct {
  double x, y;
} Point;

double dist2d(Point a, Point b) {
  return sqrt(SQR(a.x-b.x) + SQR(a.y-b.y));
}

int pt_in_poly(Point *p, int n, Point a) {
  int i, j, c = 0;

  for (i = 0, j = n-1; i < n; j = i++) {
    if (dist2d(p[i],a)+dist2d(p[j],a)-dist2d(p[i],p[j]) < EPS)
      return BOUNDARY;
    if ((((p[i].y<=a.y) && (a.y<p[j].y)) ||
         ((p[j].y<=a.y) && (a.y<p[i].y))) &&
        (a.x < (p[j].x-p[i].x) * (a.y - p[i].y) 
               / (p[j].y-p[i].y) + p[i].x)) c = !c;
  }
  return c;
}

int main() {
  Point poly[1000], trial;
  int i, n, m;

  while (scanf("%d %d", &n, &m)==2 && n) {
    for (i = 0; i < n; i++)
      scanf("%lf %lf", &poly[i].x, &poly[i].y);
    for (i = 0; i < m; i++) {
      scanf("%lf %lf", &trial.x, &trial.y);
      printf("%s\n", pt_in_poly(poly,n,trial) ? "IN" : "OUT");
    }
  }
  return 0;
}
