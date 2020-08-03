#include <iostream>
#include <vector>
#include <cmath>

int main() {
  int N, D, count = 0;
  std::cin >> N >> D;

  long long X, Y;
  for (int i = 0; i < N; ++i) {
    std::cin >> X >> Y;
    long double dist = sqrt(X * X + Y * Y);
    if (dist <= D) count++;
  }

  std::cout << count << std::endl;
  return 0;
}
