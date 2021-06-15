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
  vector<vector<bool> > grid(H + 2, vector<bool>(W + 2));
  int count = 0;
  REP(i, 1, H + 1) {
    REP(j, 1, W + 1) {
      IN(char, c);
      if (c == '.') {
        grid.at(i).at(j) = true;
        count++;
      }
    }
  }

  vector<int> dx = {-1, 0, 1, 0};
  vector<int> dy = {0, 1, 0, -1};
  vector<vector<int> > dist(H + 2, vector<int>(W + 2));
  dist.at(1).at(1) = 1;
  queue<pair<int, int> > que;
  que.push({1, 1});
  while (!que.empty()) {
    auto [x, y] = que.front();
    que.pop();
    REP(i, dx.size()) {
      if (!grid.at(x + dx.at(i)).at(y + dy.at(i))) continue;
      if (dist.at(x + dx.at(i)).at(y + dy.at(i))) continue;
      dist.at(x + dx.at(i)).at(y + dy.at(i)) = dist.at(x).at(y) + 1;
      que.push({x + dx.at(i), y + dy.at(i)});
    }
  }

  if (dist.at(H).at(W)) cout << count - dist.at(H).at(W) << endl;
  else cout << "-1" << endl;

  return 0;
}
