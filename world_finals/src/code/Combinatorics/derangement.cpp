// combinatorial: derangement
// count the number of permutations of n elements, such that no
// element appears in its original position math formula:
// derange(n)=ceil(factorial(n)/e+0.5), probability of
// derange(n)/factorial(n) converges to 0.36787944
const int maxN = 21;
long long derange[maxN];
long long cal_derange(int n) {
  derange[0] = 1;
  derange[1] = 0;
  for(int i = 2; i <= n; i++) derange[i] = (i - 1) * (derange[i - 1] + derange[i - 2]);
  return derange[n];
}
