/* Miscellaneous: Stable Marriage
   =================================================================
   Description: Given n women and n men, each with a list of
		preferences as to whom they want to marry, match
		each woman to a man in a stable way.  In a stable
		matching, there is no pair who would both rather be
		with each other than with their current partners.

   Complexity:	O(N^3) worst case, O(N^2 lg N) average case
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	March 03, 2003
   References:  www.cs.dal.ca/apics/contest99/c.txt
   -----------------------------------------------------------------
   Reliability: 1 (Atlantic Canada Preliminaries, 1999)
   Notes: 	Women order men, and men order women, according to
		preference lists.  Say we have 5 men, a, b, c, d, e, 
		and 5 women, A, B, C, D, E.  Then A's preference list 
		might look like this: 3 1 0 2 4, which means that A 
		likes d the most and e the least.  Your application
		might have rank lists instead.  A's ranklist is
		2, 1, 3, 0, 4, which means that a is her #2 choice
		(counting from 0) and b is her #1 choice.  Convert
		between the types as shown in the example.

		This implementation doesn't handle ties or
		incomplete preference lists.
*/

#include <stdio.h>
#include <string.h>
#define NMAX 100

int vpref[NMAX][NMAX]; /* women's choice of men, in descending order */
int upref[NMAX][NMAX]; /* men's choice of men */
int vrank[NMAX][NMAX]; /* women rank men, i.e. each man's "score" */
int urank[NMAX][NMAX]; /* men rank women */
int suitors[NMAX][NMAX]; /* woman A's partner is suitors[A][0] */

/* example: to get vpref from vrank, convert(vpref,vrank,n) */
/* example: to get vrank from vpref, convert(vrank,vpref,n) */
void convert(int a[NMAX][NMAX], int b[NMAX][NMAX], int n) {
  int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      a[i][b[i][j]] = j;
}

void stable(int n) {
  int choice[NMAX], nsuit[NMAX], used[NMAX];
  int i, j, best, nused;

  memset(used,0,sizeof(used));
  memset(nsuit,0,sizeof(nsuit));
  memset(choice,0,sizeof(choice));
  convert(upref,urank,n);
  for (nused = 0; nused < n; ) {
    for (i = 0; i < n; i++) { /* men propose */
      if (used[i]) continue;
      j = upref[i][choice[i]++];
      suitors[j][nsuit[j]++] = i;
      nused++;
    }
    for (i = 0; i < n; i++) { /* women choose */
      if (!nsuit[i]) continue;
      best = suitors[i][0];
      for (j = 0; j < nsuit[i]; j++) {
        if (vrank[i][suitors[i][j]] < vrank[i][best]) 
          best = suitors[i][j];
        used[suitors[i][j]] = 0;
      }
      suitors[i][0] = best;
      used[best] = 1;
      nused -= nsuit[i] - 1;
      nsuit[i] = 1;
    }
  }
}

int main() {
  int i, j, n;
  scanf("%d",&n);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
       scanf("%d",&vpref[i][j]);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
       scanf("%d",&upref[i][j]);
  convert(vrank,vpref,n);
  convert(urank,upref,n);
  stable(n);
  for (i = 0; i < n; i++) printf("%d %d\n",i+1,suitors[i][0]+1);
  return 0;
}
