double eps = 1e-6;
typedef complex<double> point;
struct circle {
  point c;
  double r;
  circle(point c = {}, double r = 0): c(c), r(r) {}
};
double cross(point a, point b) { return imag(conj(a) * b); }
double dot(point a, point b) { return real(conj(a) * b); }
