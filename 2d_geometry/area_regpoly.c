/* 2D Geometry: Area of a regular polygon
   =================================================================
   Description: Returns the area of a regular n-gon with side 
                length s.
   
   Complexity:  O(1) 
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 7, 2002
   References:  http://mathworld.wolfram.com/Area.html
   -----------------------------------------------------------------
   Reliability: 0 (Sept 2002)
   Notes:       
*/

#include <stdio.h>
#include <math.h>

double PI;

double area_regpoly(int n, double s){
  return n < 3 ? 0 : n*s*s/tan(PI/n)/4;
}

int main(){
  int n;
  double s;
  
  PI = acos(-1);
  while(scanf("%d %lf", &n, &s) == 2)
    printf("Regular %d-gon has area: %f\n", n, area_regpoly(n,s));
  return 0;
}

   
