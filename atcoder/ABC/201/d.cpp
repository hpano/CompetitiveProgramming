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
  IN(int, H);
  IN(int, W);
  vector<vector<bool> > grid(H, vector<bool>(W, false));
  REP(i, H) {
    REP(j, W) {
      IN(char, A);
      if (A == '+') grid.at(i).at(j) = true;
    }
  }

  vector<vector<pair<int, int> > > dp(H, vector<pair<int, int> >(W));

  RREP(i, H - 1) {
    int t_prev = dp.at(i + 1).at(W - 1).first;
    int a_prev = dp.at(i + 1).at(W - 1).second;
    int add = -1;
    if (grid.at(i + 1).at(W - 1)) add = 1;

    if ((i + W - 1) % 2 == 0) {  // Takahashi
      dp.at(i).at(W - 1) = make_pair(t_prev + add, a_prev);
    } else {  // Aoki
      dp.at(i).at(W - 1) = make_pair(t_prev, a_prev + add);
    }
  }
  RREP(j, W - 1) {
    int t_prev = dp.at(H - 1).at(j + 1).first;
    int a_prev = dp.at(H - 1).at(j + 1).second;
    int add = -1;
    if (grid.at(H - 1).at(j + 1)) add = 1;

    if ((H - 1 + j) % 2 == 0) {  // Takahashi
      dp.at(H - 1).at(j) = make_pair(t_prev + add, a_prev);
    } else {  // Aoki
      dp.at(H - 1).at(j) = make_pair(t_prev, a_prev + add);
    }
  }

  RREP(i, H - 1) {
    RREP(j, W - 1) {
      int t_prev1 = dp.at(i).at(j + 1).first;
      int a_prev1 = dp.at(i).at(j + 1).second;
      int t_prev2 = dp.at(i + 1).at(j).first;
      int a_prev2 = dp.at(i + 1).at(j).second;
      int add1 = -1, add2 = -1;
      if (grid.at(i).at(j + 1)) add1 = 1;
      if (grid.at(i + 1).at(j)) add2 = 1;

      if ((i + j) % 2 == 0) {  // Takahashi
        int div1 = t_prev1 + add1 - a_prev1;
        int div2 = t_prev2 + add2 - a_prev2;
        if (div1 > div2) {
          dp.at(i).at(j) = make_pair(t_prev1 + add1, a_prev1);
        } else {
          dp.at(i).at(j) = make_pair(t_prev2 + add2, a_prev2);
        }
      } else {  // Aoki
        int div1 = a_prev1 + add1 - t_prev1;
        int div2 = a_prev2 + add2 - t_prev2;
        if (div1 > div2) {
          dp.at(i).at(j) = make_pair(t_prev1, a_prev1 + add1);
        } else {
          dp.at(i).at(j) = make_pair(t_prev2, a_prev2 + add2);
        }
      }
    }
  }

  int tp = dp.at(0).at(0).first;
  int ap = dp.at(0).at(0).second;
  if (tp == ap) {
    cout << "Draw" << endl;
  } else if (tp > ap) {
    cout << "Takahashi" << endl;
  } else {
    cout << "Aoki" << endl;
  }

  return 0;
}
