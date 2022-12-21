#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
#define HASH(x, y) (x * 1000000 + y)
using namespace std;

const string filename = "input.txt";
const pair<int, int> source = {500, 0};

class Cave {
  // unordered_map<int, unordered_map<int, int>> mp;
  int mp[1000][1000];
  int sands = 0;

public:
  Cave() {
    for (int i = 0; i < 1000; i++)
      for (int j = 0; j < 1000; j++)
        mp[i][j] = 0;
  }

  int get_sand_count() { return sands; }
  void add_wall_point(int x, int y) {
    mp[x][y] = 1;
    // TRACE2(x, y);
  }
  void parse_wall_string(const string &line) {
    stringstream ss(line);
    int x, y;
    int px = -1, py = -1;
    char c;
    string dum;
    ss >> px >> c >> py >> dum;
    TRACE(line);

    while (!ss.eof()) {
      ss >> x >> c >> y >> dum;
      // cout << x << "|" << y << endl;
      // TRACE2(px, py);

      for (int i = min(px, x); i <= max(px, x); i++)
        for (int j = min(py, y); j <= max(py, y); j++)
          add_wall_point(i, j);

      px = x;
      py = y;
    }
  }

  bool feed_sand() {
    int x = source.first;
    int y = source.second;

    int t = 100000;
    while (t-- > 0) {
      if (mp[x][y + 1] == 0) {
        y++;
      } else if (mp[x - 1][y + 1] == 0) {
        x--;
        y++;
      } else if (mp[x + 1][y + 1] == 0) {
        x++;
        y++;
      } else
        break; // at rest
    }

    if (t <= 0)
      return false;

    mp[x][y] = 2;
    sands++;
    // TRACE(sands);
    // TRACE2(x, y);
    return true;
  }
};

/*
21
22  o
23  ###
*/

int main() {
  ifstream input(filename);
  assert(input.is_open());

  Cave cave;
  string line;
  while (input.good()) {
    getline(input, line);
    cave.parse_wall_string(line);
  }

  while (cave.feed_sand())
    ;
  TRACE(cave.get_sand_count());
  return 0;
}
