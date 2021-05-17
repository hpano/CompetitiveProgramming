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
  IN(string, S);
  vector<int> ok;
  vector<int> ng;

  REP(i, 10) {
    if (S.at(i) == 'o') ok.emplace_back(i);
    else if (S.at(i) == 'x') ng.emplace_back(i);
  }

  if (ok.size() >= 5 || ng.size() == 10) {
    cout << 0 << endl;
    return 0;
  }

  int count = 0;
  REP(i, 10000) {
    bool flag = true;
    string tmp = to_string(i);
    if (i < 1000) tmp += "0";

    for (auto const &n : ok) {
      if (tmp.find(to_string(n)) == std::string::npos) {
        flag = false;
        break;
      }
    }
    if (!flag) continue;

    for (auto const &n : ng) {
      if (tmp.find(to_string(n)) != std::string::npos) {
        flag = false;
        break;
      }
    }
    if (flag) count++;
  }

  cout << count << endl;

  return 0;
}
