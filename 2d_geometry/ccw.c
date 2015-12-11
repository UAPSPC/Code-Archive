/* 2D Geometry: CCW Orientation analysis
   =================================================================
   Description: Given three points a, b, c, it returns whether the
                path from a to b to c is counterclockwise, clockwise
		or undefined.
		
		Undefined is returned if the 3 points are colinear,
		and c is between a and b.
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Howard Cheng, Scott Crosswhite, Gilbert Lee
   Date:        Nov 13, 2002
   References:  wilma.cs.brown.edu/courses/cs016/packet/node18.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Colinearity with respect to the line through a, b,
                and c:
		CCW      for c in [b, +inf)
		CNEITHER for c in [a,b)
		CW       for c in (-inf, a)

		For true CW/CCW/Collinear testing, consider using
		pt_leftright.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* how close to call equal */
#define EPS 1E-8
#define SQR(x) ((x)*(x))

typedef struct {
  double x, y;
} Point;

/* counterclockwise, clockwise, or undefined */
enum {CCW, CW, CNEITHER};

int ccw(Point a, Point b, Point c)
{
  double dx1 = b.x - a.x, dx2 = c.x - b.x;
  double dy1 = b.y - a.y, dy2 = c.y - b.y;
  double t1 = dx1 * dy2;
  double t2 = dx2 * dy1;

  if(fabs(t1 - t2) < EPS) {
    if(dx1 * dx2 < 0 || dy1 * dy2 < 0) {
      if(SQR(dx1)+SQR(dy1) >= SQR(dx2)+SQR(dy2)- EPS) return CNEITHER;
      return CW;
    }
    return CCW;
  }
  return t1 > t2 ? CCW : CW;
}

int main(void)
{
  Point a, b, c;
  int a1, a2, a3, a4, a5, a6;
  int res;

  while (scanf("%lf %lf %lf %lf %lf %lf", 
	       &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6){
    res = ccw(a,b,c);
    if (res == CW) {
      printf("CW\n");
    } else if (res == CCW) {
      printf("CCW\n");
    } else if (res == CNEITHER) {
      printf("CNEITHER\n");
    }
  }
  return 0;
}
