/* C++: Knuth-Morris-Pratt (KMP) string matching algorithm
   =================================================================
   Description

   Complexity (m = length of pattern, n = length of text)
   Algorithm  | Pre-processing time  | Matching time
   -----------+----------------------+------------------------------
   Naive      | 0                    | O((n+m+1)m)
   KMP        | O(m)                 | O(n)

   -----------------------------------------------------------------
   Author       Leland Jansen
   Date         November 5, 2016
   References   T. H. Cormen, C. E. Leiserson, R. L. Rivest, and
                  C. Stein, Introduction to Algorithms, 3rd ed.
                  Cambridge, MA: Massachusetts Institute of
                  Technology, 2009.
   -----------------------------------------------------------------
   Reliability  UNKNOWN!!!
                If you test this code, please report back.
                
   Notes        Returns the string index at which the pattern is
                  first matched or -1 if the patten cannot be
                  matched.
                Assumes length of pattern and length of text do not
                  exceed the size of an integer.
*/

#include <iostream>
#include <vector>


int NaiveMatch(std::string &text, std::string &pattern) {
  if (text.empty() || pattern.empty()) return -1;
  for (int i = 0; i < text.size() - pattern.size() + 1; ++i) {
    for (int j = 0; j < pattern.size(); ++j) {
      if (text[i+j] != pattern[j]) break;
      if (j == pattern.size() - 1) return i;
    }
  }
  return -1;
}


std::vector<int> GeneratePrefixTable(std::string &pattern) {
  std::vector<int> prefix(pattern.size(), -1);
  int k = -1;
  for (int q = 1; q < pattern.size(); ++q) {
    while (-1 < k && pattern[k+1] != pattern[q]) k = prefix[k];
    if (pattern[k+1] == pattern[q]) ++k;
    prefix[q] = k;
  }
  return prefix;
}


int KmpMatch(std::string &text, std::string &pattern) {
  std::vector<int> prefix = GeneratePrefixTable(pattern);
  int q = -1;
  for (int i = 0; i < text.size(); ++i) {
    while (-1 < q && pattern[q+1] != text[i]) q = prefix[q];
    if (pattern[q+1] == text[i]) ++q;
    if (q == pattern.size()-1) return i-(int)pattern.size()+1;
  }
  return -1;
}


int main() {
  std::string pattern { "ababaca" },
      text { "bacbababaabcbabababacabababaab" };
  int match_index = KmpMatch(text, pattern);

  std::cout << "Pattern found in text at index "
            << match_index << "\n" << text << "\n";
  for (int i = 0; i < match_index; ++i) std::cout << " ";
  std::cout << pattern << std::endl;

  return 0;
}
