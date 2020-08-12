#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  string taro, hanako;
  int pt_taro = 0, pt_hanako = 0;
  for (int i = 0; i < n; ++i) {
    cin >> taro >> hanako;
    if (taro == hanako) {
      pt_taro++;
      pt_hanako++;
    } else if (taro > hanako) {
      pt_taro += 3;
    } else {
      pt_hanako += 3;
    }
  }
  cout << pt_taro << " " << pt_hanako << endl;

  return 0;
}