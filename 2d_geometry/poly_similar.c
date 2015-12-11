/* 2D Geometry: Polygon Similarity & Congruency
   =================================================================
   Description: Given polygons p1 and p2, determines whether or not 
		p2 is a transformed version of p1.  Valid transforms
		include flips, rotations, translation, scaling, and
		reversing the order of the points.

   Complexity:	O(N^2)
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	February 27, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes: 	Polygon congruency can also be determined.
		The polygons must not be self-intersecting.
		The polygons may be modified; make a copy if you
		need to.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EPS 1E-8
#define SQR(x) ((x)*(x))

typedef struct {
  double x, y;
} Point;

double dist2(Point a, Point b) {
  return SQR(a.x-b.x) + SQR(a.y-b.y);
}

double dot(Point a, Point b, Point c) {
  return (a.x-b.x)*(c.x-b.x) + (a.y-b.y)*(c.y-b.y);
}

double cross(Point a, Point b, Point c) {
  return (a.x-b.x)*(c.y-b.y) - (c.x-b.x)*(a.y-b.y);
}

/* given a polygon, remove verticies with 180 degree angles.
   return the number of verticies remaining. */
int poly_reduce(Point *poly, int n) {
  Point *npoly = malloc(n*sizeof(Point));
  int i, cnt = 0;

  for (i = 0; i < n; i++)
    if (fabs(cross(poly[i], poly[(i+1)%n], poly[(i+2)%n])) > EPS)
      npoly[cnt++] = poly[(i+1)%n];
  memcpy(poly,npoly,cnt*sizeof(Point));
  free(npoly);
  return cnt;
}

int poly_similar(Point *p1, int n, Point *p2, int m) {
  double ratio, turn;
  Point a, b, c, d, e, f, tmp;
  int i, j, ori;

  n = poly_reduce(p1,n);
  m = poly_reduce(p2,m);
  if (n != m) return 0;

  for (ori = 0; ori < 2; ori++) {
    for (i = 0; i < n; i++) {
      turn = cross(p1[0],p1[1],p1[2]);
      turn /= cross(p2[i],p2[(i+1)%n],p2[(i+2)%n]);
      ratio = dist2(p1[0],p1[1])/dist2(p2[i],p2[(i+1)%n]);
      /* uncomment the following line for polygon congruency */
      /* if (fabs(ratio-1) > EPS) continue; */
      for (j = 0; j < n; j++) {
        a = p1[j];
        b = p1[(j+1)%n];
        c = p1[(j+2)%n];
        d = p2[(j+i)%n];
        e = p2[(j+i+1)%n];
        f = p2[(j+i+2)%n];
        if (fabs(cross(a,b,c)/cross(d,e,f)-turn) > EPS ||
            fabs(dist2(a,b)/dist2(d,e)-ratio) > EPS ||
            fabs(dot(a,b,c)-dot(d,e,f)*ratio) > EPS) break;
      }
      if (j==n) return 1;
    }
    for (i = n/2; i < n; i++)
      tmp = p2[i]; p2[i] = p2[n-i-1]; p2[n-i-1] = tmp;
  }
  return 0;
}

int main() {
  Point p1[1100], p2[1100];
  int i, n, m;

  while (scanf("%d %d", &n, &m)==2) {
    for (i = 0; i < n; i++) scanf("%lf %lf", &p1[i].x, &p1[i].y);
    for (i = 0; i < m; i++) scanf("%lf %lf", &p2[i].x, &p2[i].y);
    if (!poly_similar(p1,n,p2,m)) printf("NOT ");
    printf("SIMILAR\n");
  }
  return 0;
}
