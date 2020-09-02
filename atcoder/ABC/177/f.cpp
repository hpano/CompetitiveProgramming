#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN(int, H);
  IN(int, W);
  vector<vector<int> > wall(H, vector<int>(W, 0));
  vector<vector<vector<ll> > > dp(H + 1, vector<vector<ll> >(W, vector<ll>(2, 0)));
  REP(i, W) {
    dp.at(H).at(i).at(0) = H;
  }
  REP(i, H) {
    IN(int, A);
    IN(int, B);
    for (int j = A - 1; j < B; ++j) {
      wall.at(i).at(j) = 1;
    }
  }

  for (int i = H - 1; i >= 0; --i) {
    for (int j = W - 1; j >= 0; --j) {
      if (wall.at(i).at(j) == 1) {
        if (j == W - 1) dp.at(i).at(j).at(0) = i;
        else {
          dp.at(i).at(j).at(0) = dp.at(i).at(j + 1).at(0);
          dp.at(i).at(j).at(1) = dp.at(i).at(j + 1).at(1) + 1;
        }
      } else {
        if (j == W - 1) {
          dp.at(i).at(j).at(0) = dp.at(i + 1).at(j).at(0);
          dp.at(i).at(j).at(1) = dp.at(i + 1).at(j).at(1);
        } else {
          if (dp.at(i + 1).at(j).at(0) > dp.at(i).at(j + 1).at(0)) {
            dp.at(i).at(j).at(0) = dp.at(i + 1).at(j).at(0);
            dp.at(i).at(j).at(1) = dp.at(i + 1).at(j).at(1);
          } else {
            dp.at(i).at(j).at(0) = dp.at(i).at(j + 1).at(0);
            dp.at(i).at(j).at(1) = dp.at(i).at(j + 1).at(1) + 1;
          }
        }
      }
    }
  }

  for (int i = 1; i <= H; ++i) {
    ll min = LLONG_MAX;
    for (int j = W - 1; j >= 0; --j) {
      if (dp.at(0).at(j).at(0) >= i) {
        if (dp.at(0).at(j).at(1) < min) min = dp.at(0).at(j).at(1);
      }
    }
    if (min == LLONG_MAX) cout << -1 << endl;
    else cout << min + i << endl;
  }

  return 0;
}
