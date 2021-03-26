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

bool is_over_m(string &X, ll M, ll base) {
  ll now_base = 1;
  ll ans = 0;
  RREP(i, SZ(X)) {
    ans += (X.at(i) - '0') * now_base;
    if (ans > M) return true;
    if (i != 0 && now_base > (ll)1e18 / base) return true;
    now_base *= base;
  }

  return false;
}

ll calc_max_base(string &X, ll M, int min_base) {
  ll min = min_base;
  ll max = M + 1;
  while (min < max - 1) {
    ll mid = (min + max) / 2;
    if (is_over_m(ref(X), M, mid)) {
      max = mid;
    } else {
      min = mid;
    }
  }

  return min;
}

int main() {
  IN(string, X);
  IN(ll, M);

  int min_num = 0;
  for (auto const &x : X) {
    chmax(min_num, x - '0');
  }

  if (SZ(X) == 1) {
    if (X.at(0) - '0' > M) cout << "0" << endl;
    else cout << "1" << endl;
  } else {
    cout << calc_max_base(ref(X), M, min_num) - min_num << endl;
  }

  return 0;
}
