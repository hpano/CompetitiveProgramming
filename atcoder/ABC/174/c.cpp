#include <iostream>
#include <vector>

int main() {
  int K;
  std::cin >> K;
  int val = 1, ans = -1;
  if (K % 2 == 0 || K % 5 == 0) {
    std::cout << -1 << std::endl;
    return 0;
  } else if (K % 7 == 0) {
    K /= 7;
  }

  for (int i = 0; i < 10000000; ++i) {
    if (val % K == 0) {
      ans = i + 1;
      break;
    }
    val = (val % K) * 10 + 1;
  }

  std::cout << ans << std::endl;
  return 0;
}
