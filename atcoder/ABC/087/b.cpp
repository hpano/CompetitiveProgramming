#include <bits/stdc++.h>

using namespace std;

int main() {
  int A, B, C, X, count = 0;
  cin >> A >> B >> C >> X;
  for (int i = 0; i <= A; ++i) {
    for (int j = 0; j <= B; ++j) {
      int tmp = X - 500 * i - 100 * j;
      if (tmp < 0) break;
      if (tmp / 50 <= C) count++;
    }
  }
  cout << count << endl;

  return 0;
}