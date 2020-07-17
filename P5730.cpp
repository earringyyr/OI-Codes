#include <iostream>
#include <cstdio>
using namespace std;
string s[6];
int n;
char ch;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> ch;
        int x = ch - '0';
        if (x == 0)
        {
            s[1] += "XXX";
            s[2] += "X.X";
            s[3] += "X.X";
            s[4] += "X.X";
            s[5] += "XXX";
        }
        if (x == 1)
        {
            s[1] += "..X";
            s[2] += "..X";
            s[3] += "..X";
            s[4] += "..X";
            s[5] += "..X";
        }
        if (x == 2)
        {
            s[1] += "XXX";
            s[2] += "..X";
            s[3] += "XXX";
            s[4] += "X..";
            s[5] += "XXX";
        }
        if (x == 3)
        {
            s[1] += "XXX";
            s[2] += "..X";
            s[3] += "XXX";
            s[4] += "..X";
            s[5] += "XXX";
        }
        if (x == 4)
        {
            s[1] += "X.X";
            s[2] += "X.X";
            s[3] += "XXX";
            s[4] += "..X";
            s[5] += "..X";
        }
        if (x == 5)
        {
            s[1] += "XXX";
            s[2] += "X..";
            s[3] += "XXX";
            s[4] += "..X";
            s[5] += "XXX";
        }
        if (x == 6)
        {
            s[1] += "XXX";
            s[2] += "X..";
            s[3] += "XXX";
            s[4] += "X.X";
            s[5] += "XXX";
        }
        if (x == 7)
        {
            s[1] += "XXX";
            s[2] += "..X";
            s[3] += "..X";
            s[4] += "..X";
            s[5] += "..X";
        }
        if (x == 8)
        {
            s[1] += "XXX";
            s[2] += "X.X";
            s[3] += "XXX";
            s[4] += "X.X";
            s[5] += "XXX";
        }
        if (x == 9)
        {
            s[1] += "XXX";
            s[2] += "X.X";
            s[3] += "XXX";
            s[4] += "..X";
            s[5] += "XXX";
        }
        if (i != n)
        {
            s[1] += '.';
            s[2] += '.';
            s[3] += '.';
            s[4] += '.';
            s[5] += '.';
        }
    }
    cout << s[1]
         << endl
         << s[2]
         << endl
         << s[3]
         << endl
         << s[4]
         << endl
         << s[5];
    return 0;
}