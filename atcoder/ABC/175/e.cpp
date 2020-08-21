#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

ll solve(int R, int C, vector<vector<ll> > val) {
  vector<vector<ll> > dp(R, vector<ll>(C));
  for (int i = 0; i < R; ++i) {
    priority_queue<ll, vector<ll>, greater<ll> > row_val;
    for (int j = 0; j < C; ++j) {
      ll tmp_val = val.at(i).at(j);
      ll c_val = tmp_val, r_val = tmp_val;
      if (i > 0) c_val += dp.at(i - 1).at(j);
      if (j > 0) r_val += dp.at(i).at(j - 1);
      row_val.push(tmp_val);
      if (row_val.size() > 3) {
        r_val -= row_val.top();
        row_val.pop();
      }
      if (r_val > c_val) {
        dp.at(i).at(j) = r_val;
      } else {
        dp.at(i).at(j) = c_val;
        while (!row_val.empty()) row_val.pop();
        row_val.push(tmp_val);
      }
    }
  }


  return dp.at(R - 1).at(C - 1);
}

int main() {
  IN (int, R);
  IN (int, C);
  IN (int, K);
  vector<vector<ll> > val(R, vector<ll>(C, 0));
  REP (i, K) {
    IN (int, r);
    IN (int, c);
    IN (ll, v);
    val.at(r - 1).at(c - 1) = v;
  }

  cout << solve(R, C, val) << endl;

  return 0;
}
