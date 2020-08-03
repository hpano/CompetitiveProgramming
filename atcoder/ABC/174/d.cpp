#include <iostream>
#include <vector>

int main() {
  int N;
  std::cin >> N;
  std::vector<char> c(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> c[i];
  }

  int count = 0;
  int w = 0, r = N - 1;
  while(true) {
    for (int i = w; i < N; ++i) {
      w = i;
      if (c[i] == 'W') {
        break;
      }
    }
    for (int j = r; j >= 0; --j) {
      r = j;
      if (c[j] == 'R') {
        break;
      }
    }
    if (w >= r) break;
    else {
      // c[i] = 'R';
      // c[j] = 'W';
      w++;
      r--;
      count++;
    }
  }

  std::cout << count << std::endl;
  return 0;
}
