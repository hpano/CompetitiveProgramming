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
  IN(int, M);
  vector<ll> H(N);
  INALL(ll, H);
  vector<ll> W(M);
  INALL(ll, W);

  sort(ALL(H));
  ll min = 1000000000000000000;
  vector<ll> divs(N, 0);
  ll total_div = 0;
  REP(i, 2, N) {
    if (i % 2 == 0) total_div += H.at(i - 1) - H.at(i - 2);
    divs.at(i) += total_div;
  }
  total_div = 0;
  RREP(i, 0, N - 2) {
    if (i % 2 == 0) total_div += H.at(i + 2) - H.at(i + 1);
    divs.at(i) += total_div;
  }

  REP(i, M) {
    auto itr = lower_bound(ALL(H), W.at(i));
    ll tmp_div;
    if (itr == H.end()) {
      tmp_div = divs.at(N - 1) + (W.at(i) - H.at(N - 1));
    } else {
      size_t idx = distance(H.begin(), itr);
      tmp_div = divs.at(idx);
      if (idx % 2 == 0) {
        tmp_div += H.at(idx) - W.at(i);
      } else {
        tmp_div += (H.at(idx + 1) - H.at(idx)) + (W.at(i) - H.at(idx - 1));
      }
    }
    chmin(min, tmp_div);
  }

  cout << min << endl;

  return 0;
}
