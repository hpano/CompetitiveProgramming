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

struct Ad {
  int id;
  int x;
  int y;
  int r;

  bool operator<( const Ad& right ) const {
        return x == right.x ? y < right.y : x < right.x;
    }
};

struct Answer {
  int a;
  int b;
  int c;
  int d;
};

double calc_point(Ad &ad, int a, int b, int c, int d) {
  double ans = 0.0;
  if (a > ad.x || c < ad.x || b > ad.y || d < ad.y) return ans;

  int s = (c - a) * (d - b);
  ans = 1.0 - pow(1.0 - (double)min(ad.r, s) / max(ad.r, s), 2.0);

  return ans;
}

void spread_ad(int target, vector<Ad> &ads, vector<Answer> &ans, vector<vector<bool> > &grid, int direction) {
  double p_before;
  double p_after;
  int new_val;
  switch (direction) {
    case 0:  // spread -x
      new_val = ans.at(target).a - 1;
      if (new_val < 0) return;
      REP(i, ans.at(target).b, ans.at(target).d) {
        if (grid.at(new_val).at(i)) return;
      }

      p_before = calc_point(ref(ads.at(target)), ans.at(target).a, ans.at(target).b, ans.at(target).c, ans.at(target).d);
      p_after = calc_point(ref(ads.at(target)), new_val, ans.at(target).b, ans.at(target).c, ans.at(target).d);
      if (p_after < p_before) return;

      ans.at(target).a = new_val;
      REP(i, ans.at(target).b, ans.at(target).d) {
        grid.at(new_val).at(i) = true;
      }
      break;
    case 1:  // spread -y
      new_val = ans.at(target).b - 1;
      if (new_val < 0) return;
      REP(i, ans.at(target).a, ans.at(target).c) {
        if (grid.at(i).at(new_val)) return;
      }

      p_before = calc_point(ref(ads.at(target)), ans.at(target).a, ans.at(target).b, ans.at(target).c, ans.at(target).d);
      p_after = calc_point(ref(ads.at(target)), ans.at(target).a, new_val, ans.at(target).c, ans.at(target).d);
      if (p_after < p_before) return;

      ans.at(target).b = new_val;
      REP(i, ans.at(target).a, ans.at(target).c) {
        grid.at(i).at(new_val) = true;
      }
      break;
    case 2:  // spread +x
      new_val = ans.at(target).c + 1;
      if (new_val > 10000) return;
      REP(i, ans.at(target).b, ans.at(target).d) {
        if (grid.at(new_val - 1).at(i)) return;
      }

      p_before = calc_point(ref(ads.at(target)), ans.at(target).a, ans.at(target).b, ans.at(target).c, ans.at(target).d);
      p_after = calc_point(ref(ads.at(target)), ans.at(target).a, ans.at(target).b, new_val, ans.at(target).d);
      if (p_after < p_before) return;

      ans.at(target).c = new_val;
      REP(i, ans.at(target).b, ans.at(target).d) {
        grid.at(new_val - 1).at(i) = true;
      }
      break;
    case 3:  // spread +y
      new_val = ans.at(target).d + 1;
      if (new_val > 10000) return;
      REP(i, ans.at(target).a, ans.at(target).c) {
        if (grid.at(i).at(new_val - 1)) return;
      }

      p_before = calc_point(ref(ads.at(target)), ans.at(target).a, ans.at(target).b, ans.at(target).c, ans.at(target).d);
      p_after = calc_point(ref(ads.at(target)), ans.at(target).a, ans.at(target).b, ans.at(target).c, new_val);
      if (p_after < p_before) return;

      ans.at(target).d = new_val;
      REP(i, ans.at(target).a, ans.at(target).c) {
        grid.at(i).at(new_val - 1) = true;
      }
      break;
    default:
      break;
    cout << target << " a: " << ans.at(target).a << " b: " << ans.at(target).b << " c: " << ans.at(target).c << " d: " << ans.at(target).d << endl;
  }
}

void decide_action(vector<Ad> &ads, vector<Answer> &ans, vector<vector<bool> > &grid, mt19937 &mt, uniform_int_distribution<> &rand) {
  int target = rand(mt);
  int action = rand(mt) % 4;
  if (action < 4) {
    spread_ad(target, ref(ads), ref(ans), ref(grid), action % 4);
  }
}

int main() {
  clock_t start = clock();
  IN(int, n);
  vector<Ad> ads(n);
  vector<Answer> ans(n);
  vector<vector<bool> > grid(10000, vector<bool>(10000, false));
  REP(i, n) {
    ads.at(i).id = i;
    IN(int, x);
    IN(int, y);
    IN(int, r);
    ads.at(i).x = x;
    ads.at(i).y = y;
    ads.at(i).r = r;
    ans.at(i).a = x;
    ans.at(i).b = y;
    ans.at(i).c = x + 1;
    ans.at(i).d = y + 1;
    grid.at(ads.at(i).x).at(ads.at(i).y) = true;
  }

  random_device rnd;
  mt19937 mt(rnd());
  uniform_int_distribution<> rand(0, n - 1);

  clock_t mid = clock();
  // int count = 0;
  while ((double)(mid - start) / CLOCKS_PER_SEC < 4.9) {
    decide_action(ref(ads), ref(ans), ref(grid), ref(mt), ref(rand));
    mid = clock();
    // count++;
  } 
  // cout << (double)(mid - start) / CLOCKS_PER_SEC << ", " << count << endl;

  REP(i, n) {
    cout << ans.at(i).a << " " << ans.at(i).b << " " << ans.at(i).c << " " << ans.at(i).d << endl;
  }

  return 0;
}
