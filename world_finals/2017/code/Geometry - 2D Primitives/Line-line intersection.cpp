#include "Basics.cpp"
// Intersects point of lines a-b and c-d
// -1->coincide,0->parallel,1->intersected(inter. point in 'p')
int line_line_inter(point a, point b, point c, point d, point &p) {
  if(abs(cross(b - a, d - c)) > eps) {
    p = cross(c - a, d - c) / cross(b - a, d - c) * (b - a) + a;
    return 1;
  }
  if(abs(cross(b - a, b - c)) > eps) return 0;
  return -1;
}
