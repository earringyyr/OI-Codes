#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, sum, ans, w[1005][1005], fa[1005];
struct node
{
    int u;
    int v;
    int w;
    bool operator<(const node &bb) const
    {
        return w < bb.w;
    }
} a[1000005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &w[i][j]);
            if (i > j)
            {
                a[++sum].u = i;
                a[sum].v = j;
                a[sum].w = w[i][j];
            }
        }
    sort(a + 1, a + sum + 1);
    for (int i = 1; i <= sum; ++i)
        if (getfather(a[i].u) != getfather(a[i].v))
        {
            fa[getfather(a[i].u)] = getfather(a[i].v);
            ans += a[i].w;
        }
    printf("%d", ans);
    return 0;
}