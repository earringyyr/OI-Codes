#include <iostream>
#include <cstdio>
using namespace std;
int n, m, k, sum, cnt, num[400005], head[400005], vis[400005], fa[400005], ans[400005];
struct node
{
    int v;
    int next;
} a[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ins(x, y);
        ins(y, x);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &num[i]);
        vis[num[i]] = 1;
    }
    for (int i = 0; i < n; ++i)
        if (!vis[i])
            ++cnt;
    for (int i = 0; i < n; ++i)
        if (!vis[i])
        {
            int d = head[i];
            while (d)
            {
                if (!vis[a[d].v] && getfather(i) != getfather(a[d].v))
                {
                    fa[getfather(i)] = getfather(a[d].v);
                    --cnt;
                }
                d = a[d].next;
            }
        }
    for (int i = k; i >= 1; --i)
    {
        ans[i] = cnt;
        vis[num[i]] = 0;
        int d = head[num[i]], tot = 0;
        while (d)
        {
            if (!vis[a[d].v] && getfather(num[i]) != getfather(a[d].v))
            {
                fa[getfather(num[i])] = getfather(a[d].v);
                ++tot;
            }
            d = a[d].next;
        }
        cnt -= tot - 1;
    }
    ans[0] = cnt;
    for (int i = 0; i <= k; ++i)
        printf("%d\n", ans[i]);
    return 0;
}