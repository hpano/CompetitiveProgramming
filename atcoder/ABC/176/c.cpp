#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN(ll, N);
  vector<ll> A(N);
  REP(i, N) {
    cin >> A.at(i);
  }
  ll ans = 0;
  for (int i = 1; i < N; ++i) {
    if (A.at(i) < A.at(i - 1)) {
      ans += A.at(i - 1) - A.at(i);
      A.at(i) = A.at(i - 1);
    }
  }
  cout << ans << endl;

  return 0;
}
