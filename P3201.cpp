#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, ans;
int c[100005], nxt[100005];
int st[1000005], lst[1000005];
int fa[1000005], siz[1000005];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
        fa[c[i]] = c[i];
        ++siz[c[i]];
        ans += (c[i] != c[i - 1]);
        if (!st[c[i]])
            st[c[i]] = i;
        nxt[i] = lst[c[i]];
        lst[c[i]] = i;
    }
    for (int i = 1; i <= m; ++i)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == y)
                continue;
            if (siz[fa[x]] > siz[fa[y]])
                swap(fa[x], fa[y]);
            if (!siz[fa[x]])
                continue;
            x = fa[x];
            y = fa[y];
            int d = lst[x];
            while (d)
            {
                ans -= (c[d - 1] == y) + (c[d + 1] == y);
                d = nxt[d];
            }
            d = lst[x];
            while (d)
            {
                c[d] = y;
                d = nxt[d];
            }
            nxt[st[x]] = lst[y];
            lst[y] = lst[x];
            siz[y] += siz[x];
            st[x] = 0;
            lst[x] = 0;
            siz[x] = 0;
        }
        else
            printf("%d\n", ans);
    }
    return 0;
}