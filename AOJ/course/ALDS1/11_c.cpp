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
  IN(int, n);
  vector<vector<int> > edges(n);
  REP(i, n) {
    IN(int, u);
    u--;
    IN(int, k);
    REP(j, k) {
      IN(int, v);
      edges.at(u).emplace_back(--v);
    }
  }

  vector<int> dist(n, -1);
  dist.at(0) = 0;
  queue<pair<int, int> > que;
  que.push(make_pair(0, 0));
  while (!que.empty()) {
    auto [d, node] = que.front();
    que.pop();
    for (auto const &v : edges.at(node)) {
      if (dist.at(v) != -1) continue;
      dist.at(v) = d + 1;
      que.push(make_pair(d + 1, v));
    }
  }

  REP(i, n) {
    cout << i + 1 << " " << dist.at(i) << endl;
  }

  return 0;
}
