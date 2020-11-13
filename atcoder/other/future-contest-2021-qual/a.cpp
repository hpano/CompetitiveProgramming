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

int num = 100;
int grid_size = 20;
vector<char> orders = {'U', 'D', 'L', 'R', 'I', 'O'};

struct Pos {
  int x;
  int y;

  Pos() {}
  Pos(int x_pos, int y_pos) {
    x = x_pos;
    y = y_pos;
  }

  bool check_in(Pos start, Pos goal) {
    int small_x = min(start.x, goal.x);
    int large_x = max(start.x, goal.x);
    int small_y = min(start.y, goal.y);
    int large_y = max(start.y, goal.y);
    Pos tmp(x, y);

    return (tmp != start && tmp != goal && x >= small_x && x <= large_x && y >= small_y && y <= large_y);
  }

  bool operator == (const Pos& pos) const {
    return (x == pos.x && y == pos.y);
  }

  bool operator != (const Pos& pos) const {
    return (x != pos.x || y != pos.y);
  }
};

vector<Pos> card_pos(num);
vector<vector<int> > grid(grid_size, vector<int>(grid_size, -1));

// vector<Pos> final_pos = {
//   {15, 19}, {15, 18}, {15, 17}, {15, 16}, {15, 15}, {15, 14}, {15, 13}, {15, 12}, {15, 11}, {15, 10}, {15, 9}, {15, 8}, {15, 7}, {15, 6}, {15, 5}, {15, 4}, {15, 3}, {15, 2}, {15, 1}, {15, 0},
//   {16, 0}, {16, 1}, {16, 2}, {16, 3}, {16, 4}, {16, 5}, {16, 6}, {16, 7}, {16, 8}, {16, 9}, {16, 10}, {16, 11}, {16, 12}, {16, 13}, {16, 14}, {16, 15}, {16, 16}, {16, 17}, {16, 18}, {16, 19},
//   {17, 19}, {17, 18}, {17, 17}, {17, 16}, {17, 15}, {17, 14}, {17, 13}, {17, 12}, {17, 11}, {17, 10}, {17, 9}, {17, 8}, {17, 7}, {17, 6}, {17, 5}, {17, 4}, {17, 3}, {17, 2}, {17, 1}, {17, 0},
//   {18, 0}, {18, 1}, {18, 2}, {18, 3}, {18, 4}, {18, 5}, {18, 6}, {18, 7}, {18, 8}, {18, 9}, {18, 10}, {18, 11}, {18, 12}, {18, 13}, {18, 14}, {18, 15}, {18, 16}, {18, 17}, {18, 18}, {18, 19},
//   {19, 19}, {19, 18}, {19, 17}, {19, 16}, {19, 15}, {19, 14}, {19, 13}, {19, 12}, {19, 11}, {19, 10}, {19, 9}, {19, 8}, {19, 7}, {19, 6}, {19, 5}, {19, 4}, {19, 3}, {19, 2}, {19, 1}, {19, 0}
// };

vector<Pos> final_pos = {
  {10, 9}, {10, 10}, {9, 10}, {9, 9}, {9, 8}, {10, 8}, {11, 8}, {11, 9}, {11, 10}, {11, 11}, {10, 11}, {9, 11}, {8, 11}, {8, 10}, {8, 9}, {8, 8}, {8, 7}, {9, 7}, {10, 7}, {11, 7},
  {12, 7}, {12, 8}, {12, 9}, {12, 10}, {12, 11}, {12, 12}, {11, 12}, {10, 12}, {9, 12}, {8, 12}, {7, 12}, {7, 11}, {7, 10}, {7, 9}, {7, 8}, {7, 7}, {7, 6}, {8, 6}, {9, 6}, {10, 6},
  {11, 6}, {12, 6}, {13, 6}, {13, 7}, {13, 8}, {13, 9}, {13, 10}, {13, 11}, {13, 12}, {13, 13}, {12, 13}, {11, 13}, {10, 13}, {9, 13}, {8, 13}, {7, 13}, {6, 13}, {6, 12}, {6, 11}, {6, 10},
  {6, 9}, {6, 8}, {6, 7}, {6, 6}, {6, 5}, {7, 5}, {8, 5}, {9, 5}, {10, 5}, {11, 5}, {12, 5}, {13, 5}, {14, 5}, {14, 6}, {14, 7}, {14, 8}, {14, 9}, {14, 10}, {14, 11}, {14, 12},
  {14, 13}, {14, 14}, {13, 14}, {12, 14}, {11, 14}, {10, 14}, {9, 14}, {8, 14}, {7, 14}, {6, 14}, {5, 14}, {5, 13}, {5, 12}, {5, 11}, {5, 10}, {5, 9}, {5, 8}, {5, 7}, {5, 6}, {5, 5}
};

struct Robo {
  Pos pos;
  deque<int> card;
  string order;
  int move_count;
  vector<vector<int> > map;

