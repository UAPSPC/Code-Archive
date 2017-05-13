#include "Basics.cpp"
double circ_inter_area(circle &a, circle &b) {
  double d = abs(b.c - a.c);
  if(d <= (b.r - a.r)) return a.r * a.r * M_PI;
  if(d <= (a.r - b.r)) return b.r * b.r * M_PI;
  if(d >= a.r + b.r) return 0;
  double alpha = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));
  double beta = acos((b.r * b.r + d * d - a.r * a.r) / (2 * b.r * d));
  return a.r * a.r * (alpha - 0.5 * sin(2 * alpha)) + b.r * b.r * (beta - 0.5 * sin(2 * beta));
}
