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

void print_P(vector<vector<int> > &P) {
  REP(i, SZ(P)) {
    REP(j, SZ(P)) {
      cout << P[i][j];
      if (j == SZ(P) - 1) cout << endl;
      else cout << " ";
    }
  }
}

int calc_score(vector<vector<int> > &E, vector<vector<int> > &P) {
  int score = 0;
  REP(i, SZ(E)) {
    REP(j, SZ(E)) {
      score += E[i][j] * P[i][j];
    }
  }

  return score;
}

vector<pair<int, int> > get_edge_pos(int N, int x, int y, int p) {
  vector<pair<int, int> > pos(p * 4);
  int count = 0;
  if (p == 0) return pos;
  if (x - p >= 0) pos[count++] = make_pair(x - p, y);
  if (x + p < N) pos[count++] = make_pair(x + p, y);
  if (y - p >= 0) pos[count++] = make_pair(x, y - p);
  if (y + p < N) pos[count++] = make_pair(x, y + p);
  int tx = x - p;
  int ty = y;
  REP(i, p - 1) {
    tx++; ty++;
    if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;
    pos[count++] = make_pair(tx, ty);
  }
  tx = x;
  ty = y + p;
  REP(i, p - 1) {
    tx++; ty--;
    if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;
    pos[count++] = make_pair(tx, ty);
  }
  tx = x + p;
  ty = y;
  REP(i, p - 1) {
    tx--; ty--;
    if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;
    pos[count++] = make_pair(tx, ty);
  }
  tx = x;
  ty = y - p;
  REP(i, p - 1) {
    tx--; ty++;
    if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;
    pos[count++] = make_pair(tx, ty);
  }

  if (count == p * 4) return pos;
  vector<pair<int, int> > tmp(count);
  copy(pos.begin(), pos.begin() + count, tmp.begin());
  return tmp;
}

bool init_power(vector<vector<int> > &E, vector<vector<int> > &P, vector<vector<int> > &O, int x, int y, int p, int low) {
  auto pos = get_edge_pos(SZ(P), x, y, p);
  if (p > 1) {
    for (auto const &[tx, ty] : pos) {
      if (O[tx][ty] == 0 && E[tx][ty] >= low) return false;
    }
  }

  for (auto const &[tx, ty] : pos) {
    O[tx][ty]++;
  }

  P[x][y] = p;

  return true;
}

void init(int N, vector<int> &border, vector<vector<int> > &E, vector<vector<int> > &P, vector<vector<int> > &O) {
  int max_score = 0;
  // REP(b1, 3, 31) {
  //   REP(b2, 2, b1) {
  REP(b1, 10, 21) {
    REP(b2, 2, 10) {
      vector<vector<int> > tmpP(N, vector<int>(N));
      vector<vector<int> > tmpO(N, vector<int>(N));
      vector<int> tmp_border = {31, b1, b2, 0};
      REP (m, 1, SZ(border)) {
        REP(p, 1, N + 1) {
          bool flag = false;
          REP(i, N) {
            REP(j, N) {
              if (tmpO[i][j]) continue;
              if (E[i][j] >= tmp_border[m] && E[i][j] < tmp_border[m - 1]) {
                if (tmpP[i][j] == p - 1)
                  flag |= init_power(ref(E), ref(tmpP), ref(tmpO), i, j, p, tmp_border[m]);
              }
            }
          }
          if (!flag) break;
        }
      }

      if (chmax(max_score, calc_score(ref(E), ref(tmpP)))) {
        border = tmp_border;
        P = tmpP;
        O = tmpO;
      }
    }
  }
}

void fix(vector<vector<int> > &P, vector<vector<int> > &O) {
  REP(i, SZ(P)) {
    REP(j, SZ(P)) {
      if (O[i][j] > 0) continue;
      bool flag = false;
      REP(p, P[i][j] + 1, 40) {
        auto pos = get_edge_pos(SZ(P), i, j, p);
        for (auto const &[tx, ty] : pos) {
          if (P[tx][ty]) {
            flag = true;
            break;
          }
        }
        if (flag) break;
        for (auto const &[tx, ty] : pos) {
          O[tx][ty]++;
        }
        P[i][j] = p;
      }
    }
  }
}

