/* 2D_Geometry: Soddy Circle Radius
   =================================================================
   Description: Given three tangent circles, this finds the radius
                of the circle that is tangent to the other three.
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Feb 23, 2003
   References:  http://mathworld.wolfram.com/FourCoinsProblem.html
                http://mathworld.wolfram.com/SoddyCircles.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <math.h>

double soddy_rad(double r1, double r2, double r3){
  return (r1*r2*r3)/(r2*r3+r1*(r2+r3)+2*sqrt(r1*r2*r3*(r1+r2+r3)));
}


int main(){
  double r1, r2, r3;
  while(scanf("%lf %lf %lf", &r1, &r2, &r3) == 3){
    printf("Soddy circle radius = %f\n", soddy_rad(r1, r2, r3));
  }
  return 0;
}
