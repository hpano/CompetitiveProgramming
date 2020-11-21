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
#define INALL(type, v) REP(i, v.size()) { IN(type, _tmp); v.at(i) = _tmp; }
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
  IN(int, M);
  vector<vector<int> > grid(H, vector<int>(W));

  vector<pair<int, int> > lamp(N);
  REP(i, N) {
    IN(int, A);
    IN(int, B);
    A--, B--;
    grid.at(A).at(B) = 2;
    lamp.at(i) = make_pair(A, B);
  }
  REP(i, M) {
    IN(int, C);
    IN(int, D);
    C--, D--;
    grid.at(C).at(D) = -1;
  }

  REP(i, N) {
    RREP(x, 0, lamp.at(i).first) {
      if (grid.at(x).at(lamp.at(i).second) == -1) break;
      if (grid.at(x).at(lamp.at(i).second) == 2) break;
      grid.at(x).at(lamp.at(i).second) = 1;
    }
    REP(x, lamp.at(i).first + 1, H) {
      if (grid.at(x).at(lamp.at(i).second) == -1) break;
      if (grid.at(x).at(lamp.at(i).second) == 2) break;
      grid.at(x).at(lamp.at(i).second) = 1;
    }
    RREP(y, 0, lamp.at(i).second) {
      if (grid.at(lamp.at(i).first).at(y) == -1) break;
      if (grid.at(lamp.at(i).first).at(y) == 2) break;
      grid.at(lamp.at(i).first).at(y) = 1;
    }
    REP(y, lamp.at(i).second + 1, W) {
      if (grid.at(lamp.at(i).first).at(y) == -1) break;
      if (grid.at(lamp.at(i).first).at(y) == 2) break;
      grid.at(lamp.at(i).first).at(y) = 1;
    }
  }

  int count = 0;
  REP(i, H) {
    REP(j, W) {
      if (grid.at(i).at(j) == 1 || grid.at(i).at(j) == 2) count++;
      // cout << grid.at(i).at(j) << " ";
    }
    // cout << endl;
  }
  cout << count << endl;

  return 0;
}
