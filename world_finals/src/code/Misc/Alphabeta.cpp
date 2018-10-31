int inf = 1e9;
struct state {
  int score() { return 0; } // TODO
  vector<node> children() { return {}; } // TODO
};
int ab(state s, int alpha = -inf, int beta = inf, int player = 1) {
  auto ch = s.children();
  if(ch.size() == 0) return s.score() * player; // if terminal
  int value = -inf;
  for(state c: ch) { // try best moves first!
    value = max(value, -ab(c, -beta, -alpha, -player));
    alpha = max(alpha, value);
    if(alpha >= beta) break;
  }
  return value;
}
