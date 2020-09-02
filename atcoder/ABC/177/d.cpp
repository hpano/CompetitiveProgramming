#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define IN(type, n) type n; cin >> n

int countFriends(int n, vector<bool> &is_visit, vector<vector<int> > &friends) {
  int num = 1;
  vector<int> list = friends.at(n);
  int size = list.size();

  REP(i, size) {
    int tmp_n = list.at(i);
    if (is_visit.at(tmp_n)) continue;
    is_visit.at(tmp_n) = true;
    num += countFriends(tmp_n, is_visit, friends);
  }

  return num;
}

int main() {
  IN(int, N);
  IN(int, M);
  vector<vector<int> > friends(N);
  REP(i, M) {
    IN(int, A);
    A--;
    IN(int, B);
    B--;
    friends.at(A).push_back(B);
    friends.at(B).push_back(A);
  }

  vector<bool> is_visit(N, false);
  int max = 0;
  REP(i, N) {
    if (is_visit.at(i)) continue;
    is_visit.at(i) = true;
    int num = countFriends(i, is_visit, friends);
    if (num > max) max = num;
  }
  cout << max << endl;

  return 0;
}
