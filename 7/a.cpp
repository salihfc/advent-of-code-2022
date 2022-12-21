#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE_TO_CONSIDER = 100000;
const string filename = "input.txt";

struct File {
  string name;
  int size;
};

struct Dir {
  string name;
  int total_size;
  vector<Dir *> dirs;
  vector<File> files;
  Dir *parent;
  Dir(const string &name, Dir *parent = nullptr) : name(name), parent(parent) {}
  Dir *find_sub(const string &subdir_name) {
    for (auto dir : dirs)
      if (dir->name == subdir_name)
        return dir;
    return nullptr;
  }

  void add_dir(const string &subdir_name) {
    dirs.push_back(new Dir(subdir_name, this));
  }

  void add_file(const string &filename, int size) {
    files.push_back((File){.name = filename, .size = size});
    total_size += size;

    // cout << "dir " << name << " size: " << total_size << endl;

    Dir *current = this;
    while (current->parent != nullptr) {
      current = current->parent;
      current->total_size += size;
    }
  }
};

int traverse(Dir *current) {
  int sum = 0;

  for (auto dir : current->dirs)
    sum += traverse(dir);

  if (current->total_size < MAX_SIZE_TO_CONSIDER)
    return sum + current->total_size;
  return sum;
}

int main() {
  ifstream input(filename);
  assert(input.is_open());
  Dir *home = new Dir("home");
  Dir *current_dir = home;
  string str;
  while (input >> str) {
    if (str == "$") {
      string op;
      input >> op;
      if (op == "cd") {
        string target_dir;
        input >> target_dir;
        // cout << "cd> " << target_dir << endl;

        if (target_dir == "/") {
          current_dir = home; // return to home
        } else if (target_dir == "..") {
          current_dir = current_dir->parent; // go up
          if (current_dir == nullptr)
            current_dir = home;
        } else {
          current_dir = current_dir->find_sub(target_dir);
          assert(current_dir != nullptr);
        }
      } else if (op == "ls") {
        continue;
      }

      // process command
    } else {
      // add listed dir/files to current dir
      if (str == "dir") {
        input >> str;
        current_dir->add_dir(str);
        // cout << "dir found: " << str << endl;

      } else {
        string filename;
        input >> filename;
        current_dir->add_file(filename, stoi(str));

        // cout << "file found: " << filename << " | " << str << ", " <<
        // stoi(str) << endl;
      }
    }
  }

  cout << traverse(home) << endl;
  return 0;
}
