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
  IN(int, R);
  IN(int, C);
  IN(int, sx);
  IN(int, sy);
  IN(int, gx);
  IN(int, gy);
  sx--; sy--; gx--; gy--;

  vector<vector<bool> > grid(R, vector<bool>(C));
  REP(i, R) {
    REP(j, C) {
      IN(char, c);
      grid.at(i).at(j) = (c == '.');
    }
  }

  vector<vector<int> > dist(R, vector<int>(C, -1));
  dist.at(sx).at(sy) = 0;
  queue<pair<int, int> > que;
  que.push(make_pair(sx, sy));
  while(!que.empty()) {
    auto [x, y] = que.front();
    que.pop();
    if (grid.at(x - 1).at(y) && dist.at(x - 1).at(y) == -1) {
      dist.at(x - 1).at(y) = dist.at(x).at(y) + 1;
      que.push(make_pair(x - 1, y));
    }
    if (grid.at(x).at(y - 1) && dist.at(x).at(y - 1) == -1) {
      dist.at(x).at(y - 1) = dist.at(x).at(y) + 1;
      que.push(make_pair(x, y - 1));
    }
    if (grid.at(x).at(y + 1) && dist.at(x).at(y + 1) == -1) {
      dist.at(x).at(y + 1) = dist.at(x).at(y) + 1;
      que.push(make_pair(x, y + 1));
    }
    if (grid.at(x + 1).at(y) && dist.at(x + 1).at(y) == -1) {
      dist.at(x + 1).at(y) = dist.at(x).at(y) + 1;
      que.push(make_pair(x + 1, y));
    }
  }

  cout << dist.at(gx).at(gy) << endl;

  return 0;
}
