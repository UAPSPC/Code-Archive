/* 2D Geometry - Circle Intersection Points
   =================================================================
   Description: Computes the # and location of intersections.
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Scott Crosswhite
   Date:        Dec 21, 2002
   References:  http://hades.ph.tn.tudelft.nl/.../MathWorld/
                       math/math/c/c308.htm
   -----------------------------------------------------------------
   Reliability: 1.5 (Spain 10425)
                    (Broderick's test batch)
   Notes:  
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-8
#define SQR(x) ((x)*(x))

double PI;

typedef struct {
  double x,y;
} Point;

typedef struct {
  Point o;
  double r;
} Circle;

enum int_t {NONE=0, ONE, TWO, AEQUALSB, AINB, BINA,
            AINB_TANGENT, BINA_TANGENT};

Point rotate_2d(Point p, Point o, double theta){
  double m[2][2];
  Point r;
  
  m[0][0] = m[1][1] = cos(theta);
  m[0][1] = -sin(theta);
  m[1][0] = -m[0][1];
  p.x -= o.x; 
  p.y -= o.y;
  r.x = m[0][0] * p.x + m[0][1] * p.y + o.x;
  r.y = m[1][0] * p.x + m[1][1] * p.y + o.y;
  if(fabs(r.x) < EPS) r.x = 0;
  if(fabs(r.y) < EPS) r.y = 0;
  return r;
}

int CIType (Circle A, Circle B) {
  double distance, dx = A.o.x - B.o.x, dy = A.o.y - B.o.y;

  distance = sqrt(dx*dx + dy*dy);

  if (distance < EPS && fabs(A.r-B.r) < EPS) return AEQUALSB;
  if (fabs(distance - (A.r + B.r)) < EPS) return ONE;
  if (distance > A.r + B.r) return NONE;
  if (distance + A.r <= B.r) {
    if (B.r - (distance+A.r) < EPS) return AINB_TANGENT;
    return AINB;
  }
  if (distance + B.r <= A.r) {
    if (A.r - (distance+B.r) < EPS) return BINA_TANGENT;
    return BINA;
  }
  return TWO;
}

/* Return value is # of intersections */
int CIPoints (Circle A, Circle B, Point *s, Point *t) {
  double dx = B.o.x-A.o.x, dy = B.o.y-A.o.y;
  double dA, d, c, a;
  int type;

  type = CIType(A, B);

  d = sqrt(dx*dx + dy*dy);

  switch (type) {
  case AINB_TANGENT:
    s->x = B.o.x + (B.r/d)*-dx;
    s->y = B.o.y + (B.r/d)*-dy;
    return 1;

  case BINA_TANGENT: case ONE:
    s->x = A.o.x + (A.r/d)*dx;
    s->y = A.o.y + (A.r/d)*dy;
    return 1;

  case TWO:
    c = atan2(dy, dx);
    
    a = sqrt(4*SQR(d)*SQR(A.r) - SQR(SQR(d)-SQR(B.r)+SQR(A.r))) /d;

    dA = (SQR(d) - SQR(B.r) + SQR(A.r)) / (2*d);

    t->x = s->x = dA + A.o.x;
    s->y = a/2 + A.o.y;
    t->y = -a/2 + A.o.y;

    /* Rotate these points */
    *s = rotate_2d(*s, A.o, c);
    *t = rotate_2d(*t, A.o, c);

    return 2;

  default:
    return type;
  }
}

int main () {
  Circle A, B;
  Point s, t;
  int num;

  PI = acos(-1);

  while (scanf("%lf %lf %lf %lf %lf %lf", 
	       &A.o.x, &A.o.y, &A.r, &B.o.x, &B.o.y, &B.r) == 6) {

    num = CIPoints(A, B, &s, &t);

    printf("There are %d intersections. ", num);
    if (num) printf("(%.3f, %.3f)  ", s.x, s.y);
    if (num == 2) printf("(%.3f, %.3f)", t.x, t.y);
    printf("\n");
  }

  return 0;
}
