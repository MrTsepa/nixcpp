#include <iostream>
#include "string.cpp"

using namespace std;

int main()
{
	S str1 = "Hello", str2 = 'a';
	S str3 = "123" + str1;
	str3 = str3 + "a";
	cout << str3 << endl;
	cout << str3.length();
}
