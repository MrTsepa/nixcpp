#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

struct task {
	double key;
	int ord;
	string id;
};

bool chek_str(string str)
{
	if (str.length() != 32) return false;
	bool flag = true;
	for (int i = 0; i < 32; i++) {
		if (!isalnum(str[i])) flag = false;
	}
	return flag;
}

class heap {
public:
	vector <task> vect;
	heap() {;}
	void push(task t)
	{
		vect.push_back(t);
		int i = vect.size() - 1;
		if (i == 0) return;
		int parent = (i - 1) / 2;

		while (vect[i].key < vect[parent].key) {
			task temp = vect[i];
			vect[i] = vect[parent];
			vect[parent] = temp;
			i = parent;
			if (i == 0) return;
			parent = (i - 1) / 2;
		}
	}
	void heapify(int i)
	{
		while (1) {
			int lCh = 2*i + 1;
			int rCh = 2*i + 2;
			int sCh = i;

			double sKey = 2.0;
			if(vect[lCh].key < sKey and lCh < vect.size()) sKey = vect[lCh].key;
			if(vect[rCh].key < sKey and rCh < vect.size()) sKey = vect[rCh].key;
			if(vect[i].key < sKey) sKey = vect[i].key;
			
			int sOrd = 1000000;
			if(vect[lCh].ord < sOrd and vect[lCh].key == sKey and lCh < vect.size()) sOrd = vect[lCh].ord;
			if(vect[rCh].ord < sOrd and vect[rCh].key == sKey and rCh < vect.size()) sOrd = vect[rCh].ord;
			if(vect[i].ord < sOrd and vect[i].key == sKey) sOrd = vect[i].ord;

			if(sKey == vect[lCh].key and sOrd == vect[lCh].ord)
				sCh = lCh;
			if(sKey == vect[rCh].key and sOrd == vect[rCh].ord)
				sCh = rCh;

			if (sCh == i) return;
			else {
				task temp = vect[i];
				vect[i] = vect[sCh];
				vect[sCh] = temp;
				i = sCh;
			}
		}
	}
	void print() {for (int i = 0; i < vect.size(); i++) {cout << vect[i].key << "*" << vect[i].ord << " ";}}
	task pop()
	{
		task t = vect[0];
		vect[0] = vect[vect.size() - 1];
		vect.pop_back();
		heapify(0);
		return t;
	}
	void input()
	{
		ifstream fin("input");
		int i = 0;
		while(1) {
			i++;
			string command;
			fin >> command;
			if (command == "PROCESS") {
				if(vect.size() == 0) continue;
				else {
					cout << pop().id << endl;
				}
			} else if (command == "FINISH") {
				int n;
				fin >> n;
				if(n > vect.size() or n < 0) continue;
				for (int j = 0; j < n; j++)
				       cout << pop().id << endl;	       
				cout << vect.size() << endl;
				break;
			} else if (command == "ADD") {
				double f;
				string str;
				fin >> f >> str;
				if (f < 0.0 or f > 1.0) continue;
				if (!chek_str(str)) continue;
				task temp;
				temp.key = f;
				temp.id = str;
				temp.ord = i;
				push(temp);
			}
		}
//		int k = 0;
//		FILE * fin = fopen("input", "r");
//		while (1) {		
//			char command[128];
//			fgets(command, 128, fin);
//			char* b_ptr = command;
//			while(*b_ptr == ' ') 
//				b_ptr++;
//			if (strncmp(b_ptr, "ADD ", 4) == 0) {
//				char *ptr = strchr(b_ptr + 3, ' ');
//				if (ptr == NULL) 
//					continue;
//				while (*ptr == ' ') 
//					ptr++;
//				if (!isdigit(*ptr)) 
//					continue;
//				double f = atof(ptr);
//				if (f > 1) 
//					continue;
//				ptr = strchr(b_ptr + 5, ' ');
//				if (ptr == NULL) 
//					continue;
//				while (*ptr == ' ') 
//					ptr++;
//				char* flag = ptr;
//				ptr = strchr(flag, '\n');
//				*ptr = '\0';
//				if (!chek_str(flag)) 
//					continue;
//				task temp;
//				temp.key = f;
//				strcpy(temp.id, flag);
//				temp.ord = k;
//				k++;
//				push(temp);
//			}
//			if (strncmp(b_ptr, "PROCESS", 7) == 0) {
//				char* ptr = b_ptr + 7;
//				bool flag = true;
//				while(*ptr != '\n' and *ptr != '\0') {
//					if (*ptr != ' ') 
//						flag = false;
//					ptr++;
//				}
//				if (!flag) 
//					continue;
//				if (vect.size() > 0) {
//					task temp = pop();
//					cout << temp.id << endl;
//				}
//			}
//			if (strncmp(b_ptr, "FINISH ", 7) == 0) {
//				char* ptr = strchr(b_ptr + 6, ' ');
//				if (ptr == NULL) 
//					continue;
//				while (*ptr == ' ') 
//					ptr++;
//				if (!isdigit(*ptr)) 
//					continue;
//				int n = atoi(ptr);
//				if (n < 0 or n > vect.size()) 
//					continue;
//				if (n >= 0 && n <= vect.size()) {
//					for (int i = 0; i < n; i++) {
//						task temp = pop();
//						cout << temp.id << endl;
//					}
//					cout << vect.size() << endl;
//					break;
//				}
//			}
//		}
	}
};

int main()
{
	heap H;
	H.input();
//	int i = 0;
//	while(i < 6) {
//		task temp;
//		cin >> temp.key;
//		temp.ord = i;
//		H.push(temp);
//		H.print();
//		cout << endl;
//		i++;
//	}
//	while (i > 0) {
//		H.print();
//		cout << endl;
//		H.pop();
//		i--;
//	}
}
