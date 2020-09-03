#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  vector<int> count(26, 0);
  while (getline(cin, s)) {
    for (int i = 0; i < s.size(); ++i) {
      if (s.at(i) >= 'a' && s.at(i) <= 'z') count.at(s.at(i) - 'a')++;
      else if (s.at(i) >= 'A' && s.at(i) <= 'Z') count.at(s.at(i) - 'A')++;
    }
  }

  for (int i = 0; i < count.size(); ++i) {
    char c = 'a' + i;
    cout << c << " : " << count.at(i) << endl;
  }

  return 0;
}