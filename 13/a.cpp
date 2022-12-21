#include <bits/stdc++.h>
#define TRACE(x) std::cout << "[" << #x << ": \"" << x << "\"]" << std::endl;
#define TRACE2(x, y)                                                           \
  std::cout << "[" << #x << ": " << x << "]"                                   \
            << " || "                                                          \
            << "[" << #y << ": \"" << y << "\"]" << std::endl;
#define HASH(x, y) (x * 1000000 + y)

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

const std::string filename = "input.txt";

namespace sfc {

// [[[7],2,[5],1]]

static bool range_valid(const string &str, int left, int right) {
  return (0 <= left && left < str.size()) && (0 <= right && right < str.size());
}

struct List {
  std::vector<List> items;
  int value = -1;

  List(){};
  List(int x) : value(x) {}
  List &add_sublist(const List &sub) {
    items.push_back(sub);
    return *this;
  }
  void parse_str(const string &str, int left, int right) {
    // TRACE2(left, right);
    // TRACE(str.substr(left, right - left + 1));
    assert(range_valid(str, left, right));
    if (left > right)
      return;

    if (str[left] != '[') {
      // single number -> convert to int
      value = stoi(str.substr(left, right - left + 1));
    } else {
      // list >
      int it = left + 1;
      while (it < right) {
        // TRACE2(it, right);
        if (str[it] == '[') // sublist
        {
          // find closing paranthesis for it
          int depth = 1;
          int end = it + 1;
          while (depth > 0 && end < right) {
            // TRACE2(depth, str[end);
            if (str[end] == '[')
              depth++;
            else if (str[end] == ']')
              depth--;
            end++;
          }
          end--;
          List sub;
          // TRACE2(it, end);
          sub.parse_str(str, it, end);
          items.push_back(sub);
          it = end + 1;
        } else if (str[it] == ',')
          it++;
        else {
          // number > go until ','
          int end = it;
          while (end < right && str[end] != ',')
            end++;
          List sub;
          sub.parse_str(str, it, end - 1);
          items.push_back(sub);

          it = end + 1;
        }
      }
    }
  }

  friend std::ostream &operator<<(std::ostream &output, const List &list) {

    if (list.items.size() == 0) {
      if (list.value == -1)
        output << "[]";
      else
        output << "" << list.value << "";
    } else {
      output << "[";
      for (int i = 0; i < list.items.size(); i++)
        output << list.items[i] << (i + 1 == list.items.size() ? "" : ",");
      output << "]";
    }

    return output;
  }
  bool operator!=(const List &rhs) {
    if (items.size() != rhs.items.size()) {
      // TRACE("len-diff")
      return true;
    }
    if (items.size() == 0)
      return value != rhs.value;

    for (int i = 0; i < items.size(); i++)
      if (items[i] != rhs.items[i])
        return true;

    return false;
  }

  bool operator<(const List &rhs) {
    // TRACE2((*this), (rhs));
    // cout << "l:" << (*this) << "\n";
    // cout << "r:" << (rhs) << "\n";

    if (items.empty() && rhs.items.empty()) {
      if (value != -1 && rhs.value != -1)
        return value < rhs.value;
      return (value == -1);
    }

    if (!items.empty() && !rhs.items.empty()) {
      int k = 0;

      while (k < items.size() && k < rhs.items.size()) {
        if (items[k] != rhs.items[k]) {
          // TRACE(k);
          return items[k] < rhs.items[k];
        }
        k++;
      }

      return items.size() <= rhs.items.size();
    }

    if (items.size() == 0) {
      return (value == -1) || List().add_sublist((value)) < rhs;
    }
    if (rhs.items.size() == 0) {
      if (rhs.value == -1)
        return false;
      return (*this < List().add_sublist((rhs.value)));
    }
    return value <= rhs.value;
  }
};
} // namespace sfc

int main() {
  std::ifstream input(filename);
  int ct = 0;
  int total_ct = 0;
  while (!input.eof()) {
    sfc::List l, r;

    string line;
    input >> line;
    if (line.empty())
      break;
    l.parse_str(line, 0, line.size() - 1);
    input >> line;
    r.parse_str(line, 0, line.size() - 1);

    // TRACE((l < r));
    total_ct++;
    if (l < r) {
      // TRACE2(l, r);
      ct += total_ct;
    }

    TRACE(l);
    TRACE(r);
    // if (l < r)
    // TRACE("kek");
    // TRACE((l < r));
    bool t = (l < r);
    TRACE(t);
    cout << endl;
  }
  TRACE(ct);
  TRACE(total_ct);
  return 0;
}
