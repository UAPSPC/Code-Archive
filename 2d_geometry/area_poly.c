/* 2D-Geometry: Area of a polygon
   =================================================================
   Description: Given a polygon represented as an array of N points,
                returns the signed area.  The result is positive if
		the orientation is counterclockwise, and negative
		otherwise.
   Complexity:  O(N) N being the number of vertices of the polygon
   -----------------------------------------------------------------
   Author:      Howard Cheng, Gilbert Lee
   Date:        Sept 2002
   References:  www.exaflop.org/docs/cgafaq/cga2.html
   -----------------------------------------------------------------
   Reliability: 0 (Sept 2002)
   Notes:       Remember to run fabs() on the result if a positive
                area is desired.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double x, y;
} Point;

double area_poly(Point *p, int n){
  double sum = 0;
  int i, j;
  
  for(i = n-1, j = 0; j < n; i = j++)
    sum += p[i].x * p[j].y -
           p[i].y * p[j].x;
  return sum/2.0;
}

int main(){
  Point *poly;
  int i, n;
  
  while(scanf("%d", &n) == 1 && n > 0){
    poly = (Point *) malloc(n * sizeof(Point));
    for(i = 0; i < n; i++) scanf("%lf %lf", &poly[i].x, &poly[i].y);
    printf("Signed Area = %f\n", area_poly(poly, n));
    free(poly);
  }
  return 0;
}
