#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN (int, N);
  IN (int, X);
  IN (int, K);
  int ans = N / X;
  if (N % X != 0) ans++;
  cout << ans * K << endl;

  return 0;
}
