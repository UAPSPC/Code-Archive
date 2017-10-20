/* Author: Zachary Friggstad, 2017

   The standard FFT of a sequence.
   Given n = 2^k complex numbers a[i], i=0...n-1 r, this will compute all n
   values \sum_i a[i]*zeta^{i+j} for j=0...n-1 in O(n * log(n)) time where
   zeta = exp(2 \pi i / n) is the standard n'th root of unity.

   Multiplication of polynomials.
   Given two polynomials f,g, will compute the product f*g
   in O(n * log(n)) time where n = max(deg(f), deg(g)).

   This is a numerical algorithm, in the sense calculations are performed
   with doubles and may be very slightly off, but I suspect it will not be an
   issue in any contest problem that requires FFT.

   Use:
   fft(f, v, invert):
    - f is a vector of complex values of size 2^k for some k
    - v is a vector of complex values that stores the result
    - invert is a boolean indicating if we should compute the fft or inverse fft of f

   multiply(f, g, res):
    - f, g are two vectors of complex values representing polynomials
      e.g. to represent x^3 - 3x + 7 the corresponding vector is {7, -3, 0, 1}
      (each being a "complex" type) where 7 has index 0 and 1 has index 3 (the degree)
    - res is a complex vector that will store the result

   Note:
    - f and g do not need to have sizes being powers of 2
    - after, we will have res.size() = f.size() + g.size() - 2
    - if f and g have leading 0s, then so will res

   Reference:
   Introduction to Algorithms by Cormen, Lieserson, Rivest, and Stein
   This is the "iterative" version that does not use recursion.

   Reliability:
   kinversions - Open Kattis
   tiles - icpc.kattis.com (World Finals 2015)
   polymul2 - Open Kattis
   matchings - Open Kattis
*/


#include <iostream>
#include <complex>
#include <vector>
#include <cassert>

using namespace std;

typedef double ld; // can always try long double if you are concerned
typedef complex<ld> cplx;
typedef vector<cplx> vc;
typedef vector<int> vi;

/* Compute the fft of f, store in v.
   invert will compute the inverse of the fft.

   f.size() *MUST* be a power of 2

   In particular, the regular fft (invert == false) will not normalize by
   1/f.size() but reverse fft (invert == true) will normalize. This is the easiest
   approach for convolution/polynomial multiplication.
*/
void fft(const vc& f, vc& v, bool invert) {
    int n = f.size();
    assert(n > 0 && (n&(n-1)) == 0);
    v.resize(n);

    for (int i = 0; i < n; ++i) {
        int r = 0, k = i;
        for (int j = 1; j < n; j <<= 1, r = (r<<1)|(k&1), k >>= 1);
        v[i] = f[r];
    }

    for (int m = 2; m <= n; m <<= 1) {
        int mm = m>>1;
        cplx zeta = polar<ld>(1, (invert?2:-2)*M_PI/m);
        for (int k = 0; k < n; k += m) {
            cplx om = 1;
            for (int j = 0; j < mm; ++j, om *= zeta) {
                cplx tl = v[k+j], th = om*v[k+j+mm];
                v[k+j] = tl+th;
                v[k+j+mm] = tl-th;
            }
        }
    }
    if (invert) for (auto& z : v) z /= ld(n);
}

/* Multiply polynomials f and g. Equivalently, compute the convolution of
   the sequences f[0], ..., f[df] and g[0], ..., g[dg]).

   IMPORTANT: if f is the zero polynomial, should still have a 0 entry (i.e.
   f.size() > 0 should always hold). Same for g.

   res - holds the results: the coefficients from res[0] to res[df+dg].

   Can use f = g (reference to same vector) safely.
   f,g are not constant because they are padded with 0s, but then are reverted
   to their original form again.
*/
void multiply(vc& f, vc& g, vc& res) {
    int df = f.size()-1, dg = g.size()-1;

    assert(df >= 0 && dg >= 0);

    int n = df+dg+1;
    while (n&(n-1)) ++n;

    f.resize(n,0);
    g.resize(n,0);
    vc tmp;

    fft(f, tmp, false);
    fft(g, res, false);

    for (int i = 0; i < n; ++i) tmp[i] *= res[i];

    fft(tmp, res, true);

    f.resize(df+1);
    g.resize(dg+1);
    res.resize(df+dg+1);
}

int main() {
    int df, dg;
    cout << "This test will multiply two polynomials with real coefficients\n"
         << "First enter the degrees of f and g, respectively: ";
    cin >> df >> dg;

    vc f(df+1), g(dg+1), res;

    cout << "Now the " << df+1 << " coefficients of f, starting with the leading term\n"
         << "e.g. enter -3*x^3 + 2x + 1 as -3 0 2 1\n";
    for (int i = df; i >= 0; --i) {
        ld x;
        cin >> x;
        f[i] = cplx(x);
    }
    cout << "Same for g\n";
    for (int i = dg; i >= 0; --i) {
        ld x;
        cin >> x;
        g[i] = cplx(x);
    }

    multiply(f, g, res);

    cout << "Coefficients, starting with the leading term\n";
    for (int i = df+dg; i >= 0; --i)
        cout << res[i].real() << (i?' ':'\n');

    return 0;
}
