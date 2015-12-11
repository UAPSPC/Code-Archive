/* 2D Geometry: Centroid of a Polygon
   =================================================================
   Description: Given a polygon as a set of N points, this code finds 
                the centroid of the polygon.
   
   Complexity:  O(N)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        Nov 8, 2003 
   References:  http://www.netcomuk.co.uk/~jenolive/centroid.html
                www.exaflop.org/docs/cgafaq/cga2.html
                see also area_poly.c
   -----------------------------------------------------------------
   Reliability: 2 (Spain 10002)
                (Center of Mass Nov 2003)
   Notes:       Points must be in clockwise or counterclockwise order.
                The area of the polygon must be non-zero.
                The polygon must not be self-intersecting (simple)
        	The polygon may or may not be convex.
*/

#include <stdio.h>
#include <math.h>

typedef struct {
  double x, y;
} Point;

Point centroid(Point *p, int n) {
  double area, sum;
  Point c;
  int i, j;

  c.x = c.y = sum = 0.0;  
  for(i = n-1, j = 0; j < n; i = j++) {
    sum += area = p[i].x * p[j].y - p[i].y * p[j].x;
    c.x += (p[i].x + p[j].x)*area;
    c.y += (p[i].y + p[j].y)*area;
  }
  sum *= 3.0;
  c.x /= sum;
  c.y /= sum;
  return c;
}

int main() {
  Point poly[100], c;
  int i, n;

  while (scanf("%d",&n)==1) {
    if (n < 3) break;
    for (i = 0; i < n; i++)
      scanf("%lf %lf",&poly[i].x, &poly[i].y);
    c = centroid(poly,n);
    printf("%0.3f %0.3f\n",c.x,c.y);
  }
  return 0;
}
