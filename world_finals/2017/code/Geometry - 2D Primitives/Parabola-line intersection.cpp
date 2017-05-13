#include "Basics.cpp"
// Find intersection of the line d-e and the parabola that
// is defined by point 'p' and line a-b
// Returns the number of intersections
// 'ans' has intersection points
int parabola_line_inter(point p, point a, point b, point d, point e, vector<point> &ans) {
  b = b - a;
  p /= b;
  a /= b;
  d /= b;
  e /= b;
  a -= p;
  d -= p;
  e -= p;
  point n = (e - d) * point(0, 1);
  double c = -dot(n, e);
  if(abs(n.imag()) < eps) {
    if(abs(a.imag()) > eps) {
      double x = -c / n.real();
      ans.push_back(point(x, a.imag() / 2 - x * x / (2 * a.imag())));
    }
  } else {
    double aa = 1;
    double bb = -2 * a.imag() * n.real() / n.imag();
    double cc = -2 * a.imag() * c / n.imag() - a.imag() * a.imag();
    double delta = bb * bb - 4 * aa * cc;
    if(delta > -eps) {
      if(delta < 0) delta = 0;
      delta = sqrt(delta);
      double x = (-bb + delta) / (2 * aa);
      ans.push_back(point(x, (-c - n.real() * x) / n.imag()));
      if(delta > eps) {
        double x = (-bb - delta) / (2 * aa);
        ans.push_back(point(x, (-c - n.real() * x) / n.imag()));
      }
    }
  }
  for(int i = 0; i < ans.size(); i++) ans[i] = (ans[i] + p) * b;
  return ans.size();
}
