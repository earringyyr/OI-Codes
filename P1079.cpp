#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int x, y;
char k[1005], a[1005], b[1005];
int main()
{
    scanf("%s%s", k, a);
    x = strlen(k);
    y = strlen(a);
    for (int i = 0; i < y; ++i)
    {
        int j = i % x;
        if (k[j] >= 'A' && k[j] <= 'Z')
            k[j] = k[j] - 'A' + 'a';
        if (a[i] >= 'a' && a[i] <= 'z')
        {
            if (a[i] - k[j] + 'a' >= 'a')
                putchar(a[i] - k[j] + 'a');
            else
                putchar(a[i] - k[j] + 'a' + 26);
        }
        else
        {
            if (a[i] - k[j] + 'a' >= 'A')
                putchar(a[i] - k[j] + 'a');
            else
                putchar(a[i] - k[j] + 'a' + 26);
        }
    }
    return 0;
}