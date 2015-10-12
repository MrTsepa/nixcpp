#include <iostream>
#include "string.cpp"

using namespace std;

int main()
{
    S str2 = 'A';
    S str3 = "B";
    str3 += "C";
    cout << str3+"D"+str2;
    return 0;
}
