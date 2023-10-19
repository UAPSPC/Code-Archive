/*
  Copyright 2017 - Zachary Friggstad

  The simplex method for solving linear programs. It seems a bit long when
  written this way but it can be made much more compact for a code archive
  by stripping unnecessary comments and condensing some lines in loops.

  The LP should be in standard maximization form.

  maximize:   <c,x>
  subject to: A*x <= b, x >= 0

  Use global variables A, b, and c.

  If n = # vars, m = # constraints (apart from nonnegativity) then
   A : m by n constraint matrix
   b : m-dimensional array of constants in the constraints
   c : n-dimensional array of coefficients in the objective function

  Once A, b, and c are constructed, simply call simplex(n, m).
  Returns: -1 == unbounded, 0 == infeasible, 1 == optimum solution found

  If an optimum is found: x = one such optimum, val = its value
  (x and val are global variables)

  Running time: O(n * m * I) where I = # iterations. In the worst case
  this can be exponential, but it is usually *much* better. Can probably
  be used safely in a programming contest where n*m ~ 10,000.
  This is just a heuristic statement.

  Uses Bland's pivot selection rule to avoid cycles.

  CAUTION:
   - Many loops go from 0 up to *and including* n or m. But some do not.
     Pay careful attention toward the inequalities used.

   - Make sure you adjust MAXN and MAXC appropriately.

  TODO:
    1) Investigate other pivot methods.
    2) Generate Chvatal-Gomery cuts for integer programming (should be easy).

  Reliability:
    UVa 10746 - Remember to add EPS to each value before casting back to an int.
    Kattis roadtimes - 2016 ICPC world finals problem.
    Kattis goatropes
    UVa 802 - Just use c[i] = 0 for all i for the feasibility check.
    UVa 10498
    UVA 1049 - Remember to reset LP between runs
*/

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

#define MAXN 1000 // max # of variables
#define MAXC 1000 // max # of constraints
#define EPS  1e-8

using namespace std;

// This is the A, b, and c matrix you should populate before calling simplex().
// If an optimum solution was found, it is stored in x[] and has value "val".
double A[MAXC+1][MAXN+1], b[MAXC], c[MAXN], x[MAXN], y[MAXC], val;

// For internal use only.
int xB[MAXC], xN[MAXN];

/* Variable xB[r] exits the basis, xN[c] enters the basis.

  Comment: The fabs() check is not necessary for correctness (though, the i != r check is).
           However, it speeds it up a lot in sparse instances. For "roadtimes" removing
           that check increases the time from 0.41s to 2.51s.
*/
void pivot(int n, int m, int r, int c) {
  for (int j = 0; j <= n; ++j)
    if (j != c)
      A[r][j] /= A[r][c];

  for (int i = 0; i <= m; ++i)
    if (i != r && fabs(A[i][c]) > EPS)
      for (int j = 0; j <= n; ++j)
        if (j != c)
          A[i][j] -= A[r][j]*A[i][c];

  for (int i = 0; i <= m; ++i)
    if (i != r)
      A[i][c] = -A[i][c]/A[r][c];

  A[r][c] = 1/A[r][c];

  swap(xB[r], xN[c]);
}

// Bland's rule: if two indices are valid choices for the pivot, choose the
//               one with the lexicographically smallest variable
void bland(int a, int& b, int* v) {
  if (b < 0 || v[a] < v[b]) b = a;
}

/* Returns true if a feasible basis is found, false if LP is infeasible.

   Idea: Try the all-0 solution (i.e. basis where the x >= 0 constraints are tight).
         Repeatedly pivot out any row with a negative b-entry.

   I don't have a source in mind that proves this works, but come ask me if you want :)
*/
bool phase1(int n, int m) {
  // pivot while some b-value is negative
  while (true) {
    int r = -1, c = -1;

    for (int i = 0; i < m; ++i)
      if (A[i][n] < -EPS)
        bland(i, r, xB);

    if (r == -1) return true;

    for (int j = 0; j < n; ++j)
      if (A[r][j] < -EPS)
        bland(j, c, xN);

    if (c == -1) return false;

    pivot(n, m, r, c);
  }
}

