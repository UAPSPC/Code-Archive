/*  Author: Noah Weninger, 2018

    Tests if a 64-bit number is prime using the deterministic Miller-Rabin
    algorithm. This requires use of the __uint128_t numeric type, which is
    nonstandard and might not be supported by every compiler.

    Complexity: O(log n) with a relatively large constant

    Reference:
    https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Deterministic_variants_of_the_test

    Reliability:
    primes2 - Open Kattis
    psuedoprime - Open Kattis
*/

#include<initializer_list>
#include<cstdint>
#include<iostream>
using namespace std;

using u128 = __uint128_t;
u128 powmod(u128 b, u128 e, u128 m) {
    u128 res = 1;
    for (b %= m; e; e >>= 1) {
        if (e&1) res = res*b%m;
        b = b*b%m;
    }
    return res;
}
bool is_prime(uint64_t n) {
    if (n < 2) return false;
    u128 d = n-1, r = 0;
    while (d%2 == 0) r++, d /= 2;
    for (u128 a : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (a > n-2) break;
        u128 x = powmod(a, d, n);
        if (x == 1 || x == n-1) continue;
        for (u128 j = 0; r && j < r-1; j++) {
            x = x*x%n;
            if (x == n-1) goto next;
        }
        return false;
    next:;
    }
    return true;
}
int main() {
    uint64_t n;
    while(cin >> n) {
        cout << (is_prime(n) ? "prime" : "composite") << endl;
    }
}
