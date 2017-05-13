#pragma once
double eps = 1e-6;
typedef complex<double> point;
struct circle {
  point c;
  double r;
  circle(point c, double r) : c(c), r(r) {}
  circle() {}
};
double cross(point &a, point &b) { return imag(conj(a) * b); }
double dot(point &a, point &b) { return real(conj(a) * b); }
