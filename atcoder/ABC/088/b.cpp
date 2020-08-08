#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, alice = 0, bob = 0;
  cin >> N;
  vector<int> a(N);
  for (int i = 0; i < N; ++i) {
    cin >> a.at(i);
  }
  sort(a.begin(), a.end(), greater<int>());
  for (int i = 0; i < N; ++i) {
    if (i % 2) {
      bob += a.at(i);
    } else {
      alice += a.at(i);
    }
  }

  cout << alice - bob << endl;

  return 0;
}