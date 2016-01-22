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
   Updated By:  Morgan Redshaw
   Date:        Jan 8, 2015
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Point;


inline double cross(const Point &a, const Point &b) {
    return imag(conj(a)*b);
}

double area_triangle(Point a, Point b, Point c){
    double area;
    
    area = cross(b - a, c - a);

    return fabs(area) / 2;
}


int main()
{
  double ax, ay, bx, by, cx, cy;

  while (cin >> ax >> ay >> bx >> by >> cx >> cy)
  {
    Point a(ax, ay), b(bx, by), c(cx, cy);
    cout << "Area of triangle = " << area_triangle(a, b, c) << '\n';
  }
  
  return 0;
}