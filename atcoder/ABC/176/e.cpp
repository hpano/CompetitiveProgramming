#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN (ll, H);
  IN (ll, W);
  IN (ll, M);
  map<pair<int, int>, int> hw;
  vector<ll> h(H, 0);
  vector<ll> w(W, 0);
  REP(i, M) {
    IN(ll, tmp_h);
    tmp_h--;
    IN(ll, tmp_w);
    tmp_w--;
    hw[make_pair(tmp_h, tmp_w)] = 1;
    h.at(tmp_h)++;
    w.at(tmp_w)++;
  }

  vector<ll> max_h = {};
  ll max_val_h = 0;
  REP(i, H) {
    if (h.at(i) > max_val_h) {
      max_val_h = h.at(i);
      max_h.clear();
      max_h.push_back(i);
    }
    else if (h.at(i) == max_val_h) max_h.push_back(i);
  }
  vector<ll> max_w = {};
  ll max_val_w = 0;
  REP(i, W) {
    if (w.at(i) > max_val_w) {
      max_val_w = w.at(i);
      max_w.clear();
      max_w.push_back(i);
    }
    else if (w.at(i) == max_val_w) max_w.push_back(i);
  }

  ll max = 0;
  REP(i, max_h.size()) {
    REP(j, max_w.size()) {
      ll tmp = h.at(max_h.at(i)) + w.at(max_w.at(j));
      bool flag = true;
      if (hw.count(make_pair(max_h.at(i), max_w.at(j)))) {
        flag = false;
      }
      if (flag) {
        cout << tmp << endl;
        return 0;
      } else {
        max = tmp - 1;
      }
    }
  }
  cout << max << endl;

  return 0;
}
