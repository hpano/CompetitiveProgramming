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

template<class T>
struct SegTree {
  vector<T> values;
  int length;

  SegTree(int size) {
    assert(size < 1 << 30);
    length = 1;
    while (length < size) {
      length <<= 1;
    }
    values.resize(length * 2);
  }

  void add(int pos_left, int pos_right, T value) {
    pos_left += length;
    pos_right += length;
    while (pos_left < pos_right) {
      if (pos_left % 2 == 1) {
        values.at(pos_left) += value;
        pos_left++;
      }
      if (pos_right % 2 == 1) {
        values.at(pos_right - 1) += value;
        pos_right--;
      }
      pos_left /= 2;
      pos_right /= 2;
    }
  }

  T get(int pos) {
    pos += length;
    T ans = 0;
    while (pos >= 1) {
      ans += values.at(pos);
      pos /= 2;
    }

    return ans;
  }
};

int main() {
  IN(int, n);
  IN(int, q);
  SegTree<int> tree(n);

  REP(i, q) {
    IN(int, com);
    if (com == 0) {
      IN(int, s);
      IN(int, t);
      IN(int, x);
      tree.add(s - 1, t, x);
    } else if (com == 1) {
      IN(int, idx);
      cout << tree.get(idx - 1) << endl;
    }
  }

  return 0;
}
