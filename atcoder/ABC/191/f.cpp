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

vector<int> get_divisors(int n) {
  vector<int> divisors;
  for (int i = 1; i * i <= n; ++i) {
    if (n % i != 0) continue;
    divisors.emplace_back(i);
    if (n / i != i) divisors.emplace_back(n / i);
  }

  return divisors;
}

int main() {
  IN(int, N);
  vector<int> A(N);
  int min = INT_MAX;
  REP(i, N) {
    IN(int, a);
    chmin(min, a);
    A.at(i) = a;
  }

  map<int, int> divisors;
  for (auto const &a : A) {
    for (auto const &d : get_divisors(a)) {
      if (d > min) continue;
      divisors[d]++;
    }
  }

  int count = 0;
  bool min_flag = true;
  for (auto itr = divisors.begin(); itr != divisors.end(); ++itr) {
    vector<int> cand;
    REP(i, N) {
      if (A.at(i) % itr->first == 0) {
        cand.emplace_back(A.at(i));
      }
    }

    if (cand.size() < 2) continue;
    int gcd = cand.at(0);
    REP(i, 1, cand.size()) {
      gcd = __gcd(gcd, cand.at(i));
    }
    if (gcd == itr->first) {
      count++;
      if (itr->first == min) min_flag = false;
    }
  }

  if (min_flag) count++;
  cout << count << endl;

  return 0;
}
