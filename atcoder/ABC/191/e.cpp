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

struct Edge {
  int to;
  int cost;
};

struct Dijkstra {
  int size;
  std::vector<std::vector<Edge> > graph;
  std::vector<int> total_cost;

  Dijkstra(int n) {
    init(n);
  }

  void init(int n) {
    size = n;
    graph.resize(size);
    total_cost.resize(size);
    for (int i = 0; i < size; ++i) {
      total_cost.at(i) = INT_MAX;
    }
  }

  void add_edge(int s, int t, int cost) {
    Edge e;
    e.to = t;
    e.cost = cost;
    graph.at(s).emplace_back(e);
  }

  void search(int s) {
    for (int i = 0; i < size; ++i) {
      total_cost.at(i) = INT_MAX;
    }

    total_cost.at(s) = INT_MAX;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > que;
    que.push(std::make_pair(0, s));
    while (!que.empty()) {
      std::pair<int, int> p = que.top();
      que.pop();
      int v = p.second;

      if (total_cost.at(v) < p.first) continue;
      for (auto e : graph.at(v)) {
        int target_cost = total_cost.at(v);
        if (v == s) target_cost = 0;
        if (total_cost.at(e.to) > target_cost + e.cost) {
          total_cost.at(e.to) = target_cost + e.cost;
          if (e.to != s) que.push(std::make_pair(total_cost.at(e.to), e.to));
        }
      }
    }
  }
};

int main() {
  IN(int, N);
  IN(int, M);
  vector<vector<int> > city(N, vector<int>(N, INT_MAX));
  REP(i, M) {
    IN(int, A);
    IN(int, B);
    A--;
    B--;
    IN(int, C);
    chmin(city.at(A).at(B), C);
  }

  Dijkstra g(N);

  REP(i, N) {
    REP(j, N) {
      if (city.at(i).at(j) != INT_MAX) {
        g.add_edge(i, j, city.at(i).at(j));
      }
    }
  }

  REP(i, N) {
    g.search(i);
    int ans = g.total_cost.at(i);
    if (ans == INT_MAX) cout << "-1" << endl;
    else cout << ans << endl;
  }

  return 0;
}
