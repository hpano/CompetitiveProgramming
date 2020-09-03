#include <iostream>

int main(int argc, char const *argv[]) {
  int N;
  std::cin >> N;
  int A[N];
  for (int i = 0; i < N; ++i) {
    std::cin >> A[i];
  }

  bool kabu_flag = false;
  unsigned long long money = 1000;
  unsigned long long kabu = 0;
  int limit = N - 1;
  // for (int i = N - 2; i >= 0; --i) {
  //   if (A[i] < A[A[i + 1]]) {
  //     limit = i;
  //     break;
  //   }
  // }
  for (int i = 0; i < N; ++i) {
    if (i == limit) {
      money += kabu * A[i];
      kabu = 0;
      break;
    }
    if (kabu_flag) {
      if (A[i] > A[i + 1]) {
        money += kabu * A[i];
        kabu = 0;
        kabu_flag = false;
      }
    } else {
      if (A[i] < A[i + 1]) {
        kabu = money / A[i];
        money %= A[i];
        kabu_flag = true;
      }
    }
  }

  std::cout << money << std::endl;

  return 0;
}
