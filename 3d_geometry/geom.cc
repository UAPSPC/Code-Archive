/* 3D Geometry: Geometry Primitives
   =================================================================
   Description: A wide range of 3D geometry primitives are given.

   Complexity:	O(1)
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	March 14, 2003
   References:  http://astronomy.swin.edu.au/~pbourke/geometry/planeline/
                http://astronomy.swin.edu.au/~pbourke/geometry/lineline3d/
                http://geometryalgorithms.com/algorithm_archive.htm
   -----------------------------------------------------------------
   Reliability: 0
   Notes: 	All the operators (+,-,*,/) are mandatory, but
		aside from that, you can just type in what you
		need.  You should type in the functions you need,
		try to compile the program, and then see what's
		missing.
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>
#define EPS 1E-8
#define pt(a) &(a.x), &(a.y), &(a.z)

typedef struct {
  double x, y, z;
} Point;

Point operator + (Point a, Point b) {
  Point p;

  p.x = a.x + b.x;
  p.y = a.y + b.y;
  p.z = a.z + b.z;
  return p;
}

Point operator * (double k, Point a) {
  Point p;

  p.x = k*a.x;
  p.y = k*a.y;
  p.z = k*a.z;
  return p;
}

Point operator * (Point a, double k) {
  return (k*a);
}

Point operator / (Point a, double k) {
  return a*(1/k);
}

Point operator - (Point a, Point b) {
  return a+(-1.0*b);
}

double dot(Point a, Point b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

Point cross(Point a, Point b) {
  Point cp;
 
  cp.x = a.y*b.z-b.y*a.z;
  cp.y = b.x*a.z-a.x*b.z;
  cp.z = a.x*b.y-b.x*a.y;
  return cp;
}

double lng2(Point a) {  // find the length of a vector, squared
  return dot(a,a);
}

double lng(Point a) {   // find the length of a vector
  return sqrt(dot(a,a));
}

Point closest_pt_iline(Point a, Point b, Point p) {
  double along = dot(b-a,p-a)/lng2(b-a);
  return (b-a)*along + a;
}

Point closest_pt_seg(Point a, Point b, Point p) {
  double along;

  if (lng2(b-a) < EPS) return a;
  along = dot(b-a,p-a)/lng2(b-a);
  if (along < 0) along = 0;
  if (along > 1) along = 1;
  return (b-a)*along + a;
}

/* Planes are commonly represented in one of two ways: 
   as a vector normal (perpendicular) to the plane and a
   single point on the plane, or as three non-collinear 
   points on the plane. */

Point closest_pt_plane(Point norm, Point a, Point p) {
  Point res = cross(cross(norm,p-a),norm);
  if (lng2(res) < EPS) return a;
  return res*dot(res,p-a)/lng2(res);
}

Point closest_pt_plane(Point a, Point b, Point c, Point p) {
  Point norm;

  norm = cross(b-a,c-a);
  assert(lng2(norm) > EPS);  // collinearity
  return closest_pt_plane(norm,a,p);
}

/* Given a sphere and an infinite line, determine if the two
   intersect, and if so, find the points of intersection.  If the 
   line is tangent to the sphere, the points will be the same */

int sphere_iline_isect(Point c, double r, Point a, Point b, 
                      Point *p, Point *q) {
  Point vec, mid = closest_pt_iline(a,b,c);

  if (lng2(c-mid) > r*r) return 0;
  vec = (a-b)*sqrt((r*r - lng2(c-mid))/lng2(a-b));
  *p = mid + vec;
  *q = mid - vec;
  return 1;
}

/* Often we are given a set of points in 3D space, and we know
   that they all lie in a certain plane.  We can translate
   that problem into a 2D problem using this code.

   Select three of the points to define your plane.  The points
   must be distinct and not collinear.  This code will find the 
   position of another point, p, in reference to an arbitrary, 
   but deterministic set of axes defined by the first three points.  

   This code just assumes that the points are actually coplanar. */

Point to_plane(Point a, Point b, Point c, Point p) {
  Point norm, ydir, xdir, res;

  norm = cross(b-a,c-a);
  assert(lng2(norm) > EPS);  // collinearity
  xdir = (b-a)/lng(b-a); // create orthonormal vectors
  ydir = cross(norm,xdir);
  ydir = ydir/lng(ydir);
  res.x = dot(p-a,xdir);
  res.y = dot(p-a,ydir);
  res.z = 0;
  return res;
}

/* given two lines in 3D space, find distance of closest approach */
double line_line_dist(Point a, Point b, Point c, Point d) {
  Point perp = cross(b-a,d-c);

  if (lng2(perp) < EPS)  /* parallel */
    perp = cross(b-a,cross(b-a,c-a));
  if (lng2(perp) < EPS) return 0; /* coincident */

  return fabs(dot(a-c,perp))/lng(perp);
}

/* this is the same as line_line_dist, but it also returns
   the points of closest approach */
double closest_approach(Point a, Point b, Point c, Point d,
                        Point *p, Point *q) {
  double s = dot(d-c,b-a), t = dot(a-c,d-c);
  double num, den, tmp;

  den = lng2(b-a)*lng2(d-c) - s*s;
  num = t*s - dot(a-c,b-a)*lng2(d-c);
  if (fabs(den) < EPS) { /* parallel */
    *p = a;
    *q = (d-c)*t/lng2(d-c) + c;
    if (fabs(s) < EPS) *q = a;  /* coincident */
  } else {  /* skew */
    tmp = num/den;
    *p = a + (b-a)*tmp;
    *q = c + (d-c)*(t + s*tmp)/lng2(d-c);
  }
  return lng(*p-*q);
}

/* is the point p on the infinite line ab? */
int on_iline(Point a, Point b, Point p) {
  return (lng2(p-closest_pt_iline(a,b,p)) < EPS);
}

/* is the point p on the segment ab? */
int on_seg(Point a, Point b, Point p) {
  return (lng(a-p) + lng(p-b) - lng(a-b) < EPS);
}

/* Given a plane and a line ab, determine if the two intersect,
   and if so, find the single point of intersection */
int plane_iline_isect(Point norm, Point ori, Point a, Point b, Point *p) {
  double along, den = dot(norm,b-a);

  if (fabs(den) < EPS) { /* parallel */
    if (lng2(cross(ori-a,b-a)) < EPS) return -1; /* coincident */
    return 0;  /* non-intersecting */
  }
  along = dot(norm,ori-a)/den;

  /* if you want to intersect a plane with a finite segment,
     check that (along <= 1 && along => 0) */

  *p = a + along*(b-a);
  return 1;
}

int main() {
  Point a, b, c, d, e, f;

  while (scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
               pt(a), pt(b), pt(c), pt(d))==12) {
    printf("%g  ",line_line_dist(a,b,c,d));
    printf("%g\n",closest_approach(a,b,c,d, &e, &f));
  }
  return 0;
}
