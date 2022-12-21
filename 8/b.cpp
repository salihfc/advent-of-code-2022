#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

vector<int> find_scenic(int x, int y, vector<vector<int>> &hs, int rows) {
  int cols = 99;
  int h = hs[x][y];
  if (hs[x][y - 1] > h || hs[x][y + 1] > h || hs[x - 1][y] > h ||
      hs[x + 1][y] > h)
    return {0, 0, 0, 0};

  int left = 1;
  while (y - left >= 0) {
    if (hs[x][y - left] >= h) {
      break;
    }
    left++;
  }

  int right = 1;
  while (y + right < cols) {
    if (hs[x][y + right] >= h) {
      break;
    }
    right++;
  }

  int top = 1;
  while (x - top >= 0) {
    if (hs[x - top][y] >= h) {
      break;
    }
    top++;
  }
  int bot = 1;
  while (x + bot < rows) {
    if (hs[x + bot][y] >= h) {
      break;
    }
    bot++;
  }

  if (x + bot == rows)
    bot--;
  if (x - top == -1)
    top--;
  if (y - left == -1)
    left--;
  if (y + right == cols)
    right--;
  return {left, right, top, bot};
}

int main() {
  ifstream input(filename);
  assert(input.is_open());
  string mp[99];
  vector<vector<int>> hs(99, vector<int>(99, 0));
  for (int i = 0; i < 99; i++) {
    input >> mp[i];
    for (int j = 0; j < 99; j++)
      hs[i][j] = (mp[i][j] - '0');
  }
  int n = 99;
  int m = mp[0].size();
  int scene = 0;

  for (int i = 1; i < (n - 1); i++) {
    for (int j = 1; j < (m - 1); j++) {
      auto sides = find_scenic(i, j, hs, n);
      int score = sides[0] * sides[1] * sides[2] * sides[3];
      if (score > scene) {
        scene = score;
      }
    }
  }

  cerr << "ct: " << scene << endl;
  return 0;
}
