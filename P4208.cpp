#include <iostream>
#include <cstdio>
#include <algorithm>
#define mod 31011
using namespace std;
int n, m, cnt, tot, sum, ans = 1, fa[105], l[1005], r[1005], num[1005];
struct node
{
    int u;
    int v;
    int w;
} a[1005];
bool cmp(node aa, node bb)
{
    return aa.w < bb.w;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    return getfather(fa[x]);
}
void dfs(int id, int w, int gu)
{
    if (w == r[id] + 1)
    {
        if (gu == num[id])
            ++cnt;
        return;
    }
    int x = getfather(a[w].u), y = getfather(a[w].v);
    if (x != y)
    {
        fa[x] = y;
        dfs(id, w + 1, gu + 1);
        fa[x] = x;
    }
    dfs(id, w + 1, gu);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        if (a[i].w != a[i - 1].w)
        {
            ++tot;
            l[tot] = i;
            r[tot - 1] = i - 1;
        }
        int x = getfather(a[i].u), y = getfather(a[i].v);
        if (x != y)
        {
            ++sum;
            fa[x] = y;
            ++num[tot];
        }
    }
    r[tot] = m;
    if (sum != n - 1)
    {
        printf("0");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= tot; ++i)
    {
        cnt = 0;
        dfs(i, l[i], 0);
        ans = (ans * cnt) % mod;
        for (int j = l[i]; j <= r[i]; ++j)
        {
            int x = getfather(a[j].u), y = getfather(a[j].v);
            if (x != y)
                fa[x] = y;
        }
    }
    printf("%d", ans);
    return 0;
}