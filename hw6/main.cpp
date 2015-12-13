#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <functional>

using namespace std;
typedef map<int,priority_queue<int,vector<int>,greater<int> > > VertexT;

class graph {
public:
	map <int, VertexT> M;
	bool insert_vertex (int v) {
		if (M.find(v) == M.end()) {
			M[v] = VertexT ();
			return true;
		}
		return false;
	}
	bool insert_edge (int v1, int v2, int w) {	
		if (M.find(v1) == M.end() or M.find(v2) == M.end()) {
			return false;
		}
		M[v1][v2].push(w);
		return true;
	}
	bool erase_vertex (int v) {
		if (M.find(v) == M.end()) {
			return false;
		}
		else {
			M.erase(v);
			map <int, VertexT>::iterator it;
			for (it = M.begin(); it != M.end(); it++) {
				it->second.erase(v);
			}
			return true;
		}
	}
	bool erase_edge (int v1, int v2) {
		if (M.find(v1) == M.end()) {
			return false;
		}
		if (M[v1].find(v2) == M[v1].end()) {
			return false;
		}
//		M[v1][v2].pop();
//		if (M[v1][v2].empty()) {
//			M[v1].erase(v2);
//		}
		M[v1].erase(v2);
		return true;
	}
	int get_edge (int v1, int v2) {
		if (M.find(v1) == M.end()) {
			throw 1;
		}
		if (M[v1].find(v2) == M[v1].end()) {
			throw 1;
		}
		return M[v1][v2].top();
	}
	void invert() {
		graph temp_G;
		map <int, VertexT>::iterator it1;
		for (it1 = M.begin(); it1 != M.end(); it1++) {
			temp_G.insert_vertex(it1->first);
			VertexT::iterator it2;
			for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
				temp_G.insert_vertex(it2->first);
				while(!it2->second.empty()) {
					int w = it2->second.top();
					it2->second.pop();
					temp_G.insert_edge(it2->first, it1->first, w);
				}
			}
		}
		M = temp_G.M;
	}
	void print_graph() {
		map <int, VertexT>::iterator it1;
		for (it1 = M.begin(); it1 != M.end(); it1++) {
			cout << it1->first << ": ";
			VertexT::iterator it2;
			for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
				cout << "{";
				cout << it2->first << ", ";
				cout << it2->second.top();
				cout << "} ";
			}
			cout << endl;
		}
	}
};

void input_handler()
{
	graph G;
//	ifstream fin("input");
	string str;
	cin >> str;
	while(str != "exit") {
		if (str == "insert_vertex") {
			int v;
			cin >> v;
			if (G.insert_vertex(v)) cout << "oK\n";
			else cout << "error\n";
		}
		if (str == "insert_edge") {
			int v1, v2, w;
			cin >> v1;
			cin >> v2;
			cin >> w;
			if (G.insert_edge(v1, v2, w)) cout << "oK\n";
			else cout << "error\n";
		}
		if (str == "erase_vertex") {
			int v;
			cin >> v;
			if (G.erase_vertex(v)) cout << "oK\n";
			else cout << "error\n";
		}
		if (str == "erase_edge") {
			int v1, v2;
			cin >> v1;
			cin >> v2;
			if (G.erase_edge(v1, v2)) cout << "oK\n";
			else cout << "error\n";
		}
		if (str == "get_edge") {
			int v1, v2, res;
			bool flag = true;
			cin >> v1;
			cin >> v2;
			try {
				res = G.get_edge(v1, v2);
			} catch (int x) {
				flag = false;
				cout << "edge doesn\'t exist\n";
			}
			if (flag) cout << res << endl;
		}
		if (str == "invert") {
			G.invert();
			cout << "oK\n";
		}
		cin >> str;
	}
	cout << "See you later\n";
//	fin.close();
}

int main() 
{
	input_handler();
	return 0;
}
