#include <iostream>
#include <cstdio>
using namespace std;
int n, fa[10005], vis[100005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    for (int i = 1; i <= 10000; ++i)
        fa[i] = i;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x = getfather(x);
        y = getfather(y);
        if (x == y)
            vis[x] = 1;
        else
        {
            if (x > y)
                swap(x, y);
            if (vis[x])
                vis[y] = 1;
            else
                vis[x] = 1;
            fa[x] = y;
        }
    }
    for (int i = 1; i <= 10001; ++i)
        if (!vis[i])
        {
            printf("%d", i - 1);
            break;
        }
    return 0;
}