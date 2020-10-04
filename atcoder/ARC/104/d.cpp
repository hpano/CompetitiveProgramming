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

ll solve(ll N, ll K, ll M, int now, ll max, ll sum, int num, int c) {
  ll count = 0;
  if (now > N) {
    return 0;
  }
  REP(i, K + 1) {
    ll tmp = now * i;
    ll tmp_sum = sum + tmp;
    int tmp_c = c + i;
    if (tmp_c > num) {
      break;
    } else if (tmp_sum > max) {
      break;
    }
    if (tmp_c == num && tmp_sum == max) {
      count = (count + 1) % M;
      return count;
    }
    if (tmp_c < num && tmp_sum < max) {
      count += solve(N, K, M, now + 1, max, tmp_sum, num, tmp_c);
      count %= M;
    }
  }

  return count;
}

int main() {
  IN(ll, N);
  IN(ll, K);
  IN(ll, M);
  vector<ll> ans(N);
  REP(i, 1, (int)(N + 1) / 2 + 1) {
    ll count = 1;

    REP(j, 2, N * K + 1) {
      ll max = i * j;
      count += solve(N, K, M, 1, max, 0, j, 0);
      count %= M;
    }

    ans.at(i - 1) = count;
  }

  RREP(i, (int)(N + 1) / 2, (int)N) {
    ans.at(i) = ans.at(N - i - 1);
  }

  REP(i, (int)N) {
    cout << ans.at(i) << endl;
  }

  return 0;
}
