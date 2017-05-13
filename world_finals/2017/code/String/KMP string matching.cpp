// Given strings t and p, return the indices of t where p occurs
// as a substring
vector<int> compute_prefix(string s) {
  vector<int> pi(s.size(), -1);
  int k = -1;
  for(int i = 1; i < s.size(); i++) {
    while(k >= 0 && s[k + 1] != s[i]) k = pi[k];
    if(s[k + 1] == s[i]) k++;
    pi[i] = k;
  }
  return pi;
}
vector<int> kmp_match(string t, string p) {
  vector<int> pi = compute_prefix(p);
  vector<int> shifts;
  int m = -1;
  for(int i = 0; i < t.size(); i++) {
    while(m > -1 && p[m + 1] != t[i]) m = pi[m];
    if(p[m + 1] == t[i]) m++;
    if(m == p.size() - 1) {
      shifts.push_back(i + 1 - p.size());
      m = pi[m];
    }
  }
  return shifts;
}
