#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;

const string filename = "input.txt";
const int ROW = 2000000;

int main() {
  ifstream input(filename);
  assert(input.is_open());
  string sdum;
  char cdum;
  int xs, ys;
  int xb, yb;

  map<int, int> mp;
  set<int> beacons_at_row;

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
    // TRACE2(xs, ys);
    // TRACE2(xb, yb);

    if (yb == ROW) {
      beacons_at_row.insert(xb);
      TRACE(xb);
    }

    const double base_dist = abs(xs - xb) + abs(ys - yb);

    int r = base_dist - abs(ys - ROW);
    if (r > 0) {
      int x_min = xs - r;
      int x_max = xs + r;
      mp[x_min]++;
      mp[x_max + 1]--;

      TRACE2(x_min, x_max);
    }
  }

  for (auto x : beacons_at_row)
    TRACE(x);
  int ct = 0;

  int depth = 0;
  const int NOT_SET = -2e9;
  int start = NOT_SET;

  for (auto x : mp) {
    int idx = x.first;
    depth += x.second;
    TRACE2(idx, depth);
    // TRACE(depth);
    if (start == NOT_SET) {
      start = idx;
    } else if (depth == 0) {
      ct += (idx - start);

      for (auto x : beacons_at_row)
        if (start <= x && x < idx) {
          TRACE2("deduct", x)
          ct--;
        }

      TRACE2(start, idx);
      start = NOT_SET;
    }
  }

  TRACE(ct);
  return 0;
}
