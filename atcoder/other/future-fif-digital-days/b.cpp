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

struct Mark {
  int x;
  int y;
};

struct Pori {
  int cost;
  vector<vector<bool> > blocks;
};

struct Ans {
  int x;
  int y;
  int id;
};

int N = 50, K, B;
vector<Mark> marks;
vector<Pori> poris;
vector<Ans> answer;
vector<vector<bool> > grid(N, vector<bool>(N));

void init() {
  cin >> N >> K >> B;

  REP(k, K) {
    Mark mark;
    cin >> mark.x >> mark.y;
    marks.emplace_back(mark);
  }

  REP(i, B) {
    Pori pori;
    int n, m;
    cin >> n >> m >> pori.cost;
    vector<vector<bool> > tmp_blocks(n, vector<bool>(m));
    REP(j, n) {
      REP(k, m) {
        IN(char, s);
        if (s == '#') tmp_blocks[j][k] = true;
      }
    }
    pori.blocks = tmp_blocks;
    poris.emplace_back(pori);
  }
}

void print() {
  cout << SZ(answer) << endl;
  for (auto const &p : answer) {
    cout << p.id << " " << p.x << " " << p.y << endl;
  }
}

int get_len(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

void set_block(int x1, int y1, int x2, int y2) {
  if (x1 > x2) {
    swap(x1, x2);
    swap(y1, y2);
  }

  REP(i, x1, x2 + 1) {
    if (grid[i][y1]) continue;
    Ans ans;
    ans.x = i;
    ans.y = y1;
    ans.id = 1;
    grid[i][y1] = true;
    answer.emplace_back(ans);
  }

  if (y1 > y2) {
    swap(y1, y2);
  }

  REP(i, y1, y2 + 1) {
    if (grid[x2][i]) continue;
    Ans ans;
    ans.x = x2;
    ans.y = i;
    ans.id = 1;
    grid[x2][i] = true;
    answer.emplace_back(ans);
  }
}

void calc(UnionFind &uf) {
  vector<bool> checked(K);
  Ans ans1;
  ans1.x = marks[0].x;
  ans1.y = marks[0].y;
  ans1.id = 1;
  answer.emplace_back(ans1);
  checked[0] = true;
  grid[ans1.x][ans1.y] = true;

  REP(i, K - 1) {
    int min_idx, min_x = 0, min_y = 0;
    int min_len = N * N;
    REP(k, K) {
      if (checked[k]) continue;
      REP(x, N) {
        REP(y, N) {
          if (!grid[x][y]) continue;
          int len = get_len(x, y, marks[k].x, marks[k].y);
          if (chmin(min_len, len)) {
            min_idx = k;
            min_x = x;
            min_y = y;
          }
        }
      }
    }
    set_block(min_x, min_y, marks[min_idx].x, marks[min_idx].y);
    checked[min_idx] = true;
  }
}

int main() {
  init();
  UnionFind uf(K);
  calc(ref(uf));
  print();

  return 0;
}
