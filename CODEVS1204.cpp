#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int c, d, nxt[100];
char a[100], b[100];
void kmp()
{
    int x = 0, y = -1;
    nxt[0] = -1;
    while (x < c)
    {
        if (y == -1 || a[x] == a[y])
        {
            x++;
            y++;
            nxt[x] = y;
        }
        else
            y = nxt[y];
    }
    return;
}
int main()
{
    scanf("%s%s", a, b);
    c = strlen(a);
    d = strlen(b);
    kmp();
    int j = 0;
    for (int i = 0; i < c; ++i)
    {
        if (a[i] != b[j])
        {
            if (nxt[j] == -1)
                j = 0;
            else
            {
                j = nxt[j];
                --i;
            }
            continue;
        }
        if (j == d - 1)
        {
            printf("%d", i - j + 1);
            return 0;
        }
        j++;
    }
    return 0;
}