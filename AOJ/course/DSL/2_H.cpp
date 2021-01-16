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

template<class X, class M>
struct SegTree {
  using Fn_XX = std::function<X(X, X)>;
  using Fn_XM = std::function<X(X, M)>;
  using Fn_MM = std::function<M(M, M)>;
  using Fn_MP = std::function<M(M, int)>;
  std::vector<X> values;
  std::vector<M> delays;
  int length;
  Fn_XX fxx;
  Fn_XM fxm;
  Fn_MM fmm;
  Fn_MP fmp;
  const X elm_value;
  const M elm_delay;

  SegTree(int size, Fn_XX fxx_, Fn_XM fxm_, Fn_MM fmm_, Fn_MP fmp_, X elm_value_, M elm_delay_)
          : fxx(fxx_), fxm(fxm_), fmm(fmm_), fmp(fmp_), elm_value(elm_value_), elm_delay(elm_delay_) {
    assert(size < (1 << 30));
    length = 1;
    while (length < size) {
      length <<= 1;
    }
    values.resize(length * 2, elm_value);
    delays.resize(length * 2, elm_delay);
  }

  void init(X val) {
    for (int i = length; i < length * 2; ++i) {
      values.at(i) = val;
    }
    for (int i = length - 1; i > 0; --i) {
      values.at(i) = fxx(values.at(i * 2), values.at(i * 2 + 1));
    }
  }

  void delay_update(int pos, int len) {
    if (delays.at(pos) == elm_delay) return;
    if (pos < length) {
      delays.at(pos * 2) = fmm(delays.at(pos * 2), delays.at(pos));
      delays.at(pos * 2 + 1) = fmm(delays.at(pos * 2 + 1), delays.at(pos));
    }
    values.at(pos) = fxm(values.at(pos), fmp(delays.at(pos), len));
    delays.at(pos) = elm_delay;
  }

  void set(int q_left, int q_right, X val) {
    set(q_left, q_right, val, 0, length, 1);
  }
  void set(int q_left, int q_right, X val, int t_left, int t_right, int pos) {
    delay_update(pos, t_right - t_left);
    if (t_left >= q_right || t_right <= q_left) return;
    if (t_left >= q_left && t_right <= q_right) {
      delays.at(pos) = fmm(delays.at(pos), val);
      delay_update(pos, t_right - t_left);
      return;
    }
    int t_mid = (t_left + t_right) / 2;
    set(q_left, q_right, val, t_left, t_mid, pos * 2);
    set(q_left, q_right, val, t_mid, t_right, pos * 2 + 1);
    values.at(pos) = fxx(values.at(pos * 2), values.at(pos * 2 + 1));
  }

  X get(int q_left, int q_right) {
    return get(q_left, q_right, 0, length, 1);
  }
  X get(int q_left, int q_right, int t_left, int t_right, int pos) {
    delay_update(pos, t_right - t_left);
    if (t_left >= q_right || t_right <= q_left) return elm_value;
    if (t_left >= q_left && t_right <= q_right) return values.at(pos);
    int t_mid = (t_left + t_right) / 2;
    X v_left = get(q_left, q_right, t_left, t_mid, pos * 2);
    X v_right = get(q_left, q_right, t_mid, t_right, pos * 2 + 1);
    return fxx(v_left, v_right);
  }
};

int main() {
  IN(int, n);
  IN(int, q);

  using X = int;
  using M = int;
  auto fxx = [](X x1, X x2) -> X { return min(x1, x2); };
  auto fxm = [](X x, M m) -> X { return x + m; };
  auto fmm = [](M m1, M m2) -> M { return m1 + m2; };
  auto fmp = [](M m, ll len) -> M { return m; };
  SegTree<X, M> tree(n, fxx, fxm, fmm, fmp, INT_MAX, 0);
  tree.init(0);

  REP(i, q) {
    IN(int, com);
    if (com == 0) {
      IN(int, s);
      IN(int, t);
      IN(int, x);
      tree.set(s, t + 1, x);
    } else if (com == 1) {
      IN(int, s);
      IN(int, t);
      cout << tree.get(s, t + 1) << endl;
    }
  }

  return 0;
}
