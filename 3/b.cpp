#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

int main() {
  ifstream input(filename);
  assert(input.is_open());

  auto get_index = [](char c) {
    if ('a' <= c && c <= 'z')
      return 0 + (c - 'a');
    return 26 + (c - 'A');
  };

  int sum = 0;
  string sack[3];
  while (input >> sack[0] >> sack[1] >> sack[2]) {
    vector<vector<int>> ct(3, vector<int>(52, 0));

    for (int i = 0; i < 3; i++) {
      for (auto &c : sack[i])
        ct[i][get_index(c)]++;
    }

    for (int i = 0; i < 52; i++) {
      if (ct[0][i] && ct[1][i] && ct[2][i]) {
        sum += i + 1;
        cout << sack << " | " << (i + 1) << endl;
        break;
      }
    }
  }

  cout << sum << endl;
  return 0;
}
