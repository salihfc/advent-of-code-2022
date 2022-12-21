#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;

const string filename = "input.txt";

struct Node {
  int value = -1e9;
  Node *prev = nullptr;
  Node *next = nullptr;
  bool shifted = false;

  Node(int _value = 0, Node *_prev = nullptr, Node *_next = nullptr)
      : value(_value), prev(_prev), next(_next) {}

  void move() {
    assert(value != int(-1e9));

    if (value == 0)
      return;

    int t = abs(value);
    auto tmp = this;

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
  int size = 0;

  void add_node_with_value(int value) {
    if (head == nullptr) {
      head = tail = new Node(value);
      head->next = head;
      head->prev = head;
    } else {
      auto new_node = new Node(value, tail, head);
      head->prev = tail->next = new_node;
      tail = new_node; // new node becomes tail
    }
    size++;
  }

  void mix() {
    Node *cur = head;
    Node *next = nullptr;

    int t = size;
    while (t--) {
      next = cur->next;
      while (next->shifted)
        next = next->next;

      TRACE2("MIX STEP", cur->value);
      cur->move();
      cur = next;
    }
  }

  void print() {
    auto cur = head;
    int t = size;
    while (t--) {
      TRACE(cur->value);
      cur = cur->next;
    }
  }

  int ans() {
    int sum = 0;
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
  int x;
  while (input >> x)
    list.add_node_with_value(x);
  // list.print();
  list.mix();
  TRACE(list.ans());
  return 0;
}
