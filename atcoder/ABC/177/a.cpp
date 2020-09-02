#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN(double, D);
  IN(double, T);
  IN(double, S);

  if (D / S <= T) cout << "Yes" << endl;
  else cout << "No" << endl;

  return 0;
}
