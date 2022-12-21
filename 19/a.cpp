#include <bits/stdc++.h>
#define TRACE(x) cout << "[" << #x << ": " << x << "]" << endl;
#define TRACE2(x, y)                                                           \
  cout << "[" << #x << ": " << x << "]"                                        \
       << " || "                                                               \
       << "[" << #y << ": " << y << "]" << endl;
using namespace std;
#define endl "\n"
const string filename = "input.txt";

const int ROCK_COUNT = 4;
enum ROCKS { ORE = 0, CLAY, OBS, GEO };
const map<string, ROCKS> ROCK_NAME_TO_ID = {
    {"ore", ORE},
    {"clay", CLAY},
    {"obsidian", OBS},
    {"geode", GEO},
};

struct RockCollection {
  int count[ROCK_COUNT] = {0, 0, 0, 0};

  RockCollection() {}
  RockCollection(int x, int y, int z, int w) {
    count[0] = x;
    count[1] = y;
    count[2] = z;
    count[3] = w;
  }

  void add(ROCKS type, int add_count) {
    assert(type < ROCK_COUNT);
    count[type] += add_count;
  }

  void add_collection(const RockCollection &rhs) {
    for (int i = 0; i < ROCK_COUNT; i++)
      add((ROCKS)i, rhs.get_count((ROCKS)i));
  }

  int get_count(ROCKS type) const { return count[type]; }

  bool contains(const RockCollection &sub) const {
    for (int i = 0; i < ROCK_COUNT; i++)
      if (sub.count[i] > count[i])
        return false;
    return true;
  }

  int extraction_count(RockCollection sub) {
    int count = 1e9;
    for (int i = 0; i < ROCK_COUNT; i++)
      if (sub.get_count((ROCKS)i) > 0)
        count = min(count, get_count((ROCKS)i) / sub.get_count((ROCKS)i));
    return count;
  }

  void use_multiple(const RockCollection &sub, int use_count) {
    for (int i = 0; i < ROCK_COUNT; i++)
      count[i] -= sub.count[i] * use_count;
  }

  void use(const RockCollection &sub) {
    assert(contains(sub));
    for (int i = 0; i < ROCK_COUNT; i++)
      count[i] -= sub.count[i];
  }

  friend ostream &operator<<(ostream &output, RockCollection &collection) {
    for (int i = 0; i < ROCK_COUNT; i++)
      output << collection.get_count((ROCKS)i) << " ";
    return output;
  }

  bool operator<(const RockCollection &rhs) const {
    return (count[3] != rhs.get_count((ROCKS)3))
               ? count[3] <= rhs.get_count((ROCKS)3)
           : (count[2] != rhs.get_count((ROCKS)2))
               ? count[2] <= rhs.get_count((ROCKS)2)
           : (count[1] != rhs.get_count((ROCKS)1))
               ? count[1] <= rhs.get_count((ROCKS)1)
           : (count[0] != rhs.get_count((ROCKS)0))
               ? count[0] <= rhs.get_count((ROCKS)0)
               : false;
  }

  bool operator==(const RockCollection &rhs) const {
    return count[0] == rhs.get_count((ROCKS)0) &&
           count[1] == rhs.get_count((ROCKS)1) &&
           count[2] == rhs.get_count((ROCKS)2) &&
           count[3] == rhs.get_count((ROCKS)3);
  }
};

static istream &skip_until(istream &input, string token) {
  string next;
  while (input >> next && next != token)
    ;
  return input;
}

typedef RockCollection RobotRecipe;
typedef RockCollection RobotArmy;

struct SimState {
  int minutes = 0;
  RobotArmy robots;
  RockCollection inventory;
  SimState() { robots.add(ORE, 1); }
  friend ostream &operator<<(ostream &output, SimState &state) {
    output << "<< SIM >> " << endl;
    output << "min: " << state.minutes << endl;
    output << "inventory: " << state.inventory << endl;
    output << "robots: " << state.robots << endl;
    output << "<<  >>" << endl;
    return output;
  }

  bool operator<(const SimState &rhs) const {
    return !(robots == rhs.robots)         ? rhs.robots < robots
           : !(inventory == rhs.inventory) ? rhs.inventory < inventory
                                           : rhs.minutes > minutes;
  }
};

struct Blueprint {
  RobotRecipe robot_recipes[ROCK_COUNT];

