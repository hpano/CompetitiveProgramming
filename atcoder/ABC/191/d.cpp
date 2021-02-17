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

ll floor_base(ll num, ll base = 10000) {
  return (num / base) * base;
}

int main() {
  IN(double, X);
  ll xl = abs((ll)round(X * 10000));
  IN(double, Y);
  ll yl = abs((ll)round(Y * 10000));
  IN(double, R);
  ll rl = (ll)round(R * 10000);

  if (xl - rl <= 0) xl += floor_base(rl - xl + 10000);
  if (yl - rl <= 0) yl += floor_base(rl - yl + 10000);

  ll ans = 0;
  for (ll pos_x = floor_base(xl + rl); pos_x >= xl - rl; pos_x -= 10000) {
    ll len_x = pos_x - xl;
    ll len_y;
    if (len_x == 0) len_y = rl;
    else len_y = (ll)sqrtl(rl * rl - len_x * len_x);
    ans += (yl + len_y) / 10000 - (yl - len_y - 1) / 10000;
  }

  cout << ans << endl;

  return 0;
}
