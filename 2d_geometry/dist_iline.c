/* 2D-Geometry: Distance from a point to an infinte line
   =================================================================
   Description: Calculates the minimum(orthogonal) distance from a
                point P to an infinite line.  The line is defined
		by two points A and B.

   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Howard Cheng, Gilbert Lee
   Date:        Sept 8, 2002
   References:  http://www.exaflop.org/docs/cgafaq/cga1.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Assumes that point A != point B, otherwise the line
                would not be properly defined -> returns dist=nan
*/

#include <stdio.h>
#include <math.h>

typedef struct{
  double x,y;
} Point;

#define SQR(x) ((x)*(x))

double dist_2d(Point a, Point b){
  return sqrt(SQR(a.x-b.x)+SQR(a.y-b.y));
}

double dist_iline(Point a, Point b, Point p){
  return fabs(((a.y-p.y)*(b.x-a.x)-
	       (a.x-p.x)*(b.y-a.y))
	      /dist_2d(a,b));
}

int main(){
  Point a, b, p;
  
  while(scanf("%lf %lf %lf %lf %lf %lf", 
	      &a.x, &a.y, &b.x, &b.y, &p.x, &p.y) == 6){
    printf("Distance = %f\n", dist_iline(a,b,p));
  }
  return 0;
}
