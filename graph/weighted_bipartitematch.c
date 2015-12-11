/* Graph Theory: Maximum Weighted Bipartite Matching
   Combinatorics: Assignment Problem
   =================================================================
   Description: Given N workers and N jobs to complete, where each worker has a
                certain compatibility (weight) to each job, find an assignment
		(perfect matching) of workers to jobs which maximizes the
		compatibility (weight).
   
   Complexity:  O(n^3), where n is the number of workers or jobs.
   -----------------------------------------------------------------
   Author:      Jason Klaus
   Date:        February 18, 2004
   References:  www.cs.umd.edu/class/fall2003/cmsc651/lec07.ps
   -----------------------------------------------------------------
   Reliability: 3
   Notes:       - W is a 2 dimensional array where W[i][j] is the weight of
                  worker i doing job j.  Weights must be non-negative.  If
		  there is no weight assigned to a particular worker and job
		  pair, set it to zero.  If there is a different number of
		  workers than jobs, create dummy workers or jobs accordingly
		  with zero weight edges.
		- M is a 1 dimensional array populated by the algorithm where
		  M[i] is the index of the job matched to worker i.
		- This algorithm could be used on non-negative floating point
		  weights as well.
*/

#include <stdio.h>

/* Maximum number of workers/jobs */
#define MAX_N 100

int W[MAX_N][MAX_N], U[MAX_N], V[MAX_N], Y[MAX_N]; /* <-- weight variables */
int M[MAX_N], N[MAX_N], P[MAX_N], Q[MAX_N], R[MAX_N], S[MAX_N], T[MAX_N];

/* Returns the maximum weight, with the perfect matching stored in M. */
int Assign(int n)
{
  int w, y; /* <-- weight variables */
  int i, j, m, p, q, s, t, v;

  for (i = 0; i < n; i++) {
    M[i] = N[i] = -1;
    U[i] = V[i] = 0;

    for (j = 0; j < n; j++)
      if (W[i][j] > U[i])
	U[i] = W[i][j];
  }

  for (m = 0; m < n; m++) {
    for (p = i = 0; i < n; i++) {
      T[i] = 0;
      Y[i] = -1;

      if (M[i] == -1) {
	S[i] = 1;
	P[p++] = i;
      }
      else
	S[i] = 0;
    }

    while (1) {
      for (q = s = 0; s < p; s++) {
	i = P[s];

	for (j = 0; j < n; j++)
	  if (!T[j]) {
	    y = U[i] + V[j] - W[i][j];

	    if (y == 0) {
	      R[j] = i;
	      if (N[j] == -1)
		goto end_phase;
	      T[j] = 1;
	      Q[q++] = j;
	    }
	    else if ((Y[j] == -1) || (y < Y[j])) {
	      Y[j] = y;
	      R[j] = i;
	    }
	  }
      }

      if (q == 0) {
	y = -1;

	for (j = 0; j < n; j++)
	  if (!T[j] && ((y == -1) || (Y[j] < y)))
	    y = Y[j];

	for (j = 0; j < n; j++) {
	  if (T[j])
	    V[j] += y;

	  if (S[j])
	    U[j] -= y;
	}

	for (j = 0; j < n; j++)
	  if (!T[j]) {
	    Y[j] -= y;

	    if (Y[j] == 0) {
	      if (N[j] == -1)
		goto end_phase;
	      T[j] = 1;
	      Q[q++] = j;
	    }
	  }
      }

      for (p = t = 0; t < q; t++) {
	i = N[Q[t]];
	S[i] = 1;
	P[p++] = i;
      }
    }
   
  end_phase:
    i = R[j];
    v = M[i];
    M[i] = j;
    N[j] = i;

    while (v != -1) {
      j = v;
      i = R[j];
      v = M[i];
      M[i] = j;
      N[j] = i;    
    }
  }

  for (i = w = 0; i < n; i++)
    w += W[i][M[i]];

  return w;
}


int main()
{
  int w; /* <-- weight variables */
  int n, i, j;

  while ((scanf("%d", &n) == 1) && (n != 0)) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	scanf("%d", &W[i][j]);
      }
    }

    w = Assign(n);

    printf("Optimum weight: %d\n", w);
    printf("Matchings:\n");

    for (i = 0; i < n; i++) {
      printf("%d matched to %d\n", i, M[i]);
    }
  }

  return 0;
}
