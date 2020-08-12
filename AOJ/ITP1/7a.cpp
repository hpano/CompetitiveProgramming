#include <bits/stdc++.h>
using namespace std;

int main() {
  int m = 0, f = 0, r = 0;
  while (true) {
    cin >> m >> f >> r;
    if (m == -1 && f == -1 && r == -1) break;
    string result = "F";
    int mf = m + f;
    if (m == -1 || f == -1) result = "F";
    else if (mf >= 80) result = "A";
    else if (mf >= 65) result = "B"; 
    else if (mf >= 50) result = "C"; 
    else if (mf >= 30) {
      if (r >= 50) result = "C"; 
      else result = "D";
    }
    cout << result << endl;
  }

  return 0;
}