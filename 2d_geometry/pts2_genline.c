/* 2D-Geometry: Generalized Equation of a line given two points
   =================================================================
   Description: Given two points, computes the unique values 
                A, B and C for the line going through A and B such
		that   Ax + By = C
		and    A >= 0
		and    A^2 + B^2 = 1
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 7, 2003
   References:  www.uwm.edu/~ericskey/TANOTES/Ageometry/node4.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - The good thing about a generalized equation is 
                  that unlike the slope/offset version, it is
		  always defined 
		- Two lines are parallel iff both their A's are the
		  same, and their B's are the same.
*/

#include <stdio.h>
#include <math.h>

#define SQR(x) ((x)*(x))

typedef struct{
  double x, y;
} Point;

typedef struct{
  double a, b, c;
} Line;

Line pt2line(Point a, Point b){
  double dx = a.x-b.x, dy = a.y-b.y;
  double len = sqrt(SQR(dx)+SQR(dy));
  Line res;

  if(dy < 0){
    dy *= -1; 
    dx *= -1;
  }
  res.a = dy/len;
  res.b = -dx/len;
  res.c = res.a*a.x + res.b*a.y;
  return res;
}

int main(){
  Point a, b;
  Line line;
  while(scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y) == 4){
    line = pt2line(a,b);
    printf("Equation of line going through (%.3f,%.3f)->(%.3f,%.3f):\n",
	   a.x, a.y, b.x, b.y);
    printf("(%.3f) X + (%.3f) Y = %.3f\n",
	   line.a, line.b, line.c);
  }
  return 0;
}
