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

int pow2(int n) {
  assert(n < 32);
  int ans = 1;
  REP(i, n) {
    ans *= 2;
  }

  return ans;
}

vector<int> get_neibors(int target, vector<vector<bool> > &edges){
  vector<int> neibors;
  REP(i, edges.at(target).size()) {
    if (edges.at(target).at(i)) neibors.emplace_back(i);
  }

  return neibors;
}

bool is_group_ok(vector<int> &group, vector<vector<bool> > &edges) {
  if (group.size() == 1) return true;

  for (auto const &target : group) {
    for (auto const &member : group) {
      if (member == target) continue;
      if (!edges.at(target).at(member)) return false;
    }
  }

  return true;
}

vector<vector<int> > get_max_groups(int target, vector<vector<bool> > &edges) {
  vector<vector<int> > max_groups;
  vector<int> neibors = get_neibors(target, ref(edges));
  if (neibors.size() == 0) return max_groups;

  int max_size = 0;
  REP(i, pow2((int)neibors.size())) {
    vector<int> group;
    group.emplace_back(target);
    REP(j, neibors.size()) {
      if ((i >> j) & 1) {
        group.emplace_back(neibors.at(j));
      }
    }
    if (!is_group_ok(ref(group), ref(edges))) continue;
    if ((int)group.size() < max_size) continue;
    if ((int)group.size() > max_size) {
      max_size = (int)group.size();
      max_groups.clear();
    }
    max_groups.emplace_back(group);
  }

  return max_groups;
}

int get_min_edge_node(vector<vector<bool> > &edges, vector<bool> &checked) {
  int ans = (int)edges.size();
  int min = ans * ans;
  REP(i, edges.size()) {
    if (checked.at(i)) continue;
    int count = 0;
    REP(j, edges.at(i).size()) {
      if (edges.at(i).at(j)) count++;
    }
    if (chmin(min, count)) ans = i;
  }

  return ans;
}

int solve(int N, int target, vector<vector<bool> > &edges, vector<bool> &checked) {
  if (target >= N) return 0;

  vector<vector<int> > max_groups = get_max_groups(target, ref(edges));
  if (max_groups.size() == 0) {
    checked.at(target) = true;
    return 1 + solve(N, get_min_edge_node(ref(edges), ref(checked)), ref(edges), ref(checked));
  }

  int ans = N;
  for (auto const &group : max_groups) {
    vector<vector<bool> > new_edges = edges;
    for (auto const &member : group) {
      REP(k, new_edges.at(member).size()) {
        new_edges.at(member).at(k) = false;
        new_edges.at(k).at(member) = false;
      }
    }

    vector<bool> new_checked = checked;
    for (auto const &member : group) {
      assert(new_checked.at(member) == false);
      new_checked.at(member) = true;
    }

    chmin(ans, solve(N, get_min_edge_node(ref(new_edges), ref(new_checked)), ref(new_edges), ref(new_checked)));
  }

  assert (ans < N);
  return ans + 1;
}

int main() {
  IN(int, N);
  IN(int, M);

  vector<vector<bool> > edges(N, vector<bool>(N, false));
  REP(i, M) {
    IN(int, A);
    IN(int, B);
    A--; B--;
    edges.at(A).at(B) = true;
    edges.at(B).at(A) = true;
  }

  int ans = N;
  REP(j, N) {
    vector<vector<bool> > new_edges = edges;
    vector<bool> checked(N, false);
    chmin(ans, solve(N, j, ref(new_edges), ref(checked)));
  }
  cout << ans << endl;

  return 0;
}
