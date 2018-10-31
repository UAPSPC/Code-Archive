void rec_unrank_perm(int n, int k, long long r, vector<int> &id, vector<int> &pi) {
  if(k > 0) {
    swap(id[n - 1], id[r % n]);
    rec_unrank_perm(n - 1, k - 1, r / n, id, pi);
    pi.push_back(id[n - 1]);
    swap(id[n - 1], id[r % n]);
  }
}
// Returns a k-permutation corresponds to rank 'r' of n objects.
// 'id' should be a full identity permutation of size at least n
// and it remains the same at the end of the function
vector<int> unrank_perm(int n, int k, long long r, vector<int> &id) {
  vector<int> ans;
  rec_unrank_perm(n, k, r, id, ans);
  return ans;
}
long long rec_rank_perm(int n, int k, vector<int> &pirev, vector<int> &pi) {
  if(k == 0) return 0;
  int s = pi[k - 1];
  swap(pi[k - 1], pi[pirev[n - 1] - (n - k)]);
  swap(pirev[s], pirev[n - 1]);
  long long ans = s + n * rec_rank_perm(n - 1, k - 1, pirev, pi);
  swap(pirev[s], pirev[n - 1]);
  swap(pi[k - 1], pi[pirev[n - 1] - (n - k)]);
  return ans;
}
// Returns rank of the k-permutaion 'pi' of n objects.
// 'id' should be a full identity permutation of size at least n
// and it remains the same at the end of the function
long long rank_perm(int n, vector<int> &id, vector<int> pi) {
  for(int i = 0; i < pi.size(); i++) id[pi[i]] = i + n - pi.size();
  long long ans = rec_rank_perm(n, pi.size(), id, pi);
  for(int v: pi) id[v] = v;
  return ans;
}
