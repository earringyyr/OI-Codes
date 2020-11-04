#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, k;
int ans[300005];
int fa[10005][1005];
struct node
{
    int id;
    int u;
    int v;
    int w;
} a[300005];
bool cmp(node aa, node bb)
{
    return aa.w > bb.w;
}
int getfather(int x, int y)
{
    if (fa[x][y] == y)
        return y;
    fa[x][y] = getfather(x, fa[x][y]);
    return fa[x][y];
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= n; ++j)
            fa[i][j] = j;
    for (int i = 1; i <= m; ++i)
    {
        a[i].id = i;
        scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    }
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        int l = 1, r = k + 1;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (getfather(mid, a[i].u) != getfather(mid, a[i].v))
                r = mid;
            else
                l = mid + 1;
        }
        if (l == k + 1)
            ans[a[i].id] = 0;
        else
        {
            ans[a[i].id] = l;
            fa[l][getfather(l, a[i].u)] = getfather(l, a[i].v);
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}