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

  void simplify(string name) {
    if (mp[name].value == INVALID) {
      simplify(mp[name].left);
      simplify(mp[name].right);
    }

    if (resolvable(name))
      mp[name].value = resolve(name);
  }

  ll resolve(string name) {
    ll result = mp[name].value;
    if (result != INVALID)
      return result;

    ll left = resolve(mp[name].left);
    ll right = resolve(mp[name].right);
    return eval(left, right, mp[name].op);
  }

  bool resolvable(string name) {
    if (name == "humn")
      return false;

    ll result = mp[name].value;
    if (result != INVALID)
      return true;
    bool left = resolvable(mp[name].left);
    bool right = resolvable(mp[name].right);
    return left && right;
  }

  void equate(string name, ll value) {
    TRACE2(name, value);
    if (name == "humn") {
      TRACE2("humn", value);
      exit(0);
    }

    assert(resolvable(name) == false);
    // value = a op b
    if (resolvable(mp[name].left)) {
      TRACE("left known");
      ll left_value = resolve(mp[name].left);
      TRACE2(left_value, mp[name].op);

      ll value_to_equate_to;
      switch (mp[name].op) {
      case '+':
        value_to_equate_to = value - left_value;
        break;

      case '-':
        value_to_equate_to = -value + left_value;
        break;

      case '*':
        value_to_equate_to = value / left_value;
        break;

      case '/':
        value_to_equate_to = left_value / value;
        break;

      default:
        assert(0);
        break;
      }

      equate(mp[name].right, value_to_equate_to);
    }

    else {
      TRACE("right known");

      // value = unk op const
      ll right_value = resolve(mp[name].right);
      TRACE2(right_value, mp[name].op);

      switch (mp[name].op) {
      case '+':
        equate(mp[name].left, value - right_value);
        break;

      case '-':
        equate(mp[name].left, value + right_value);
        break;

      case '*':
        equate(mp[name].left, value / right_value);
        break;

      case '/':
        equate(mp[name].left, right_value * value);
        break;

      default:
        break;
      }
    }
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
  inter.simplify("root");

  ll value;
  string var;

  if (inter.resolvable(inter.mp["root"].left)) {
    value = inter.resolve(inter.mp["root"].left);
    var = inter.mp["root"].right;
  } else {
    value = inter.resolve(inter.mp["root"].right);
    var = inter.mp["root"].left;
  }

  inter.equate(var, value);
  return 0;
}
