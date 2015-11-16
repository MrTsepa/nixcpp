#include <iostream>

using namespace std;

void func (int a) {a++;}

int main()
{
	int a = 1;
	func (a);
	cout << a << endl;
}
