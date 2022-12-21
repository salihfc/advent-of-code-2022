#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
#define HASH(x, y) (x * 1000000 + y)
using namespace std;

const string filename = "input.txt";
static const int sign(int x) { return (x == 0) ? 0 : ((x < 0) ? -1 : 1); }

struct Vector2 {
  int x;
  int y;

  bool touching(Vector2 other) {
    return (abs(x - other.x) <= 1 && abs(y - other.y) <= 1);
  }

  void move_toward(Vector2 other) {
    x += sign(other.x - x);
    y += sign(other.y - y);
  }

  void move(char dir) {
    switch (dir) {
    case 'U':
      y += 1;
      break;
    case 'D':
      y -= 1;
      break;
    case 'R':
      x += 1;
      break;
    case 'L':
      x -= 1;
      break;

    default:
      assert(0);
      break;
    }
  }

  friend ostream &operator<<(ostream &output, const Vector2 &vec) {
    output << "[" << vec.x << ", " << vec.y << "]";
    return output;
  }
};

struct RopeSim {
  Vector2 head;
  Vector2 tail[9];

  unordered_set<int> visited_by_tail;

  void move(char dir) {
    head.move(dir);
    if (!head.touching(tail[0])) {
      tail[0].move_toward(head);
    }

    for (int i = 1; i < 9; i++) {
      if (!tail[i - 1].touching(tail[i])) {
        tail[i].move_toward(tail[i - 1]);
      }
    }

    visited_by_tail.insert(HASH(tail[8].x, tail[8].y));
  }
  int ans() { return visited_by_tail.size(); }
};

int main() {
  ifstream input(filename);
  assert(input.is_open());
  char dir;
  int step;

  RopeSim sim = (RopeSim){.head = (Vector2){0, 0},
                          .tail = {
                              (Vector2){0, 0},
                              (Vector2){0, 0},
                              (Vector2){0, 0},
                              (Vector2){0, 0},
                              (Vector2){0, 0},
                              (Vector2){0, 0},
                              (Vector2){0, 0},
                              (Vector2){0, 0},
                              (Vector2){0, 0},
                          }};

  sim.visited_by_tail.insert(HASH(sim.tail[8].x, sim.tail[8].y));
  int ct = 0;

  while (input >> dir >> step) {
    while (step--) {
      sim.move(dir);
      ct++;
    }
  }

  TRACE(sim.ans());
  return 0;
}
