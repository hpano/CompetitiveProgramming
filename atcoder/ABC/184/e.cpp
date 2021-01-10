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

int main() {
  IN(int, H);
  IN(int, W);
  vector<vector<char> > grid(H, vector<char>(W));
  int start_x = 0, start_y = 0;
  int goal_x = 0, goal_y = 0;
  vector<vector<pair<int, int> > > portal(26);
  REP(i, H) {
    REP(j, W) {
      IN(char, c);
      grid.at(i).at(j) = c;
      if (c == 'S') {
        start_x = i;
        start_y = j;
      } else if (c == 'G') {
        goal_x = i;
        goal_y = j;
      } else if (c != '.' && c != '#') {
        portal.at(c - 'a').emplace_back(make_pair(i, j));
      }
    }
  }

  vector<vector<int> > cost(H, vector<int>(W, INT_MAX));
  vector<bool> uncheck(26, true);
  priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > que;
  que.push(make_pair(0, make_pair(start_x, start_y)));
  cost.at(start_x).at(start_y) = 0;
  while (!que.empty()) {
    int x, y;
    int tmp_cost;
    pair<int, int> xy;
    tie(tmp_cost, xy) = que.top();
    tie(x, y) = xy;
    que.pop();
    // cout << x << ", " << y << ", " << tmp_cost << endl;
    // int tmp_cost = cost.at(x).at(y);
    if (grid.at(x).at(y) != 'S' && grid.at(x).at(y) != 'G' && grid.at(x).at(y) != '.') {
      char tmp_c = grid.at(x).at(y);
      if (uncheck.at(tmp_c - 'a')) {
        REP(i, portal.at(tmp_c - 'a').size()) {
          int tmp_x, tmp_y;
          tie(tmp_x, tmp_y) = portal.at(tmp_c - 'a').at(i);
          if (tmp_x == x && tmp_y == y) continue;
          if (cost.at(tmp_x).at(tmp_y) > tmp_cost + 1) {
            que.push(make_pair(tmp_cost + 1, make_pair(tmp_x, tmp_y)));
            cost.at(tmp_x).at(tmp_y) = tmp_cost + 1;
          }
        }
        uncheck.at(tmp_c - 'a') = false;
      }
    }

    if (x - 1 >= 0 && grid.at(x - 1).at(y) != '#') {
      if (cost.at(x - 1).at(y) > tmp_cost + 1) {
        que.push(make_pair(tmp_cost + 1, make_pair(x - 1, y)));
        cost.at(x - 1).at(y) = tmp_cost + 1;
      }
    }
    if (x + 1 < H && grid.at(x + 1).at(y) != '#') {
      if (cost.at(x + 1).at(y) > tmp_cost + 1) {
        que.push(make_pair(tmp_cost + 1, make_pair(x + 1, y)));
        cost.at(x + 1).at(y) = tmp_cost + 1;
      }
    }
    if (y - 1 >= 0 && grid.at(x).at(y - 1) != '#') {
      if (cost.at(x).at(y - 1) > tmp_cost + 1) {
        que.push(make_pair(tmp_cost + 1, make_pair(x, y - 1)));
        cost.at(x).at(y - 1) = tmp_cost + 1;
      }
    }
    if (y + 1 < W && grid.at(x).at(y + 1) != '#') {
      if (cost.at(x).at(y + 1) > tmp_cost + 1) {
        que.push(make_pair(tmp_cost + 1, make_pair(x, y + 1)));
        cost.at(x).at(y + 1) = tmp_cost + 1;
      }
    }
  }

  if (cost.at(goal_x).at(goal_y) == INT_MAX) {
    cout << "-1" << endl;
  } else {
    cout << cost.at(goal_x).at(goal_y) << endl;
  }

  return 0;
}
