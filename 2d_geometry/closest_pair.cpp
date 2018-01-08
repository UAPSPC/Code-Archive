/* Copyright 2018 - Zachary Friggstad

   Finds the closest pair of points in R^2 in O(n log^2 n) time. Will work
   for many distance functions: standard Euclidean, Manhattan, max norm, etc
   See comments above the function dist() for more details.

   The running time could be reduced to O(n log n) but I did not bother with this
   because the implementation complexity is higher and the payoff is probably not
   worth it.

   Read the points into the global array pts[] and call closestPair(n).
   Don't worry about setting the i-component of pts[], this will be done
   by the algorithm.

   Global index variables pi, pj will be set to the indices of the closest pair.
   Global variable mind will store their distance.

   Reliability
    - UVa: 20145
    - Kattis: closestpair1
    - Kattis: closestpair 2
*/

#include <iostream>
#include <algorithm>
#include <cmath>

#define MAXN 100000

using namespace std;

struct point {
    double x, y;
    int i;
};

bool compX(const point& p, const point& q) { return p.x < q.x; }
bool compY(const point& p, const point& q) { return p.y < q.y; }

point pts[MAXN], ptsSort[MAXN], aux[MAXN];
int pi, pj;  // indices of closest pair
double mind; // distance of closest pair

/*
    This currently returns the standard Euclidean distance between two points,
    but you can replace it with Manhattan distances,
    max(|p.x-q.x|, |p.y-q.y|), or any \ell_k norm
    (|p.x-q.x|^k + |p.y-q.y|^k)^{1/k} with k >= 1
    and the algorithm will still be correct and run in O(n log^2 n) time.
*/
double dist(const point& p, const point& q) {
    double dx = p.x - q.x, dy = p.y - q.y;
    return sqrt(dx*dx + dy*dy);
}

void closestPairRec(point p[], int n) {
    if (n <= 1) return;

    int mid = n>>1;
    closestPairRec(p, mid);
    closestPairRec(p+mid, n-mid);

    int m = 0;
    for (int i = 0; i < n; ++i)
        if (abs(p[i].x - p[mid].x) < mind)
            aux[m++] = p[i];

    sort(aux, aux+m, compY);

    // total number of all iterations is guaranteed to be O(n)
    for (int i = 0; i < m; ++i)
        for (int j = i+1; j < m && aux[j].y < aux[i].y + mind; ++j) {
            double d = dist(aux[i], aux[j]);
            if (d < mind) {
                mind = d;
                pi = aux[i].i;
                pj = aux[j].i;
            }
        }
}

void closestPair(int n) {
    for (int i = 0; i < n; ++i) {
        pts[i].i = i;
        ptsSort[i] = pts[i];
    }
    sort(ptsSort, ptsSort+n, compX);

    mind = INFINITY;

    closestPairRec(ptsSort, n);
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;

    closestPair(n);

    cout << "Minimum distance: " << mind << endl
         << "Achieved by:" << endl
         << pi << ": " << pts[pi].x << ' ' << pts[pi].y << endl
         << pj << ": " << pts[pj].x << ' ' << pts[pj].y << endl;

    return 0;
}
