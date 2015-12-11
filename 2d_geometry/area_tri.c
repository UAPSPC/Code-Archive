/* 2D-Geometry: Area of a Triangle - 3 points
   =================================================================
   Description: Given three vertices a triangle, returns the area
                of the triangle.
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 7, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <math.h>

typedef struct{
  double x, y;
} Point;

double area_tri(Point a, Point b, Point c){
  double area;
  
  area = (b.x-a.x)*(c.y-a.y)-
         (b.y-a.y)*(c.x-a.x); 
  return (fabs(area))/2;
}

int main(){
  Point a, b, c;

  while(scanf("%lf %lf %lf %lf %lf %lf",
	      &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6){
    printf("Area of triangle = %f\n", area_tri(a,b,c));
  }
  return 0;
}
