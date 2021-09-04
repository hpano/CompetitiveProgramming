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

int eval1(int ap, int aq, int K) {
  return min(ap, K - ap) - min((ap + aq) % K, K - (ap + aq) % K);
}

int eval2(int ap, int aq, int K) {
  return ap - (ap + aq) % K;
}

int main() {
  IN(int, N);
  IN(int, M);
  IN(int, K);
  INALL(int, A, N);

  random_device rnd;
  mt19937 mt(rnd());
  uniform_int_distribution<> randN(0, N - 1);

  int big_num = 0;
  for (auto const &a : A) {
    if (a > K / 2) big_num++;
  }

  bool flag = true;
  REP(i, M) {
    if (big_num < M - i - 10 && flag) {
      int max_val = 0;
      pair<int, int> max_idx = make_pair(-1, -1);
      REP(j, N) {
        if (A[j] == 0) continue;
        REP(k, N) {
          if (A[k] == 0) continue;
          if (chmax(max_val, eval1(A[j], A[k], K))) max_idx = make_pair(j, k);
        }
      }

      if (max_idx.first == -1) {
        flag = false;
        i--;
        continue;
      }

      if (A[max_idx.first] > K / 2) big_num--;
      A[max_idx.first] = (A[max_idx.first] + A[max_idx.second]) % K;
      if (A[max_idx.first] > K / 2) big_num++;
      cout << max_idx.first << " " << max_idx.second << endl;
    } else {
      flag = true;
      int max_val = 0;
      pair<int, int> max_idx = make_pair(-1, -1);
      REP(j, N) {
        if (A[j] == 0) continue;
        if (A[j] <= K / 2) continue;
        REP(k, N) {
          if (A[k] == 0) continue;
          if (chmax(max_val, eval2(A[j], A[k], K))) max_idx = make_pair(j, k);
        }
      }

      if (max_idx.first == -1) return 0;

      if (A[max_idx.first] > K / 2) big_num--;
      A[max_idx.first] = (A[max_idx.first] + A[max_idx.second]) % K;
      if (A[max_idx.first] > K / 2) big_num++;
      cout << max_idx.first << " " << max_idx.second << endl;
    }
  }

  return 0;
}
