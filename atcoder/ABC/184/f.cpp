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
  IN(int, N);
  IN(ll, T);
  vector<ll> A(N);
  // INALL(ll, A);
  map<ll, ll> mapA;
  REP(i, N) {
    IN(ll, a);
    A.at(i) = a;
    mapA[a]++;
  }
  sort(ALL(A));

  ll sum = 0;
  ll fin_idx = 0;
  REP(i, N) {
    if (sum + A.at(i) > T) break;
    else if (sum + A.at(i) == T) {
      cout << T << endl;
      return 0;
    }
    sum += A.at(i);
    fin_idx = i;
  }

  for (int rem = T - sum; rem > 0; --rem) {
    RREP(i, fin_idx + 1) {
      if (mapA.find(A.at(i) + rem) != mapA.end()) {
        cout << sum + rem << endl;
        return 0;
      }
    }
  }

  vector<vector<ll> > dp(N + 1, vector<ll>(T + 1, 0));
  REP(i, N) {
    for (ll t = 0; t <= T; ++t) {
      if (t >= A.at(i)) dp.at(i + 1).at(t) = max(dp.at(i).at(t - A.at(i)) + A.at(i), dp.at(i).at(t));
      else dp.at(i + 1).at(t) = dp.at(i).at(t);
    }
  }

  cout << dp.at(N).at(T) << endl;

  return 0;
}
