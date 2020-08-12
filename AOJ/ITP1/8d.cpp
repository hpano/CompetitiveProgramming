#include <bits/stdc++.h>
using namespace std;

int main() {
  string s, p;
  cin >> s >> p;
  s += s;
  int size_s = s.size();
  int size_p = p.size();
  for (int i = 0; i <= size_s - size_p; ++i) {
    if (s.at(i) == p.at(0) && s.substr(i, size_p) == p) {
      cout << "Yes" << endl;
      return 0;
    } 
  }
  cout << "No" << endl;

  return 0;
}