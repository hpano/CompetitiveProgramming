#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN(ll, N);
  vector<ll> A(N);
  ll mod = 1000000007;
  REP(i, N) {
    IN(ll, tmp);
    tmp %= mod;
    A.at(i) = tmp;
  }

  ll ans = 0;
  ll sum = A.at(N - 1);
  for (int i = N - 2; i >= 0; --i) {
    ans += sum * A.at(i);
    ans %= mod;
    sum += A.at(i);
    sum %= mod;
  }
  cout << ans << endl;

  return 0;
}
