#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

vector<vector<char>> stacks = {
    {'D', 'T', 'R', 'B', 'J', 'L', 'W', 'G'},
    {'S', 'W', 'C'},
    {'R', 'Z', 'T', 'M'},
    {'D', 'T', 'C', 'H', 'S', 'P', 'V'},
    {'G', 'P', 'T', 'L', 'D', 'Z'},
    {'F', 'B', 'R', 'Z', 'J', 'Q', 'C', 'D'},
    {'S', 'B', 'D', 'J', 'M', 'F', 'T', 'R'},
    {'L', 'H', 'R', 'B', 'T', 'V', 'M'},
    {'Q', 'P', 'D', 'S', 'V'},
};

bool do_move(int src, int dst, int ct) {
  stack<char> k;
  while (ct--) {
    k.push(stacks[src].back());
    stacks[src].pop_back();
  }

  while (!k.empty()) {
    stacks[dst].push_back(k.top());
    k.pop();
  }
  return true;
}

int main() {
  ifstream input(filename);
  assert(input.is_open());
  int ct = 0, src = 0, dst = 0;
  string dum;

  while (input >> dum >> ct >> dum >> src >> dum >> dst &&
         do_move(src - 1, dst - 1, ct))
    ;

  for (auto v : stacks)
    cout << v.back();

  return 0;
}
