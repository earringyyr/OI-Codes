#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    char c;
    while (cin >> c)
    {
        if (c >= 'a' && c <= 'z')
            cout << char(c - 'a' + 'A');
        else
            cout << char(c);
    }
    return 0;
}