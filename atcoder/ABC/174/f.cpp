#include <iostream>
#include <vector>
#include <bitset>

int main() {
  int N, Q;
  std::cin >> N >> Q;
  std::vector<int> c(N);

  for (int i = 0; i < N; ++i) {
    int num;
    std::cin >> num;
    c[i] = 1 << (num - 1);
  }

  for (int i = 0; i < Q; ++i) {
    int l, r;
    std::bitset<500000> ans(0);
    std::cin >> l >> r;
    for (int j = l - 1; j < r; ++j) {
      std::bitset<500000> val(c[j]);
      ans = ans | val;
    }
    std::cout << ans.count() <<std::endl;
  }

  return 0;
}
