#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[300];
int a, b;
int main()
{
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; ++i)
    {
        if (s[i] == 'b')
            ++a;
        if (s[i] == 'o' && s[i - 1] != 'b')
            ++a;
        if (s[i] == 'y' && s[i - 1] != 'o')
            ++a;
        if (s[i] == 'g')
            ++b;
        if (s[i] == 'i' && s[i - 1] != 'g')
            ++b;
        if (s[i] == 'r' && s[i - 1] != 'i')
            ++b;
        if (s[i] == 'l' && s[i - 1] != 'r')
            ++b;
    }
    cout << a << endl
         << b;
    return 0;
}