#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;

const string filename = "input.txt";

enum {
  LINE = 0,
  PLUS,
  REV_L,
  SMALL_L,
  RECT,

  ROCK_COUNT
};

struct Vector2 {
  int x;
  int y;

  Vector2 operator+(const Vector2 &rhs) {
    Vector2 v = (Vector2){
        .x = x + rhs.x,
        .y = y + rhs.y,
    };
    return v;
  }

  Vector2 &to_side(bool side) {
    if (side)
      return left();
    return right();
  }

  Vector2 &left() {
    x -= 1;
    return *this;
  }

  Vector2 &right() {
    x += 1;
    return *this;
  }

  Vector2 get_down() { return (Vector2){x, y - 1}; }
};

unordered_map<int, vector<Vector2>> BLOCK_CELLS;

struct Tetris {
  string jets;
  int it_jet = 0;
  int height = 0;
  int next_rock = 0;
  unordered_map<int, unordered_map<int, bool>> cave;

  bool rock_empty(int type, Vector2 pos) {
    for (auto diff : BLOCK_CELLS.at(type)) {
      Vector2 cell_pos = pos + diff;
      if (!cell_empty(cell_pos))
        return false;
    }
    return true;
  }

  bool cell_empty(const Vector2 &pos) {
    if (pos.x < 0 || 6 < pos.x)
      return false;
    if (pos.y < 0)
      return false;
    return cave[pos.x][pos.y] == 0;
  }

  void place_rock(int type, Vector2 pos) {
    for (auto diff : BLOCK_CELLS.at(type)) {
      Vector2 cell_pos = pos + diff;
      cave[cell_pos.x][cell_pos.y] = 1;

      height = max(height, cell_pos.y + 1);
    }
  }

  void send_rock() {
    int current_rock = next_rock;
    next_rock = (next_rock + 1) % (ROCK_COUNT);

    Vector2 current_pos = (Vector2){2, height + 3};

    while (true) {
      auto next_side_pos = current_pos;
      next_side_pos.to_side(jets[it_jet]);
      it_jet = (it_jet + 1) % (jets.size());

      if (rock_empty(current_rock, next_side_pos))
        current_pos = next_side_pos;

      auto down = current_pos.get_down();
      if (rock_empty(current_rock, down))
        current_pos = down;
      else
        break;
    }

    place_rock(current_rock, current_pos);
  }
};

int main() {
  ifstream input(filename);
  assert(input.is_open());
  Tetris tetris;
  input >> tetris.jets;
  BLOCK_CELLS[LINE] = {(Vector2){0, 0}, (Vector2){1, 0}, (Vector2){2, 0},
                       (Vector2){3, 0}};
  BLOCK_CELLS[PLUS] = {(Vector2){1, 0}, (Vector2){0, 1}, (Vector2){1, 1},
                       (Vector2){2, 1}, (Vector2){1, 2}};
  BLOCK_CELLS[REV_L] = {(Vector2){0, 0}, (Vector2){1, 0}, (Vector2){2, 0},
                        (Vector2){2, 1}, (Vector2){2, 2}};
  BLOCK_CELLS[SMALL_L] = {(Vector2){0, 0}, (Vector2){0, 1}, (Vector2){0, 2},
                          (Vector2){0, 3}};
  BLOCK_CELLS[RECT] = {(Vector2){0, 0}, (Vector2){0, 1}, (Vector2){1, 0},
                       (Vector2){1, 1}};

  int TURN_COUNT = 2022;
  while (TURN_COUNT--) {
    TRACE2(TURN_COUNT, tetris.height);
    tetris.send_rock();
  }

  TRACE(tetris.height);
  return 0;
}
