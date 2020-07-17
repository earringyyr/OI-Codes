#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int t, n, sum, bo[10005], tr[10005][10];
char s[10005];
bool insert()
{
    int root = 1, p = 1, len = strlen(s);
    for (int i = 0; i < len; ++i)
    {
        if (!tr[root][s[i] - '0'])
            tr[root][s[i] - '0'] = ++sum;
        else if (i == len - 1)
            p = 0;
        root = tr[root][s[i] - '0'];
        if (bo[root])
            p = 0;
    }
    bo[root] = 1;
    return p;
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        int pan = 1;
        sum = 1;
        memset(tr, 0, sizeof(tr));
        memset(bo, 0, sizeof(bo));
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%s", s);
            if (!insert())
                pan = 0;
        }
        if (pan)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}