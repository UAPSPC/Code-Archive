/* 3d geometry: Great Circle
   =================================================================
   Description: Given the latitude and longitude of two points in
                degrees, calculates the distance over the sphere
		between them. Latitude is given in the range
		[-90, 90] degrees, and Longitude is given in the 
		range [-180,180] degrees.
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Broderick Arneson
   Date:        October 4th, 2002. 
   References:  Page on the net
   -----------------------------------------------------------------
   Reliability: Spain 10316
   Notes:       - Set radius to what you need.

*/

#include <stdio.h>
#include <math.h>

double pi;

double greatcircle (double lat1, double long1, 
		    double lat2, double long2) {

  double radius = 1.0; 

  double a = pi*(lat1/180.0);
  double b = pi*(lat2/180.0);
  double c = pi*((long2-long1)/180.0);
  return radius*acos(sin(a)*sin(b) + cos(a)*cos(b)*cos(c));
}

int main () {
  double lat1, lat2, long1, long2;
  
  pi = acos(-1);
  while (scanf("%lf %lf %lf %lf ",&lat1,&long1,&lat2,&long2)==4) {
    d = greatcircle(lat1, long1, lat2, long2);
    printf("Great Circle Distance = %.5lf\n", d);
  }
  return 0;
}
