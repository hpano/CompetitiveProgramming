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

struct UnionFind {
  std::vector<int> parent;
  std::vector<int> rank;

  UnionFind(int N) : parent(N), rank(N, 0) {
    for (int i = 0; i < N; ++i) {
      parent.at(i) = i;
    }
  }

  int root(int x) {
    if (parent.at(x) == x) return x;
    return parent.at(x) = root(parent.at(x));
  }

  void merge(int x, int y) {
    int rx = root(x);
    int ry = root(y);
    if (rx == ry) return;

    if (rank.at(rx) < rank.at(ry)) {
      parent.at(rx) = ry;
    } else {
      parent.at(ry) = rx;
      if (rank.at(rx) == rank.at(ry)) {
        rank.at(rx)++;
      }
    }
  }

  bool is_same(int x, int y) {
    int rx = root(x);
    int ry = root(y);
    return rx == ry;
  }
};

int main() {
  IN(int, N);
  UnionFind uf(N + 2);
  vector<pair<int, int> > pos(N);
  REP(i, N) {
    IN(int, x);
    IN(int, y);
    pos.at(i) = make_pair(x, y);
  }

  vector<tuple<double, int, int> > lens;
  REP(i, N) {
    REP(j, i + 1, N) {
      int x_div = pos.at(i).first - pos.at(j).first;
      int y_div = pos.at(i).second - pos.at(j).second;
      double tmp_len = sqrt(x_div * x_div + y_div * y_div);
      lens.emplace_back(make_tuple(tmp_len, i, j));
    }
    lens.emplace_back(make_tuple((100 - pos.at(i).second), i, N));
    lens.emplace_back(make_tuple((pos.at(i).second + 100), i, N + 1));
  }
  lens.emplace_back(make_tuple(200, N, N + 1));
  sort(lens.begin(), lens.end());

  for (int i = 0; i < (int)lens.size(); ++i) {
    uf.merge(get<1>(lens.at(i)), get<2>(lens.at(i)));
    if (uf.is_same(N, N + 1)) {
      cout << get<0>(lens.at(i)) / 2 << endl;
      return 0;
    }
  }

  return 0;
}
