#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

bool comp(pair<string, int> p1, pair<string, int> p2) {
	return (p1.second > p2.second);
}

int main()
{
	ifstream fin("input");
	map <string, int> M;
	fin >> noskipws;
	char c;
	string str;
	while((fin >> c) != '\0') {
		if (isalpha(c)) 
			str.push_back(tolower(c));
		else {
			if (!str.empty()) {
				M[str]++;
				str.clear();
			}
		}
	}
	vector<pair<string, int> > v;
	for (map<string, int>::iterator it(M.begin()); it != M.end(); it++) {
		cout << it->first << " " << it->second << endl;
		v.push_back(*it);
	}
	stable_sort(v.begin(), v.end(), comp);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].second << " " << v[i].first << endl;
	}
}
