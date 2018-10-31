#include "Line-line intersection.cpp"
// Returns number of circles that are tangent to all three lines
// 'cirs' has all possible circles with radius > 0
// It has zero circles when two of them are coincide
// It has two circles when only two of them are parallel
// It has four circles when they form a triangle. In this case
// first circle is incircle. Next circles are ex-circles tangent
// to edge a,b,c of triangle respectively.
int get_circle(point a1, point a2, point b1, point b2, point c1, point c2, vector<circle> &cirs) {
  point a, b, c;
  int sa = line_line_inter(a1, a2, b1, b2, c);
  int sb = line_line_inter(b1, b2, c1, c2, a);
  int sc = line_line_inter(c1, c2, a1, a2, b);
  if(sa == -1 || sb == -1 || sc == -1) return 0;
  if(sa + sb + sc == 0) return 0;
  if(sb == 0) {
    swap(a1, c1);
    swap(a2, c2);
  }
  if(sc == 0) {
    swap(b1, c1);
    swap(b2, c2);
  }
  sa = line_line_inter(a1, a2, b1, b2, c);
  line_line_inter(b1, b2, c1, c2, a);
  line_line_inter(c1, c2, a1, a2, b);
  if(sa == 0) {
    point v1 = polar(1.0, (arg(a2 - a1) + arg(a - b)) / 2) + b;
    point v2 = polar(1.0, (arg(a1 - a2) + arg(a - b)) / 2) + b;
    point v3 = polar(1.0, (arg(b2 - b1) + arg(a - b)) / 2) + a;
    point v4 = polar(1.0, (arg(b1 - b2) + arg(a - b)) / 2) + a;
    point p;
    if(line_line_inter(b, v1, a, v3, p) == 0) swap(v3, v4);
    line_line_inter(b, v1, a, v3, p);
    circle c1, c2;
    c1.c = p;
    line_line_inter(b, v2, a, v4, p);
    c2.c = p;
    c1.r = c2.r = abs(((a1 - b1) / (b2 - b1)).imag() * abs(b2 - b1)) / 2;
    cirs.push_back(c1);
    cirs.push_back(c2);
  } else {
    if(abs(a - b) < eps) return 0;
    point bisec1[4][2];
    point bisec2[4][2];
    bisec1[0][0] = polar(1.0, (arg(c - a) + arg(b - a)) / 2);
    bisec1[0][1] = a;
    bisec2[0][0] = polar(1.0, (arg(c - b) + arg(a - b)) / 2);
    bisec2[0][1] = b;
    bisec1[1][0] = polar(1.0, (arg(c - a) + arg(b - a)) / 2);
    bisec1[1][1] = a;
    bisec2[1][0] = polar(1.0, (arg(c - b) + arg(b - a)) / 2);
    bisec2[1][1] = b;
    bisec1[2][0] = polar(1.0, (arg(a - b) + arg(c - b)) / 2);
    bisec1[2][1] = b;
    bisec2[2][0] = polar(1.0, (arg(a - c) + arg(c - b)) / 2);
    bisec2[2][1] = c;
    bisec1[3][0] = polar(1.0, (arg(b - c) + arg(a - c)) / 2);
    bisec1[3][1] = b;
    bisec2[3][0] = polar(1.0, (arg(b - a) + arg(a - c)) / 2);
    bisec2[3][1] = c;
    for(int i = 0; i < 4; i++) {
      point p;
      line_line_inter(bisec1[i][1], bisec1[i][1] + bisec1[i][0], bisec2[i][1], bisec2[i][1] + bisec2[i][0], p);
      circle c1;
      c1.c = p;
      c1.r = abs(((p - a) / (b - a)).imag()) * abs(b - a);
      cirs.push_back(c1);
    }
  }
  return cirs.size();
}
