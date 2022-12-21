#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;

#define int long long
#define MAXX (4000000LL)
#define TUNE(x, y) (x * MAXX + y)
#define CROSS(tune) (tune / MAXX + (tune % MAXX) * MAXX)

const string filename = "input.txt";

const int MIN_COORD = 0LL;
const int MAX_COORD = MAXX;

signed main() {
  ifstream input(filename);
  assert(input.is_open());
  string sdum;
  char cdum;
  int xs, ys;
  int xb, yb;

  map<int, int> mp;
  set<int> beacons_at_row;

  // TRACE(CROSS(10589795131431));
  // return 0;

  while (true) {
    input.ignore(12);
    if (input.eof())
      break;

    input >> xs;
    input.ignore(4);
    input >> ys;
    input.ignore(25);
    input >> xb;
    input.ignore(4);
    input >> yb;
    input.ignore(); // for '\n'

    const int base_dist = abs(xs - xb) + abs(ys - yb);

    int l = max(0LL, ys - base_dist);
    int r = min(base_dist + ys, MAX_COORD);
    TRACE2(l, r);

    for (int ROW = l; ROW <= r; ROW++) {
      int r = base_dist - abs(ys - ROW);
      int x_min = max(0LL, xs - r);
      int x_max = min(MAXX, xs + r);

      mp[TUNE(ROW, x_min)]++;
      mp[TUNE(ROW, x_max + 1)]--;
    }
  }

  int depth = 0;
  const int NOT_SET = -2e9;
  int start = NOT_SET;

  for (auto x : mp) {
    int idx = x.first;
    depth += x.second;
    // TRACE2(idx, depth);
    // TRACE(depth);
    if (start == NOT_SET) {
      start = idx;
    } else if (depth == 0) {
      TRACE2(start, idx - 1);
      start = NOT_SET;
    }
  }
}
