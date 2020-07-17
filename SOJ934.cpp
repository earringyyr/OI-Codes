#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int cnt, la, lb, nxt[1000005];
char a[1000005], b[1000005];
void kmp()
{
    int x = 0, y = -1;
    nxt[0] = -1;
    while (x <= lb)
        if (y == -1 || b[x] == b[y])
        {
            ++x;
            ++y;
            nxt[x] = y;
        }
        else
            y = nxt[y];
    return;
}
int main()
{
    scanf("%s%s", a, b);
    la = strlen(a);
    lb = strlen(b);
    kmp();
    int j = 0;
    for (int i = 0; i < la; ++i)
    {
        if (a[i] != b[j])
            if (nxt[j] != -1)
            {
                j = nxt[j];
                --i;
            }
            else
                j = 0;
        else
            ++j;
        if (j == lb)
        {
            ++cnt;
            printf("%d\n", i - j + 2);
            j = nxt[j];
        }
    }
    if (!cnt)
        printf("NO");
    return 0;
}