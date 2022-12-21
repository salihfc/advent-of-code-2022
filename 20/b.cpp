#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;
#define ll long long

const string filename = "input.txt";
// const ll KEY = 811589153;
const ll KEY = 811589153;
const int MIX_ROUNDS = 10;

struct Node {
  ll value = -1;
  Node *prev = nullptr;
  Node *next = nullptr;
  bool shifted = false;

  Node(int _value = 0, Node *_prev = nullptr, Node *_next = nullptr)
      : value(_value), prev(_prev), next(_next) {}

  void move(ll total_size) {
    assert(value != (ll)(-1));

    if (value == 0)
      return;

    ll t = ((KEY % total_size) * (abs(value) % total_size)) % total_size;

    TRACE2(value, t);
    if (value > 0)
      while (t--)
        swap_with_next();
    else if (value < 0)
      while (t--)
        swap_with_prev();

    shifted = true;
  }
  void swap_with_next() {
    /*
        [aprev]-><-[a]-><-[anext]<-->[ann]
    */
    auto old_prev = prev;
    auto old_next = next;
    auto old_nn = next->next;

    old_prev->next = old_next;
    prev = old_next;
    next = old_nn;
    old_next->prev = old_prev;
    old_next->next = this;
    old_nn->prev = this;
  }

  void swap_with_prev() {
    /*
        [pp]-><-[prev]-><-[this]<-->[next]
    */
    auto old_pp = prev->prev;
    auto old_prev = prev;
    auto old_next = next;

    old_pp->next = this;
    old_prev->prev = this;
    old_prev->next = old_next;
    prev = old_pp;
    next = old_prev;
    old_next->prev = old_prev;
  }
};

struct List {
  Node *head = nullptr;
  Node *tail = nullptr;
  Node *mix_order[5005];
  ll size = 0;

  void add_node_with_value(ll value) {
    if (head == nullptr) {
      head = tail = new Node(value);
      head->next = head;
      head->prev = head;
      mix_order[size] = head;
    } else {
      auto new_node = new Node(value, tail, head);
      head->prev = tail->next = new_node;
      tail = new_node; // new node becomes tail
      mix_order[size] = new_node;
    }
    size++;
  }

  void mix() {
    for (int j = 0; j < size; j++)
      mix_order[j]->shifted = false;
    for (int j = 0; j < size; j++)
      mix_order[j]->move(size);
  }

  void print() {
    cout << " < LIST > " << endl;
    auto cur = head;
    int t = size;
    while (t--) {
      TRACE(cur->value);
      cur = cur->next;
    }
    cout << " ---- " << endl;
  }

  ll ans() {
    ll sum = 0;
    // already mixed
    Node *zero = head;
    while (zero->value != 0)
      zero = zero->next;

    auto cur = zero;
    for (int i = 0; i < 3; i++) {
      int t = 1000;
      while (t--)
        cur = cur->next;

      sum += cur->value;
      TRACE(cur->value);
    }

    return sum;
  }
};

int main() {
  ifstream input(filename);
  assert(input.is_open());

  List list;
  ll x;
  while (input >> x)
    list.add_node_with_value(x);

  list.print();
  int round = MIX_ROUNDS;
  while (round--) {
    list.mix();
    list.print();
  }

  ll ans = list.ans() * KEY;
  TRACE(ans);
  return 0;
}
