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
  IN(ll, M);
  INALL(ll, P, N);
  vector<ll> sum1;
  REP(i, N) {
    if (P.at(i) > M) continue;
    sum1.emplace_back(P.at(i));
    REP(j, i + 1, N) {
      if (P.at(i) + P.at(j) <= M) sum1.emplace_back(P.at(i) + P.at(j));
    }
  }
  vector<ll> sum2;
  sum2.emplace_back(0);
  REP(i, N) {
    if (P.at(i) > M) continue;
    sum2.emplace_back(P.at(i));
    REP(j, i + 1, N) {
      if (P.at(i) + P.at(j) <= M) sum2.emplace_back(P.at(i) + P.at(j));
    }
  }
  sort(ALL(sum2));

  ll ans = 0;
  for (auto const &s1 : sum1) {
    int left = 0, right = (int)sum2.size(), mid;
    while (right - left > 1) {
      mid = (left + right) / 2;
      if (s1 + sum2.at(mid) <= M) left = mid;
      else right = mid;
    }
    chmax(ans, s1 + sum2.at(left));
  }

  cout << ans << endl;

  return 0;
}
