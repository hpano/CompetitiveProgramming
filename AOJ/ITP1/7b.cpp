#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x;
  while (true) {
    cin >> n >> x;
    if (n == 0 && x == 0) break;
    int count = 0;
    for (int i = 1; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if ((x - i - j) > j && (x - i - j) <= n) count++;
      }
    }
    cout << count << endl;
  }

  return 0;
}