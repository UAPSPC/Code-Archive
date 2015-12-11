/* 2D-Geometry: Area of triangle - Heron's formula
   =================================================================
   Description: Given the three lengths of a triangle, returns
                the area of the triangle.
                Returns -1 if triangle does not exist
   Complexity:  O(1) (square root)
   -----------------------------------------------------------------
   Author:      Gilbert Lee, Ashley Zinyk
   Date:        Sept 7, 2002
   References:  http://mathworld.wolfram.com/Area.html
   -----------------------------------------------------------------
   Reliability: 1 (Sept 2002)
   Notes: If you deal with needle-shaped triangles, you might have
          problems with numerical inaccuracy.  In that case, try
          area_heron2, which is more stable but hard to type in.
*/

#include <stdio.h>
#include <math.h>

/*
double area_heron2(double a, double b, double c) {
  double t;

  if (a < b) { t=a; a=b; b=t; }
  if (a < c) { t=a; a=c; c=t; }
  if (b < c) { t=b; b=c; c=t; }

  if ((c-(a-b)) < 0.0) return -1;
  return sqrt((a+(b+c))*(c-(a-b))*(c+(a-b))*(a+(b-c)))/4.0;
} */

double area_heron(double a, double b, double c){
  double s = (a+b+c)/2.0;
  if(a > s || b > s || c > s) return -1;
  return sqrt(s*(s-a)*(s-b)*(s-c));
}

int main(){
  double a, b, c;
  
  while(scanf("%lf %lf %lf", &a, &b, &c) == 3){
    printf("Area of triangle = %f\n", area_heron(a,b,c));
  }
  return 0;
}
