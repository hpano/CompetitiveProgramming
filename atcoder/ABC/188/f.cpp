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

ll calc(ll x, ll y, map<ll, ll> &data) {
  if (x >= y) {
    return x - y;
  }
  if (data.find(y) != data.end()) {
    return data[y];
  }

  ll ans = abs(y - x);
  if (y % 2 == 1) {
    chmin(ans, min(calc(x, y - 1, ref(data)), calc(x, y + 1, ref(data))) + 1);
    data[y] = ans;
    return ans;
  }
  
  chmin(ans, calc(x, y / 2, ref(data)) + 1);
  data[y] = ans;

  return ans;
}

int main() {
  IN(ll, X);
  IN(ll, Y);
  map<ll, ll> data;

  cout << calc(X, Y, ref(data)) << endl;

  return 0;
}
