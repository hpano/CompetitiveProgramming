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
void yes() { cout << "Yes" << endl; }
void no() { cout << "No" << endl; }
#pragma endregion

void set_values(int A, int B, int C, vector<vector<vector<double> > > &values, double val) {
  values.at(A).at(B).at(C) = val;
  values.at(A).at(C).at(B) = val;
  values.at(B).at(A).at(C) = val;
  values.at(B).at(C).at(A) = val;
  values.at(C).at(A).at(B) = val;
  values.at(C).at(B).at(A) = val;
}

double calc(int A, int B, int C, vector<vector<vector<double> > > &values) {
  if (A == 100 || B == 100 || C == 100) return 0.0;
  if (values.at(A).at(B).at(C) != -1) return values.at(A).at(B).at(C);

  double ans = 0.0;
  if (A != 0) ans += (1.0 + calc(A + 1, B, C, ref(values))) * A / (A + B + C);
  if (B != 0) ans += (1.0 + calc(A, B + 1, C, ref(values))) * B / (A + B + C);
  if (C != 0) ans += (1.0 + calc(A, B, C + 1, ref(values))) * C / (A + B + C);
  set_values(A, B, C, ref(values), ans);

  return ans;
}

int main() {
  IN(int, A);
  IN(int, B);
  IN(int, C);

  vector<vector<vector<double> > > values(100, vector<vector<double> >(100, vector<double>(100, -1)));
  cout << fixed << setprecision(6);
  cout << calc(A, B, C, ref(values)) << endl;

  return 0;
}
