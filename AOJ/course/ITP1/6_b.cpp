#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  map<char, int> mtoi;
  mtoi.insert(make_pair('S', 0));
  mtoi.insert(make_pair('H', 1));
  mtoi.insert(make_pair('C', 2));
  mtoi.insert(make_pair('D', 3));
  char itom[] = {'S', 'H', 'C', 'D'};
  vector<vector<int> > num(4, vector<int>(13, 0));

  for (int i = 0; i < n; ++i) {
    char c;
    int x;
    cin >> c >> x;
    num.at(mtoi.at(c)).at(x - 1) = 1;
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 13; ++j) {
      if (num.at(i).at(j) == 0) cout << itom[i] << " " << j + 1 << endl;
    }
  }

  return 0;
}