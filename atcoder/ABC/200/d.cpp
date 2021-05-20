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

void print(vector<bool> &v) {
  vector<int> ans;
  REP(i, v.size()) {
    if (v.at(i)) ans.emplace_back(i + 1);
  }

  cout << ans.size();
  for (auto const &a : ans) {
    cout << " " << a;
  }
  cout << endl;
}

void print(int idx) {
  cout << "1 " << idx + 1 << endl;
}

int main() {
  IN(int, N);
  vector<vector<bool> > remain_elms(200, vector<bool>(N, false));
  vector<bool> exist(200);

  REP(i, N) {
    IN(ll, A);
    if (exist.at(A % 200)) {
      yes();
      print(ref(remain_elms.at(A % 200)));
      print(i);
      return 0;
    }
    remain_elms.at(A % 200).at(i) = true;
    exist.at(A % 200) = true;

    REP(j, 200) {
      if (!exist.at(j)) continue;
      if (remain_elms.at(j).at(i)) continue;

      vector<bool> tmp = remain_elms.at(j);
      tmp.at(i) = true;
      if (exist.at((j + A) % 200)) {
        bool is_ok = false;
        REP(k, N) {
          if (tmp.at(k) != remain_elms.at((j + A) % 200).at(k)) {
            is_ok = true;
            break;
          }
        }

        if (is_ok) {
          yes();
          print(ref(remain_elms.at((j + A) % 200)));
          print(ref(tmp));
          return 0;
        }
      } else {
        remain_elms.at((j + A) % 200) = tmp;
        exist.at((j + A) % 200) = true;
      }
    }
  }

  no();

  return 0;
}
