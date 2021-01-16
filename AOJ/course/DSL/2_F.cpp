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

struct SegTree {
  vector<int> values;
  vector<int> delays;
  int length;

  SegTree(int size) {
    assert(size < (1 << 30));
    length = 1;
    while (length < size) {
      length <<= 1;
    }
    values.resize(length * 2, INT_MAX);
    delays.resize(length * 2, INT_MAX);
  }

  void delay_update(int pos) {
    if (delays.at(pos) == INT_MAX) return;
    if (pos < length) {
      delays.at(pos * 2) = delays.at(pos);
      delays.at(pos * 2 + 1) = delays.at(pos);
    }
    values.at(pos) = delays.at(pos);
    delays.at(pos) = INT_MAX;
  }

  void update(int q_left, int q_right, int val) {
    update(q_left, q_right, val, 0, length, 1);
  }
  void update(int q_left, int q_right, int val, int t_left, int t_right, int pos) {
    delay_update(pos);
    if (t_left >= q_right || t_right <= q_left) return;
    if (t_left >= q_left && t_right <= q_right) {
      delays.at(pos) = val;
      delay_update(pos);
      return;
    }
    int t_mid = (t_left + t_right) / 2;
    update(q_left, q_right, val, t_left, t_mid, pos * 2);
    update(q_left, q_right, val, t_mid, t_right, pos * 2 + 1);
    values.at(pos) = min(values.at(pos * 2), values.at(pos * 2 + 1));
  }

  int find(int q_left, int q_right) {
    return find(q_left, q_right, 0, length, 1);
  }
  int find(int q_left, int q_right, int t_left, int t_right, int pos) {
    delay_update(pos);
    if (t_left >= q_right || t_right <= q_left) return INT_MAX;
    if (t_left >= q_left && t_right <= q_right) return values.at(pos);
    int t_mid = (t_left + t_right) / 2;
    return min(find(q_left, q_right, t_left, t_mid, pos * 2), find(q_left, q_right, t_mid, t_right, pos * 2 + 1));
  }

  void debug_print() {
    cout << "== values ==" << endl;
    REP(i, SZ(values)) {
      if (values.at(i) == INT_MAX) cout << "INF ";
      else cout << setw(3) << values.at(i) << " ";
    }
    cout << endl;
    cout << "== delays ==" << endl;
    REP(i, SZ(delays)) {
      if (delays.at(i) == INT_MAX) cout << "INF ";
      else cout << setw(3) << delays.at(i) << " ";
    }
    cout << endl;
  }
};

int main() {
  IN(int, n);
  IN(int, q);
  SegTree tree(n);

  REP(i, q) {
    IN(int, com);
    if (com == 0) {
      IN(int, s);
      IN(int, t);
      IN(int, x);
      tree.update(s, t + 1, x);
    } else if (com == 1) {
      IN(int, s);
      IN(int, t);
      cout << tree.find(s, t + 1) << endl;
    }
  }

  return 0;
}
