// binomial coefficient C(n,k)
long long Cdp[51][51]; // memset to -1
long long C(int n, int k) {
  if(Cdp[n][k] != -1) return Cdp[n][k];
  return Cdp[n][k] = (k == 0 || k == n ? 1 : C(n - 1, k - 1) + C(n - 1, k));
}
