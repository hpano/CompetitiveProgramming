#pragma region Macros
#include <bits/stdc++.h>

using namespace std;
// using ll = long long;
#define ll = long long

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
  while (true) {
    IN(int, h);
    IN(int, w);
    if (h == 0 && w == 0) break;

    string keyboard = "";
    REP(i, h) {
      IN(string, tmp);
      keyboard += tmp;
    }
    IN(string, s);

    int pre_idx = 0;
    int count = 0;
    REP(i, s.length()) {
      int idx = (int)keyboard.find(s.at(i));
      count += abs(idx % w - pre_idx % w) + abs(idx / w - pre_idx / w) + 1;
      pre_idx = idx;
    }

    cout << count << endl;
  }

  return 0;
}
