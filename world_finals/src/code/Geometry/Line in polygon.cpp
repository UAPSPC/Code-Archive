#include "Is Left Of.cpp"
#include "Line-line intersection.cpp"
double Lowest = -10000000;
double Highest = 10000000;
point InvalidLowerBound = point(Lowest - 1, Lowest - 1);
point InvalidUpperBound = point(Highest + 1, Highest + 1);
// Checks how line a-b interacts with polygon segment c-d
// 0 - doesn't touch middle or vertex edge + 1.
// 1 - touches in middle of edge
// 2 - touches the vertex index edge + 1. May or may not exit.
int where_touches_segment(point a, point b, point c, point d, point &p) {
  int res = line_line_inter(a, b, c, d, p);
  if(res == 1 && dot(p - c, p - d) < -eps) {
    return 1;
  } else if(res == -1 || (res == 1 && abs(p - d) < eps)) {
    p = d;
    return 2;
  } // res == 0 || (res == 1 && dot(p - c, p - d) >= eps)
  return 0;
}
// By x, then y.
bool LE(point a, point b) {
  // If their x are equal, check y.
  if(abs(a.real() - b.real()) > eps) return a.real() < b.real();
  return a.imag() < b.imag() + eps;
}
// By x, then y.
bool GE(point a, point b) {
  // If their x are equal, check y.
  if(abs(a.real() - b.real()) > eps) return a.real() > b.real();
  return a.imag() > b.imag() - eps;
}
// Given the line a, will return points just above and just below base
// on the line.
void GenAboveBelow(point a, point b, point base, point &pLow, point &pHigh) {
  pLow = base + b - a;
  pHigh = base - b + a;
  if(LE(pHigh, pLow)) swap(pLow, pHigh);
}
// Checks if segStart is outside the polygon. Assumes CCW
bool SegmentStaysInPolygonFromD(point segStart, point c, point d, point e) {
  if(IsLeftOf(c, d, e, false)) { // Convex
    return IsLeftOf(c, d, segStart, true) && IsLeftOf(d, e, segStart, true);
  } else { // Concave
    return IsLeftOf(c, d, segStart, true) || IsLeftOf(d, e, segStart, true);
  }
}
// Polygon should be given in CCW order. Is O(n)
// Allows arbitrary points and will return the two furthest points
// reachable from a. If returns InvalidLowerBound or
// InvalidUpperBound, then the line starting from a is partially
// outside.
pair<point, point> line_polygon_intersections(point a, point b, vector<point> &polygon) {
  point aLowerMost = InvalidLowerBound;
  point aUpperMost = InvalidUpperBound;
  for(int edge = 0; edge < polygon.size(); ++edge) {
    point p;
    point c = polygon[edge % polygon.size()];
    point d = polygon[(edge + 1) % polygon.size()];
    point e = polygon[(edge + 2) % polygon.size()];
    int res = where_touches_segment(a, b, c, d, p);
    if(res == 0) continue;
    bool exitsLower = true;
    bool exitsUpper = true;
    if(res == 0) {
      continue;
    } else if(res == 2) { // Collided on endpoint (polygon[edge + 1]).
      point pLow, pHigh;
      GenAboveBelow(a, b, d, pLow, pHigh);
      exitsLower = !SegmentStaysInPolygonFromD(pLow, c, d, e);
      exitsUpper = !SegmentStaysInPolygonFromD(pHigh, c, d, e);
    }
    if(exitsLower && LE(p, a) && GE(p, aLowerMost)) { aLowerMost = p; }
    if(exitsUpper && GE(p, a) && LE(p, aUpperMost)) { aUpperMost = p; }
  }
  return make_pair(aLowerMost, aUpperMost);
}
