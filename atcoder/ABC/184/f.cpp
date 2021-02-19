#pragma region Macros
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define REP2(i, n) for (int i = 0, i##_len = (int)(n); i < i##_len; ++i)
#define REP3(i, l, r) for (int i = (l), i##_len = (int)(r); i < i##_len; ++i)
#define GET_MACRO_REP(_1, _2, _3, NAME, ...) NAME
#define REP(...) GET_MACRO_REP(__VA_ARGS__, REP3, REP2) (__VA_ARGS__)
#define RREP2(i, n) for (int i = (n - 1); i >= 0; --i)
#define RREP3(i, l, r) for (int i = (r - 1), i##_len = (l); i >= i##_len; --i)
#define GET_MACRO_RREP(_1, _2, _3, NAME, ...) NAME
#define RREP(...) GET_MACRO_REP(__VA_ARGS__, RREP3, RREP2) (__VA_ARGS__)
#define IN(type, n) type n; cin >> n
#define INALL(type, v) REP(i, v.size()) { IN(type, _tmp); v.at(i) = _tmp; }
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())

#ifdef _DEBUG
#define DEBUG(x) cout << #x << ": " << x << endl
#else
#define DEBUG(x)
#endif

template<class T>bool chmax(T &a, const T &b) { if (a < b) { a = b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b < a) { a = b; return 1; } return 0; }
void yes() { cout << "Yes" << endl; }
void no() { cout << "No" << endl; }
#pragma endregion

vector<ll> make_sums(vector<ll> &A) {
  vector<ll> sums;
  REP(i, (1 << A.size())) {
    ll tmp_sum = 0;
    int bit = i;
    REP(j, A.size()) {
      if (bit % 2 == 1) tmp_sum += A.at(j);
      bit /= 2;
    }
    sums.emplace_back(tmp_sum);
  }

  sort(ALL(sums));

  return sums;
}

pair<vector<ll>, vector<ll> > get_sums(vector<ll> &A) {
  vector<ll> A1(A.size() / 2);
  vector<ll> A2(A.size() - A1.size());
  REP(i, A1.size()) {
    A1.at(i) = A.at(i);
  }
  REP(i, A2.size()) {
    A2.at(i) = A.at(i + A1.size());
  }

  return make_pair(make_sums(ref(A1)), make_sums(ref(A2)));
}

int binary_search(vector<ll> &A, ll key) {
  int left = -1;
  int right = (int)A.size();
  while (right - left > 1) {
    int mid = (left + right) / 2;
    if (A.at(mid) == key) return mid;
    else if (A.at(mid) > key) right = mid;
    else left = mid;
  }

  return left;
}

int main() {
  IN(int, N);
  IN(ll, T);
  vector<ll> A(N);
  INALL(ll, A);

  auto [A1, A2] = get_sums(ref(A));

  ll max = 0;
  for (auto const &a1 : A1) {
    if (a1 > T) break;
    ll target = T - a1;
    int idx = binary_search(ref(A2), target);
    if (idx == -1) break;
    chmax(max, a1 + A2.at(idx));
  }

  cout << max << endl;

  return 0;
}
