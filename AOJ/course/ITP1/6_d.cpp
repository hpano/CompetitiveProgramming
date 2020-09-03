#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > A(n, vector<int>(m));
  vector<int> b(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> A.at(i).at(j);
    }
  }
  for (int i = 0; i < m; ++i) {
    cin >> b.at(i);
  }

  vector<int> c(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      c.at(i) += A.at(i).at(j) * b.at(j);
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << c.at(i) << endl;
  }

  return 0;
}