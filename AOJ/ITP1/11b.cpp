#include <bits/stdc++.h>
using namespace std;

class Dice {
  int U, D, N, E, S, W;

  void goN() {
    int tmp = U;
    U = S;
    S = D;
    D = N;
    N = tmp;
  }

  void goE() {
    int tmp = U;
    U = W;
    W = D;
    D = E;
    E = tmp;
  }

  void goS() {
    int tmp = U;
    U = N;
    N = D;
    D = S;
    S = tmp;
  }

  void goW() {
    int tmp = U;
    U = E;
    E = D;
    D = W;
    W = tmp;
  }

  public:
  Dice(vector<int> label) {
    U = label.at(0);
    S = label.at(1);
    E = label.at(2);
    W = label.at(3);
    N = label.at(4);
    D = label.at(5);
  }

  void go(char way) {
    switch(way) {
      case 'N':
        goN();
        break;
      case 'E':
        goE();
        break;
      case 'S':
        goS();
        break;
      case 'W':
        goW();
        break;
    }
  }

  char getPos(int label) {
    if (U == label) return 'U';
    else if (D == label) return 'D';
    else if (N == label) return 'N';
    else if (E == label) return 'E';
    else if (S == label) return 'S';
    else if (W == label) return 'W';
    return 'Z';
  }

  int getLabel(char pos) {
    if (pos == 'U') return U;
    else if (pos == 'D') return D;
    else if (pos == 'N') return N;
    else if (pos == 'E') return E;
    else if (pos == 'S') return S;
    else if (pos == 'W') return W;
    return -1;
  }
};

int main() {
  vector<int> label(6);
  for (int i = 0; i < 6; ++i) cin >> label.at(i);
  Dice d1(label);
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int up, front;
    cin >> up >> front;
    char now_front, now_up;
    while (true) {
      now_front = d1.getPos(front);
      if (now_front == 'S') break;
      else if (now_front == 'E' || now_front == 'W') d1.go('E');
      else d1.go('N');
    }
    while (true) {
      now_up = d1.getPos(up);
      if (now_up == 'U') break;
      else d1.go('E');
    }
    cout << d1.getLabel('E') << endl;
  }

  return 0;
}