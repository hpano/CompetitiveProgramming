#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (int i = 0; i < n; ++i) cin >> x.at(i);
  for (int i = 0; i < n; ++i) cin >> y.at(i);
  double p1 = 0.0;
  double p2 = 0.0;
  double p3 = 0.0;
  double max = 0.0;
  for (int i = 0; i < n; ++i) {
    double dist = abs(x.at(i) - y.at(i));
    p1 += dist;
    p2 += dist * dist;
    p3 += dist * dist * dist;
    if (dist > max) max = dist;
  }
  p2 = sqrt(p2);
  p3 = pow(p3, 1.0/3.0);
  cout << fixed << setprecision(5);
  cout << p1 << endl;
  cout << p2 << endl;
  cout << p3 << endl;
  cout << max << endl;

  return 0;
}