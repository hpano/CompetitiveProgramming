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

bool check_div(vector<int> &div, int a, int b, int c) {
  REP(i, a, b + 1) {
    if (div.at(i) == -1) {
      div.at(i) = c;
    } else if (div.at(i) != c) {
      return false;
    }
  }

  return true;
}

int count_none(vector<int> &floor, int f) {
  int count = 0;
  REP(i, f) {
    if (floor.at(i) == -1) count++;
  }

  return count;
}

int get_nth_none(vector<int> &floor, int n) {
  int count = 0;
  REP(i, floor.size()) {
    if (floor.at(i) == -1) count++;
    if (count == n) return i;
  }

  return -1;
}

int main() {
  IN(int, N);
  vector<int> div(N * 2, -1);
  vector<int> floor(N * 2, -1);
  vector<pair<int, int> > one_none;
  int both_none = 0;
  REP(i, N) {
    IN(int, a);
    IN(int, b);
    if (a != -1) {
      a--;
      if (floor.at(a) != -1) {
        no();
        return 0;
      }
      floor.at(a) = i;
    }
    if (b != -1) {
      b--;
      if (floor.at(b) != -1) {
        no();
        return 0;
      }
      floor.at(b) = i;
    }

    if (a != -1 && b != -1) {
      if (a >= b) {
        no();
        return 0;
      }
      int c = b - a - 1;
      if (!check_div(ref(div), a, b, c)) {
        no();
        return 0;
      }
    } else {
      if (a == -1 && b == -1) {
        both_none++;
      } else {
        one_none.emplace_back(make_pair(a, b));
      }
    }
  }

  REP(i, one_none.size()) {
    int a = one_none.at(i).first;
    int b = one_none.at(i).second;
    if (a != -1) {
      int c = div.at(a);
      if (c == -1) {
        int prev_none = count_none(ref(floor), a);
        int c_none = 0;
        REP(j, a + 1, N * 2) {
          if (floor.at(j) == -1) {
            c_none++;
            if (c_none == prev_none) {
              b = j;
              c = b - a - 1;
              floor.at(b) = floor.at(a);
              if (!check_div(ref(div), a, b, c)) {
                no();
                return 0;
              }
              break;
            }
          }
          if (j == N * 2 - 1) {
            no();
            return 0;
          }
        }
      } else {
        b = c + a + 1;
        if (floor.at(b) != -1) {
          no();
          return 0;
        } else {
          floor.at(b) = floor.at(a);
          if (!check_div(ref(div), a, b, c)) {
            no();
            return 0;
          }
        }
      }
    } else if (b != -1) {
      int c = div.at(b);
      if (c == -1) {
        int this_none = count_none(ref(floor), b);
        int c_none = 0;
        REP(j, 0, b) {
          if (floor.at(j) == -1) {
            a = j;
            c = b - a - 1;
            floor.at(a) = floor.at(b);
            if (!check_div(ref(div), a, b, c)) {
              no();
              return 0;
            }
            break;
          }
          if (j == N * 2 - 1) {
            no();
            return 0;
          }
        }
      } else {
        a = b - c - 1;
        if (floor.at(a) != -1) {
          no();
          return 0;
        } else {
          floor.at(a) = floor.at(b);
          if (!check_div(ref(div), a, b, c)) {
            no();
            return 0;
          }
        }
      }
    }
  }

  int idx = 0;
  REP(i, both_none) {
    REP(j, idx, N * 2) {
      if (floor.at(j) == -1) {
        int a = j;
        REP(k, a + 1, N * 2) {
          if (floor.at(k) == -1) {
            int b = k;
            int c = b - a - 1;
            if (!check_div(ref(div), a, b, c)) {
              no();
              return 0;
            }
            break;
          }
          if (k == N * 2 - 1) {
            no();
            return 0;
          }
        }
        break;
      }
      if (j == N * 2 - 1) {
        no();
        break;
      }
    }
  }

  yes();

  return 0;
}
