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

  string getPos(int label, string avoid) {
    string pos = "";
    if (U == label && avoid.find("U") == string::npos) pos += "U";
    if (D == label && avoid.find("D") == string::npos) pos += "D";
    if (N == label && avoid.find("N") == string::npos) pos += "N";
    if (E == label && avoid.find("E") == string::npos) pos += "E";
    if (S == label && avoid.find("S") == string::npos) pos += "S";
    if (W == label && avoid.find("W") == string::npos) pos += "W";
    return pos;
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

bool isSameAllSurf(Dice &d1, Dice &d2) {
  if (d1.getLabel('U') == d2.getLabel('U') &&
    d1.getLabel('D') == d2.getLabel('D') &&
    d1.getLabel('N') == d2.getLabel('N') &&
    d1.getLabel('E') == d2.getLabel('E') &&
    d1.getLabel('S') == d2.getLabel('S') &&
    d1.getLabel('W') == d2.getLabel('W')) return true;
  return false;
}

bool isSame(Dice &d1, Dice &d2) {
  for (int i = 0; i < 4; ++i) {
    d1.go('S');
    for (int j = 0; j < 4; ++j) {
      d1.go('E');
      if (isSameAllSurf(d1, d2)) return true;
    }
  }
  d1.go('E');
  d1.go('S');
  for (int i = 0; i < 4; ++i) {
    d1.go('E');
    if (isSameAllSurf(d1, d2)) return true;
  }
  d1.go('S');
  d1.go('S');
  for (int i = 0; i < 4; ++i) {
    d1.go('E');
    if (isSameAllSurf(d1, d2)) return true;
  }

  return false;
}

int main() {
  vector<int> label(6);
  for (int i = 0; i < 6; ++i) cin >> label.at(i);
  Dice d1(label);
  for (int i = 0; i < 6; ++i) cin >> label.at(i);
  Dice d2(label);
  if (isSame(d1, d2)) cout << "Yes" << endl;
  else cout << "No" << endl;

  return 0;
}