#include <bits/stdc++.h>

using namespace std;

struct pos {
  int x;
  int y;
  int t;
};

int main() {
  int N;
  cin >> N;
  vector<pos> poss(N + 1);
  poss.at(0) = {0, 0, 0};
  for (int i = 1; i <= N; ++i) {
    cin >> poss.at(i).t >> poss.at(i).x >> poss.at(i).y;
  }
  for (int i = 0; i < N; ++i) {
    int dist = abs(poss.at(i).x - poss.at(i + 1).x) + 
               abs(poss.at(i).y - poss.at(i + 1).y);
    int time = poss.at(i + 1).t - poss.at(i).t;
    if ((time - dist) < 0 || (time - dist) % 2 != 0) {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;

  return 0;
}