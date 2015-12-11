/* 2D-Geometry: Distance between two points in 2D
   =================================================================
   Description: Computes the distance between two points
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 8, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <math.h>

#define SQR(x) ((x)*(x))

typedef struct{
  double x, y;
} Point;

double dist_2d(Point a, Point b){
  return sqrt(SQR(a.x-b.x)+SQR(a.y-b.y));
}

int main(){
  Point a, b;

  while(scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y) == 4){
    printf("Distance = %f\n", dist_2d(a,b));
  }
  return 0;
}
