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
#pragma endregion

int main() {
  IN(int, N);
  vector<vector<pair<int, int> > > xy(N, vector<pair<int, int> >());
  REP(i, N) {
    IN(int, A);
    REP(j, A) {
      IN(int, x);
      IN(int, y);
      xy.at(i).push_back(make_pair(--x, y));
    }
  }

  int bit_max = (int)pow(2, N);
  int max = 0;
  REP(bnum, bit_max) {
    bool ok_flag = true;
    bitset<15> bit(bnum);
    REP(i, N) {
      if(bit[i]) {
        REP(j, xy.at(i).size()) {
          if (bit[xy.at(i).at(j).first] != xy.at(i).at(j).second) {
            ok_flag = false;
            break;
          }
        }
      }
      if (!ok_flag) break;
    }
    if (ok_flag) {
      int num = (int)bit.count();
      chmax(max, num);
    }
  }
  cout << max << endl;

  return 0;
}
