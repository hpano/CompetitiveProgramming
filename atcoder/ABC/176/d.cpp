#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int main() {
  IN (int, H);
  IN (int, W);
  IN (int, Ch);
  Ch--;
  IN (int, Cw);
  Cw--;
  IN (int, Dh);
  Dh--;
  IN (int, Dw);
  Dw--;
  vector<vector<int> > score(H + 4, vector<int>(W + 4, -2));
  REP(i, H) {
    REP(j, W) {
      IN(char, c);
      if (c == '.') score.at(i + 2).at(j + 2) = -1;
    }
  }

  queue<pair<int, int> > pos;
  queue<pair<int, int> > pos_next;
  score.at(Ch + 2).at(Cw + 2) = 0;
  pos.push(make_pair(Ch + 2, Cw + 2));

  while(!pos.empty()) {
    pair<int, int> tmp_pos = pos.front();
    pos.pop();
    for (int n = 0 ; n < 4; ++n) {
      int i = tmp_pos.first, j = tmp_pos.second;
      if (n == 0) i--;
      else if (n == 1) j++;
      else if (n == 2) i++;
      else if (n == 3) j--;

      if (score.at(i).at(j) == -1 || score.at(i).at(j) > score.at(tmp_pos.first).at(tmp_pos.second)) {
        score.at(i).at(j) = score.at(tmp_pos.first).at(tmp_pos.second);
        pos.push(make_pair(i, j));
      }
    }

    for (int i = tmp_pos.first - 2; i <= tmp_pos.first + 2; ++i) {
      for (int j = tmp_pos.second - 2; j <= tmp_pos.second + 2; ++j) {
        if (i == tmp_pos.first && j == tmp_pos.second) continue;
        if (score.at(i).at(j) == -1 || score.at(i).at(j) > score.at(tmp_pos.first).at(tmp_pos.second) + 1) {
          score.at(i).at(j) = score.at(tmp_pos.first).at(tmp_pos.second) + 1;
          pos_next.push(make_pair(i, j));
        }
      }
    }

    if (pos.empty()) {
      pos = pos_next;
      while (!pos_next.empty()) pos_next.pop();
    }

    // for debug
    // cout << "(" << tmp_pos.first << ", " << tmp_pos.second << ")" << endl;
    // REP(i, H + 4) {
    //   REP(j, W + 4) {
    //     int tmp_sc = score.at(i).at(j);
    //     if (tmp_sc == -2) cout << '#';
    //     else if (tmp_sc == -1) cout << '.';
    //     else cout << tmp_sc;
    //   }
    //   cout << endl;
    // }
    // cout << endl;

  }
  cout << score.at(Dh + 2).at(Dw + 2) << endl;

  return 0;
}
