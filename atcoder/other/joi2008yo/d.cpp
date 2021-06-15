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
  IN(int, m);
  IN(int, baseX);
  IN(int, baseY);
  vector<pair<int, int> > places(m - 1);
  REP(i, m - 1) {
    IN(int, x);
    IN(int, y);
    places.at(i) = make_pair(x - baseX, y - baseY);
  }

  IN(int, n);
  map<pair<int, int>, bool> grid;
  vector<pair<int, int> > stars(n);
  REP(i, n) {
    IN(int, x);
    IN(int, y);
    grid[make_pair(x, y)] = true;
    stars.at(i) = make_pair(x, y);
  }

  for (auto const &[x, y] : stars) {
    bool ok_flag = true;
    for (auto const &[px, py] : places) {
      if (x + px < 0 || x + px > 1000000 || y + py < 0 || y + py > 1000000 || !grid[make_pair(x + px, y + py)]) {
        ok_flag = false;
        break;
      }
    }
    if (ok_flag) {
      cout << x - baseX << " " << y - baseY << endl;
      break;
    }
  }

  return 0;
}
