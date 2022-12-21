#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

int main() {
  ifstream input(filename);

  // rock paper scis
  const int selection_score[3] = {1, 2, 3};

  const int match[3][3] = {
      {3, 0, 6},
      {6, 3, 0},
      {0, 6, 3},
  };

  int score = 0;
  char opp, me;

  while (!input.eof()) {
    input >> opp >> me;
    score += match[me - 'X'][opp - 'A'] + selection_score[me - 'X'];
  }
  score -= match[me - 'X'][opp - 'A'] + selection_score[me - 'X'];

  cout << score << endl;
  return 0;
}
