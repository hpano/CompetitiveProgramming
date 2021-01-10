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
#define INALL(v) for (auto &e : v) { cin >> e; }
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
  vector<int> As(N);
  vector<int> Bs(M);
  INALL(As);
  INALL(Bs);

  vector<vector<int> > dp(N, vector<int>(M));
  if (As.at(0) != Bs.at(0)) dp.at(0).at(0) = 1;
  REP(i, 1, N) {
    if (As.at(i) == Bs.at(0)) dp.at(i).at(0) = i;
    else dp.at(i).at(0) = dp.at(i - 1).at(0) + 1;
  }
  REP(j, 1, M) {
    if (As.at(0) == Bs.at(j)) dp.at(0).at(j) = j;
    else dp.at(0).at(j) = dp.at(0).at(j - 1) + 1;
  }
  REP(i, 1, N) {
    REP(j, 1, M) {
      dp.at(i).at(j) = min(dp.at(i - 1).at(j - 1) + (As.at(i) == Bs.at(j) ? 0 : 1),
                           min(dp.at(i - 1).at(j) + 1, dp.at(i).at(j - 1) + 1));
    }
  }

  cout << dp.at(N - 1).at(M - 1) << endl;

  return 0;
}
