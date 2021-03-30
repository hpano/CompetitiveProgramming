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

ll pow_ten(int num) {
  ll ans = 1;
  REP(i, num) {
    ans *= 10;
  }

  return ans;
}

ll calc_point(string &s, int num) {
  vector<int> count(10, 0);
  REP(i, 4) {
    count.at(s.at(i) - '0')++;
  }
  count.at(num)++;

  ll point = 0;
  REP(i, 1, 10) {
    point += (ll)i * pow_ten(count.at(i));
  }

  return point;
}

int main() {
  IN(int, K);
  vector<int> count(10, 0);
  IN(string, S);
  IN(string, T);
  for (auto const &c : S) {
    if (c == '#') continue;
    count.at(c - '0')++;
  }
  for (auto const &c : T) {
    if (c == '#') continue;
    count.at(c - '0')++;
  }

  ll total = (ll)(K * 9 - 8) * (K * 9 - 9);
  ll win = 0;
  REP(i, 1, 10) {
    if (count.at(i) == K) continue;
    count.at(i)++;
    REP(j, 1, 10) {
      if (count.at(j) == K) continue;
      if (calc_point(ref(S), i) > calc_point(ref(T), j)) {
        win += (ll)(K - count.at(i) + 1) * (K - count.at(j));
      }
    }
    count.at(i)--;
  }

  cout << fixed << setprecision(7);
  cout << (double)win / (double)total << endl;

  return 0;
}
