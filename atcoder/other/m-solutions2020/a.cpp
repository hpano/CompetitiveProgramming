#include <iostream>

int main(int argc, char const *argv[]) {
  int X, r;
  std::cin >> X;
  if (X >= 400 && X < 600) r = 8;
  else if (X < 800) r = 7;
  else if (X < 1000) r = 6;
  else if (X < 1200) r = 5;
  else if (X < 1400) r = 4;
  else if (X < 1600) r = 3;
  else if (X < 1800) r = 2;
  else r = 1;

  std::cout << r << std::endl;

  return 0;
}
