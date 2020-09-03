#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  int q;
  cin >> s >> q;
  for (int i = 0; i < q; ++i) {
    string command;
    int a, b;
    cin >> command >> a >> b;
    if (command == "print") {
      cout << s.substr(a, b - a + 1) << endl;
    } else if (command == "reverse") {
      string tmp = s.substr(a, b - a + 1);
      reverse(tmp.begin(), tmp.end());
      s = s.substr(0, a) + tmp + s.substr(b + 1, s.size() - b + 1);
    } else if (command == "replace") {
      string p;
      cin >> p;
      s = s.substr(0, a) + p + s.substr(b + 1, s.size() - b + 1);
    }
  }

  return 0;
}