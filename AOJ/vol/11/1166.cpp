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
  while (true) {
    IN(int, w);
    IN(int, h);
    if (w == 0 && h == 0) break;
    vector<vector<bool> > walls(h * 2 + 1, vector<bool>(w + 1, true));

    REP(i, 1, h * 2) {
      if (i % 2) {
        REP(j, 1, w) {
          IN(bool, c);
          walls[i][j] = c;
        }
      } else {
        REP(j, w) {
          IN(bool, c);
          walls[i][j] = c;
        }
      }
    }

    vector<vector<int> > dist(h, vector<int>(w, 0));
    dist[0][0] = 1;
    queue<pair<int, int> > que;
    que.push({0, 0});
    while(!que.empty()) {
      auto [x, y] = que.front();
      que.pop();
      if (!walls[x * 2][y]) {
        if (!dist[x - 1][y]) {
          dist[x - 1][y] = dist[x][y] + 1;
          que.push(make_pair(x - 1, y));
        }
      }
      if (!walls[x * 2 + 1][y + 1]) {
        if (!dist[x][y + 1]) {
          dist[x][y + 1] = dist[x][y] + 1;
          que.push(make_pair(x, y + 1));
        }
      }
      if (!walls[(x + 1) * 2][y]) {
        if (!dist[x + 1][y]) {
          dist[x + 1][y] = dist[x][y] + 1;
          que.push(make_pair(x + 1, y));
        }
      }
      if (!walls[x * 2 + 1][y]) {
        if (!dist[x][y - 1]) {
          dist[x][y - 1] = dist[x][y] + 1;
          que.push(make_pair(x, y - 1));
        }
      }
    }

    cout << dist[h - 1][w - 1] << endl;
  }

  return 0;
}
