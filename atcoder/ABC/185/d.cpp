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

int main() {
  IN(int, N);
  IN(int, M);
  vector<int> As(M);
  INALL(As);
  sort(ALL(As));

  vector<int> whites_width;
  int min_width = N;
  REP(i, M) {
    int A = As.at(i);
    int prev_A = 0;
    if (i != 0) prev_A = As.at(i - 1);

    if (A - prev_A != 1) {
      chmin(min_width, A - prev_A - 1);
      whites_width.emplace_back(A - prev_A - 1);
    }
    prev_A = A;
  }
  if (M == 0) {
    whites_width.emplace_back(N);
  }else if (As.at(M - 1) != N) {
    whites_width.emplace_back(N - As.at(M - 1));
  }

  int count = 0;
  for (auto w : whites_width) {
    count += w / min_width;
    if (w % min_width != 0) count++;
  }

  cout << count << endl;

  return 0;
}
