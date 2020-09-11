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
#define INALL(type, v) REP(i, v.size()) { IN(type, _tmp); v.at(i) = _tmp; }
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())

#ifdef _DEBUG
#define DEBUG(x) cout << #x << ": " << x << endl
#else
#define DEBUG(x)
#endif

template<class T>bool chmax(T &a, const T &b) { if (a < b) { a = b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b < a) { a = b; return 1; } return 0; }
#pragma endregion

bool check_visit_all(vector<bool> &visit) {
  REP(i, visit.size()) {
    if (!visit.at(i)) return false;
  }

  return true;
}

int solve(vector<vector<int> > &path, int node, vector<bool> visit) {
  visit.at(node) = true;
  if (check_visit_all(ref(visit))) return 1;
  int ans = 0;
  REP(i, path.at(node).size()) {
    int next = path.at(node).at(i);
    if (visit.at(next)) continue;
    ans += solve(ref(path), next, visit);
  }

  return ans;
}

int main() {
  IN(int, N);
  IN(int, M);
  vector<vector<int> > path(N, vector<int>());
  REP(i, M) {
    IN(int, a);
    IN(int, b);
    path.at(--a).push_back(--b);
    path.at(b).push_back(a);
  }

  vector<bool> visit(N, false);
  int ans = solve(ref(path), 0, visit);

  cout << ans << endl;

  return 0;
}
