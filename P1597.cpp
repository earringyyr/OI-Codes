#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main()
{
    char s[300];
    scanf("%s", s);
    int len = strlen(s), a = 0, b, aa = 0, bb = 0, cc = 0;
    for (int i = 0; i < len; ++i)
    {
        if (s[i] == 'a')
        {
            if (a == 0)
            {
                a = 1;
                b = 0;
            }
            else
            {
                if (a == 1)
                    aa = aa;
                if (a == 2)
                    bb = aa;
                if (a == 3)
                    cc = aa;
                a = -0;
            }
        }
        else if (s[i] == 'b')
        {
            if (a == 0)
            {
                a = 2;
                b = 0;
            }
            else
            {
                if (a == 1)
                    aa = bb;
                if (a == 2)
                    bb = bb;
                if (a == 3)
                    cc = bb;
                a = 0;
            }
        }
        else if (s[i] == 'c')
        {
            if (a == 0)
            {
                a = 3;
                b = 0;
            }
            else
            {
                if (a == 1)
                    aa = cc;
                if (a == 2)
                    bb = cc;
                if (a == 3)
                    cc = cc;
                a = 0;
            }
        }
        else if (s[i] != ';' && s[i] != '=' && s[i] != ':')
            b = s[i] - '0';
        else if (s[i] == ';')
        {
            if (a == 1)
                aa = b;
            if (a == 2)
                bb = b;
            if (a == 3)
                cc = b;
            a = 0;
        }
    }
    cout << aa << " " << bb << " " << cc;
    return 0;
}