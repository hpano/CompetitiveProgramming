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
#pragma endregion

// ll solve(ll N, ll now, vector<ll> &v, vector<int> &ok) {
//   ll count = 0;
//   if (ok.at(now) == -1) return 0;
//   else if (ok.at(now) == 1) return 1;
//   else {
//     if (now == N) return 1;
//     else if (now > N) return 0;
//   }
//   REP(i, v.size()) {
//     ll next = now + v.at(i);
//     if (next == N) {return count + 1;
//     else if (next > N) return count;
//     count += solve(N, next, v);
//     count %= 998244353;
//   }

//   return count;
// }

ll solve(ll N, ll num, vector<ll> v, ll idx, vector<ll> n) {
  ll mod = 998244353;
  ll count = 0;
  // if (N < num) return count;
  if (N % num == 0) {
    n.at(idx - 1) = N / num;
    vector<ll> row;
    REP(i, n.size()) {
      REP(j, n.at(i)) {
        row.push_back(v.at(i));
      }
    }
    // REP(i, row.size()) {
    //   cout << row.at(i);
    // }
    // cout << endl;
    do { 
      count++;
      count %= mod;
    } while (next_permutation(ALL(row)));
  }
  if (idx >= (ll)v.size()) return count;
  REP(i, 0, N / num) {
    n.at(idx - 1) = i;
    count += solve(N - i * num, v.at(idx), v, idx + 1, n);
    count %= mod;
  }

  return count;
}

int main() {
  IN(ll, N);
  IN(ll, K);
  // vector<ll> v(K * 2);
  vector<ll> v;
  vector<int> ok(N, 0);
  REP(i, K) {
    IN(ll, L1);
    IN(ll, L2);
    // v.at(i * 2) = L1;
    // v.at(i * 2 + 1) = L2;
    v.push_back(L1);
    if (L1 != L2) v.push_back(L2);
  }
  // sort(ALL(v));
  // v.erase(unique(ALL(v)), v.end());
  vector<ll> n(v.size(), 0);
  // reverse(v.begin(), v.end());
  ll count = solve(N - 1, v.at(0), v, 1, n);
  cout << count << endl;

  return 0;
}
