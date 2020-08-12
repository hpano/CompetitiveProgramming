#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cout << fixed << setprecision(5);
  while (true) {
    cin >> n;
    if (n == 0) break;
    int sum = 0;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
      cin >> s.at(i);
      sum += s.at(i);
    }
    double ave = (double) sum / n;
    double sum_diff = 0.0;
    for (int i = 0; i < n; ++i) {
      sum_diff += (double) (s.at(i) - ave) * (s.at(i) - ave);
    }
    double sigma = sqrt(sum_diff / n);
    cout << sigma << endl;
  }

  return 0;
}