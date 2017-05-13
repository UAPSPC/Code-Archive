#include "Basics.cpp"
// Intersects two circles and intersection points are in 'inter'
// -1-> outside, 0-> inside, 1-> tangent, 2-> 2 intersections
int circ_circ_inter(circle &a, circle &b, vector<point> &inter) {
  double d2 = norm(b.c - a.c), rS = a.r + b.r, rD = a.r - b.r;
  if(d2 > rS * rS) return -1;
  if(d2 < rD * rD) return 0;
  double ca = 0.5 * (1 + rS * rD / d2);
  point z = point(ca, sqrt((a.r * a.r / d2) - ca * ca));
  inter.push_back(a.c + (b.c - a.c) * z);
  if(abs(z.imag()) > eps) inter.push_back(a.c + (b.c - a.c) * conj(z));
  return inter.size();
}
