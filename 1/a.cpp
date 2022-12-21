#include <bits/stdc++.h>
using namespace std;

const string filename = "input.txt";

int main()
{
	ifstream input(filename);

	int mx = 0;

	while(!input.eof())
	{
		string line;
		int acc = 0;

		while(getline(input, line) && line.length())
		{
			cout << line << endl;
			acc += stoi(line);
		}

		mx = max(mx, acc); 
	}

	cout << mx << endl;
	return 0;
}