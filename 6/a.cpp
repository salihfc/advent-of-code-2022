#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

int main() {
  ifstream input(filename);
  assert(input.is_open());
  string stream;
  input >> stream;
  unordered_map<char, int> ct;

  int msg_len = 14;

  for (int i = 0; i < msg_len; i++) {
    ct[stream[i]]++;
  }

  for (int i = msg_len; i < stream.size(); i++) {
    if (ct.size() == msg_len) {
      cout << i << endl;
      return 0;
    }

    ct[stream[i]]++;
    ct[stream[i - msg_len]]--;
    if (ct[stream[i - msg_len]] == 0)
      ct.erase(stream[i - msg_len]);
  }

  return 0;
}