  friend istream &operator>>(istream &input, Blueprint &blueprint) {
    string type, dum;
    int count;

    for (int i = 0; i < ROCK_COUNT; i++) {
      skip_until(input, "costs");
      if (input.eof())
        return input;

      bool done = false;
      while (!done) {
        input >> count >> type;
        if (type.back() == '.') {
          done = true;
          type.pop_back();
        } else {
          // read 'and'
          input >> dum;
        }

        if (type.size())
          blueprint.robot_recipes[i].add(ROCK_NAME_TO_ID.at(type), count);
      }
    }

    cout << "\nBLUEPRINT\n";
    for (int i = 0; i < ROCK_COUNT; i++) {
      for (int j = 0; j < ROCK_COUNT; j++) {
        cout << blueprint.robot_recipes[i].count[j] << " ";
      }
      cout << endl;
    }
    cout << "\n-----\n";

    return input;
  }

  int sim() {
    int max_final_geo_count = 0;
    SimState start_state;
    map<RobotArmy, pair<RockCollection, int>> best;
    // priority_queue<SimState> q;
    queue<SimState> q;
    q.push(start_state);

    while (!q.empty()) {
      auto cur = q.front();
      // auto cur = q.top();
      q.pop();

      int k = q.size();
      if (k % 100000 == 0)
        cout << cur << endl;

      if (cur.minutes >= 24) {
        // finalize
        max_final_geo_count =
            max(max_final_geo_count, cur.inventory.get_count(GEO));
        continue;
      }

      cur.minutes += 1;
      // look for options
      RockCollection max_extract;

      for (int i = 0; i < ROCK_COUNT; i++) {
        int extraction = cur.inventory.extraction_count(robot_recipes[i]);
        // TRACE(extraction);
        max_extract.count[i] = extraction;

        if (false && extraction > 0) {

          SimState next = cur;
          next.inventory.use_multiple(robot_recipes[i], extraction);
          next.robots.add(ROCKS(i), extraction);

          next.inventory.add_collection(cur.robots);

          if (best.count(next.robots) &&
              next.inventory < best[next.robots].first &&
              next.minutes >= best[next.robots].second)
            continue;

          best[next.robots] = {next.inventory, next.minutes};
          q.push(next);
        }

        // if (cur.inventory.contains(robot_recipes[i])) {
        //   SimState next = cur;
        //   next.robots.add((ROCKS)i, 1);
        //   next.inventory.use(robot_recipes[i]);
        //   next.inventory.add_collection(
        //       cur.robots); // only the previous turns robot mine ores

        //   q.push(next);
        // }
      }

      for (int i = 0; i <= max_extract.get_count((ROCKS)0); i++) {
        for (int j = 0; j <= max_extract.get_count((ROCKS)1); j++) {
          for (int k = 0; k <= max_extract.get_count((ROCKS)2); k++) {
            for (int l = 0; l <= max_extract.get_count((ROCKS)3); l++) {
              SimState next = cur;
              if (next.inventory.extraction_count(robot_recipes[0]) < i)
                continue;
              next.inventory.use_multiple(robot_recipes[0], i);
              if (next.inventory.extraction_count(robot_recipes[1]) < j)
                continue;
              next.inventory.use_multiple(robot_recipes[1], j);
              if (next.inventory.extraction_count(robot_recipes[2]) < k)
                continue;
              next.inventory.use_multiple(robot_recipes[2], k);
              if (next.inventory.extraction_count(robot_recipes[3]) < l)
                continue;
              next.inventory.use_multiple(robot_recipes[3], l);

              next.robots.add_collection(RockCollection(i, j, k, l));
              next.inventory.add_collection(cur.robots);

              // if (best.count(next.robots) &&
              //     next.inventory < best[next.robots].first &&
              //     next.minutes >= best[next.robots].second)
              //   continue;

              // best[next.robots] = {next.inventory, next.minutes};
              q.push(next);
            }
          }
        }
      }

      // finally no production case
      // cur.inventory.add_collection(cur.robots);
      // q.push(cur);
    }

    TRACE(max_final_geo_count);
    return max_final_geo_count;
  }
};

int main() {
  ifstream input(filename);
  assert(input.is_open());

  int id = 0;
  int total = 0;

  while (!input.eof()) {
    Blueprint blueprint;
    ++id;
    input >> blueprint;
    if (input.eof())
      break;
    total += id * blueprint.sim();
  }

  TRACE(total);
  return 0;
}
