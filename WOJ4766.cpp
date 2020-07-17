#include <iostream>
#include <cstdio>
using namespace std;
int n, aa, bb, sum, cnt, h, t, p, q[100005], num[100005], tot[100005], head[100005], vis[100005], siz[100005], fa[100005], ans[100005];
struct node
{
    int v;
    int next;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int f)
{
    fa[k] = f;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
        }
        d = a[d].next;
    }
    return;
}
void dfs2(int k, int val)
{
    vis[k] = val;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k])
            dfs2(a[d].v, val);
        d = a[d].next;
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &aa, &bb);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ++num[u];
        ++num[v];
        ++tot[u];
        ++tot[v];
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i)
    {
        if (siz[i] == aa)
        {
            p = 1;
            dfs2(i, 1);
            for (int j = 1; j <= n; ++j)
                if (!vis[j])
                    vis[j] = -1;
            break;
        }
        if (siz[i] == bb)
        {
            p = 1;
            dfs2(i, -1);
            for (int j = 1; j <= n; ++j)
                if (!vis[j])
                    vis[j] = 1;
            break;
        }
    }
    if (!p)
    {
        printf("-1");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 1 && num[i] == 1)
            q[++t] = i;
    while (h < t)
    {
        ++cnt;
        int k = q[++h];
        ans[k] = cnt;
        int d = head[k];
        while (d)
        {
            if (vis[a[d].v] == 1 && !ans[a[d].v])
            {
                --num[a[d].v];
                if (num[a[d].v] == 1)
                    q[++t] = a[d].v;
            }
            d = a[d].next;
        }
    }
    h = 0;
    t = 0;
    cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (vis[i] == -1 && tot[i] == 1)
            q[++t] = i;
    while (h < t)
    {
        --cnt;
        int k = q[++h];
        ans[k] = cnt;
        int d = head[k];
        while (d)
        {
            if (vis[a[d].v] == -1 && !ans[a[d].v])
            {
                --tot[a[d].v];
                if (tot[a[d].v] == 1)
                    q[++t] = a[d].v;
            }
            d = a[d].next;
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    return 0;
}