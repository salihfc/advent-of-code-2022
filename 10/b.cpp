#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
#define HASH(x, y) (x * 1000000 + y)
using namespace std;

const string filename = "input.txt";
int sig[300];
int cycle = 0;

int main() {
  ifstream input(filename);
  assert(input.is_open());
  string op;

  stack<int> pending;

  sig[0] = 1;
  cycle = 1;

  while (input >> op) {
    if (op == "noop") {

      if (pending.empty()) {
        sig[cycle] = sig[cycle - 1];
      } else {
        sig[cycle] = pending.top();
        pending.pop();
      }
    } else if (op == "addx") {
      int t = 0;
      input >> t;

      if (pending.empty()) {
        sig[cycle] = sig[cycle - 1];
      } else {
        sig[cycle] = pending.top();
        pending.pop();
      }

      cycle++;

      if (pending.empty()) {
        sig[cycle] = sig[cycle - 1];
      } else {
        sig[cycle] = pending.top();
        pending.pop();
      }

      int k = sig[cycle] + t;
      pending.push(k);
    }

    cycle++;
  }

  while (pending.size()) {
    sig[cycle++] = pending.top();
    pending.pop();
  }

  const int W = 40;
  const int H = 6;

  for (int i = 0; i < H; i++) {
    for (int j = 1; j <= W; j++) {
      int x = sig[W * i + j];
      if (j == x || j == x + 1 || j == x + 2)
        cout << "#";
      else
        cout << ".";
    }
    cout << endl;
  }

  return 0;
}
