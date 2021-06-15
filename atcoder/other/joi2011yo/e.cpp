#pragma region Macros
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define REP2(i, n) for (int i = 0, i##_len = (int)(n); i < i##_len; ++i)
#define REP3(i, l, r) for (int i = (l), i##_len = (int)(r); i < i##_len; ++i)
#define GET_MACRO_REP(_1, _2, _3, NAME, ...) NAME
#define REP(...) GET_MACRO_REP(__VA_ARGS__, REP3, REP2) (__VA_ARGS__)
#define RREP2(i, n) for (int i = (n - 1); i >= 0; --i)
#define RREP3(i, l, r) for (int i = (r - 1), i##_len = (l); i >= i##_len; --i)
#define GET_MACRO_RREP(_1, _2, _3, NAME, ...) NAME
#define RREP(...) GET_MACRO_REP(__VA_ARGS__, RREP3, RREP2) (__VA_ARGS__)
#define IN(type, n) type n; cin >> n
#define INALL(type, v, s) vector<type> v(s); for (auto &e : v) { cin >> e; }
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())

#ifdef _DEBUG
#define DEBUG(x) cout << #x << ": " << x << endl
#else
#define DEBUG(x)
#endif

template<class T>bool chmax(T &a, const T &b) { if (a < b) { a = b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b < a) { a = b; return 1; } return 0; }
void yes() { cout << "Yes" << endl; }
void no() { cout << "No" << endl; }
#pragma endregion

int main() {
  IN(int, H);
  IN(int, W);
  IN(int, N);
  vector<vector<bool> > grid(H + 2, vector<bool>(W + 2));
  vector<pair<int, int> > facts(N + 1);
  REP(i, 1, H + 1) {
    REP(j, 1, W + 1) {
      IN(char, c);
      if (c == 'X') continue;
      if (c >= '1' && c <= '9') facts.at(c - '0') = make_pair(i, j);
      else if (c == 'S') facts.at(0) = make_pair(i, j);
      grid.at(i).at(j) = true;
    }
  }

  vector<int> dx = {-1, 0, 0, 1};
  vector<int> dy = {0, -1, 1, 0};
  int ans = 0;
  REP(n, N) {
    vector<vector<int> > dist(H + 2, vector<int>(W + 2, -1));
    dist.at(facts.at(n).first).at(facts.at(n).second) = 0;
    queue<pair<int, int> > que;
    que.push(facts.at(n));
    while (!que.empty()) {
      auto [x, y] = que.front();
      que.pop();
      REP(i, dx.size()) { 
        if (grid.at(x + dx.at(i)).at(y + dy.at(i)) && dist.at(x + dx.at(i)).at(y + dy.at(i)) == -1) {
          dist.at(x + dx.at(i)).at(y + dy.at(i)) = dist.at(x).at(y) + 1;
          que.push(make_pair(x + dx.at(i), y + dy.at(i)));
        }
      }
    }
    ans += dist.at(facts.at(n + 1).first).at(facts.at(n + 1).second);
  }

  cout << ans << endl;

  return 0;
}
