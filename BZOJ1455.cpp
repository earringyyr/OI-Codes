#include <iostream>
#include <cstdio>
using namespace std;
int n, m, a[1000005], fa[1000005], dis[1000005], lch[1000005], rch[1000005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (a[x] > a[y])
        swap(x, y);
    rch[x] = merge(rch[x], y);
    fa[rch[x]] = x;
    if (dis[rch[x]] < dis[lch[x]])
        swap(lch[x], rch[x]);
    dis[x] = dis[rch[x]] + 1;
    return x;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        fa[i] = i;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        char type;
        scanf(" %c", &type);
        if (type == 'M')
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (a[x] == -1 || a[y] == -1)
                continue;
            if (getfather(x) == getfather(y))
                continue;
            merge(getfather(x), getfather(y));
        }
        else
        {
            int x;
            scanf("%d", &x);
            if (a[x] == -1)
            {
                puts("0");
                continue;
            }
            x = getfather(x);
            printf("%d\n", a[x]);
            a[x] = -1;
            fa[lch[x]] = lch[x];
            fa[rch[x]] = rch[x];
            fa[x] = merge(lch[x], rch[x]);
        }
    }
    return 0;
}