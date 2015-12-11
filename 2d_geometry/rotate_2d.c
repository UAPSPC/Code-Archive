/* 2D-Geometry: Rotation of a point around a point
   =================================================================
   Description: Rotates a point P around an origin point O, and 
                returns the new point.  The parameter theta is the
		amount to rotate P counter-clockwise, and is 
		measured in radians.
   
   Complexity:  O(1) (trig functions)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 8, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 2 (Spain 10406, 10250)
   Notes:       The routine has a built in fixer for -0.00
*/

#include <stdio.h>
#include <math.h>

#define EPS 1e-8

typedef struct{
  double x, y;
} Point;

Point rotate_2d(Point p, Point o, double theta){
  double m[2][2];
  Point r;
  
  m[0][0] = m[1][1] = cos(theta);
  m[0][1] = -sin(theta);
  m[1][0] = -m[0][1];
  p.x -= o.x; 
  p.y -= o.y;
  r.x = m[0][0] * p.x + m[0][1] * p.y + o.x;
  r.y = m[1][0] * p.x + m[1][1] * p.y + o.y;
  if(fabs(r.x) < EPS) r.x = 0;
  if(fabs(r.y) < EPS) r.y = 0;
  return r;
}

int main(){
  Point p,o,r;
  double deg, PI = acos(-1);
  
  while(scanf("%lf %lf %lf %lf %lf", 
	      &p.x, &p.y, &o.x, &o.y, &deg) == 5){
    deg *= PI/180.0;
    r = rotate_2d(p,o,deg);
    printf("[%.3f,%.3f] rotated %.3f radians around [%.3f,%.3f] = [%.3f,%.3f]\n",
	   p.x, p.y, deg, o.x, o.y, r.x, r.y);
  }
  return 0;
}
