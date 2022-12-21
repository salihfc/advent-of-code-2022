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
      TRACE(t);

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

  while (cycle < 300) {
    sig[cycle] = sig[cycle - 1];
    cycle++;
  }

  const int targets[6] = {20, 60, 100, 140, 180, 220};
  int sum = 0;
  for (int i = 0; i < 6; i++) {
    TRACE2(targets[i], sig[targets[i]]);
    sum += sig[targets[i]] * targets[i];
  }

  for (int i = 0; i <= targets[0]; i++) {
    TRACE2(i, sig[i]);
  }

  TRACE(sum);
  return 0;
}