/*
  Assumes A[i][n] >= 0 for all 0 <= i < m (i.e. current basis is feasible).

  Returns true if an optimum is found, false if the LP is unbounded.

  Currently uses Bland's rule. Should probably test other pivoting procedures.
*/
bool phase2(int n, int m) {
  // pivot until no improvement
  while (true) {
    int r = -1, c = -1;

    // find a column with negative c-coefficient
    // yes, it should be A[m][j] > EPS even though we said "negative",
    // this is because row A[m] is storing -c
    for (int j = 0; j < n; ++j)
      if (A[m][j] > EPS)
        bland(j, c, xN);

    if (c == -1) return true;

    for (int i = 0; i < m; ++i)
      if (A[i][c] > EPS) {
        if (r == -1) r = i;
        else {
          double lhs = A[i][c]*A[r][n], rhs = A[r][c]*A[i][n];
          if (lhs > rhs + EPS) r = i;
          else if (fabs(lhs-rhs) < EPS) bland(i, r, xB);
        }
      }

    if (r == -1) return false;

    pivot(n, m, r, c);
  }
}


/* Returns: 1 - opt found (x is this opt and val is its value)
            0 - infeasible, -1 - unbounded

   Two-phase simplex method.
*/
int simplex(int n, int m) {
  //add b to the end of A and c to the bottom of A
  for (int j = 0; j < n; ++j) {
    A[m][j] = c[j];
    xN[j] = j;
  }

  // prepare initial (possibly infeasible) basis
  for (int i = 0; i < m; ++i) {
    A[i][n] = b[i];
    xB[i] = i+n;
  }

  A[m][n] = 0; //this will be -(value of x)

  // now pivot to a feasible basis
  if (!phase1(n, m)) return 0;

  // and then pivot to an optimum basis
  if (!phase2(n, m)) return -1;

  // recover x and val
  val = -A[m][n];
  for (int i = 0; i < n; ++i) x[i] = 0;
  for (int i = 0; i < m; ++i) {
    if (xB[i] < n)
      x[xB[i]] = A[i][n];
  }

  for (int i = 0; i < n; ++i)
    if (xN[i] >= n)
    y[xN[i] - n] = -A[m][i];

  return 1;
}


int main() {
  //n = # vars, m = # constraints in Ax <= b (i.e. excluding x >= 0 constraints)
  int n, m;

  int leaves = 4;
  int k2 = 3;

  n = leaves+1;
  m = leaves+2;

  A[0][0] = 1;
  b[0] = 1;

  for (int i = 1; i < n; ++i) A[1][i] = 1;
  b[1] = k2;

  for (int i = 2; i < m; ++i) {
    A[i][0] = A[i][i-1] = -1;
    b[i] = -1;
  }

  c[0] = -1;
  for (int i = 1; i < n; ++i) c[i] = 1;

  // cutting planes!
  A[m][0] = -1;
  for (int i = 1; i < n; ++i) A[m][i] = 1;
  b[m] = -1;
  ++m;


  for (int i = 0; i <  n; ++i) cout << setw(5) << c[i] << ' '; cout << endl;
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) cout << setw(5) << A[j][i] << ' ';
    cout << b[j] << endl;
  }

  // cin >> n >> m;

  // for (int j = 0; j < n; ++j) cin >> c[j];
  //
  // for (int i = 0; i < m; ++i) {
  //   for (int j = 0; j < n; ++j)
  //     cin >> A[i][j];
  //   cin >> b[i];
  // }

  int result = simplex(n, m);

  if (result == -1)
    cout << "Unbounded" << endl;
  else if (result == 0)
    cout << "Infeasible" << endl;
  else {
    cout << "Optimal value: " << val << endl;
    cout << "x:";
    for (int i = 0; i < n; ++i) cout << ' ' << x[i];
    cout << endl;
  }

  cout << "Duals:" << endl;
  for (int i = 0; i < m; ++i) cout << setw(5) << y[i] << ' '; cout << endl;

  cout << endl;

  for (int j = 0; j <= m; ++j) {
    for (int i = 0; i < n; ++i) cout << setw(5) << A[j][i] << ' ';
    cout << b[j] << endl;
  }

  return 0;
}
