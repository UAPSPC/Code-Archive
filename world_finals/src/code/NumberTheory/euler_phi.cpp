// Returns the number of positive integers less than N that are
// relatively prime to N. WARNING: check if usage of `pow` is ok.
long long phi(long long n) {
  long long res = 1;
  for(int i = 2; i * i <= n; i++) {
    int count = 0;
    for(; n % i == 0; count++) n /= i;
    if(count) res *= pow(i, count) - pow(i, count - 1);
  }
  if(n > 1) res *= n - 1;
  return res;
}
