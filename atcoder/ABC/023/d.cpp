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

bool can_ans(vector<ll> &H, vector<ll> &S, ll val) {
  map<ll, int> count;
  REP(i, H.size()) {
    if (val < H.at(i)) return false;
    ll div = (val - H.at(i)) / S.at(i);
    count[div]++;
  }

  ll sum = 0;
  for (auto const &c : count) {
    sum += c.second;
    if (sum > c.first + 1) return false;
  }

  return true;
}

int main() {
  IN(int, N);
  vector<ll> H(N);
  vector<ll> S(N);
  REP(i, N) cin >> H.at(i) >> S.at(i);

  ll left = 0, right = LLONG_MAX, mid;
  while (right - left > 1) {
    mid = (left + right) / 2;
    if (can_ans(ref(H), ref(S), mid)) right = mid;
    else left = mid;
  }

  cout << right << endl;

  return 0;
}