void modify(vector<vector<int> > &P, vector<vector<int> > &O) {
  random_device rnd;
  mt19937 mt(rnd());
  uniform_int_distribution randN(0, SZ(P) - 1);
  int x = randN(mt);
  int y = randN(mt);

  if (P[x][y] == 40) return;
  else if (P[x][y] == 0) {
    REP(i, SZ(P)) {
      REP(j, SZ(P)) {
        if (P[i][j] == 0) continue;
        int div = P[i][j] - (abs(x - i) + abs(y - j)) + 1;
        if (div <= 0) continue;
        RREP(p, P[i][j] - div + 1, P[i][j] + 1) {
          auto pos = get_edge_pos(SZ(P), i, j, p);
          for (auto const &[tx, ty] : pos) O[tx][ty]--;
        }
        P[i][j] -= div;
      }
    }

    auto pos = get_edge_pos(SZ(P), x, y, 1);
    for (auto const &[tx, ty] : pos) O[tx][ty]++;
    P[x][y] = 1;
  } else {
    int p = P[x][y] + 1;
    auto pos = get_edge_pos(SZ(P), x, y, p);
    for (auto const &[tx, ty] : pos) {
      if (P[tx][ty] > 0) {
        REP(tp, 1, P[tx][ty] + 1) {
          auto tmp_pos = get_edge_pos(SZ(P), tx, ty, tp);
          for (auto const &[ttx, tty] : tmp_pos) O[ttx][tty]--;
        }
        P[tx][ty] = 0;
      }
      O[tx][ty]++;
    }
    P[x][y] = p;

    fix(ref(P), ref(O));
  }
}

void mountain(clock_t start, vector<vector<int> > &E, vector<vector<int> > &P, vector<vector<int> > &O) {
  // int count = 0;
  vector<vector<int> > tmpP = P;
  vector<vector<int> > tmpO = O;
  int max_score = 0;
  int pre_score = calc_score(ref(E), ref(P));
  double start_temp = 4;
  double end_temp = 1;
  while(true) {
    clock_t now = clock();
    if ((double)(now - start) / CLOCKS_PER_SEC > 1.98) break;

    vector<vector<int> > newP = tmpP;
    vector<vector<int> > newO = tmpO;
    modify(ref(newP), ref(newO));

    int new_score = calc_score(ref(E), ref(newP));
    double temp = start_temp + (end_temp - start_temp) * ((double)(now - start) / CLOCKS_PER_SEC) / 1.98;
    double prob = exp((new_score - pre_score) / temp);
    // if (new_score > pre_score) {
    // cerr << pre_score << ", " << new_score << ", " << temp << ", " << prob << endl;
    if (prob > (rand() % INT_MAX) / (double)INT_MAX) {
      tmpP = newP;
      tmpO = newO;
      pre_score = new_score;
      if (chmax(max_score, new_score)) {
        P = newP;
        O = newO;
      }
      // cerr << "new " << prob << endl;
    }
    // count++;
  }

  // cerr << "loop: " << count << endl;
}

void check(vector<vector<int> > &P, vector<vector<int> > &O) {
  vector<vector<int> > sum(SZ(P), vector<int>(SZ(P)));
  REP(i, SZ(P)) {
    REP(j, SZ(P)) {
      REP(p, 1, P[i][j] + 1) {
        auto pos = get_edge_pos(SZ(P), i, j, p);
        for (auto const &[tx, ty] : pos) {
          sum[tx][ty]++;
        }
      }
    }
  }

  REP(i, SZ(P)) {
    REP(j, SZ(P)) {
      if (O[i][j] == sum[i][j]) continue;
      cerr << i << ", " << j << ", O: " << O[i][j] << ", sum: " << sum[i][j] << endl;
    }
  }
}

int main() {
  clock_t start = clock();

  IN(int, N);
  vector<vector<int> > E(N, vector<int>(N));
  vector<vector<int> > P(N, vector<int>(N));
  vector<vector<int> > O(N, vector<int>(N));
  REP(i, N) {
    REP(j, N) {
      cin >> E[i][j];
    }
  }

  vector<int> border = {31, 15, 7, 0};
  init(N, ref(border), ref(E), ref(P), ref(O));
  // cerr << (double)clock() / CLOCKS_PER_SEC << endl;
  mountain(start, ref(E), ref(P), ref(O));
  // cerr << (double)clock() / CLOCKS_PER_SEC << endl;
  print_P(ref(P));
  // cerr << (double)clock() / CLOCKS_PER_SEC << endl;
  // cerr << "score: " << calc_score(ref(E), ref(P)) << endl;
  // check(ref(P), ref(O));

  return 0;
}
