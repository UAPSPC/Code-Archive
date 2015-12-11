/* 2D-Geometry: Angle between three points
   =================================================================
   Description: Given 3 points A, B, C, it returns the magnitude of
                angle ABC in radians.

		Will only return the angle 0 <= theta <= PI/2.   

   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Nov 14, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Uses vectors to calculate the angle:
                a . b = |a| * |b| * cos(theta) -->
		theta = acos(a . b / (|a| * |b|))
*/

#include <stdio.h>
#include <math.h>

#define SQR(x) ((x)*(x))

typedef struct {
  double x, y;
} Point;

double angle2d(Point a, Point b, Point c){
  double dx1 = a.x - b.x, dy1 = a.y - b.y;
  double dx2 = c.x - b.x, dy2 = c.y - b.y;
  double dot = dx1 * dx2 + dy1 * dy2;
  double l1 = sqrt(SQR(dx1)+SQR(dy1));
  double l2 = sqrt(SQR(dx2)+SQR(dy2));

  return acos(dot / (l1*l2));
}

int main(){
  Point a, b, c;
  printf("Enter A, B and C:\n"); 
  while(scanf("%lf %lf %lf %lf %lf %lf",
	      &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6){
    printf("Angle ABC in radians = %f\n", angle2d(a, b, c));
  }
  return 0;
} 
  


  
