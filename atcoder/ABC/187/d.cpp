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
  vector<pair<ll, int> > cities(N);
  vector<pair<int, int> > AB(N);
  vector<pair<int, int> > As(N);
  ll aoki = 0;
  ll takahashi = 0;
  REP(i, N) {
    IN(int, A);
    IN(int, B);
    AB.at(i) = make_pair(A, B);
    cities.at(i) = make_pair((ll)B, i);
    aoki += A;
  }

  sort(ALL(cities), greater<pair<ll, int> >());
  REP(i, N) {
    // cout << "num: " << cities.at(i).first << ", idx: " << cities.at(i).second << endl;
    cities.at(i).first += (ll)AB.at(cities.at(i).second).first * 2;
  }
  stable_sort(ALL(cities), [](const pair<ll, int>& p1, const pair<ll, int>& p2) { return p1.first > p2.first; });
  REP(i, N) {
    // cout << "num: " << cities.at(i).first << ", idx: " << cities.at(i).second << endl;
  }
  int count = 0;
  REP(i, N) {
    int idx = cities.at(i).second;
    // cout << "idx: " << idx << endl;
    takahashi += AB.at(idx).first + AB.at(idx).second;
    aoki -= AB.at(idx).first;
    count ++;
    // cout << "t: " << takahashi << ", a: " << aoki << endl;
    if (takahashi > aoki) {
      cout << count << endl;
      return 0;
    }
  }

  return 0;
}
