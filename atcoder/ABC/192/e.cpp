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

struct Rail {
  int to;
  ll distance;
  ll depature;

  Rail(int to_, ll distance_, ll depature_) : to(to_), distance(distance_), depature(depature_) {}

  ll get_next_depature(ll now) {
    if (now % depature == 0) return now;
    else return (now / depature + 1) * depature;
  }

  ll calc_arrive(ll now) {
    return get_next_depature(now) + distance;
  }
};

int main() {
  IN(int, N);
  IN(int, M);
  IN(int, X);
  IN(int, Y);
  vector<vector<Rail> > rails(N + 1);
  REP(i, M) {
    IN(int, A);
    IN(int, B);
    IN(ll, T);
    IN(ll, K);
    Rail rail1(B, T, K);
    Rail rail2(A, T, K);
    rails.at(A).emplace_back(rail1);
    rails.at(B).emplace_back(rail2);
  }

  vector<ll> times(N + 1, (ll)1e18);
  times.at(X) = 0;
  priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > que_city;
  que_city.push(make_pair(0, X));
  while (!que_city.empty()) {
    ll now = que_city.top().first;
    int city = que_city.top().second;
    que_city.pop();
    if (now > times.at(city)) continue;
    for (auto rail : rails.at(city)) {
      ll arrive = rail.calc_arrive(now);
      if (chmin(times.at(rail.to), arrive)) {
        que_city.push(make_pair(arrive, rail.to));
      }
    }
  }

  if (times.at(Y) == (ll)1e18) cout << -1 << endl;
  else cout << times.at(Y) << endl;

  return 0;
}
