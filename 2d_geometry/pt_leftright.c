/* 2D_Geometry: Point Left/Right/In Line test
   ===================================================================
   Description: 
     Given a directed line segment and a point, this code returns
     whether the point is to the left of, to the right of, or colinear
     with the line segment.
   
   Complexity:  O(1)
   -------------------------------------------------------------------
   Author:      Jason Klaus
   Date:        Nov 8, 2002
 
   References:  Based on Cross products, pg.936,
                   Introduction to Algorithms (2nd Edition),
                   Cormen, Leiserson, Rivest, Stein 
   -------------------------------------------------------------------
   Reliability: 0 successes.

   Notes:
     - The line segment runs from Point a to Point b
     - If Point a == Point b, then any Point p will be considered
       colinear.
     - The point to be compared is Point p.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPSILON 1E-10

typedef struct {
  double x, y;
} Point;

enum {LEFT, RIGHT, CL};

int pt_leftright(Point a, Point b, Point p)
{
  double res;

  res = (p.x - a.x)*(b.y - a.y) -
        (p.y - a.y)*(b.x - a.x);
  
  if (fabs(res) < EPSILON)
    return CL;
  else if (res > 0.0)
    return RIGHT;
  return LEFT;
}

int main(void)
{
  Point a, b, p;
  int res;

  while (scanf("%lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y,
               &p.x, &p.y) == 6) {
    res = pt_leftright(a, b, p);

    printf("(%.2lf, %.2lf) is ", p.x, p.y);

    switch (res) {
    case LEFT:
      printf("Left of");
      break;
    case RIGHT:
      printf("Right of");
      break;
    default:
      printf("Co-Linear with");
      break;
    }
    
    printf(" the line segment (%.2lf, %.2lf) -> (%.2lf, %.2lf)\n",
           a.x, a.y, b.x, b.y);
  }
  return 0;
}
