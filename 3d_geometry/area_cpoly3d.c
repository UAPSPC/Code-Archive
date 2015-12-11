/* 3D-Geometry: Area of a convex polygon in a plane given in 3D
   =================================================================
   Description: Given the points of a planar convex polygon in 3D
                space, returns its area.  

		The points of the polygon must be either in cw or
		ccw order.  
   
   Complexity:  O(N) where N is the number of points
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 06, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 - Topcoder Round 2 2003
   Notes:       - Uses Heron's formula v1.  Change to v2 if needed
                - There must be at least 3 points
		- Doesn't work for non-convex polygons
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SQR(x) ((x)*(x))

typedef struct{
  double x, y, z;
} Point;

double area_heron(double a, double b, double c){
  double s = (a+b+c)/2.0;
  if(a > s || b > s || c > s) return -1;
  return sqrt(s*(s-a)*(s-b)*(s-c));
}

double dist3d(Point a, Point b){
  return sqrt(SQR(a.x-b.x)+SQR(a.y-b.y)+SQR(a.z-b.z));
}

double area_poly3d(Point *p, int n){
  int i; double total = 0; 
  for(i = 2; i < n; i++)
    total += area_heron(dist3d(p[0], p[i]), 
			dist3d(p[0], p[i-1]),
			dist3d(p[i], p[i-1]));
  return total;
}

int main(){
  int i, n; Point *p;

  while(scanf("%d", &n) == 1 && n >= 3){
    p = (Point *)malloc(n*sizeof(Point));
    for(i = 0; i < n; i++)
      scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
    printf("Area of convex polygon is %.3f\n", area_poly3d(p, n));
    free(p);
  }
  return 0;
}
