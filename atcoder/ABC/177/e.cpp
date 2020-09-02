#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

void count_num(ll n, unordered_map<ll, ll> &count, unordered_map<ll, ll> &over_count) {
  if (over_count.count(n)) over_count[n]++;
  else {
    count[n]++;
    if (count[n] > 1) over_count[n] = count[n];
  }
}

int main() {
  ll MAX = 1000000;
  vector<ll> min_div(MAX + 1, 1);
  for (int i = 2; i <= MAX; ++i) {
    if (min_div[i] == 1) {
      for (int j = i; j <= MAX; j+= i) {
        min_div[j] = i;
      }
    }
  }

  IN(ll, N);
  vector<ll> A(N);
  unordered_map<ll, ll> count;
  unordered_map<ll, ll> over_count;
  REP(i, N) {
    IN(ll, A);
    ll tmp_div = 1;
    while(A != 1) {
      if (tmp_div != min_div[A]) {
        tmp_div = min_div[A];
        count_num(tmp_div, count, over_count);
      }
      A /= tmp_div;
    }
  }

  if (over_count.size() == 0) {
    cout << "pairwise coprime" << endl;
    return 0;
  }
  bool is_pairwise = true;
  for (auto itr = over_count.begin(), itr_end = over_count.end(); itr != itr_end; ++itr) {
    if (itr->second == N) {
      cout << "not coprime" << endl;
      return 0;
    }
  }
  cout << "setwise coprime" << endl;

  return 0;
}
