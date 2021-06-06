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

ll calc_time(ll now, ll c, ll d) {
  ll ans = now + c + d / (now + 1);
  ll sqr = (ll)sqrtl(d);
  for(ll i = max(0LL, sqr - 10); i <= min(d, sqr + 10); ++i) {
    if (i < now) continue;
    ll tmp = i + c + d / (i + 1);
    chmin(ans, tmp);
  }
  return ans;
}

int main() {
  IN(int, N);
  IN(int, M);
  vector<vector<tuple<int, ll, ll> > > edge(N, vector<tuple<int, ll, ll> >());
  REP(i, M) {
    IN(int, A);
    IN(int, B);
    A--; B--;
    IN(ll, C);
    IN(ll, D);
    if (A == B) continue;
    edge.at(A).emplace_back(make_tuple(B, C, D));
    edge.at(B).emplace_back(make_tuple(A, C, D));
  }

  vector<ll> time(N, LLONG_MAX);
  time.at(0) = 0LL;
  priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > que;
  que.push(make_pair(0LL, 0));
  while (!que.empty()) {
    auto [now, node] = que.top();
    que.pop();
    if (time.at(node) < now) continue;
    for (auto const &[to, c, d] : edge.at(node)) {
      ll arrive = calc_time(now, c, d);
      if (chmin(time.at(to), arrive)) {
        que.push(make_pair(arrive, to));
      }
    }
  }

  if (time.at(N - 1) == LLONG_MAX) cout << -1 << endl;
  else cout << time.at(N - 1) << endl;

  return 0;
}
