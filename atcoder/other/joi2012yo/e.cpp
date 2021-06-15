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
  IN(int, W);
  IN(int, H);
  vector<vector<bool> > grid(H + 2, vector<bool>(W + 2));
  REP(i, 1, H + 1) {
    REP(j, 1, W + 1) {
      IN(bool, c);
      grid.at(i).at(j) = c;
    }
  }

  vector<int> dx = {-1, -1, 0, 0, 1, 1};
  vector<vector<int> > dy = {{-1, 0, -1, 1, -1, 0}, {0, 1, -1, 1, 0, 1}};
  vector<vector<bool> > checked(H + 2, vector<bool>(W + 2));
  queue<pair<int, int> > que;
  que.push(make_pair(0, 0));
  int count = 0;
  while(!que.empty()) {
    auto [x, y] = que.front();
    que.pop();
    if (checked[x][y]) continue;
    checked[x][y] = true;
    REP(i, dx.size()) {
      if (x + dx[i] < 0 || x + dx[i] > H + 1 || y + dy[x % 2][i] < 0 || y + dy[x % 2][i] > W + 1) continue;
      if (grid[x + dx[i]][y + dy[x % 2][i]]) {
        count++;
      } else if (!checked[x + dx[i]][y + dy[x % 2][i]]) {
        que.push(make_pair(x + dx[i], y + dy[x % 2][i]));
      }
    }
  }

  cout << count << endl;

  return 0;
}
