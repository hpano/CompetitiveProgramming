#include <bits/stdc++.h>
using namespace std;

int main() {
  string w, s, t;
  cin >> w;
  transform(w.begin(), w.end(), w.begin(), ::tolower);
  int count = 0;
  while (true) {
    cin >> s;
    if (s == "END_OF_TEXT") break;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (s == w) count++;
  }
  cout << count << endl;

  return 0;
}