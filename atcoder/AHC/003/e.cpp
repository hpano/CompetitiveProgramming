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
#define INALL(type, v, s) vector<type> v(s); for (auto &e : v) { cin >> e; }
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

int calc_cost(int val) {
  int mask = 256;
  RREP(i, 1, 10) {
    if (mask & val) return i * 1000;
    mask >>= 1;
  }

  return 10000;
}

string calc_simple(int si, int sj, int ti, int tj) {
  int now_i = si, now_j = sj;
  string order = "";
  while (true) {
    if (ti == now_i && tj == now_j) break;
    if (ti > now_i) {
      order += "D";
      now_i++;
      continue;
    }
    if (ti < now_i) {
      order += "U";
      now_i--;
      continue;
    }
    if (tj > now_j) {
      order += "R";
      now_j++;
      continue;
    }
    if (tj < now_j) {
      order += "L";
      now_j--;
      continue;
    }
  }

  return order;
}

string calc_route(vector<int> &hs, vector<int> &vs, int si, int sj, int ti, int tj) {
  vector<vector<pair<ll, char> > > total_cost(30, vector<pair<ll, char> >(30, make_pair(LLONG_MAX, 'D')));
  total_cost.at(si).at(sj).first = 0;
  priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int> >, greater<tuple<ll, int, int> > > que;
  que.push(make_tuple(0, si, sj));
  int opp_cost_x1 = 2000;
  int opp_cost_x2 = 0;
  int opp_cost_y1 = 2000;
  int opp_cost_y2 = 0;
  if (si > ti) swap(opp_cost_x1, opp_cost_x2);
  if (sj > tj) swap(opp_cost_y1, opp_cost_y2);
  if (si == ti) opp_cost_y1 = opp_cost_y2 = 3000;
  if (sj == tj) opp_cost_x1 = opp_cost_x2 = 3000;

  while (!que.empty() && total_cost.at(ti).at(tj).first == LLONG_MAX) {
    tuple<ll, int, int> t = que.top();
    que.pop();
    ll cost = get<0>(t);
    int x = get<1>(t);
    int y = get<2>(t);

    if (total_cost.at(x).at(y).first < cost) continue;
    if (x > 0 && chmin(total_cost.at(x - 1).at(y).first, cost + calc_cost(vs.at(y)) + opp_cost_x1)) {
      total_cost.at(x - 1).at(y).second = 'U';
      que.push(make_tuple(total_cost.at(x - 1).at(y).first, x - 1, y));
    }
    if (x < 29 && chmin(total_cost.at(x + 1).at(y).first, cost + calc_cost(vs.at(y)) + opp_cost_x2)) {
      total_cost.at(x + 1).at(y).second = 'D';
      que.push(make_tuple(total_cost.at(x + 1).at(y).first, x + 1, y));
    }
    if (y > 0 && chmin(total_cost.at(x).at(y - 1).first, cost + calc_cost(hs.at(x)) + opp_cost_y1)) {
      total_cost.at(x).at(y - 1).second = 'L';
      que.push(make_tuple(total_cost.at(x).at(y - 1).first, x, y - 1));
    }
    if (y < 29 && chmin(total_cost.at(x).at(y + 1).first, cost + calc_cost(hs.at(x)) + opp_cost_y2)) {
      total_cost.at(x).at(y + 1).second = 'R';
      que.push(make_tuple(total_cost.at(x).at(y + 1).first, x, y + 1));
    }
  }
  assert(total_cost.at(ti).at(tj).first < LLONG_MAX);

  string order = "";
  int ni = ti, nj = tj;
  while (true) {
    if (ni == si && nj == sj) break;
    char c = total_cost.at(ni).at(nj).second;
    order += c;
    if (c == 'D') ni--;
    else if (c == 'R') nj--;
    else if (c == 'U') ni++;
    else if (c == 'L') nj++;
  }
  reverse(ALL(order));

  return order;
}

