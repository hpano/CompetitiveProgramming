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

tuple<int, int, int, int, int, int, int, int> get_candi(pair<int, int> p1, pair<int, int> p2) {
  int x1 = p1.first + (p1.second - p2.second);
  int y1 = p1.second + (p2.first - p1.first);
  int x2 = p2.first + (p1.second - p2.second);
  int y2 = p2.second + (p2.first - p1.first);
  int x3 = p1.first - (p1.second - p2.second);
  int y3 = p1.second - (p2.first - p1.first);
  int x4 = p2.first - (p1.second - p2.second);
  int y4 = p2.second - (p2.first - p1.first);
  if (x1 < 0 || x1 > 5000) x1 = 5001;
  if (y1 < 0 || y1 > 5000) y1 = 5001;
  if (x2 < 0 || x2 > 5000) x2 = 5001;
  if (y2 < 0 || y2 > 5000) y2 = 5001;
  if (x3 < 0 || x3 > 5000) x3 = 5001;
  if (y3 < 0 || y3 > 5000) y3 = 5001;
  if (x4 < 0 || x4 > 5000) x4 = 5001;
  if (y4 < 0 || y4 > 5000) y4 = 5001;

  return {x1, y1, x2, y2, x3, y3, x4, y4};
}

int calc(pair<int, int> p1, pair<int, int> p2) {
  return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}

int main() {
  IN(int, n);
  vector<pair<int, int> > poles(n);
  vector<vector<bool> > grid(5002, vector<bool>(5002));
  REP(i, n) {
    IN(int, x);
    IN(int, y);
    poles.at(i) = make_pair(x, y);
    grid.at(x).at(y) = true;
  }

  int ans = 0;
  REP(i, n - 1) {
    REP(j, i + 1, n) {
      auto [x1, y1, x2, y2, x3, y3, x4, y4] = get_candi(poles.at(i), poles.at(j));
      if ((grid.at(x1).at(y1) && grid.at(x2).at(y2)) || (grid.at(x3).at(y3) && grid.at(x4).at(y4))) {
        chmax(ans, calc(poles.at(i), poles.at(j)));
      }
    }
  }

  cout << ans << endl;

  return 0;
}
