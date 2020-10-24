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
  IN(ll, N);
  if (N < 8 || N > 748307129767950528) {
    cout << "-1" << endl;
    return 0;
  }

  vector<ll> num3(40, 1);
  int max_idx3 = 1;
  REP(i, 1, 40) {
    ll tmp = num3.at(i - 1) * 3;
    if (tmp >= 1000000000000000000) break;
    num3.at(i) = tmp;
    max_idx3 = i;
  }
  vector<ll> num5(28, 1);
  int max_idx5 = 1;
  REP(i, 1, 28) {
    ll tmp = num5.at(i - 1) * 5;
    if (tmp >= 1000000000000000000) break;
    num5.at(i) = tmp;
    max_idx5 = i;
  }

  REP(i, 1, max_idx3 + 1) {
    REP(j, 1, max_idx5 + 1) {
      ll tmp = num3.at(i) + num5.at(j);
      if (tmp <= num3.at(i) || tmp <= num5.at(j)) {
        break;
      }
      if (tmp == N) {
        cout << i << " " << j << endl;
        return 0;
      }
    }
  }

  cout << "-1" << endl;

  return 0;
}
