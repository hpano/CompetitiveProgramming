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

int main() {
  IN(int, N);
  IN(int, M);
  vector<vector<int> > node(N);
  vector<vector<int> > group;
  REP(i, M) {
    IN(int, A);
    A--;
    IN(int, B);
    B--;
    node.at(A).emplace_back(B);
    node.at(B).emplace_back(A);
  }

  // REP(i, N) {
  //   cout << "node" << i << ": ";
  //   for (auto n : node.at(i)) {
  //     cout << n << ", ";
  //   }
  //   cout << endl;
  // }

  vector<pair<int, int> > sizes(N);
  REP(i, N) {
    sizes.at(i) = make_pair((int)node.at(i).size(), i);
  }
  sort(ALL(sizes), greater<pair<int, int> >());

  // REP(i, N) {
  //   cout << sizes.at(i).first << ", " << sizes.at(i).second << endl;
  // }

  REP(i, N) {
    int idx = sizes.at(i).second;
    // REP(j, (int)group.size()) {
    //   cout << "groupe" << j << ": ";
    //   REP(k, (int)group.at(j).size()) {
    //     cout << group.at(j).at(k) << ", ";
    //   }
    //   cout << endl;
    // }
    // cout << "idx: " << idx << endl;
    bool new_flag = true;
    REP(j, (int)group.size()) {
      bool add_flag = true;
      REP(k, (int)group.at(j).size()) {
        int tmp_node = group.at(j).at(k);
        // cout << "tmp_node: " << tmp_node << endl;
        bool ok_flag = false;
        for (int n : node.at(tmp_node)) {
          if (n == idx) {
            ok_flag = true;
          }
        }
        if (!ok_flag) {
          add_flag = false;
        }
      }
      if (add_flag) {
        group.at(j).emplace_back(idx);
        new_flag = false;
        break;
      }
    }

    if (new_flag) {
      // cout << "new" << endl;
      vector<int> v(1, idx);
      group.emplace_back(v);
    }
  }

  cout << group.size() << endl;

  return 0;
}
