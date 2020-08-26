#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN(string, N);
  int ans = 0;
  REP(i, N.size()) {
    int a = N.at(i) - '0';
    ans += a;
  }
  if (ans % 9 == 0) cout << "Yes" << endl;
  else cout << "No" << endl;

  return 0;
}
