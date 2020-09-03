#include <iostream>

int main(int argc, char const *argv[]) {
  int N, K;
  std::cin >> N >> K;

  int A[N];
  for (int i = 0; i < N; ++i) {
    std::cin >> A[i];
  }

  for (int i = K; i < N; ++i) {
    if (A[i] > A[i - K]) std::cout << "Yes" << std::endl;
    else std::cout << "No" << std::endl;
  }

  return 0;
}
