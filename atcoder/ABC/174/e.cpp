#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
  int N, K;
  std::cin >> N >> K;
  std::vector<long double>A(N);
  // int max = 0;
  // int max_idx = 0;
  for (int i = 0; i < N; ++i) {
    std::cin >> A[i];
    // if (A[i] > max) {
    //   max = A[i];
    //   max_idx = i;
    // }
  }

  for (int i = 0; i < K; ++i) {
    std::sort(A.begin(), A.end());
    A[N - 1] /= 2;
  }
  std::sort(A.begin(), A.end());
  long long ans = std::ceil(A[N - 1]);

  std::cout << ans << std::endl;

  for (int i = 0; i < N; ++i) {
    std::cout << A[i] << std::endl;
  }

  return 0;
}
