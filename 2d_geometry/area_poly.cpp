/* 2D-Geometry: Area of a polygon
   =================================================================
   Description: Given a polygon represented as an array of N points,
                returns the signed area.  The result is positive if
		the orientation is counterclockwise, and negative
		otherwise.
   Complexity:  O(N) N being the number of vertices of the polygon
   -----------------------------------------------------------------
   Author:      Howard Cheng, Gilbert Lee
   Date:        Sept 2002
   References:  www.exaflop.org/docs/cgafaq/cga2.html
   -----------------------------------------------------------------
   Editor:      Morgan Redshaw
   Date:        January 2016
   
   Changes: Changed to use c++
            Used complex<double> for point rather than specialized struct
   -----------------------------------------------------------------
   Reliability: 0 (Sept 2002)
   Notes:       Remember to run fabs() on the result if a positive
                area is desired.
*/

#include <complex>
#include <iostream>
#include <vector>

using namespace std;

typedef complex<double> Point;

double cross(const Point &a, const Point &b) {
    return imag(conj(a)*b);
}

double area_poly(const vector<Point> &p){
    double sum = 0;

    for(int i = poly.size()-1, j = 0; j < poly.size(); i = j++)
        sum += cross(p[i], p[j]);

    return sum/2.0;
}

int main(){
    vector<Point> poly;
    int i, n;

    while(cin >> n, n > 0)
    {
        poly.resize(n);
        
        for(i = 0; i < n; i++)
        {
            double x, y;
            cin >> x >> y;
            poly[i] = Point(x, y);
        }
        printf("Signed Area = %f\n", area_poly(poly));
    }
    return 0;
}
