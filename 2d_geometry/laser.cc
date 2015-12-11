/* 2D-Geometry: Laser Reflections
   =================================================================
   Description: Given the starting point of a laser beam, and its
		directional vector, determine where the beam hits a
		wall (mirror), and its new direction after reflection.

   Complexity:	O(1)
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	March 07, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes: 	Returns 0 if the beam misses the wall, 1 if the beam
		hits the wall, and -1 if the beam hits the wall
		edge-on.  If the beam hit an end-point, the
		reflection vector is undefined, and -2 is returned.
*/

#include <stdio.h>
#include <math.h>
#define EPS 1E-8

typedef struct {
  double x, y;
} Point;

Point operator + (Point a, Point b) {
  Point p;

  p.x = a.x + b.x;
  p.y = a.y + b.y;
  return p;
}

Point operator * (double k, Point a) {
  Point p;

  p.x = k*a.x;
  p.y = k*a.y;
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
  return a.x*b.x + a.y*b.y;
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

/* return 1 for intersection, 0 for not, -1 for coincidental */
int intersect_iline(Point a, Point b, Point c, Point d, Point *p) {
  double den, num;

  num = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  den = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);

  if (fabs(den) >= EPS) {
    *p = a + (b-a)*num/den;
    return 1;
  } else {
    if (fabs(num) >= EPS) {
      return 0;
    } else {
      return -1;
    }
  }
}

Point reflect(Point a, Point b, Point c) {
  return 2.0*closest_pt_iline(a,b,c) - c;
}

int bounce(Point ori, Point dir, Point a, Point b, 
           Point *np, Point *ndir) {
  Point tmp;
  int res;

  res = intersect_iline(ori, ori+dir, a, b, &tmp);
  if (res == -1) return -1;
  if (res != 1 || dot(tmp-ori,dir) < 0 ||
      fabs(lng(a-tmp) + lng(b-tmp) - lng(a-b)) > EPS)
        return 0;
  *np = tmp;
  if (lng2(a-tmp) < EPS || lng2(b-tmp) < EPS) return -2;
  *ndir = reflect(a,b,tmp+dir) - tmp;
  return 1;
}

int main() {
  Point wall[2], ori, vec, newori, newvec;
  int res;

  while (scanf("%lf %lf %lf %lf", &wall[0].x, &wall[0].y, 
        &wall[1].x, &wall[1].y) == 4) {
    scanf("%lf %lf", &ori.x, &ori.y);
    scanf("%lf %lf", &vec.x, &vec.y);

    res = bounce(ori, vec, wall[0], wall[1], &newori, &newvec);
    if (res==0) printf("missed\n");
    else if (res==-1) printf("hit edge-on\n");
    else if (res==-2) printf("hit a corner\n");
    else printf("hit %g %g, new vector is %g %g\n",
                newori.x, newori.y, newvec.x, newvec.y);
  }
  return 0;
}
