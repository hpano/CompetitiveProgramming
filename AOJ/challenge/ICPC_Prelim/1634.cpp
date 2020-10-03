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

void bundo(vector<ll> w, int idx, ll sum, unordered_map<ll, ll> &sums) {
  if (idx == (int)w.size()) {
    sums[sum]++;
  } else {
    bundo(w, idx + 1, sum + w.at(idx), sums);
    bundo(w, idx + 1, sum - w.at(idx), sums);
    bundo(w, idx + 1, sum, sums);
  }
}

int main() {
  while (true) {
    IN(int, n);
    IN(int, m);
    if (n == 0 && m == 0) break;

    vector<ll> a(n);
    INALL(ll, a);
    vector<ll> w(m);
    INALL(ll, w);
    unordered_map<ll, ll> sums;
    bundo(w, 0, 0, sums);

    // REP(i, sums.size()) {
    //   cout << sums.at(i) << " ";
    // }
    // cout << endl;

    bool isOK = true;
    REP(i, n) {
      if (sums.find(a.at(i)) == sums.end()) {
        isOK = false;
      }
    }
    if (isOK) {
      cout << 0 << endl;
      continue;
    }

    vector<vector<ll> > cands(n, vector<ll>());
    int start = 1;
    REP(i, n) {
      if (sums.find(a.at(i)) != sums.end()) {
        continue;
      } else {
        for (auto itr = sums.begin(); itr != sums.end(); ++itr) {
          cands.at(i).emplace_back(abs(a.at(i) - itr->first));
        }
        sort(ALL(cands.at(i)));
        cands.at(i).erase(unique(ALL(cands.at(i))), cands.at(i).end());
        start = i + 1;
        break;
      }
    }

    int pre = start - 1;
    int end = n - 1;
    REP(i, start, n) {
      if (cands.at(pre).size() == 0) {
        break;
      }
      if (sums.find(a.at(i)) != sums.end()) {
        continue;
      }
      REP(j, cands.at(pre).size()) {
        if (sums.find(a.at(i) + cands.at(pre).at(j)) != sums.end() || sums.find(a.at(i) - cands.at(pre).at(j)) != sums.end()) {
          cands.at(i).emplace_back(cands.at(pre).at(j));
        }
      }
      pre = i;
    }
    end = pre;

    if (cands.at(end).size() == 0) {
      cout << -1 << endl;
    } else {
      cout << cands.at(end).at(0) << endl;
    }

  }
  return 0;
}
