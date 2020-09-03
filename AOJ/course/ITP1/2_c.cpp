#include <bits/stdc++.h>
using namespace std;

int main() {
  int N = 3;
  vector<int> num(N);
  for (int i = 0; i < N; ++i) {
    cin >> num.at(i);
  }
  sort(num.begin(), num.end());
  for (int i = 0; i < N; ++i) {
    cout << num.at(i);
    if (i == N - 1) cout << endl;
    else cout << " ";
  }

  return 0;
}