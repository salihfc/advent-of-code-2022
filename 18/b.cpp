#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;

#define PRIME (101)
const string filename = "input.txt";

struct Vector3 {
  int x;
  int y;
  int z;

  vector<Vector3> sides() {
    return {
        (Vector3){x + 1, y, z}, (Vector3){x - 1, y, z}, (Vector3){x, y + 1, z},
        (Vector3){x, y - 1, z}, (Vector3){x, y, z + 1}, (Vector3){x, y, z - 1},
    };
  }

  bool operator==(const Vector3 &rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
  }

  bool operator<(const Vector3 &rhs) const {
    return (x != rhs.x) ? x < rhs.x : (y != rhs.y) ? y < rhs.y : z < rhs.z;
  }
};

/*
  Custom hash for unordered_map / unordered_set
*/
class Vector3Hash {
public:
  size_t operator()(const Vector3 &t) const {
    return t.x + t.y * PRIME + t.z * PRIME * PRIME;
  }
};

struct FloodFill {
  unordered_set<Vector3, Vector3Hash> visited;
  int hit_sides = 0;

  void start(Vector3 pos, unordered_set<Vector3, Vector3Hash> &mp,
             int max_dist) {
    visited.insert(pos);
    queue<pair<Vector3, int>> q;
    q.push({pos, 0});

    while (!q.empty()) {
      auto cur = q.front();
      q.pop();

      if (cur.second >= max_dist)
        continue;

      for (auto side : cur.first.sides()) {
        if (mp.count(side)) // occupied
          hit_sides++;
        else {
          if (visited.count(side) == 0) {
            visited.insert(side);
            q.push({side, cur.second + 1});
          }
        }
      }
    }
  }
};

int main() {
  ifstream input(filename);
  assert(input.is_open());
  int x, y, z;
  char c;

  vector<Vector3> cubes;
  unordered_set<Vector3, Vector3Hash> hashmap;

  while (input >> x >> c >> y >> c >> z) {
    Vector3 cube = (Vector3){x, y, z};
    cubes.push_back(cube);
    hashmap.insert(cube);
  }

  FloodFill fill;
  fill.start((Vector3){0, 0, 0}, hashmap, 250);
  TRACE(fill.hit_sides);
  return 0;
}
// 2518