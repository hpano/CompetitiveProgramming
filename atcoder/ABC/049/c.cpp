#include <bits/stdc++.h>

using namespace std;

int main() {
  string S;
  cin >> S;

  for (int i = S.size() - 1; i >= 0; --i) {
    switch (S.at(i)) {
      case 'e':
        if ((i - 4 >= 0) && (S.substr(i - 4, 5) == "erase")) {
          i -= 4;
        } else {
          cout << "NO" << endl;
          return 0;
        }
        break;
      case 'm':
        if ((i - 4 >= 0) && (S.substr(i - 4, 5) == "dream")) {
          i -= 4;
        } else {
          cout << "NO" << endl;
          return 0;
        }
        break;
      case 'r':
        if (i - 6 >= 0 && S.at(i - 2) == 'm' && S.substr(i - 6, 7) == "dreamer") {
          i -= 6;
        } else if (i - 5 >= 0 && S.at(i - 2) == 's' && S.substr(i - 5, 6) == "eraser") {
          i -= 5;
        } else {
          cout << "NO" << endl;
          return 0;
        }
        break;
      default:
        cout << "NO" << endl;
        return 0;
    }
  }
  cout << "YES" << endl;

  return 0;
}