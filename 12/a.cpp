#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
#define HASH(x, y) (x * 1000000 + y)
using namespace std;

const string filename = "input.txt";

class Vector2 {
public:
  int x = 0;
  int y = 0;

  Vector2(int _x = 0, int _y = 0) : x(_x), y(_y) {}
  bool operator==(const Vector2 &rhs) const {
    return (x == rhs.x) && (y == rhs.y);
  }
  bool operator<(const Vector2 &rhs) const {
    return (x == rhs.x) ? y > rhs.y : (x > rhs.x);
  }

  vector<Vector2> neighbors() {
    return {(Vector2){x + 1, y}, (Vector2){x - 1, y}, (Vector2){x, y + 1},
            (Vector2){x, y - 1}};
  }
};

struct BFSState {
  Vector2 pos;
  int depth;

  bool operator<(const BFSState &rhs) const { return depth > rhs.depth; }
};

int bfs(Vector2 start, Vector2 end, vector<string> &mp) {
  set<Vector2> visited;
  visited.insert(start);
  priority_queue<BFSState> q;
  q.push((BFSState){.pos = start, .depth = 0});

  while (!q.empty()) {
    auto cur = q.top();
    q.pop();
    TRACE2(cur.pos.x, cur.pos.y);

    if (cur.pos == end) {
      return cur.depth;
    }

    auto v = cur.pos.neighbors();

    for (auto &next : v) {
      if (visited.count(next))
        continue;

      if (next.x < 0 || mp.size() <= next.x || next.y < 0 ||
          mp[0].size() <= next.y)
        continue;

      if (mp[next.x][next.y] > mp[cur.pos.x][cur.pos.y] + 1)
        continue;

      visited.insert(next);
      q.push((BFSState){next, (cur.depth + 1)});
    }
  }

  return -1;
}

int main() {
  ifstream input(filename);
  assert(input.is_open());
  vector<string> v;
  string line;
  while (input >> line) {
    if (line.back() == '\n')
      line.pop_back();
    v.push_back(line);
  }

  Vector2 start;
  Vector2 end;

  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      if (v[i][j] == 'S') {
        start = (Vector2){i, j};
        v[i][j] = 'a';
      } else if (v[i][j] == 'E') {
        end = (Vector2){i, j};
        v[i][j] = 'z';
      }
    }
  }

  int k = bfs(start, end, v);
  TRACE(k);
  return 0;
}
