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
  int num = 1;
  REP(i, N) {
    num *= 2;
  }
  vector<int> As(num);
  INALL(As);

  vector<int> rem;
  REP(i, num) {
    rem.emplace_back(i);
  }

  REP(i, N - 1) {
    vector<int> prev_rem = rem;
    rem.clear();
    for (int j = 0; j < (int)prev_rem.size(); j += 2) {
      if (As.at(prev_rem.at(j)) > As.at(prev_rem.at(j + 1))) {
        rem.emplace_back(prev_rem.at(j));
      } else {
        rem.emplace_back(prev_rem.at(j + 1));
      }
    }
  }
  assert(rem.size() == 2);

  if (As.at(rem.at(0)) > As.at(rem.at(1))) cout << rem.at(1) + 1 << endl;
  else cout << rem.at(0) + 1 << endl;

  return 0;
}
