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
  vector<pair<double, double> > pos(N);
  REP (count, N) {
    IN(double, x);
    IN(double, y);
    pos.at(count) = make_pair(x, y);
  }

  REP(i, N - 2) {
    REP(j, i + 1, N - 1) {
      double slope;
      if (pos.at(i).first == pos.at(j).first) slope = 10000000;
      else slope = (pos.at(i).second - pos.at(j).second) / (pos.at(i).first - pos.at(j).first);
      REP(k, j + 1, N) {
        if (slope == 10000000 && pos.at(k).first == pos.at(i).first) {
          yes();
          return 0;
        }
        else if (pos.at(k).second == ((pos.at(k).first - pos.at(i).first) * slope) + pos.at(i).second) {
          yes();
          return 0;
        }
      }
    }
  }
  no();

  return 0;
}