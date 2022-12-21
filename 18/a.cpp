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

  bool operator<(const Vector3 &rhs) const {
    return (x != rhs.x) ? x < rhs.x : (y != rhs.y) ? y < rhs.y : z < rhs.z;
  }
};

int main() {
  ifstream input(filename);
  assert(input.is_open());
  int x, y, z;
  char c;

  vector<Vector3> cubes;
  map<Vector3, int> hashmap;

  while (input >> x >> c >> y >> c >> z) {
    Vector3 cube = (Vector3){x, y, z};
    cubes.push_back(cube);
    hashmap[cube] = 1;
  }

  int open_side_count = 0;
  for (Vector3 &cube : cubes) {
    for (Vector3 &side : cube.sides())
      open_side_count += (hashmap[side] == 0);
  }

  TRACE(open_side_count);
  return 0;
}
