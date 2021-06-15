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

int dfs(vector<vector<bool> > &grid, vector<vector<bool> > checked, int h, int w) {
  if (!grid.at(h).at(w) || checked.at(h).at(w)) return 0;
  checked.at(h).at(w) = true;
  int count = 0;
  chmax(count, dfs(ref(grid), checked, h - 1, w));
  chmax(count, dfs(ref(grid), checked, h, w - 1));
  chmax(count, dfs(ref(grid), checked, h, w + 1));
  chmax(count, dfs(ref(grid), checked, h + 1, w));
  count++;

  return count;
}

int main() {
  IN(int, m);
  IN(int, n);
  vector<vector<bool> > grid(n + 2, vector<bool>(m + 2));
  REP(i, 1, n + 1) {
    REP(j, 1, m + 1) {
      IN(bool, c);
      grid.at(i).at(j) = c;
    }
  }

  vector<vector<bool> > checked(n + 2, vector<bool>(m + 2));
  int ans = 0;
  REP(i, 1, n + 1) {
    REP(j, 1, m + 1) {
      if (!grid.at(i).at(j)) continue;
      chmax(ans, dfs(ref(grid), checked, i, j));
    }
  }

  cout << ans << endl;

  return 0;
}
