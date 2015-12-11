/* 2D Geometry - Circle Intersection Type
   =================================================================
   Description: Determines the type of intersection of 2 circles.
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Scott Crosswhite
   Date:        Oct 24, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:  NONE - No intersection
           ONE - One intersection (no other common points)
	   TWO - Two intersections
	   AEQUALSB - Same circle
	   AINB, BINA - One circle is in the other
	   AINB_TANGENT, BINA_TANGENT - As above, with 1 pt tangent
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-8

typedef struct {
  double x,y;
} Point;

typedef struct {
  Point o;
  double r;
} Circle;

enum int_t {NONE=0, ONE, TWO, AEQUALSB, AINB, BINA, 
	    AINB_TANGENT, BINA_TANGENT};

int CIType (Circle A, Circle B) {
  double distance, dx = A.o.x - B.o.x, dy = A.o.y - B.o.y;

  distance = sqrt(dx*dx + dy*dy);

  if (distance < EPSILON && fabs(A.r-B.r) < EPSILON) return AEQUALSB; 
  if (fabs(distance - (A.r + B.r)) < EPSILON) return ONE; 
  if (distance > A.r + B.r) return NONE;
  if (distance + A.r <= B.r) {
    if (B.r - (distance+A.r) < EPSILON) return AINB_TANGENT;
    return AINB;
  } 
  if (distance + B.r <= A.r) {
    if (A.r - (distance+B.r) < EPSILON) return BINA_TANGENT;
    return BINA; 
  }
  return TWO;
}

/* To test output */
char type_s[8][50] = {"No intersection", 
		      "One intersection",
		      "Two intersections",
		      "Circles match",
		      "A is entirely in B",
		      "B is entirely in A",
		      "A is in B and tangent",
		      "B is in A and tangent"};

int main () {
  int type;
  Circle A, B;

  while (scanf("%lf %lf %lf %lf %lf %lf", 
	       &A.o.x, &A.o.y, &A.r, &B.o.x, &B.o.y, &B.r) == 6) {

    type = CIType(A, B);
    printf("Type: %s \n", type_s[type]);
  }

  return 0;
}
