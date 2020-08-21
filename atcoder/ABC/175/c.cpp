#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN(ll, X);
  IN(ll, K);
  IN(ll, D);

  X = abs(X);
  if (X / D >= K) {
    cout << X - K * D << endl;
  } else {
    ll x1 = X % D;
    ll x2 = abs(x1 - D);
    if ((K - (X / D)) % 2 == 0) cout << x1 << endl;
    else cout << x2 << endl;
  }

  return 0;
}
