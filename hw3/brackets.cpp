#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    string str;
    cin >> str;
    stack <char> S;
    bool flag = true;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(') {
            S.push(str[i]);
            continue;
        }
        if (str[i] == ')' and !S.empty()) {
            S.pop();
            continue;
        }
        flag = false;
        break;
    }
    if (!S.empty()) flag = false;
    if (flag) cout << "YES";
    else cout << "NO";
}
