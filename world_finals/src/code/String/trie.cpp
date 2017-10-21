// This Trie is designed for returning the longest
// substring that appears more than once in a string
struct TrieNode {
  int cnt;
  map<char, TrieNode *> child;
  TrieNode() { cnt = 0; }
};
// Need to initialize each time after calling deleteTrie
TrieNode *root = NULL;
string resultString = "";
int resultCnt = 0;
// start is the start point in s
void insertTrie(string &s, int start) {
  if(root == NULL) root = new TrieNode;
  TrieNode *current = root;
  for(int i = start; i < s.size(); i++) {
    if(current->child[s[i]] == NULL) current->child[s[i]] = new TrieNode;
    current->child[s[i]]->cnt++;
    current = current->child[s[i]];
  }
}
// string tmp="";findLongest(root,tmp);
void findLongest(TrieNode *current, string &s) {
  for(auto c : current->child)
    if(c.second->cnt > 1) {
      s.push_back(c.first);
      findLongest(c.second, s);
      s.pop_back();
    }
  if(s.size() > resultString.size()) {
    resultString = s;
    resultCnt = current->cnt;
  }
}
void deleteTrie(TrieNode *current) {
  if(current == NULL) return;
  for(auto c : current->child) deleteTrie(c.second);
  delete current;
}
