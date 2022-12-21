#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

int main() {
  ifstream input(filename);
  assert(input.is_open());

  char dm;
  int ct = 0;
  int x, y, z, w;
  while (input >> x >> dm >> y >> dm >> z >> dm >> w) {
    ct += !(x > w || z > y);
  }

  cout << ct << endl;
  return 0;
}
