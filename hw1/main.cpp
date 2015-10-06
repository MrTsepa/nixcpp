#include <iostream>
#include <math.h>
#include "complex.cpp"

using namespace std;

int main()
{
	double a, b;
	cin >> a >> b;
	C x(a, b);
	cin >> a >> b;
	C y(a, b);
	x = y;
	cout << (x+y) << endl;
	return 0;
}
