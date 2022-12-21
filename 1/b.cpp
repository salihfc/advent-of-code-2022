#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

class TopThree{
	int t[3] = {0, 0, 0};

public:
	void insert(int x)
	{
		if (x > t[2])
			t[2] = x;
		
		if (t[1] < t[2])
			swap(t[1], t[2]);

		if (t[0] < t[1])
			swap(t[0], t[1]);
	}

	int sum()
	{
		return t[0] + t[1] + t[2];
	}

};

int main()
{
	ifstream input(filename);

	int mx = 0;
	TopThree top;

	while(!input.eof())
	{
		string line;
		int acc = 0;

		while(getline(input, line) && line.length())
		{
			cout << line << endl;
			acc += stoi(line);
		}

		top.insert(acc);
	}

	cout << top.sum() << endl;
	return 0;
}