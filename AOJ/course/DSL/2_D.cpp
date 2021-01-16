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
  vector<int> delay;
  int length;

  SegTree(int size) {
    assert(size < (1 << 30));
    length = 1;
    while (length < size) {
      length <<= 1;
    }
    values.resize(length * 2, INT_MAX);
    delay.resize(length * 2, INT_MAX);
  }

  void delay_update(int pos) {
    if (delay.at(pos) == INT_MAX) return;
    if (pos < length) {
      delay.at(pos * 2) = delay.at(pos);
      delay.at(pos * 2 + 1) = delay.at(pos);
    }
    values.at(pos) = delay.at(pos);
    delay.at(pos) = INT_MAX;
  }

  void update_above(int pos) {
    if (pos < 1) return;
    update_above(pos / 2);
    delay_update(pos);
  }

  void update(int pos_left, int pos_right, int val) {
    pos_left += length;
    pos_right += length;
    while (pos_left < pos_right) {
      if (pos_left % 2 == 1) {
        // delay_update(pos_left);
        update_above(pos_left);
        delay.at(pos_left) = val;
        pos_left++;
      }
      if (pos_right % 2 == 1) {
        // delay_update(pos_right - 1);
        update_above(pos_right);
        delay.at(pos_right - 1) = val;
        pos_right--;
      }
      pos_left /= 2;
      pos_right /= 2;
    }
  }

  int find (int pos) {
    pos += length;
    delay_update(pos);
    update_above(pos);
    return values.at(pos);
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
      IN(int, idx);
      cout << tree.find(idx) << endl;
    }
  }

  return 0;
}
