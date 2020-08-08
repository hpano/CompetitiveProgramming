#include <bits/stdc++.h>

using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> d(N);
  for (int i = 0; i < N; ++i) {
    cin >> d.at(i);
  }
  sort(d.begin(), d.end());
  int tmp = d.at(0);
  int count = 1;
  for (int i = 1; i < N; ++i) {
    if (d.at(i) != tmp) count++;
    tmp = d.at(i);
  }
  cout << count << endl;

  return 0;
}