void modify_by_h(vector<int> &hs, vector<int> &vs, ll score, int sj, int ti, ll height, ll width) {
  int min_j = 9, max_j = 0;
  REP(i, 8) {
    if (!(hs.at(ti) >> i & 1)) continue;
    ll tmp = (score - ((i + 1) * 1000) * width) / height;
    if (tmp > 0 && tmp < 9001) {
      if (tmp < 500) tmp += 500;
      int j = (int)(tmp + 500) / 1000 - 1;
      if (vs.at(sj) >> j & 1) {
        chmin(min_j, j);
        chmax(max_j, j);
        continue;
      }
    }
    hs.at(ti) &= ~(1 << i);
  }

  REP(j, min_j) vs.at(sj) &= ~(1 << j);
  RREP(j, max_j + 1, 8) vs.at(sj) &= ~(1 << j);
}

void modify_by_v(vector<int> &hs, vector<int> &vs, ll score, int sj, int ti, ll height, ll width) {
  int min_i = 10, max_i = 0;
  REP(j, 9) {
    if (!(vs.at(sj) >> j & 1)) continue;
    ll tmp = (score - ((j + 1) * 1000) * height) / width;
    if (tmp > 0 && tmp < 9001) {
      if (tmp < 500) tmp += 500;
      int i = (int)(tmp + 500) / 1000 - 1;
      if (hs.at(ti) >> i & 1) {
        chmin(min_i, i);
        chmax(max_i, i);
        continue;
      }
    }
    vs.at(sj) &= ~(1 << j);
  }

  REP(i, min_i) hs.at(ti) &= ~(1 << i);
  RREP(i, max_i + 1, 9) hs.at(ti) &= ~(1 << i);
}

void modify_cost(vector<int> &hs, vector<int> &vs, ll score, int si, int sj, int ti, int tj) {
  ll height = abs(ti - si);
  ll width = abs(tj - sj);
  int prev_hs = hs.at(ti);
  int prev_vs = vs.at(sj);

  if (height == 0) {
    hs.at(ti) = 1 << (((score / width + 500) / 1000) - 1);
    return;
  }
  if (width == 0) {
    vs.at(sj) = 1 << (((score / height + 500) / 1000) - 1);
    return;
  }

  if (height < width) modify_by_v(ref(hs), ref(vs), score, sj, ti, height, width);
  else modify_by_h(ref(hs), ref(vs), score, sj, ti, height, width);

  if (hs.at(ti) == 0) {
    hs.at(ti) = 511;
    if (vs.at(sj) == 0) vs.at(sj) = 511;
    else vs.at(sj) = prev_vs;
  } else if (vs.at(sj) == 0) {
    hs.at(ti) = prev_hs;
    vs.at(sj) = 511;
  }
}

int main() {
  // clock_t start = clock();
  int query = 1000;
  int div = 160;
  vector<int> hs(30, 511);
  vector<int> vs(30, 511);

  REP(q, div) {
    // cerr << "query " << q << endl;
    // for (auto const &h : hs) cerr << h << " ";
    // cerr << endl;
    // for (auto const &v : vs) cerr << v << " ";
    // cerr << endl;
    // clock_t mid = clock();
    // assert((double)(mid - start) / CLOCKS_PER_SEC < 1.999);
    IN(int, si);
    IN(int, sj);
    IN(int, ti);
    IN(int, tj);
    string order = calc_simple(si, sj, ti, tj);
    cout << order << endl;
    IN(ll, score);
    modify_cost(ref(hs), ref(vs), score, si, sj, ti, tj);
  }

  REP(q, div, query) {
    // clock_t mid = clock();
    // assert((double)(mid - start) / CLOCKS_PER_SEC < 1.999);
    IN(int, si);
    IN(int, sj);
    IN(int, ti);
    IN(int, tj);
    string order = calc_route(ref(hs), ref(vs), si, sj, ti, tj);
    cout << order << endl;
    IN(ll, score);
  }

  return 0;
}
