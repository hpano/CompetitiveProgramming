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
  IN(int, N);
  int min_A = INT_MAX, min_A2 = INT_MAX, min_A_id = -1, min_B = INT_MAX, min_B2 = INT_MAX, min_B_id = -1;
  REP(i, N) {
    IN(int, A);
    if (A < min_A) {
      min_A2 = min_A;
      min_A = A;
      min_A_id = i;
    }
    else chmin(min_A2, A);

    IN(int, B);
    if (B < min_B) {
      min_B2 = min_B;
      min_B = B;
      min_B_id = i;
    }
    else chmin(min_B2, B);
  }

  if (min_A_id != min_B_id) {
    cout << max(min_A, min_B) << endl;
  } else {
    int ans = min_A + min_B;
    chmin (ans, max(min_A, min_B2));
    chmin (ans, max(min_A2, min_B));
    cout << ans << endl;
  }

  return 0;
}
