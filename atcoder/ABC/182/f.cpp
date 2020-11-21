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
  IN(ll, X);
  vector<ll> A(N);
  vector<ll> max_use(N);
  REP(i, N) {
    IN(ll, a);
    A.at(i) = a;
    if (i > 0) max_use.at(i - 1) = a / A.at(i - 1);
  }

  if (X == A.at(N - 1)) {
    cout << "1" << endl;
    return 0;
  }
  vector<map<ll, ll> > dp(N);
  dp.at(N - 1)[X - (X / A.at(N - 1)) * A.at(N - 1)]++;
  dp.at(N - 1)[X - (X / A.at(N - 1) + 1) * A.at(N - 1)]++;
  RREP(i, N - 1) {
    for (auto itr = dp.at(i + 1).begin(); itr != dp.at(i + 1).end(); ++itr) {
      ll rem = itr->first;
      ll amount = rem / A.at(i);
      rem -= amount * A.at(i);
      if (abs(rem) < A.at(i)) 
        dp.at(i)[rem] += itr->second;
      if (abs(amount + 1) < max_use.at(i) && abs(rem - A.at(i)) < A.at(i)) 
        dp.at(i)[rem - A.at(i)] += itr->second;
      if (abs(amount - 1) < max_use.at(i) && abs(rem + A.at(i)) < A.at(i)) 
        dp.at(i)[rem + A.at(i)] += itr->second;
    }
  }

  cout << dp.at(0)[0] << endl;

  return 0;
}
