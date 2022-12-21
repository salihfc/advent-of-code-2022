#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
#define int long long
using namespace std;

const string filename = "input.txt";
const int PRIME = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19;

struct TurnResult {
  int next_owner;
  int next_worry;
};

struct Monke {
  vector<int> items;
  void add_item(int item) { items.push_back(item); }
};

TurnResult MonkeyMove(int monkey_id, int object_worry) {
  int w = object_worry;
  int next_monkey = -1;

  switch (monkey_id) {
  case 0:
    w *= 17;

    next_monkey = ((w % 2) == 0) ? 2 : 6;
    break;

  case 1:
    w *= w;

    next_monkey = ((w % 7) == 0) ? 0 : 2;
    break;

  case 2:
    w += 7;

    next_monkey = ((w % 13) == 0) ? 7 : 6;
    break;

  case 3:
    w += 4;

    next_monkey = ((w % 5) == 0) ? 4 : 5;
    break;

  case 4:
    w = (w + 5);

    next_monkey = ((w % 3) == 0) ? 1 : 5;
    break;

  case 5:
    w = (w + 6);

    next_monkey = ((w % 19) == 0) ? 1 : 0;
    break;

  case 6:
    w = (w * 13);

    next_monkey = ((w % 11) == 0) ? 3 : 7;
    break;

  case 7:
    w = (w + 2);

    next_monkey = ((w % 17) == 0) ? 4 : 3;
    break;

  default:
    assert(0);
    break;
  }

  w %= PRIME;
  return (TurnResult){.next_owner = next_monkey, .next_worry = w};
}

vector<int> parse(string &line, char delim) {
  vector<int> res;
  string token;
  int it = 0;
  while (it < line.size()) {
    while (it < line.size() && line[it] != delim) {
      token += line[it];
      it++;
    }

    if (line[it] == ',')
      it++;
    res.push_back(stoi(token));
    token.clear();
  }
  return res;
}

signed main() {
  ifstream input(filename);
  assert(input.is_open());
  int ROUNDS = 10000;
  const int MONKE_COUNT = 8;

  Monke monkeys[MONKE_COUNT] = {
      (Monke){.items = vector<int>{85, 79, 63, 72}},
      (Monke){.items = vector<int>{53, 94, 65, 81, 93, 73, 57, 92}},
      (Monke){.items = vector<int>{62, 63}},
      (Monke){.items = vector<int>{57, 92, 56}},
      (Monke){.items = vector<int>{67}},
      (Monke){.items = vector<int>{85, 56, 66, 72, 57, 99}},
      (Monke){.items = vector<int>{86, 65, 98, 97, 69}},
      (Monke){.items = vector<int>{87, 68, 92, 66, 91, 50, 68}},
  };

  int inspects[MONKE_COUNT] = {0};

  while (ROUNDS--) {
    for (int i = 0; i < MONKE_COUNT; i++) {
      for (auto item : monkeys[i].items) {
        inspects[i]++;
        auto res = MonkeyMove(i, item);
        // TRACE2(res.next_owner, res.next_worry);
        monkeys[res.next_owner].add_item(res.next_worry);
      }
      monkeys[i].items.clear();
    }
  }

  sort(inspects, inspects + MONKE_COUNT);
  for (int i = 0; i < MONKE_COUNT; i++) {
    TRACE2(i, inspects[i]);
  }

  int kek = inspects[MONKE_COUNT - 1] * 1LL * inspects[MONKE_COUNT - 2];
  TRACE(kek);

  return 0;
}
