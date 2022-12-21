#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

int main() {
  ifstream input(filename);

  // rock paper scis
  const int selection_score[3] = {1, 2, 3};
  const int to_win[3] = {1, 2, 0};
  const int to_draw[3] = {0, 1, 2};
  const int to_lose[3] = {2, 0, 1};

  int score = 0;
  char opp, result;

  while (!input.eof()) {
    input >> opp >> result;
    if (input.eof())
      break;

    cerr << opp << " | " << result << endl;
    score += int(result == 'X') * (0 + selection_score[to_lose[opp - 'A']]);
    score += int(result == 'Y') * (3 + selection_score[to_draw[opp - 'A']]);
    score += int(result == 'Z') * (6 + selection_score[to_win[opp - 'A']]);
  }

  cout << score << endl;
  return 0;
}
