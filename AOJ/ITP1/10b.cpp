#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;
  double rad = c * M_PI / 180;
  double S = a * b * sin(rad) / 2;
  double h = b * sin(rad);
  double a_dash = a - b * cos(rad);
  double L = a + b + sqrt(h * h + a_dash * a_dash);
  cout << fixed << setprecision(5);
  cout << S << " " << L << " " << h << endl;

  return 0;
}