// Returns the sum of all positive divisors for a positive integer N
// WARNING: check if usage of `pow` is ok.
long long sum_divisors(long long n) {
  long long res = 1;
  for(int i = 2; i*i <= n; i++) {
    int count = 0;
    for(; n % i == 0; count++) n /= i;
    if(count) res *= (pow(i, count+1)-1)/(i-1);
  }
  if(n > 1) res *= (pow(n, 2)-1)/(n-1);
  return res;
}
