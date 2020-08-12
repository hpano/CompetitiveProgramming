#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  getline(cin, s);
  for (int i = 0; i < s.size(); ++i) {
    if (s.at(i) >= 'a' && s.at(i) <= 'z') s.at(i) += 'A' - 'a';
    else if (s.at(i) >= 'A' && s.at(i) <= 'Z') s.at(i) += 'a' - 'A';
  }
  cout << s << endl;

  return 0;
}