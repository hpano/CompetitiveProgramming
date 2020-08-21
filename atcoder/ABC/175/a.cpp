#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n
using namespace std;

int main() {
  int flag = 0;
  REP (i, 3) {
    IN (char, c);
    if (c == 'R') flag |= 1 << i;
  }
  switch (flag) {
    case 0:
      cout << 0 << endl;
      break;
    case 3:
    case 6:
      cout << 2 << endl;
      break;
    case 7:
      cout << 3 << endl;
      break;
    default:
      cout << 1 << endl;
      break;
  }

  return 0;
}
