#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[3];
char s[15];
int main()
{
    scanf("%s", s + 1);
    for (int i = 2; i <= 6; i += 2)
    {
        if (s[i] >= '0' && s[i] <= '9')
            a[i / 2] = s[i] - '0';
        else
            a[i / 2] = s[i] - 'A' + 10;
        if (s[i + 1] >= '0' && s[i + 1] <= '9')
            a[i / 2] = a[i / 2] * 16 + s[i + 1] - '0';
        else
            a[i / 2] = a[i / 2] * 16 + s[i + 1] - 'A' + 10;
    }
    putchar('#');
    for (int i = 1; i <= 3; ++i)
    {
        a[i] = 255 - a[i];
        if (a[i] / 16 >= 0 && a[i] / 16 < 10)
            putchar(a[i] / 16 + '0');
        else
            putchar(a[i] / 16 - 10 + 'A');
        if (a[i] % 16 >= 0 && a[i] % 16 < 10)
            putchar(a[i] % 16 + '0');
        else
            putchar(a[i] % 16 - 10 + 'A');
    }
    return 0;
}