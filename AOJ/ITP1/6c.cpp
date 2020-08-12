#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<vector<vector<int> > > house(4, vector<vector<int> >(3, vector<int>(10, 0)));
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int b, f, r, v;
    cin >> b >> f >> r >> v;
    house.at(--b).at(--f).at(--r) += v;
  }

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 10; ++k) {
        cout << " " << house.at(i).at(j).at(k);
      }
      cout << endl;
    }
    if (i != 3) cout << "####################" << endl;
  }

  return 0;
}