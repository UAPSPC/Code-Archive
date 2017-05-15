// The Euler Phi function returns the number of
// positive integers less than N that are relatively
// prime to N. O(sqrt(n))
int phi(int n) {
  int i, count, res = 1;
  for(i = 2; i * i <= n; i++) {
    count = 0;
    while(n % i == 0) {
      n /= i;
      count++;
    }
    if(count > 0) res *= (pow(i, count) - pow(i, count - 1));
  }
  if(n > 1) res *= (n - 1);
  return res;
}
