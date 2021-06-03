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
  int mask = 128;
  RREP(i, 1, 9) {
    if (mask & val) return i * 1000 + 500;
    mask >>= 1;
  }

  return 9500;
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

string calc_route(vector<vector<int> > &hs, vector<vector<int> > &vs, int si, int sj, int ti, int tj) {
  vector<vector<pair<ll, char> > > total_cost(30, vector<pair<ll, char> >(30, make_pair(LLONG_MAX, 'D')));
  total_cost.at(si).at(sj).first = 0;
  priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int> >, greater<tuple<ll, int, int> > > que;
  que.push(make_tuple(0, si, sj));
  int opp_cost_x1 = 3000;
  int opp_cost_x2 = 0;
  int opp_cost_y1 = 3000;
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
    if (x > 0 && chmin(total_cost.at(x - 1).at(y).first, cost + calc_cost(vs.at(y).at((x - 1) / 15)) + opp_cost_x1)) {
      total_cost.at(x - 1).at(y).second = 'U';
      que.push(make_tuple(total_cost.at(x - 1).at(y).first, x - 1, y));
    }
    if (x < 29 && chmin(total_cost.at(x + 1).at(y).first, cost + calc_cost(vs.at(y).at(x / 15)) + opp_cost_x2)) {
      total_cost.at(x + 1).at(y).second = 'D';
      que.push(make_tuple(total_cost.at(x + 1).at(y).first, x + 1, y));
    }
    if (y > 0 && chmin(total_cost.at(x).at(y - 1).first, cost + calc_cost(hs.at(x).at((y - 1) / 15)) + opp_cost_y1)) {
      total_cost.at(x).at(y - 1).second = 'L';
      que.push(make_tuple(total_cost.at(x).at(y - 1).first, x, y - 1));
    }
    if (y < 29 && chmin(total_cost.at(x).at(y + 1).first, cost + calc_cost(hs.at(x).at(y / 15)) + opp_cost_y2)) {
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

pair<ll, ll> get_length(int s, int t) {
  ll len0 = 0, len1 = 0;
  ll min_st = min(s, t);
  ll max_st = max(s, t);
  if (min_st < 15) {
    if (max_st <= 15) {
      len0 = max_st - min_st;
    } else {
      len0 = 15 - min_st;
      len1 = max_st - 15;
    }
  } else {
    len1 = max_st - min_st;
  }

  return make_pair(len0, len1);
}

bool modify_sub_1(int &vec, int &min_idx, int &max_idx, ll val) {
  if (val > 0 && val < 9001) {
    if (val < 1000) val += 1000;
    int idx = (int)val / 1000 - 1;
    if (vec >> idx & 1) {
      chmin(min_idx, idx);
      chmax(max_idx, idx);
      return true;
    }
  }

  return false;
}

bool modify_sub_2(vector<int> &vec, vector<int> &min_idx, vector<int> &max_idx, ll val, int idx0, int idx1, ll hw0, ll hw1) {
  if (val <= 0) return false;
  bool is_ok = false;
  REP(j, 8) {
    if (!(vec.at(idx0) >> j & 1)) continue;
    ll candi = (val - (j * 1000 + 1500) * hw0) / hw1;
    if (modify_sub_1(ref(vec.at(idx1)), ref(min_idx.at(idx1)), ref(max_idx.at(idx1)), candi)) {
      chmin(min_idx.at(idx0), j);
      chmax(max_idx.at(idx0), j);
      is_ok = true;
    }
  }

  return is_ok;
}

bool modify_sub(vector<int> &vec, vector<int> &mins, vector<int> &maxs, ll val, ll hw0, ll hw1) {
  if (hw0) {
    if (hw1) {  // 01
      if (modify_sub_2(ref(vec), ref(mins), ref(maxs), val, 0, 1, hw0, hw1)) {
        return true;
      }
    } else {  // 0
      if (modify_sub_1(ref(vec.at(0)), ref(mins.at(0)), ref(maxs.at(0)), val / hw0)) {
        return true;
      }
    }
  } else {  // 1
    if (modify_sub_1(ref(vec.at(1)), ref(mins.at(1)), ref(maxs.at(1)), val / hw1)) {
      return true;
    }
  }

  return false;
}

bool modify_1(int &hv, int &min_idx, int &max_idx, vector<int> &vec, vector<int> &mins, vector<int> &maxs, ll val, ll hw_main1, ll hw0, ll hw1) {
  if (val <= 0) return false;
  bool is_ok = false;
  REP(i, 8) {
    if (!(hv >> i & 1)) continue;
    ll candi = (val - (i * 1000 + 1500) * hw_main1);
    if (modify_sub(ref(vec), ref(mins), ref(maxs), candi, hw0, hw1)) {
      chmin(min_idx, i);
      chmax(max_idx, i);
      is_ok = true;
    }
  }

  return is_ok;
}

bool modify_2(vector<int> &hv, vector<int> &min_idx, vector<int> &max_idx, vector<int> &vec, vector<int> &mins, vector<int> &maxs, ll val, int idx0, int idx1, ll hw_main0, ll hw_main1, ll hw0, ll hw1) {
  if (val <= 0) return false;
  bool is_ok = false;
  REP(i, 8) {
    if (!(hv.at(idx0) >> i & 1)) continue;
    ll candi = (val - (i * 1000 + 1500) * hw_main0);
    if (modify_1(ref(hv.at(idx1)), ref(min_idx.at(idx1)), ref(max_idx.at(idx1)), ref(vec), ref(mins), ref(maxs), candi, hw_main1, hw0, hw1)) {
      chmin(min_idx.at(idx0), i);
      chmax(max_idx.at(idx0), i);
    }
  }

  return is_ok;
}

void modify_by_h(vector<vector<int> > &hs, vector<vector<int> > &vs, ll score, int sj, int ti, ll height0, ll height1, ll width0, ll width1) {
  vector<int> min_i(2, 9);
  vector<int> max_i(2, 0);
  vector<int> min_j(2, 9);
  vector<int> max_j(2, 0);

  if (width0) {
    if (width1) {  // w01
      modify_2(ref(hs.at(ti)), ref(min_i), ref(max_i), ref(vs.at(sj)), ref(min_j), ref(max_j), score, 0, 1, width0, width1, height0, height1);
    } else {  // w0
      modify_1(ref(hs.at(ti).at(0)), ref(min_i.at(0)), ref(max_i.at(0)), ref(vs.at(sj)), ref(min_j), ref(max_j), score, width0, height0, height1);
    }
  } else {
    if (width1) {  // w1
      modify_1(ref(hs.at(ti).at(1)), ref(min_i.at(1)), ref(max_i.at(1)), ref(vs.at(sj)), ref(min_j), ref(max_j), score, width1, height0, height1);
    } else {  // w len 0
      modify_sub(ref(vs.at(sj)), ref(min_j), ref(max_j), score, height0, height1);
    }
  }

  if (width0 + width1 > 0) {
    REP(idx, 2) {
      REP(i, min_i.at(idx)) hs.at(ti).at(idx) &= ~(1 << i);
      RREP(i, max_i.at(idx) + 1, 8) hs.at(ti).at(idx) &= ~(1 << i);
    }
  }

  REP(idx, 2) {
    REP(j, min_j.at(idx)) vs.at(sj).at(idx) &= ~(1 << j);
    RREP(j, max_j.at(idx) + 1, 8) vs.at(sj).at(idx) &= ~(1 << j);
  }
}

void modify_by_v(vector<vector<int> > &hs, vector<vector<int> > &vs, ll score, int sj, int ti, ll height0, ll height1, ll width0, ll width1) {
  vector<int> min_i(2, 9);
  vector<int> max_i(2, 0);
  vector<int> min_j(2, 9);
  vector<int> max_j(2, 0);

  if (height0) {
    if (height1) {  // h01
      modify_2(ref(vs.at(sj)), ref(min_j), ref(max_j), ref(hs.at(ti)), ref(min_i), ref(max_i), score, 0, 1, height0, height1, width0, width1);
    } else {  // h0
      modify_1(ref(vs.at(sj).at(0)), ref(min_j.at(0)), ref(max_j.at(0)), ref(hs.at(ti)), ref(min_i), ref(max_i), score, height0, width0, width1);
    }
  } else {
    if (height1) {  // h1
      modify_1(ref(vs.at(sj).at(1)), ref(min_j.at(1)), ref(max_j.at(1)), ref(hs.at(ti)), ref(min_i), ref(max_i), score, height1, width0, width1);
    } else {  // h len 0
      modify_sub(ref(hs.at(ti)), ref(min_i), ref(max_i), score, width0, width1);
    }
  }

  if (height0 + height1 > 0) {
    REP(idx, 2) {
      REP(j, min_j.at(idx)) vs.at(sj).at(idx) &= ~(1 << j);
      RREP(j, max_j.at(idx) + 1, 8) vs.at(sj).at(idx) &= ~(1 << j);
    }
  }

  REP(idx, 2) {
    REP(i, min_i.at(idx)) hs.at(ti).at(idx) &= ~(1 << i);
    RREP(i, max_i.at(idx) + 1, 8) hs.at(ti).at(idx) &= ~(1 << i);
  }
}

void modify_cost(vector<vector<int> > &hs, vector<vector<int> > &vs, ll score, int si, int sj, int ti, int tj) {
  auto [height0, height1] = get_length(si, ti);
  auto [width0, width1] = get_length(sj, tj);
  ll height = height0 + height1;
  ll width = width0 + width1;

  vector<int> prev_hs = hs.at(ti);
  vector<int> prev_vs = vs.at(sj);

  if (height < width) modify_by_v(ref(hs), ref(vs), score, sj, ti, height0, height1, width0, width1);
  else modify_by_h(ref(hs), ref(vs), score, sj, ti, height0, height1, width0, width1);

  if (hs.at(ti).at(0) == 0 && hs.at(ti).at(1) == 0) {
    for (auto &h : hs.at(ti)) h = 255;
    if (vs.at(sj).at(0) == 0 && vs.at(sj).at(1) == 0) {
      for (auto &v : vs.at(sj)) v = 255;
    } else if (vs.at(sj).at(0) == 0) {
      vs.at(sj).at(0) = 255;
      vs.at(sj).at(1) = prev_vs.at(1);
    } else if (vs.at(sj).at(1) == 0) {
      vs.at(sj).at(0) = prev_vs.at(0);
      vs.at(sj).at(1) = 255;
    } else {
      vs.at(sj) = prev_vs;
    }
  } else if (vs.at(sj).at(0) == 0 && vs.at(sj).at(1) == 0) {
    for (auto &v : vs.at(sj)) v = 255;
    if (hs.at(ti).at(0) == 0) {
      hs.at(ti).at(0) = 255;
      hs.at(ti).at(1) = prev_hs.at(1);
    } else if (hs.at(ti).at(1) == 0) {
      hs.at(ti).at(0) = prev_hs.at(0);
      hs.at(ti).at(1) = 255;
    } else {
      hs.at(ti) = prev_hs;
    }
  } else if (hs.at(ti).at(0) == 0) {
    hs.at(ti).at(0) = 255;
    hs.at(ti).at(1) = prev_hs.at(1);
    if (vs.at(sj).at(0) == 0) {
      vs.at(sj).at(0) = 255;
      vs.at(sj).at(1) = prev_vs.at(1);
    } else if (vs.at(sj).at(1) == 0) {
      vs.at(sj).at(0) = prev_vs.at(0);
      vs.at(sj).at(1) = 255;
    } else {
      vs.at(sj) = prev_vs;
    }
  } else if (hs.at(ti).at(1) == 0) {
    hs.at(ti).at(0) = prev_hs.at(0);
    hs.at(ti).at(1) = 255;
    if (vs.at(sj).at(0) == 0) {
      vs.at(sj).at(0) = 255;
      vs.at(sj).at(1) = prev_vs.at(1);
    } else if (vs.at(sj).at(1) == 0) {
      vs.at(sj).at(0) = prev_vs.at(0);
      vs.at(sj).at(1) = 255;
    } else {
      vs.at(sj) = prev_vs;
    }
  } else if (vs.at(sj).at(0) == 0) {
    vs.at(sj).at(0) = 255;
    vs.at(sj).at(1) = prev_vs.at(1);
    hs.at(ti) = prev_hs;
  } else if (vs.at(sj).at(1) == 0) {
    vs.at(sj).at(0) = prev_vs.at(0);
    vs.at(sj).at(1) = 255;
    hs.at(ti) = prev_hs;
  }
}

int main() {
  // clock_t start = clock();
  int query = 1000;
  int div = 200;
  vector<vector<int> > hs(30, vector<int>(2, 255));
  vector<vector<int> > vs(30, vector<int>(2, 255));

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
