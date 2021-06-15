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

int solve(vector<vector<int> > &dp, vector<int> &w, int left, int right) {
  if (dp.at(left).at(right) != -1) return dp.at(left).at(right);
  if (right - left < 2) return 0;

  int ans = 0;
  if (abs(w.at(left) - w.at(right - 1)) <= 1 && solve(ref(dp), ref(w), left + 1, right - 1) == right - left - 2) {
    ans = right - left;
  }

  REP(mid, left + 1, right) {
    ans = max(ans, solve(ref(dp), ref(w), left, mid) + solve(ref(dp), ref(w), mid, right));
  }

  return dp.at(left).at(right) = ans;
}

int main() {
  while (true) {
    IN(int, n);
    if (n == 0) break;
    INALL(int, w, n);
    vector<vector<int> > dp(n + 1, vector<int>(n + 1, -1));
    cout << solve(ref(dp), ref(w), 0, n) << endl;
  }

  return 0;
}
