/* 2D Geometry: Largest rectangle not enclosing points
   =================================================================
   Description: Given a field of length W by H, and a set of 
                N points, find one of the largest rectangles 
		which do not enclose any points
   
   Complexity:  O(N^3) where N is the number of points
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Feb 15, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - Field is [0..W] x [0..H].  Offset as needed.
                - This works by trying all possible left and right
		  boundaries, and determining the largest possible
		  rectangle given those two bounds.
*/

#define MAXN 100

#include <stdio.h>
#include <set>
#include <vector>

using namespace std;

typedef struct{
  double x, y;
} Point;

typedef struct{
  double left,right,top,bot;
} Rect;

Rect max_Rect(Point *p, int n, double width, double height){
  set< double > xset, yset, ys; Rect r;
  double old, curr, bot, top, area, best;
  set<double>::iterator left, right, y;
  
  xset.insert(0); xset.insert(width);
  yset.insert(0); yset.insert(height);
  for(int i = 0; i < n; i++){
    xset.insert(p[i].x);
    yset.insert(p[i].y);
  }

  area = -1;
  for(left = xset.begin(); left != xset.end(); left++){
    for(right = left; right != xset.end(); right++){
      ys.clear();
      ys.insert(height);
      for(int i = 0; i < n; i++)
	if(*left < p[i].x && p[i].x < *right) ys.insert(p[i].y);
      old = best = 0;
      for(y = ys.begin(); y != ys.end(); y++){
	if(*y-old > best){
	  best = *y-old;
	  bot = old;
	  top = *y;
	}
	old = *y;
      }
      curr = best*(*right-*left);
      if(curr > area){
	area = curr;
	r.left = *left;
	r.right = *right;
	r.bot = bot;
	r.top = top;
      }
    }
  }
  return r;
}

int main(){
  int i, n; double w, h;
  Rect r; Point p[MAXN];
  
  while(scanf(" %lf %lf %d", &w, &h, &n) == 3){
    for(i = 0; i < n; i++)
      scanf("%lf %lf", &p[i].x, &p[i].y);
    r = max_Rect(p, n, w, h);
    printf("Largest rectangle: %.2f -> %.2f, %.2f -> %.2f\n",
	   r.left, r.right, r.bot, r.top);
  }
  return 0;
}
