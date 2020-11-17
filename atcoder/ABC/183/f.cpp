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
  std::vector<map<int, int> > class_n;

  UnionFind(int N) : parent(N), rank(N, 0), class_n(N) {
    for (int i = 0; i < N; ++i) {
      parent.at(i) = i;
    }
  }

  void set_class(vector<int> c) {
    for (int i = 0; i < (int)c.size(); ++i) {
      class_n.at(i)[c.at(i)]++;
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
      for (auto itr = class_n.at(rx).begin(); itr != class_n.at(rx).end(); ++itr) {
        class_n.at(ry)[itr->first] += itr->second;
      }
    } else {
      parent.at(ry) = rx;
      for (auto itr = class_n.at(ry).begin(); itr != class_n.at(ry).end(); ++itr) {
        class_n.at(rx)[itr->first] += itr->second;
      }
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
  IN(int, Q);
  UnionFind uf(N);
  vector<int> C(N);
  INALL(int, C);
  uf.set_class(C);

  REP(q, Q) {
    IN(int, qnum);
    IN(int, a);
    IN(int, b);
    a--;
    b--;

    if (qnum == 1) {
      uf.merge(a, b);
    } else if (qnum == 2) {
      cout << uf.class_n.at(uf.root(a))[++b] << endl;
    }
  }

  return 0;
}
