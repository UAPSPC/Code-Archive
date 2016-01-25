/* Computational Geometry: Convex Hull (minimizing version)
   =================================================================
   Description: 
     Given a list of n (n >= 1) points in an array, this routine
     returns the vertices of the convex hull in counterclockwise
     order.  It also returns the number of vertices in the convex
     hull.

     The convex hull is the smallest convex polygon that encompasses
     or borders all of the points.
   
   Complexity:  O(n lg n)  ->  O(qsort) + O(n)
   -----------------------------------------------------------------
   Author:      Jason Klaus
   Date:        Oct 25, 2002
 
   References:  Based on Graham's Scan, pg.949-955,
                   Introduction to Algorithms (2nd Edition),
                   Cormen, Leiserson, Rivest, Stein 
   -----------------------------------------------------------------
   Editor:      Morgan Redshaw
   Date:        January 2016
   
   Changes: Improved name for cross_prod_dir
            Changed to be C++ rather than C
            Used complex<double> for point rather than specialized struct
   -----------------------------------------------------------------
   Reliability: 2 Spain successes with older version.
                2 successes with current version, on UVA 681 and UVA 10065

   Notes:
   - The hull contains a minimum number of points; all co-linear
     points and non-distinct points are eliminated from the hull.
     The reference algorithm does not do this, and also has a
     restriction that the points must be distinct and not duplicate
     polar angles with respects to the reference.  These restrictions
     have been removed from this implementation.
   - The points in the original polygon will be re-ordered.
   - Point.real() is x, Point.imag() is y
*/

#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using namespace std;

const double Epsilon = 1E-10;

typedef complex<double> Point;

bool operator<(const Point & p1, const Point &p2)
{
    return p1.imag() < p2.imag() || 
            (fabs(p1.imag() - p2.imag()) < Epsilon && p1.real() < p2.real());
}

double cross(const Point &a, const Point &b) {
    return imag(conj(a)*b);
}


Point P0;

enum Direction {CCW, CW, CL};

Direction cross_prod_dir(const Point &p1, const Point &p2, const Point &p0)
{
    double res = cross(p1 - p0, p2 - p0);

    if (fabs(res) < Epsilon)
        return CL;
    else if (res > 0.0)
        return CW;
    else
        return CCW;
}


bool polar_cmp(Point p1, Point p2)
{
    Direction res = cross_prod_dir(p1, p2, P0);

    if (res == CW)
        return true;
    else if (res == CCW)
        return false;
    else {
        double d = norm(p1 - P0) - norm(p2 - P0);

        if (fabs(d) < Epsilon)
            return false;
        else if (d < 0.0)
            return true;
        else
            return false;
    }
}

vector<Point> convex_hull(vector<Point> &poly)
{
    if (poly.size() <= 1)
        return poly;

    vector<Point> hull;

    int min = 0;
    P0 = poly[0];

    // Find point that has lowest y, and then has lowest x
    for (int i = 1; i < poly.size(); i++) {
        if (poly[i].imag() < P0.imag() || (fabs(poly[i].imag() - P0.imag()) < Epsilon && (poly[i].real() < P0.real()))) {
          min = i;
          P0 = poly[i];
        }
    }

    // Put P0 into start of poly
    poly[min] = poly[0];
    poly[0] = P0;
    hull.push_back(P0);

    sort(poly.begin() + 1, poly.end(), polar_cmp);
  
    // Find first distinct element from P0
    int i;
    for (i = 1; i < poly.size(); i++) {
        if (norm(poly[i] - P0) > Epsilon)
          break;
    }

    if (i == poly.size())
        return hull;

    hull.reserve(poly.size());
    hull.push_back(poly[i++]);

    for ( ; i < poly.size(); i++) {
        while (hull.size() > 1 && cross_prod_dir(poly[i], *(hull.end() - 1), *(hull.end() - 2)) != CCW)
            hull.pop_back();

        hull.push_back(poly[i]);
    }

    return hull;
}



int main(void)
{
    vector<Point> polygon, hull;
    int n;

    while (cin >> n && n > 0) {
        polygon.resize(n);

        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            polygon[i] = Point(x, y);
        }

        hull = convex_hull(polygon);

        cout << "Sorted:\n";
        for (int i = 0; i < n; i++) {
            cout << polygon[i].real() << ' ' << polygon[i].imag() << '\n';
        }
        cout << '\n';

        cout << "Hull size = " << hull.size() << '\n';
        for (int i = 0; i < hull.size(); i++) {
            cout << hull[i].real() << ' ' << hull[i].imag() << '\n';
        }
        cout << '\n';
    }
    return 0;
}