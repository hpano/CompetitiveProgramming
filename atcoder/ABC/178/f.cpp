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
#pragma endregion

int main() {
  IN(ll, N);
  vector<ll> A(N + 1, 0);
  vector<pair<ll, ll> > Ap;
  vector<ll> B(N + 1, 0);
  vector<pair<ll, ll> > Bp;
  ll now_n = 0;
  ll count = 0;
  REP(i, N) {
    IN(ll, a);
    if (now_n == 0) {
      now_n = a;
      count = 1;
    }
    else if (now_n != a) {
      A.at(now_n) = count;
      Ap.push_back(make_pair(count, now_n));
      now_n = a;
      count = 1;
    } else {
      count++;
    }
    if (i == N - 1) {
      A.at(now_n) = count;
      Ap.push_back(make_pair(count, now_n));
    }
  }
  now_n = 0;
  count = 0;
  REP(i, N) {
    IN(ll, b);
    if (now_n == 0) {
      now_n = b;
      count = 1;
    }
    else if (now_n != b) {
      B.at(now_n) = count;
      Bp.push_back(make_pair(count, now_n));
      now_n = b;
      count = 1;
    } else {
      count++;
    }
    if (i == N - 1) {
      B.at(now_n) = count;
      Bp.push_back(make_pair(count, now_n));
    }
  }

  REP(i, N + 1) {
    ll sum = A.at(i) + B.at(i);
    if (sum > N) {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;

  sort(Ap.rbegin(), Ap.rend());

  vector<vector<ll> > ansB(N + 1);
  REP(i, Ap.size()) {
    REP(j, Bp.size()) {
      if (Bp.at(j).second != Ap.at(i).second) {
        if (Bp.at(j).first >= Ap.at(i).first) {
          REP(k, Ap.at(i).first) {
            ansB.at(Ap.at(i).second).push_back(Bp.at(j).second);
          }
          Bp.at(j).first -= Ap.at(i).first;
          Ap.at(i).first = 0;
          break;
        } else {
          REP(k, Bp.at(j).first) {
            ansB.at(Ap.at(i).second).push_back(Bp.at(j).second);
          }
          Ap.at(i).first -= Bp.at(j).first;
          Bp.at(j).first = 0;
        }
      }
    }
  }

  ll out_count = 0;
  REP(i, ansB.size()) {
    REP(j, ansB.at(i).size()) {
      cout << ansB.at(i).at(j);
      out_count++;
      if (out_count < N) {
        cout << " ";
      } else {
        break;
      }
    }
  }
  cout << endl;

  return 0;
}
