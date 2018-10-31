#include "Parabola-line intersection.cpp"
// Returns number of circles that pass through point a and b and
// are tangent to the line c-d
// 'ans' has all possible circles with radius > 0
int get_circle(point a, point b, point c, point d, vector<circle> &ans) {
  point pa = (a + b) / 2.0;
  point pb = (b - a) * point(0, 1) + pa;
  vector<point> ta;
  parabola_line_inter(a, c, d, pa, pb, ta);
  for(point p: ta) ans.push_back(circle(p, abs(a - p)));
  return ans.size();
}
