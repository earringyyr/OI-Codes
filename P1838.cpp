#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[10];
int len, a[4][4];
int main()
{
    scanf("%s", s);
    len = strlen(s);
    if (len != 9)
    {
        if (len % 2 == 0)
            cout << "uim wins.";
        else
            cout << "xiaoa wins.";
        return 0;
    }
    for (int i = 0; i < len; ++i)
        a[(s[i] - '0' - 1) / 3 + 1][(s[i] - '0') % 3 == 0 ? 3 : (s[i] - '0') % 3] = i % 2;
    for (int i = 1; i <= 3; ++i)
    {
        int k = a[i][1];
        if (a[i][2] == k && a[i][3] == k)
            if (k == 0)
            {
                cout << "xiaoa wins.";
                return 0;
            }
            else
            {
                cout << "uim wins;";
                return 0;
            }
    }
    for (int i = 1; i <= 3; ++i)
    {
        int k = a[1][i];
        if (a[2][i] == k && a[3][i] == k)
            if (k == 0)
            {
                cout << "xiaoa wins.";
                return 0;
            }
            else
            {
                cout << "uim wins;";
                return 0;
            }
    }
    int k = a[2][2];
    if ((a[1][1] == k && a[3][3] == k) || (a[1][3] == k && a[3][1] == k))
        if (k == 0)
        {
            cout << "xiaoa wins.";
            return 0;
        }
        else
        {
            cout << "uim wins;";
            return 0;
        }
    cout << "drew.";
    return 0;
}