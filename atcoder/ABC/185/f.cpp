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
  vector<int> vals;
  int length;

  SegTree(int num) {
    length = num;
    int v_size = 1;
    while (v_size < length) {
      v_size <<= 1;
    }
    vals.resize(v_size * 2);
  }

  void update(int pos) {
    if (pos <= 1) return;
    int parent = (pos) / 2;
    vals.at(parent) = vals.at(parent * 2) ^ vals.at(parent * 2 + 1);
    update(parent);
  }

  void replace(int pos, int val) {
    pos += length;
    vals.at(pos) ^= val;
    update(pos);
  }

  int get(int left, int right) {
    left += length;
    right += length;
    int ans = 0;
    while (left < right) {
      if (left % 2 == 1) {
        ans ^= vals.at(left);
        left++;
      }
      left /= 2;

      if (right % 2 == 1) {
        ans ^= vals.at(right - 1);
        right--;
      }
      right /= 2;
    }

    return ans;
  }
};

int main() {
  IN(int, N);
  IN(int, Q);
  SegTree As(N);
  REP(i, N) {
    IN(int, A);
    As.replace(i, A);
  }

  REP(i, Q) {
    IN(int, T);
    if (T == 1) {
      IN(int, X);
      IN(int, Y);
      As.replace(X - 1, Y);
    } else if (T == 2) {
      IN(int, X);
      IN(int, Y);
      cout << As.get(X - 1, Y) << endl;
    }
  }

  return 0;
}
