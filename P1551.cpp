#include <iostream>
#include <cstdio>
using namespace std;
int n, m, p, fa[5005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x = getfather(x);
        y = getfather(y);
        if (x != y)
            fa[x] = y;
    }
    for (int i = 1; i <= p; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x = getfather(x);
        y = getfather(y);
        if (x == y)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}