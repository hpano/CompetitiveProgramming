#include <bits/stdc++.h>
using namespace std;

int main() {
  int r, c;
  cin >> r >> c;
  vector<vector<int> > sheet(r + 1, vector<int>(c + 1, 0));
  for (int i = 0; i < r; ++i) {
    int sum = 0;
    for (int j = 0; j < c; ++j) {
      cin >> sheet.at(i).at(j);
      sum += sheet.at(i).at(j);
    }
    sheet.at(i).at(c) = sum;
  }

  for (int j = 0; j < c + 1; ++j) {
    int sum = 0;
    for (int i = 0; i < r; ++i) {
      sum += sheet.at(i).at(j);
    }
    sheet.at(r).at(j) = sum;
  }

  for (int i = 0; i < r + 1; ++i) {
    for (int j = 0; j < c + 1; ++j) {
      cout << sheet.at(i).at(j);
      if (j == c) cout << endl;
      else cout << " ";
    }
  }

  return 0;
}