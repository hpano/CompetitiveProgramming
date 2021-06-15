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

ll mod = 1000000007;

ll jun(vector<ll> &count, int num) {
  if (num == 0) return 0;
  if (count[num]) return count[num];
  count[num] = count[num - 1] * num % mod;
  return count[num];
}

ll calc(vector<vector<ll> > &num, vector<ll> &count, int N, int M, int w, int b, int K) {
  if (w > b + K || w > N || b > M) return 0;
  if (num[w][b] != -1) return num[w][b];
  if (N - w <= M - b + K) {
    ll mot = jun(ref(count), N - w) * jun(ref(count), M - b) % mod;
    ll chi = jun(ref(count), N - w + M - b);
    if (chi < mot) chi += mod;
    ll ans = chi / mot;
    num[w][b] = ans;
    return ans;
  }
  num[w][b] = (calc(ref(num), ref(count), N, M, w + 1, b, K) + calc(ref(num), ref(count), N, M, w, b + 1, K)) % mod;

  return num[w][b];
}

int main() {
  IN(int, N);
  IN(int, M);
  IN(int, K);
  vector<ll> count(N + M + 1);
  count[1] = 1;
  vector<vector<ll> > num(N + 1, vector<ll>(M + 1, -1));

  cout << calc(ref(num), ref(count), N, M, 0, 0, K) << endl;

  return 0;
}
