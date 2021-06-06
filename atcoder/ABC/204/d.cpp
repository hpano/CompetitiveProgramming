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
  IN(int, N);
  INALL(int, T, N);

  int sum = 0;
  for (auto const &t : T) {
    sum += t;
  }
  int div = sum / 2 + sum % 2;
  int ans = -1000000;

  vector<vector<bool> > dp(N + 1, vector<bool>(100010));
  dp.at(0).at(0) = true;
  REP(i, N) {
    REP(j, 100010) {
      if (dp.at(i).at(j)) {
        dp.at(i + 1).at(j) = true;
        dp.at(i + 1).at(j + T.at(i)) = true;
      }
    }
  }

  REP(j, div, 100010) {
    if (dp.at(N).at(j)) {
      ans = j;
      break;
    }
  }
  assert(ans > 0);

  cout << ans << endl;

  return 0;
}
