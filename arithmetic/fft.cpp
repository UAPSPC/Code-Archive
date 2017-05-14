#include <iostream>
#include <cstdio>
#include <complex>
#include <cmath>
#include <vector>

using namespace std;

/* C++: Discrete Fast Fourier Transform
   ====================================
   Description: Given a function f: {0,...,n-1} -> C into the complex numbers, we
   can write the function uniquely as f(x) = Sum_{k = 0}^{n-1} ak z^k, where
   z = e^{2pi i/n}. The function fft takes an input function f (as a vector of
   complex numbers), and returns the values a0,...,a{n-1} in a vector. Conversely,
   the inversefft function takes the valuesa0,...,a{n-1}, and returns the function f.

   The Fourier transform is useful whenever we want to compute a convolution,
   which is a function h: {0,...,n-1} -> C defined in terms of two other functions
   f and g by h(m) = Sum_{k = 0}^{n-1} f(m) g(k-m), where the values of m and k-m
   are considered modulo n. If we write f = Sum ak z^k, g = Sum bk z^k, and h = Sum ck z^k,
   then we find ck = ak*zk, so that we can compute h = inversefft(fft(f)*fft(g)) in O(n log(n))
   time, rather than the naive O(n^2) time.

   Complexity: O(n log(n)), where n is the size of the domain of the input function.
   ------------------------
   Author: Jacob Denson
   Date: May 14, 2017
   References: Essentially transliterated from
   https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm,
   aside from the bugs in the psuedocode on that page. For a good
   explanation of the algorithm, see Stein and Shakarchi, Vol 1. Chapter 7.
   ------------------------
   Reliability: 0 (But I have written tests, see below. Could be tested on the
   ABABA problem from NAIPC 2016, I think - Ask Zac for more info).
   Notes: Watch out for standard floating point inaccuracies, etc. This code
   only works if your function is defined on a domain of length [n], where
   n is a power of 2.
*/

// f: The function we compute the transform of.
// n: The dimension of the function f.
// s: The skip value, which should be set to 1 at the start of the algorithm.
// r: An n'th primitive root of unity.
// o: The vector we want to load the output values into.
void fft(vector<complex<long double>>& f, long long fb, long long n, long long s,
    vector<complex<long double>>& o, long long ob, complex<long double> r) {
    if (n == 1) o[ob] = f[fb];

    else {
        fft(f, fb, n/2, 2*s, o, ob, pow(r,2));
        fft(f, fb + s, n/2, 2*s, o, ob + n/2, pow(r,2));

        for (int k = 0; k < n/2; k++) {
            auto x = o[ob + k];
            o[ob + k] = (x + pow(r,k)*o[ob + k + n/2])/2.0L;
            o[ob + k + n/2] = (x - pow(r,k)*o[ob + k + n/2])/2.0L;
        }
    }
}

vector<complex<long double>> fft(vector<complex<long double>>& f) {
    long long n = f.size();
    complex<long double> r(cos(-2*M_PI/n), sin(-2*M_PI/n));
    vector<complex<long double>> o(n);
    fft(f,0,n,1,o,0,r);
    return o;
}

vector<complex<long double>> inversefft(vector<complex<long double>>& f) {
    long long n = f.size();

    for (int k = 0; k < n; k++) f[k] = conj(f[k]);

    vector<complex<long double>> o = fft(f);

    for (int k = 0; k < n; k++) f[k] = conj(f[k]);
    for (int k = 0; k < n; k++) o[k] = ((long double) n)*conj(o[k]);

    return o;
}











void print_complex(vector<complex<long double>> lst) {
    for (auto x: lst) { cout << x << endl; }
    cout << endl;
}

int main() {
    // Test 1: Fourier transform of {1,0} is {1/2,1/2}
    cout << "Test 1: " << endl;
    vector<complex<long double>> test1 = {1,0};
    print_complex(test1);

    auto output1 = fft(test1);
    print_complex(output1);

    auto inverse1 = inversefft(output1);
    print_complex(inverse1);

    // Test 2: Fourier transform of {3,0,...,0} is {3/8,3/8,...,3/8}.
    cout << "Test 2: " << endl;
    vector<complex<long double>> test2 = {3,0,0,0,0,0,0,0};
    print_complex(test2);
    auto output2 = fft(test2);
    print_complex(output2);
    auto inverse2 = inversefft(output2);
    print_complex(inverse2);

    // Test 3: Fourier transform of {0,0,...,0} is {0,0,...,0}
    cout << "Test 3: " << endl;
    vector<complex<long double>> test3 = {0,0,0,0};
    print_complex(test3);
    auto output3 = fft(test3);
    print_complex(output3);
    auto inverse3 = inversefft(output3);
    print_complex(inverse3);

    // Test 4: Fourier transform of {1,1,1,1} is {1,0,0,0}
    cout << "Test 4: " << endl;
    vector<complex<long double>> test4 = {1,1,1,1};
    print_complex(test4);
    auto output4 = fft(test4);
    print_complex(output4);
    auto inverse4 = inversefft(output4);
    print_complex(inverse4);

    // Test 5: Fourier transform of {0,1,0,0,0,0,0,0} is
    // {0.125, 0.88 - 0.88i, -0.125i, -0.88-0.88i, -0.125,-0.088+0.088i, 0.125i, 0.088+0.088i}
    cout << "Test 5: " << endl;
    vector<complex<long double>> test5 = {0,1,0,0,0,0,0,0};
    print_complex(test5);
    auto output5 = fft(test5);
    print_complex(output5);
    auto inverse5 = inversefft(output5);
    print_complex(inverse5);
}