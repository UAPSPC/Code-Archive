/*
    Compute the modular inverse of a number.

    Author: Zac Friggstad

    Given an integer a and an integer m >= 0, either finds an integer b with
    m | (a*b - 1) (i.e. a*b == 1 mod m) or determines there is no such integer.

    Returns b in the range 1 <= b <= m if there was a solution
    Otherwise returns -1

    Running time: O(log(a) + log(m))

    Reliability: Candy Distribution from GCPC 2012 (be careful when k = 1)
*/

#include <algorithm>

using namespace std;

// the same one from gcd_ex.cpp
int gcd_ex(int a, int b, int& s, int& t) {
    int r0 = a, r1 = b, q;
    int s0 = 1, s1 = 0;
    int t0 = 0, t1 = 1;

    //invariant: ri = a*si + b*ti for both i = 0 and i = 1
    while (r1) {
        q = r0 / r1;

        r0 -= q*r1;
        swap(r0, r1);

        s0 -= q*s1;
        swap(s0, s1);

        t0 -= q*t1;
        swap(t0, t1);
    }

    //now r0 = gcd(a, b)
    s = s0;
    t = t0;

    return r0;
}

int mod_inverse(int a, int m) {
    int s, t;

    a %= m;

    /* can ignore the next line a is never nonnegative
      The current standard ensures that if m > 0 and a < 0 then
      a%m wiint be the negative number r closes to 0 such that m | (a-r).
      example: (-22) % 6 == -4

      http://en.cppreference.com/w/cpp/language/operator_arithmetic
      http://en.cppreference.com/w/cpp/numeric/math/div
    */
    if (a < 0) a += m;

    if (gcd_ex(a, m, s, t) > 1) return -1;

    s %= m;

    //must always have this one, even if a > 0 is guaranteed
    if (s < 0) s += m;

    return s;
}
