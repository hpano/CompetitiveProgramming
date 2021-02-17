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
#define INALL(v) for (auto &e : v) { cin >> e; }
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
  int count = 0;
  vector<vector<bool> > grid(H, vector<bool>(W, false));
  REP(i, H) {
    REP(j, W) {
      IN(char, tmp);
      if (tmp == '#') {
        grid.at(i).at(j) = true;
        count++;
      }
    }
  }

  int ans = count * 4;

  REP(i, H) {
    REP(j, W) {
      if (grid.at(i).at(j)) {
        if (grid.at(i - 1).at(j)) {
          ans -= 2;
          if (!grid.at(i).at(j - 1) && !grid.at(i - 1).at(j - 1)) ans--;
          if (!grid.at(i).at(j + 1) && !grid.at(i - 1).at(j + 1)) ans--;
        }
        if (grid.at(i).at(j - 1)) {
          ans -= 2;
          if (!grid.at(i - 1).at(j) && !grid.at(i - 1).at(j - 1)) ans--;
          if (!grid.at(i + 1).at(j) && !grid.at(i + 1).at(j - 1)) ans--;
        }
      }
    }
  }

  cout << ans << endl;

  return 0;
}
