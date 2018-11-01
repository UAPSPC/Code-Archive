const double eps = 1e-6;
struct point3 {
  double x, y, z;
  point3(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
  point3 operator+(point3 p) const { return point3(x + p.x, y + p.y, z + p.z); }
  point3 operator*(double k) const { return point3(k * x, k * y, k * z); }
  point3 operator-(point3 p) const { return *this + (p * -1.0); }
  point3 operator/(double k) const { return *this * (1.0 / k); }
  double norm() { return x * x + y * y + z * z; }
  double abs() { return sqrt(norm()); }
  point3 normalize() { return *this / this->abs(); }
};
// dot product
double dot(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
// cross product
point3 cross(point3 a, point3 b) { return point3(a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y); }
struct line {
  point3 a, b;
  line(point3 A = point3(), point3 B = point3()): a(A), b(B) {}
  // Direction unit vector a -> b
  point3 dir() { return (b - a).normalize(); }
};
// Returns closest point on an infinite line u to the point p
point3 cpoint_iline(line u, point3 p) {
  point3 ud = u.dir();
  return u.a - ud * dot(u.a - p, ud);
}
// Returns Shortest distance between two infinite lines u and v
double dist_ilines(line u, line v) { return dot(v.a - u.a, cross(u.dir(), v.dir()).normalize()); }
// Finds the closest point on infinite line u to infinite line v
// Note: if (uv*uv - uu*vv) is zero then the lines are parallel
// and such a single closest point does not exist. Check for
// this if needed.
point3 cpoint_ilines(line u, line v) {
  point3 ud = u.dir();
  point3 vd = v.dir();
  double uu = dot(ud, ud), vv = dot(vd, vd), uv = dot(ud, vd);
  double t = dot(u.a, ud) - dot(v.a, ud);
  t *= vv;
  t -= uv * (dot(u.a, vd) - dot(v.a, vd));
  t /= (uv * uv - uu * vv);
  return u.a + ud * t;
}
// Closest point on a line segment u to a given point p
point3 cpoint_lineseg(line u, point3 p) {
  point3 ud = u.b - u.a;
  double s = dot(u.a - p, ud) / ud.norm();
  if(s < -1.0) return u.b;
  if(s > 0.0) return u.a;
  return u.a - ud * s;
}
struct plane {
  point3 n, p;
  plane(point3 ni = point3(), point3 pi = point3()): n(ni), p(pi) {}
  plane(point3 a, point3 b, point3 c): n(cross(b - a, c - a).normalize()), p(a) {}
  // Value of d for the equation ax + by + cz + d = 0
  double d() { return -dot(n, p); }
};
// Closest point on a plane u to a given point p
point3 cpoint_plane(plane u, point3 p) { return p - u.n * (dot(u.n, p) + u.d()); }
// Point of intersection of an infinite line v and a plane u.
// Note: if dot(u.n, vd) == 0 then the line and plane do not
// intersect at a single point. Check for this if needed.
point3 iline_isect_plane(plane u, line v) {
  point3 vd = v.dir();
  return v.a - vd * ((dot(u.n, v.a) + u.d()) / dot(u.n, vd));
}
// Infinite line of intersection between two planes u and v.
// Note: if dot(v.n, uvu) == 0 then the planes do not intersect
// at a line. Check for this case if it is needed.
line isect_planes(plane u, plane v) {
  point3 o = u.n * -u.d(), uv = cross(u.n, v.n);
  point3 uvu = cross(uv, u.n);
  point3 a = o - uvu * ((dot(v.n, o) + v.d()) / (dot(v.n, uvu) * uvu.norm()));
  return line(a, a + uv);
}
// Returns great circle distance (lat[-90,90], long[-180,180])
double greatcircle(double lt1, double lo1, double lt2, double lo2, double r) {
  double a = M_PI * (lt1 / 180.0), b = M_PI * (lt2 / 180.0);
  double c = M_PI * ((lo2 - lo1) / 180.0);
  return r * acos(sin(a) * sin(b) + cos(a) * cos(b) * cos(c));
}
// Rotates point p around directed line a->b with angle 'theta'
point3 rotate(point3 a, point3 b, point3 p, double theta) {
  point3 o = cpoint_iline(line(a, b), p);
  point3 perp = cross(b - a, p - o);
  return o + perp * sin(theta) + (p - o) * cos(theta);
}
// Signed distance from p to nearest point on surface of box with
// dimensions b. Positive = outside, negative = inside
double signed_box_distance(point3 p, point3 b) {
  point3 d = point3(abs(p.x),abs(p.y),abs(p.z)) - b;
  return min(max(d.x,max(d.y,d.z)),0.0) + point3(max(d.x,0.0),max(d.y,0.0),max(d.z,0.0)).abs();
}
