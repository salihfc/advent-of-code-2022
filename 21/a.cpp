#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;
#define ll long long
const string filename = "input.txt";

const ll INVALID = -1e9;

struct Expression {
  ll value = INVALID;
  string left;
  char op;
  string right;

  Expression() {}
  Expression(ll value) : value(value) {}
  Expression(string left, string right, char op)
      : left(left), right(right), op(op) {}
};

static ll eval(ll a, ll b, char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    assert(b != 0);
    return a / b;
  default:
    assert(0);
    break;
  }
}

struct Interpreter {
  map<string, Expression> mp;

  void add_exp(string name, Expression exp) { mp[name] = exp; }
  ll resolve(string name) {
    ll result = mp[name].value;
    if (result != INVALID)
      return result;

    ll left = resolve(mp[name].left);
    ll right = resolve(mp[name].right);
    return eval(left, right, mp[name].op);
  }
};

signed main() {
  ifstream input(filename);
  assert(input.is_open());

  Interpreter inter;

  string line;
  while (getline(input, line)) {
    stringstream ss(line);
    string name;
    ss >> name;
    assert(name.back() == ':');
    name.pop_back();
    ss.ignore();
    ll peeked = ss.peek();
    if ('0' <= peeked && peeked <= '9') {
      ll v;
      ss >> v;
      inter.add_exp(name, Expression(v));
    } else {
      string l, r;
      char op;
      ss >> l >> op >> r;
      inter.add_exp(name, Expression(l, r, op));
    }
  }

  ll ans = inter.resolve("root");
  TRACE(ans);

  return 0;
}
