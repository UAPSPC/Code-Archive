// Returns half of length of largest palindrome centered at
// every position in the string
// Add \0 at start, end, and middle to handle palindromes between
// characters + get length of largest palindrome at each index.
// Then, int characterBefore = i / 2; int lenToStart = P[i] / 2;
// int lenToEnd = lenToStart - (i % 2 == 0);
vector<int> manacher(string s) {
  vector<int> ans(s.size(), 0);
  int maxi = 0;
  for(int i = 1; i < s.size(); i++) {
    int k = 0;
    if(maxi + ans[maxi] >= i) k = min(ans[maxi] + maxi - i, ans[2 * maxi - i]);
    for(; s[i + k] == s[i - k] && i - k >= 0 && i + k < s.size(); k++)
      ;
    ans[i] = k - 1;
    if(i + ans[i] > maxi + ans[maxi]) maxi = i;
  }
  return ans;
}
