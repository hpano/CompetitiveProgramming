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

void make_tree(vector<int> &parents, vector<vector<int> > &children, vector<vector<int> > &pairs, vector<bool> &is_checked, int target) {
  if (is_checked.at(target)) return;
  is_checked.at(target) = true;
  for (auto const &p : pairs.at(target)) {
    if (is_checked.at(p)) continue;
    parents.at(p) = target;
    children.at(target).emplace_back(p);
    make_tree(ref(parents), ref(children), ref(pairs), ref(is_checked), p);
  }
}

void init(int N, vector<pair<int, int> > &edges, vector<int> &parents, vector<vector<int> > &children) {
  vector<vector<int> > pairs(N, vector<int>());
  REP(i, N - 1) {
    IN(int, A);
    IN(int, B);
    A--; B--;
    edges.at(i).first = A;
    edges.at(i).second = B;

    pairs.at(A).emplace_back(B);
    pairs.at(B).emplace_back(A);
  }

  vector<bool> is_checked(N, false);
  make_tree(ref(parents), ref(children), ref(pairs), ref(is_checked), 0);
}

void calc_values(vector<vector<int> > &children, vector<ll> &values, int target) {
  for (auto const &child : children.at(target)) {
    values.at(child) += values.at(target);
    calc_values(ref(children), ref(values), child);
  }
}

void solve(vector<pair<int, int> > &edges, vector<int> &parents, vector<vector<int> > &children, vector<ll> &values, int &root) {
  IN(int, Q);
  REP(i, Q) {
    IN(int, t);
    IN(int, e);
    IN(ll, x);
    e--;

    int A = edges.at(e).first;
    int B = edges.at(e).second;
    if (t == 2) swap(A, B);

    if (parents.at(A) == B) {
      values.at(A) += x;
    } else {
      values.at(root) += x;
      values.at(B) -= x;
    }
  }

  calc_values(ref(children), ref(values), root);
}

int main() {
  IN(int, N);
  vector<pair<int, int> > edges(N - 1, pair<int, int>());
  vector<int> parents(N, -1);
  vector<vector<int> > children(N, vector<int>());
  vector<ll> values(N, 0);
  int root = 0;

  init(N, ref(edges), ref(parents), ref(children));
  solve(ref(edges), ref(parents), ref(children), ref(values), ref(root));
  REP(i, N) {
    cout << values.at(i) << endl;
  }

  return 0;
}
