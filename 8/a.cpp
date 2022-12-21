#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

int main() {
  ifstream input(filename);
  assert(input.is_open());
  string mp[99];
  for (int i = 0; i < 99; i++) {
    input >> mp[i];
    // cout << mp[i] << endl;
  }
  int n = 99;
  int m = mp[0].size();
  int ct = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int h = mp[i][j];

      bool all_small_left = true;
      for (int k = 0; k < j; k++)
        if (mp[i][k] >= h) {
          all_small_left = false;
          break;
        }

      if (all_small_left) {
        ct++;
        continue;
      }

      bool all_small_right = true;
      for (int k = j + 1; k < m; k++)
        if (mp[i][k] >= h) {
          all_small_right = false;
          break;
        }

      if (all_small_right) {
        ct++;
        continue;
      }

      bool all_small_top = true;
      for (int k = 0; k < i; k++)
        if (mp[k][j] >= h) {
          all_small_top = false;
          break;
        }

      if (all_small_top) {
        ct++;
        continue;
      }

      bool all_small_bot = true;
      for (int k = i + 1; k < n; k++)
        if (mp[k][j] >= h) {
          all_small_bot = false;
          break;
        }

      if (all_small_bot) {
        ct++;
        continue;
      }
    }
  }

  cerr << "ct: " << ct << endl;
  return 0;
}
