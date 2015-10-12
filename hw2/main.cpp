#include <iostream>
#include "string.cpp"

using namespace std;

int main()
{
    char* str = "Hello";
    S str2 = "Hello, ";
    S str3 = "World!";
    S str4 = str2+str3;
    str2 += str3;
    cout << str2;
    return 0;
}
