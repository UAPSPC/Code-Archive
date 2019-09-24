/*  Author: Jason Cannon, 2017
    
    Computes the smallest circle that contains all of a given set of points in the
    Euclidean plane (smallest enclosing circle) using Welzl's randomized algorithm.

    Complexity: O(n)

    Reference:
    https://en.wikipedia.org/wiki/Smallest-circle_problem

    Reliability:
    10005 (Packing polygons) - UVA Online Judge
    Stars in a Can - Open Kattis
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

struct point {
    double x, y;
    point() {}
    point(double x, double y): x(x), y(y) {}
};
struct circle {
    double x, y, r;
    circle() {}
    circle(double x, double y, double r): x(x), y(y), r(r) {}
};

/*
    Given a set of points, determine the enclosing circle.
    Works for 0-3 points, where 0 returns -1 radius centered at (0, 0).
*/
circle calc_circle(vector<point> R) {
    if (R.size() == 0) {
        return circle(0, 0, -1);
    } else if (R.size() == 1) {
        return circle(R[0].x, R[1].y, 0);
    } else if (R.size() == 2) {
        // Constructing a circle from 2 points.
        return circle((R[0].x+R[1].x)/2.0,
                      (R[0].y+R[1].y)/2.0,
                      hypot(R[0].x-R[1].x, R[0].y-R[1].y)/2.0);
    } else {
        // Constructing a circle from 3 points.
        double d = 2.0 * ((R[0].y - R[2].y) * (R[0].x - R[1].x) - (R[0].y - R[1].y) * (R[0].x - R[2].x));
        double x = ((R[0].y - R[2].y) * (R[0].y*R[0].y - R[1].y*R[1].y  + R[0].x*R[0].x - R[1].x*R[1].x) 
                   - (R[0].y - R[1].y) * (R[0].y*R[0].y - R[2].y*R[2].y + R[0].x*R[0].x - R[2].x*R[2].x)) / d;
        double y = ((R[0].x - R[2].x) * (R[0].x*R[0].x - R[1].x*R[1].x + R[0].y*R[0].y - R[1].y*R[1].y) 
                   - (R[0].x - R[1].x) * (R[0].x*R[0].x - R[2].x*R[2].x + R[0].y*R[0].y - R[2].y*R[2].y)) / -d;

        return circle(x, y, hypot(R[0].x - x, R[0].y - y));
    }
}

/*
    Welzl's Algorithm. 
    Runtime: O(n), determines the smallest enclosing circle for a set of points.
*/
circle _welzl(vector<point>& P, int i, vector<point> R) {
    // No points or three on the boundry.
    if (i == P.size() || R.size() >= 3)
        return calc_circle(R);
    // Calculate the circle without p_i.
    circle C = _welzl(P, i+1, R);
    // Check if p_i exists within the enclosing circle.
    if (hypot(P[i].x-C.x,P[i].y-C.y) > C.r) {
        // p_i must exist on the boundry.
        R.push_back(P[i]);
        // Move p_i to R.
        C = _welzl(P, i+1, R);
    }
    // Return the enclosing circle w.r.t to p_i.
    return C;
}

circle welzl(vector<point> P) {
    // Shuffle the points randomly.
    // Not neccessarily needed if points are given in random order, however, usually doesn't hurt.
    random_shuffle(P.begin(), P.end());
    return _welzl(P, 0, vector<point>());
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<point> P(n);
        for (int i = 0; i < n ; ++i)
            cin >> P[i].x >> P[i].y;
        circle c = welzl(P);
        cout << "Smallest enclosing circle: x=" << c.x << ", y=" << c.y << ", r=" << c.r << endl;
    }
    return 0;
}