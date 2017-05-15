// f: The function we compute the transform of.
// n: The dimension of the function f.
// s: The skip value, should be set to 1 at the start of the algorithm.
// r: An n'th primitive root of unity.
// o: The vector we want to load the output values into.
using cld = complex<long double>;
void fft(vector<cld> &f, long long fb, long long n, long long s, vector<cld> &o, long long ob, cld r) {
  if(n == 1)
    o[ob] = f[fb];
  else {
    fft(f, fb, n / 2, 2 * s, o, ob, pow(r, 2));
    fft(f, fb + s, n / 2, 2 * s, o, ob + n / 2, pow(r, 2));
    for(int k = 0; k < n / 2; k++) {
      auto x = o[ob + k];
      o[ob + k] = (x + pow(r, k) * o[ob + k + n / 2]) / 2.0L;
      o[ob + k + n / 2] = (x - pow(r, k) * o[ob + k + n / 2]) / 2.0L;
    }
  }
}
vector<cld> fft(vector<cld> &f) {
  long long n = f.size();
  cld r(cos(-2 * M_PI / n), sin(-2 * M_PI / n));
  vector<cld> o(n);
  fft(f, 0, n, 1, o, 0, r);
  return o;
}
vector<cld> inversefft(vector<cld> &f) {
  long long n = f.size();
  for(int k = 0; k < n; k++) f[k] = conj(f[k]);
  vector<cld> o = fft(f);
  for(int k = 0; k < n; k++) f[k] = conj(f[k]);
  for(int k = 0; k < n; k++) o[k] = ((long double)n) * conj(o[k]);
  return o;
}