  Robo() {
    pos.x = 0;
    pos.y = 0;
    card.clear();
    order = "";
    move_count = 0;
    map = grid;
  }

  void move_action(Pos dest) {
    int x_move = dest.x - pos.x;
    int y_move = dest.y - pos.y;

    if (y_move >= 0) {
      REP(i, y_move) order += 'R';
    } else {
      y_move = abs(y_move);
      REP(i, y_move) order += 'L';
    }

    if (x_move >= 0) {
      REP(i, x_move) order += 'D';
    } else {
      x_move = abs(x_move);
      REP(i, x_move) order += 'U';
    }

    pos = dest;
    move_count += x_move + y_move;
  }

  void move(Pos goal) {
    while (!card.empty()) {
      int target = card.back();
      if (final_pos.at(target).check_in(pos, goal)) {
        move_action(final_pos.at(target));
        put_card();
      } else {
        break;
      }
    }
    move_action(goal);
  }

  void get_card(int id) {
    card.push_back(id);
    order += 'I';
    map.at(pos.x).at(pos.y) = -1;
  }

  void put_card() {
    if (map.at(pos.x).at(pos.y) != -1) return;
    int target = card.back();
    card.pop_back();
    order += 'O';
    map.at(pos.x).at(pos.y) = target;
  }
};

void init() {
  REP(i, num) {
    IN(int, x);
    IN(int, y);
    Pos tmp(x, y);
    card_pos.at(i) = tmp;
    grid.at(x).at(y) = i;
  }

  // REP(i, grid_size) {
  //   REP(j, grid_size) {
  //     printf("%2d ", grid.at(i).at(j));
  //   }
  //   cout << endl;
  // }
}

void align_final_pos(Robo &robo) {
  while (!robo.card.empty()) {
    int target = robo.card.back();
    robo.move(final_pos.at(target));
    robo.put_card();
  }

  REP(i, num) {
    robo.move(final_pos.at(i));
    robo.get_card(i);
  }
}

pair<int, string> solve(vector<int> &jun) {
  Robo robo;

  REP(i, num) {
    int target = jun.at(i);
    if (final_pos.at(target) == card_pos.at(target)) continue;
    robo.move(card_pos.at(target));
    robo.get_card(target);
  }

  align_final_pos(robo);

  return make_pair(robo.move_count, robo.order);
}

int main() {
  int count = 4000;
  string order = "";
  vector<int> jun;

  std::chrono::system_clock::time_point  start, end;
  start = std::chrono::system_clock::now();
  end = start + std::chrono::milliseconds(2800);
  std::random_device rnd;
  std::mt19937 mt(rnd());

  init();
  vector<int> block_sizes = {1, 2, 4, 5, 10, 20};
  REP(bs, block_sizes.size()) {
    int block_size = block_sizes.at(bs);
    REP(x_move, -5, 6) {
      REP(i, num) final_pos.at(i).x += x_move;
      REP(y_move, -5, 6) {
        REP(i, num) final_pos.at(i).y += y_move;

        jun.clear();
        for (int block = 0; block * block_size < grid_size; ++block) {
          if (block % 2 == 0) {
            REP(i, grid_size) {
              if (i % 2 == 0) {
                REP(j, block * block_size, (block + 1) * block_size) {
                  if (grid.at(i).at(j) != -1) jun.emplace_back(grid.at(i).at(j));
                }
              } else {
                RREP(j, block * block_size, (block + 1) * block_size) {
                  if (grid.at(i).at(j) != -1) jun.emplace_back(grid.at(i).at(j));
                }
              }
            }
          } else {
            RREP(i, grid_size) {
              if (i % 2 == 0) {
                REP(j, block * block_size, (block + 1) * block_size) {
                  if (grid.at(i).at(j) != -1) jun.emplace_back(grid.at(i).at(j));
                }
              } else {
                RREP(j, block * block_size, (block + 1) * block_size) {
                  if (grid.at(i).at(j) != -1) jun.emplace_back(grid.at(i).at(j));
                }
              }
            }
          }
        }

        int tmp_count;
        string tmp_order;
        tie(tmp_count, tmp_order) = solve(jun);
        if (tmp_count < count) {
          count = tmp_count;
          order = tmp_order;
        }

        cerr << block_size << ", " << tmp_count << endl;
        // cerr << tmp_count << endl;

        REP(i, num) final_pos.at(i).y -= y_move;
      }
      REP(i, num) final_pos.at(i).x -= x_move;
    }
  }

  int cicle_count = 0;
  while (std::chrono::system_clock::now() < end) {
    int tmp_count;
    string tmp_order;
    tie(tmp_count, tmp_order) = solve(jun);
    if (tmp_count < count) {
      count = tmp_count;
      order = tmp_order;
    }
    // cerr << tmp_count << endl;
    shuffle(ALL(jun), mt);
    cicle_count++;
  }

  cout << order << endl;
  cerr << count << endl;
  cerr << cicle_count << endl;

  return 0;
}
