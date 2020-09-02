#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN(string, S);
  IN(string, T);
  int sS = S.size();
  int sT = T.size();
  int min = 1000000;
  for (int i = 0; i < sS - sT + 1; ++i) {
    string tmp = S.substr(i, sT);
    int count = 0;
    for (int j = 0; j < sT; ++j) {
      if (tmp[j] != T[j]) count++;
    }
    if (count < min) min = count;
  }
  cout << min << endl;

  return 0;
}
