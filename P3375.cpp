#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, len;
int nxt[1000005];
char s[1000005], c[10000005];
void kmp()
{
    int x = 0, y = 1;
    nxt[1] = 0;
    while (y <= n)
    {
        if (!x || s[x] == s[y])
        {
            ++x;
            ++y;
            nxt[y] = x;
        }
        else
            x = nxt[x];
    }
}
int main()
{
    scanf("%s%s", c + 1, s + 1);
    n = strlen(s + 1);
    len = strlen(c + 1);
    kmp();
    int j = 1;
    for (int i = 1; i <= len; ++i)
    {
        if (s[j] == c[i])
        {
            if (j == n)
            {
                printf("%d\n", i - n + 1);
                j = nxt[n + 1];
            }
            else
                ++j;
        }
        else
        {
            j = nxt[j];
            if (j)
                --i;
            else
                j = 1;
        }
    }
    for (int i = 2; i <= n + 1; ++i)
        if (nxt[i])
            printf("%d ", nxt[i] - 1);
        else
            printf("0");
    return 0;
}