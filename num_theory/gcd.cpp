/*
    Greatest common divisor of two nonnegative integers.

    Author: Zac Friggstad

    For nonnegative integers a,b, gcd(a,b) is the largest integer
    that divides both a and b. By convension gcd(0,0) = 0.

    Two different implementations are present here. Both work just fine.

    Running time of both: O(log(a) + log(b))

    Reliability: UVA 11417
*/

#include <algorithm>

using namespace std;

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

int gcd_iterative(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
