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
  ll mod = 1000000007;
  IN(int, H);
  IN(int, W);
  vector<vector<char> > S(H, vector<char>(W));
  REP(i, H) {
    REP(j, W) {
      cin >> S.at(i).at(j);
    }
  }

  vector<vector<ll> > dp(H, vector<ll>(W, 0));
  dp.at(0).at(0) = 1;
  vector<vector<ll> > add_i(H, vector<ll>(W));
  vector<vector<ll> > add_j(H, vector<ll>(W));
  vector<vector<ll> > add_ij(H, vector<ll>(W));

  REP(i, H) {
    REP(j, W) {
      if (S.at(i).at(j) == '#') {
        if (i < H - 1) add_i.at(i + 1).at(j) = 0;
        if (j < W - 1) add_j.at(i).at(j + 1) = 0;
        if (i < H - 1 && j < W - 1) add_ij.at(i + 1).at(j + 1) = 0;
        continue;
      }
      dp.at(i).at(j) = (dp.at(i).at(j) + add_i.at(i).at(j) + add_j.at(i).at(j) + add_ij.at(i).at(j)) % mod;
      if (i < H - 1) add_i.at(i + 1).at(j) = (add_i.at(i).at(j) + dp.at(i).at(j)) % mod;
      if (j < W - 1) add_j.at(i).at(j + 1) = (add_j.at(i).at(j) + dp.at(i).at(j)) % mod;
      if (i < H - 1 && j < W - 1) add_ij.at(i + 1).at(j + 1) = (add_ij.at(i).at(j) + dp.at(i).at(j)) % mod;
    }
  }

  cout << dp.at(H - 1).at(W - 1) % mod << endl;

  return 0;
}
