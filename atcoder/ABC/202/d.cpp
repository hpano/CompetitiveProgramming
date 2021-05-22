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

pair<ll, string> calc(vector<vector<ll> > &dp, int A, int B, ll target, ll now) {
  if (A == 0 || B == 0) {
    string S;
    REP(i, A) S += 'a';
    REP(i, B) S += 'b';
    if (now + 1 >= target) {
      return make_pair(-1, S);
    }
    return make_pair(1, "");
  }
  if (dp.at(A).at(B)) {
    ll tmp = dp.at(A).at(B);
    if (now + tmp == target) {
      string S = "";
      REP(i, B) S += 'b';
      REP(i, A) S += 'a';
      return make_pair(-1, S);
    }
    if (now + tmp < target) {
      return make_pair(tmp, "");
    }
  }

  ll val = 0;
  ll tmp;
  string S;
  tie(tmp, S) = calc(ref(dp), A - 1, B, target, now);
  if (tmp == -1) {
    return make_pair(-1, "a" + S);
  }
  val += tmp;
  now += tmp;
  tie(tmp, S) = calc(ref(dp), A, B - 1, target, now);
  if (tmp == -1) {
    return make_pair(-1, "b" + S);
  }
  val += tmp;
  now += tmp;

  dp.at(A).at(B) = val;
  return make_pair(val, "");
}

int main() {
  IN(int, A);
  IN(int, B);
  IN(ll, K);

  vector<vector<ll> > dp(A + 1, vector<ll>(B + 1));
  ll count;
  string ans;
  tie(count, ans) = calc(ref(dp), A, B, K, 0);

  cout << ans << endl;

  return 0;
}
