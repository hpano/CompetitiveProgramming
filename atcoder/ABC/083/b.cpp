#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, A, B, sum_all = 0;
  cin >> N >> A >> B;
  for (int i = 1; i <= N; ++i) {
    int sum = 0;
    int tmp = i;
    while (tmp > 0) {
      sum += tmp % 10;
      tmp /= 10;
    }
    if (sum >= A && sum <= B) sum_all += i;
  }
  cout << sum_all << endl;

  return 0;
}