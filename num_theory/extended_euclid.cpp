/*
    Extended Euclidean Algortihm

    Author: Zac Friggstad

    1) Given nonnegative integers a, b:
    gcd_ex(a, b, s, t) returns g = gcd(a,b) and sets s,t such that a*s + b*t = g
    Guaranteed all intermediate values in the calculation are <= max(a, b)

    2) Given arbitrary integers a, b:
    gcd_ex_any(a, b, s, t) returns g = gcd(|a|, |b|) and sets s, t such that
    a*s + b*t = g
    Guaranteed all intermediate values in the calculation are <= max(|a|, |b|)

    Running time of both: O(log(a) + log(b))

    Reliability: UVa 10104
*/

#include <algorithm>
#include <cstdlib>

using namespace std;

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

int gcd_ex_any(int a, int b, int& s, int& t) {
    int g = gcd_ex(abs(a), abs(b), s, t);
    if (a < 0) s = -s;
    if (b < 0) t = -t;

    return g;
}
