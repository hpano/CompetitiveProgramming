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

void dfs(vector<vector<bool> > &grid, vector<vector<bool> > &checked, int h, int w) {
  REP(i, h - 1, h + 2) {
    REP(j, w - 1, w + 2) {
      if (!grid.at(i).at(j)) continue;
      if (!checked.at(i).at(j)) {
        checked.at(i).at(j) = true;
        dfs(ref(grid), ref(checked), i, j);
      }
    }
  }
}

int main() {
  while (true) {
    IN(int, w);
    IN(int, h);
    if (w == 0 && h == 0) break;

    vector<vector<bool> > grid(h + 2, vector<bool>(w + 2, false));
    REP(i, 1, h + 1) {
      REP(j, 1, w + 1) {
        IN(bool, c);
        grid.at(i).at(j) = c;
      }
    }

    vector<vector<bool> > checked(h + 2, vector<bool>(w + 2, false));
    int count = 0;
    REP(i, 1, h + 1) {
      REP(j, 1, w + 1) {
        if (grid.at(i).at(j) && !checked.at(i).at(j)) {
          count++;
          checked.at(i).at(j) = true;
          dfs(ref(grid), ref(checked), i, j);
        }
      }
    }

    cout << count << endl;
  }

  return 0;
}
