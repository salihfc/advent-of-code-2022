#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;

const string filename = "input.txt";
const int TOTAL_TIME = 30;

class Graph {
  map<int, vector<int>> v;
  map<int, int> flows;

public:
  void add_edge(int a, int b) { v[a].push_back(b); }
  void set_flow(int a, int b) { flows[a] = b; }
  int flow(int a) { return flows[a]; }
  vector<int> neighbours(int a) { return v[a]; }
};

struct State {
  int total_pressure = 0;
  int time_passed = 0;
  set<int> opened;
  int node_name;

  bool operator<(const State &rhs) const {
    return (rhs.total_pressure != total_pressure)
               ? total_pressure < rhs.total_pressure
           : (time_passed != rhs.time_passed)
               ? time_passed < rhs.time_passed
               : opened.size() < rhs.opened.size();
  }
};

int main() {
  ifstream input(filename);
  assert(input.is_open());

  map<string, int> name_to_int;
  vector<int> already_opened;

  Graph g;
  string node, dum;
  int rate;
  string line;
  int NODE_COUNT = 0;

  while (getline(input, line)) {
    stringstream stream(line);
    // TRACE(line);
    stream >> dum >> node;
    stream.ignore(15);
    stream >> rate;
    stream.ignore(1);
    stream >> dum >> dum >> dum >> dum;
    stream.ignore(1);
    // TRACE(rate);
    if (name_to_int.count(node) == 0) {
      name_to_int[node] = NODE_COUNT++;
    }

    g.set_flow(name_to_int[node], rate);
    if (rate == 0)
      already_opened.push_back(name_to_int[node]);
    // TRACE2(node, rate);

    string neighbour;
    while (!stream.eof()) {
      char c[2];
      int k = stream.readsome(c, 2);
      if (k == 2)
        neighbour = c;
      else
        break;
      // TRACE(neighbour);
      stream.readsome(c, 2);

      if (name_to_int.count(neighbour) == 0) {
        name_to_int[neighbour] = NODE_COUNT++;
      }

      g.add_edge(name_to_int[node], name_to_int[neighbour]);
      // TRACE2(node, neighbour);
    }

    // break;
  }

  TRACE(NODE_COUNT);
  TRACE(already_opened.size());
  for (auto x : name_to_int)
    TRACE2(x.first, x.second);
  // return 0;
  //
  State current = (State){.total_pressure = 0,
                          .time_passed = 0,
                          .node_name = name_to_int[string("AA")]};

  for (auto opened : already_opened)
    current.opened.insert(opened);

  priority_queue<State> q;
  q.push(current);

  int maxx = 0;

  while (!q.empty()) {
    current = q.top();
    q.pop();

    // TRACE2(current.node_name, current.time_passed);
    // TRACE(current.total_pressure);

    if (current.time_passed >= TOTAL_TIME) {
      if (current.total_pressure > maxx)
        TRACE2(maxx, q.size());
      maxx = max(maxx, current.total_pressure);
      continue;
    }

    if (current.opened.count(current.node_name) == 0) // current not opened
    {
      auto next = current;
      next.time_passed += 1;
      next.total_pressure +=
          g.flow(current.node_name) * (TOTAL_TIME - next.time_passed);
      next.opened.insert(next.node_name);
      q.push(next);

      if (next.opened.size() == NODE_COUNT) {
        if (current.total_pressure > maxx)
          TRACE2(maxx, q.size());
        maxx = max(maxx, current.total_pressure);
        continue;
      }
    }

    for (auto neigh : g.neighbours(current.node_name)) {
      auto next = current;
      next.node_name = neigh;
      next.time_passed += 1;
      q.push(next);
    }
  }

  TRACE(maxx);
  return 0;
}
