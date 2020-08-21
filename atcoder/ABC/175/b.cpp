#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n
using namespace std;

int main() {
  IN (int, N);
  vector<int> L(N);
  int count = 0;
  REP (i, N) {
    cin >> L.at(i);
  }
  for (int i = 0; i < N - 2; ++i) {
    for (int j = i + 1; j < N - 1; ++j) {
      for (int k = j + 1; k < N; ++k) {
        int li = L.at(i), lj = L.at(j), lk = L.at(k);
        if (li == lj || lj == lk || lk == li) continue;
        if (li >= lj + lk) continue;
        if (lj >= li + lk) continue;
        if (lk >= li + lj) continue;
        count++;
      }
    }
  }
  cout << count << endl;

  return 0;
}
