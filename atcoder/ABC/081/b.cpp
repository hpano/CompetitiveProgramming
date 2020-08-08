#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, ans = INT8_MAX;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A.at(i);
    if (A.at(i) % 2) {
      ans = 0;
      break;
    } else {
      int tmp = 0;
      while (!(A.at(i) % 2)) {
        tmp++;
        A.at(i) /= 2;
        if (tmp > ans) break;
      }
      if (tmp < ans) ans = tmp;
    }
  }
  cout << ans << endl;

  return 0;
}