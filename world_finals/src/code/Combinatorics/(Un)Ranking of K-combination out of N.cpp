const int maxn = 100;
const int maxk = 10;
// combination[i][j] = j!/(i!*(j-i)!)
long long combination[maxk][maxn];
long long cumsum[maxk][maxn];
void initialize() { //~O(nk)
  memset(combination, 0, sizeof combination);
  for(int i = 0; i < maxn; i++) combination[0][i] = 1;
  for(int i = 1; i < maxk; i++)
    for(int j = 1; j < maxn; j++) combination[i][j] = combination[i][j - 1] + combination[i - 1][j - 1];
  for(int i = 0; i < maxk; i++) cumsum[i][0] = combination[i][0];
  for(int i = 0; i < maxk; i++)
    for(int j = 1; j < maxn; j++) cumsum[i][j] = cumsum[i][j - 1] + combination[i][j];
}
// Returns rank of the given combination 'c' of n objects.
long long rank_comb(int n, vector<int> c) {
  long long ans = 0;
  int prev = -1;
  sort(c.begin(), c.end()); // comment this if it is sorted
  for(int i = 0; i < c.size(); i++) {
    ans += cumsum[c.size() - i - 1][n - prev - 2] - cumsum[c.size() - i - 1][n - c[i] - 1];
    prev = c[i];
  }
  return ans;
}
struct comp {
  long long base;
  int operator()(long long a, long long val) { return (base - a) > val; }
};
// Returns k-combination of rank 'r' of n objects
vector<int> unrank_comb(int n, int k, long long r) {
  vector<int> c;
  int prev = -1;
  for(int i = 0; i < k; i++) {
    int j = k - i - 1;
    long long base = cumsum[j][n - prev - 2];
    prev = n - 1 - (lower_bound(cumsum[j], cumsum[j] + n - prev - 1, r, comp{base}) - cumsum[j]);
    r -= base - cumsum[j][n - prev - 1];
    c.push_back(prev);
  }
  return c;
}
