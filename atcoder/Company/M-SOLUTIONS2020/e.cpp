// できなかった

#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char const *argv[]) {
  int N;
  std::cin >> N;
  std::vector<int> X(N);
  std::vector<int> Y(N);
  std::vector<int> P(N);
  std::vector<int> min(N);
  std::vector<long long> rx(20001, 0);
  std::vector<long long> ry(20001, 0);
  for (int i = 0; i < N; ++i) {
    std::cin >> X[i] >> Y[i] >> P[i];
    if (X[i] > Y[i]) min[i] = Y[i];
    else min[i] = X[i];
    rx[X[i] + 10001] += P[i] * min[i];
    ry[Y[i] + 10001] += P[i] * min[i];
  }

  long long sum = 0;
  for (int i = 0; i < 20001; ++i) {
    sum += X[i];
  }

  int max = 0;
  for (int i = 0; i <= N; ++i) {
    std::vector<long long>::iterator maxItRX = *std::max_element(rx.begin(), rx.end());
    std::vector<long long>::iterator maxItRY = *std::max_element(ry.begin(), ry.end());
    int maxIndexRX = std::distance(rx.begin(), maxItRX);
    int maxIndexRY = std::distance(ry.begin(), maxItRY);

    if (rx[maxIndexRX] > ry[maxIndexRY]) {
      sum -= rx[maxIndexRX];
      rx[maxIndexRX] = 0;
      for (int j = 0; j < N; ++j) {
        if (abs(X[j] - (maxIndexRX - 10001)) < min[j]) {
          min[j] = abs(X[j] - (maxIndexRX - 10001));
        }
      }
    }
  }



  return 0;
}
