#include <bits/stdc++.h>
using namespace std;

int main() {
  int S;
  cin >> S;
  int s = S % 60;
  S = (S - s) / 60;
  int m = S % 60;
  int h = (S - m) / 60;
  cout << h << ":" << m << ":" << s << endl;

  return 0;
}