#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

ll solve(int N, int K, vector<int> P, vector<int>C) {
  vector<vector<int> > loops = {};
  vector<ll> sum = {};
  bitset<5000> flag_check;
  ll max_score = LLONG_MIN;

  REP (i, N) {
    if (flag_check[i]) continue;
    int next = P.at(i) - 1;
    ll tmp_sum = 0;
    vector<int> tmp_vec = {};
    while (true) {
      if (flag_check[next]) break;
      flag_check.set(next);
      tmp_vec.push_back(next);
      tmp_sum += C.at(next);
      next = P.at(next) - 1;
    }
    loops.push_back(tmp_vec);
    sum.push_back(tmp_sum);
  }

  REP (i, loops.size()) {
    vector<int> v = loops.at(i);
    int size = v.size();
    ll max_all = LLONG_MIN;
    ll max_limit = LLONG_MIN;
    REP (j, size) {
      ll tmp_sum = 0;
      int next = v.at(j);
      REP (k, size) {
        tmp_sum += C.at(next);
        if (k < K % size) {
          max_limit = max(max_limit, tmp_sum);
        }
        max_all = max(max_all, tmp_sum);
        next = P.at(next) - 1;
      }
    }
    ll sum_v = sum.at(i);
    ll max_v;
    if (sum_v > 0) {
      max_v = max(sum_v * (K / size) + max_limit, sum_v * (K / size - 1) + max_all);
    } else {
      max_v = max(max_limit, max_all);
    }
    max_score = max(max_score, max_v);
  }

  return max_score;
}

int main() {
  IN(int, N);
  IN(int, K);
  vector<int> P(N);
  vector<int> C(N);
  vector<int> sumv(N);
  long long sum = 0;
  REP(i, N) {
    cin >> P.at(i);
  }
  REP(i, N) {
    cin >> C.at(i);
    sum += C.at(i);
  }

  cout << solve(N, K, P, C) << endl;;

  return 0;
}
