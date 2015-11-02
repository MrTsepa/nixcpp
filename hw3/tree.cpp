#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

bool isnumber(char c)
{
    if (c >= 48 and c < 58) return true;
    else return false;
}

int main()
{
    string str;
    getline (cin, str);

    stack <double> S;
    int i = 0;
    while(i < str.length())
    {
        if (str[i] == '-') {
            int temp = 0;
            i++;
            while(isnumber(str[i])) {
                temp *= 10;
                temp += (str[i] - 48);
                i++;
            }
            temp *= -1;
            S.push(temp * 1.0);
        }
        if (isnumber(str[i])) {
            int temp = str[i] - 48;
            i++;
            while(isnumber(str[i])) {
                temp *= 10;
                temp += (str[i] - 48);
                i++;
            }
            S.push(temp * 1.0);
        }
        if (str[i] == ')') {
            double temp1 = S.top();
            S.pop();
            double temp2 = S.top();
            S.pop();
            S.push((temp1+temp2) / 2.0);
        }

        i++;
    }
    cout << fixed << setprecision(2);
    cout << S.top();
}
