#include <iostream>
#include "string.cpp"

using namespace std;

int main()
{
	S str1 = "";
	S str2 = "A";
	for (int i = 0; i < 100; i++){
		cout << str1 << " " << strlen(str1.str()) << " "  << str1.length() << endl;
		str1 += str2;
		sleep(1);
	}
}
