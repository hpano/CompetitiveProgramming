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
  IN(ll, T);
  REP(t, T) {
    IN(ll, N);
    IN(ll, A);
    IN(ll, B);
    ll mod = 1000000007;
    ll mini = A;
    ll deka = B;
    chmin(mini, B);
    chmax(deka, A);
    ll Nmini = N / mini;
    ll Ndeka = N / deka;

    ll deka_num = (N - deka + 1);
    ll mini_num = (deka_num - mini + 1);
    ll ans = deka_num * deka_num % mod;
    ans = (ans * mini_num % mod) * (N - mini + 1 + deka - mini + 1) % mod;
    ll mini_amari = (N - deka) % mini;
    (deka_num % mini) * (mini - mini_amari) % mod;
  }

  return 0;
}
