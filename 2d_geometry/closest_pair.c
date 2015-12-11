/* 2D Geometry: Closest pair of points
   =================================================================
   Description: Given a set of N points, finds two points A and B
                such that the distance between them is no greater
		than the distance between any other pair of points
		in the set.
   
   Complexity:  O(N lg N lg N)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        December 10, 2002
   References:  www.csc.liv.ac.uk/~ped/teachadmin/algor/d_and_c.html
                students.cec.wustl.edu/~cs241/handouts/closestpair.pdf
   -----------------------------------------------------------------
   Reliability: 1 (Spain 10245)
   Notes:       Call the function as shown in main().
                The original array of points will be sorted.
                The points are returned as globals.  N must be >= 2.
		- min stores the SQUARE of the minimum distance

                The traditional solution to this problem is
                O(N lg N), but it is about 80% more code and
                200% more difficult to understand.
		*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SQR(a) ((a)*(a))

typedef struct {
  double x, y;
} Point;

Point mina, minb;                        /* globals */
double min;

void checkpair(Point a, Point b) {
  double dist2 = SQR(b.x-a.x)+SQR(b.y-a.y);
  if (dist2 < min) {
    min = dist2;
    mina = a; minb = b;
  }
}

int xcmp(Point *a, Point *b) {
  if (a->x < b->x) return -1;
  if (a->x > b->x) return 1;
  if (a->y < b->y) return -1;
  if (a->y > b->y) return 1;
  return 0;
}

/* copy and paste xcmp when typing this in */
int ycmp(Point *a, Point *b) {
  if (a->y < b->y) return -1;
  if (a->y > b->y) return 1;
  if (a->x < b->x) return -1;
  if (a->x > b->x) return 1;
  return 0;
}

void closest_pair(Point *p, int n) {
  Point *q;
  int i, j, cnt;

  if (n==2) checkpair(p[0],p[1]);      /* base cases */
  if (n<=2) return;

  closest_pair(p,n/2);               /* do each half */
  closest_pair(&p[n/2],n-n/2);

  q = malloc(n*sizeof(Point));      /* do the middle */
  for (cnt = i = 0; i < n; i++)
    if (SQR(p[i].x - p[n/2].x) < min) q[cnt++] = p[i];
  qsort(q,cnt,sizeof(Point),(void *)ycmp);
  for (i = 0; i < cnt; i++) {
    if (SQR(q[i].x - p[n/2].x) >= min) break;
    for (j = i+1; j < cnt; j++) {
      if (SQR(q[i].y - q[j].y) >= min) break;
      checkpair(q[i],q[j]);
    }
  }
  free(q);
}

int main() {
  int n, i;
  Point p[1000];

  while (scanf("%d",&n)==1) {
    for (i = 0; i < n; i++)
      scanf("%lf %lf", &p[i].x, &p[i].y);

    qsort(p, n, sizeof(Point),(void *) xcmp);
    min = DBL_MAX;                    /* DBL_MAX is in limits.h */
    /* You can also use a value guaranteed to be
                         greater than the greatest distance, squared */
    closest_pair(p, n);

    printf("(%lf,%lf) (%lf,%lf)\n", mina.x, mina.y, minb.x, minb.y);
  }
  return 0;
}
