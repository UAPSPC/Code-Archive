/* 2D-Geometry: Area of an Ellipse
   =================================================================
   Description: Given the quadratic form of an ellipse:
                   ax^2 + bxy + cy^2 = 1 
		returns the area of the ellipse
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 7, 2002
   References:  http://mathworld.wolfram.com/Ellipse.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <math.h>

double PI;

double area_gen_ellipse(double a, double b, double c){
  return 2*PI / (sqrt(4*a*c-b*b));
}

int main(){
  double a, b, c;
  
  PI = acos(-1);
  while(scanf("%lf %lf %lf", &a, &b, &c) == 3){
    printf("Area of Ellipse is %f.\n", area_gen_ellipse(a,b,c));
  }
  return 0;
}
