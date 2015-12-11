/* 2D-Geometry: Area of the union of Rectangles
   =================================================================
   Description: Given a set of N rectangles, determines the area of
                it's union.
   
   Complexity:  O(N^2)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 8, 2002
   References:
   -----------------------------------------------------------------
   Reliability: 1 successful use (Spain Problem 688) Sept 2002
   Notes:       Scan line technique - For each y-line, it determines
                how much is inside the polygon, thus computing area
                in rectangular blocks
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 200

typedef struct{
  double minx, miny, maxx, maxy;
} Rect;

typedef struct{
  double x, miny, maxy;
  char m;                 
} Edge;

Rect r[MAXN];
double ys[2*MAXN];
Edge e[2*MAXN];

int cmp_double(double *a, double *b){
  return *a < *b ? -1 : *a > *b ? 1 : 0;
}

int cmp_edge(Edge *a, Edge *b){
  return a->x < b->x ? -1 : a->x > b->x ? 1 : 0;
}

double area_unionrect(int n){
  int flag, i, j;
  double curr, sum, sx;

  for(i = 0; i < n; i++){
    e[2*i].miny = e[2*i+1].miny = ys[2*i] = r[i].miny;
    e[2*i].maxy = e[2*i+1].maxy = ys[2*i+1] = r[i].maxy;
    e[2*i].x = r[i].minx;
    e[2*i].m = 1;
    e[2*i+1].x = r[i].maxx;
    e[2*i+1].m = -1;
  }

  qsort(ys, 2*n, sizeof(ys[0]), (void *)cmp_double);
  qsort(e, 2*n, sizeof(e[0]), (void *)cmp_edge);
  
  sum = 0;
  for(i = 0; i < 2*n; i++){
    if(i) sum += (ys[i]-ys[i-1])*curr;
    curr = flag = 0;
    for(j = 0; j < 2*n; j++){
      if(e[j].miny <= ys[i] && ys[i] < e[j].maxy){
	if(!flag) sx = e[j].x;
	flag += e[j].m;
	if(!flag) curr += e[j].x-sx;
      }
    }
  }
  return sum;
}

int main(){
  int i, n;
  
  while(scanf("%d", &n) == 1){
    for(i = 0; i < n; i++){
      scanf("%lf %lf %lf %lf", 
	    &r[i].minx, &r[i].miny, &r[i].maxx, &r[i].maxy);
    }
    printf("Area of union is %f\n", area_unionrect(n));
  }
  return 0;
}
