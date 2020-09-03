#include <iostream>

int main(int argc, char const *argv[]) {
  int A, B, C, K;
  int count = 0;

  std::cin >> A >> B >> C;
  std::cin >> K;

  while (B <= A) {
    B *= 2;
    count++;
  }
  while (C <= B) {
    C *= 2;
    count++;
  }

  if (count <= K) std::cout << "Yes" << std::endl;
  else std::cout << "No" << std::endl;

  return 0;
}
