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

using edge_que_t = tuple<ll, vector<vector<int> >, vector<vector<int> > >;
/*
void init_edge(priority_queue<edge_que_t, vector<edge_que_t>, greater<edge_que_t> > &edges, int size) {
  random_device rnd;
  mt19937 mt(rnd());
  uniform_int_distribution<> randD(100, 2000);
  uniform_int_distribution<> randM(1, 2);

  REP(s, size) {
    vector<vector<vector<int> > > edge(2, vector<vector<int> >(30, vector<int>(29)));
    for (auto &e : edge) {
      int D = randD(mt);
      int M = randM(mt);
      uniform_int_distribution<> randHV(1000 + D, 9000 - D);
      uniform_int_distribution<> randDelGam(-D, D);
      uniform_int_distribution<> randxy(1, 28);
      int div = 29;
      if (M == 2) div = randxy(mt);

      REP(i, 30) {
        int HV0 = randHV(mt);
        int HV1 = randHV(mt);
        REP(j, 29) {
          int DelGam = randDelGam(mt);
          if (j < div) {
            e.at(i).at(j) = HV0 + DelGam;
          } else {
            e.at(i).at(j) = HV1 + DelGam;
          }
        }
      }
    }
    edges.push(make_tuple(0, edge.at(0), edge.at(1)));
  }
}
*/
void init_edge(priority_queue<edge_que_t, vector<edge_que_t>, greater<edge_que_t> > &edges, int size) {
  random_device rnd;
  mt19937 mt(rnd());
  uniform_int_distribution<> rand_val(1, 8);

  REP(s, size) {
    vector<vector<vector<int> > > edge(2);
    for (auto &e : edge) {
      REP(i, 30) {
        int val = rand_val(mt) * 1000 + 500;
        vector<int> tmp(29, val);
        e.emplace_back(tmp);
      }
    }
    edges.push(make_tuple(0, edge.at(0), edge.at(1)));
  }
}

string calc_route(vector<vector<int> > &hs, vector<vector<int> > &vs, int si, int sj, int ti, int tj) {
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
  if (si == ti) opp_cost_y1 = opp_cost_y2 = 2000;
  if (sj == tj) opp_cost_x1 = opp_cost_x2 = 2000;

  while (!que.empty() && total_cost.at(ti).at(tj).first == LLONG_MAX) {
    tuple<ll, int, int> t = que.top();
    que.pop();
    ll cost = get<0>(t);
    int x = get<1>(t);
    int y = get<2>(t);

    if (total_cost.at(x).at(y).first < cost) continue;
    if (x > 0 && chmin(total_cost.at(x - 1).at(y).first, cost + vs.at(y).at(x - 1) + opp_cost_x1)) {
      total_cost.at(x - 1).at(y).second = 'U';
      que.push(make_tuple(total_cost.at(x - 1).at(y).first, x - 1, y));
    }
    if (x < 29 && chmin(total_cost.at(x + 1).at(y).first, cost + vs.at(y).at(x) + opp_cost_x2)) {
      total_cost.at(x + 1).at(y).second = 'D';
      que.push(make_tuple(total_cost.at(x + 1).at(y).first, x + 1, y));
    }
    if (y > 0 && chmin(total_cost.at(x).at(y - 1).first, cost + hs.at(x).at(y - 1) + opp_cost_y1)) {
      total_cost.at(x).at(y - 1).second = 'L';
      que.push(make_tuple(total_cost.at(x).at(y - 1).first, x, y - 1));
    }
    if (y < 29 && chmin(total_cost.at(x).at(y + 1).first, cost + hs.at(x).at(y) + opp_cost_y2)) {
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

void calc_point(priority_queue<edge_que_t, vector<edge_que_t>, greater<edge_que_t> > &edge_que, string order, ll score, int si, int sj) {
  priority_queue<edge_que_t, vector<edge_que_t>, greater<edge_que_t> > new_que;
  ll limit = 0;
  // cerr << edge_que.size() << endl;
  while (!edge_que.empty()) {
    edge_que_t t = edge_que.top();
    edge_que.pop();

    if (limit == 0) limit = get<0>(t) * 2;
    else if (get<0>(t) > limit) break;
    int ni = si, nj = sj;
    ll cost = 0;
    for (auto const &c : order) {
      if (c == 'D') {
        cost += get<2>(t).at(nj).at(ni);
        ni++;
      } else if (c == 'R') {
        cost += get<1>(t).at(ni).at(nj);
        nj++;
      } else if (c == 'U') {
        cost += get<2>(t).at(nj).at(ni - 1);
        ni--;
      } else if (c == 'L') {
        cost += get<1>(t).at(ni).at(nj - 1);
        nj--;
      }
    }

    get<0>(t) += abs(score - cost);
    new_que.push(t);
  }
  edge_que = new_que;
  // cerr << edge_que.size() << endl;
}

int main() {
  // clock_t start = clock();
  int query = 1000;
  int edge_size = 1600;
  priority_queue<edge_que_t, vector<edge_que_t>, greater<edge_que_t> > edge_que;
  init_edge(ref(edge_que), edge_size);

  REP(q, query) {
    // clock_t mid = clock();
    // assert((double)(mid - start) / CLOCKS_PER_SEC < 1.999);
    IN(int, si);
    IN(int, sj);
    IN(int, ti);
    IN(int, tj);
    edge_que_t edge = edge_que.top();
    string order = calc_route(get<1>(edge), get<2>(edge), si, sj, ti, tj);
    cout << order << endl;
    IN(ll, score);
    if (edge_que.size() > 1) calc_point(ref(edge_que), order, score, si, sj);
    if (q < 100 && edge_que.size() < 3) {
      int count = 0;
      priority_queue<edge_que_t, vector<edge_que_t>, greater<edge_que_t> > tmp_que;
      while (!edge_que.empty()) {
        edge_que_t tmp = edge_que.top();
        edge_que.pop();
        get<0>(tmp) = -5 + count;
        tmp_que.push(tmp);
        count++;
      }
      edge_que = tmp_que;
      init_edge(ref(edge_que), edge_size);
    }
  }

  return 0;
}
