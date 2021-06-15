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

int main() {
  IN(int, k);
  vector<pair<int, int> > given(k);
  REP(i, k) {
    IN(int, r);
    IN(int, c);
    given.at(i) = make_pair(r, c);
  }

  vector<int> position = {0, 1, 2, 3, 4, 5, 6, 7};
  do {
    bool is_ok = true;
    for (auto const &[r, c] : given) {
      if (position.at(r) != c) {
        is_ok = false;
        break;
      }
    }
    if (!is_ok) continue;

    REP(i, 7) {
      for (int x = i + 1, y = position.at(i) + 1; x < 8 && y < 8; ++x, ++y) {
        if (position.at(x) == y) {
          is_ok = false;
          break;
        }
      }
      if (!is_ok) break;
      for (int x = i + 1, y = position.at(i) - 1; x < 8 && y >= 0; ++x, --y) {
        if (position.at(x) == y) {
          is_ok = false;
          break;
        }
      }
      if (!is_ok) break;
    }

    if (is_ok) {
      REP(i, 8) {
        REP(j, 8) {
          if (j == position.at(i)) cout << "Q";
          else cout << ".";
        }
        cout << endl;
      }
      break;
    }
  } while (next_permutation(ALL(position)));

  return 0;
}
