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
  string sack;
  while (input >> sack) {
    vector<int> l(52, 0), r(52, 0);
    int n = sack.size();
    for (int i = 0; i < n / 2; i++)
      l[get_index(sack[i])]++;
    for (int i = n / 2; i < n; i++)
      r[get_index(sack[i])]++;

    for (int i = 0; i < 52; i++) {
      if (l[i] && r[i]) {
        sum += i + 1;
        cout << sack << " | " << (i + 1) << endl;
        break;
      }
    }
  }

  cout << sum << endl;
  return 0;
}
