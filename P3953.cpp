#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int t, n, m, k, p, sum, ssum, head[100005], hhead[100005], d[100005], vis[100005], f[100005][100], use[100005][100];
struct node
{
    int v;
    int w;
    int next;
} a[200005], aa[200005];
struct point
{
    int id;
    int d;
    point(int aa, int bb)
    {
        id = aa;
        d = bb;
    }
    bool operator<(const point bb) const
    {
        return d > bb.d;
    }
};
priority_queue<point> q;
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void iins(int u, int v, int w)
{
    ++ssum;
    aa[ssum].v = v;
    aa[ssum].w = w;
    aa[ssum].next = hhead[u];
    hhead[u] = ssum;
    return;
}
void dijkstra()
{
    memset(d, 0x7f, sizeof(d));
    d[n] = 0;
    q.push(point(n, 0));
    while (!q.empty())
    {
        point k = q.top();
        q.pop();
        if (vis[k.id])
            continue;
        vis[k.id] = 1;
        int dd = hhead[k.id];
        while (dd)
        {
            if (!vis[aa[dd].v] && d[aa[dd].v] > d[k.id] + aa[dd].w)
            {
                d[aa[dd].v] = d[k.id] + aa[dd].w;
                q.push(point(aa[dd].v, d[aa[dd].v]));
            }
            dd = aa[dd].next;
        }
    }
    return;
}
int dfs(int w, int k)
{
    if (use[w][k])
    {
        f[w][k] = -1;
        return -1;
    }
    if (f[w][k])
        return f[w][k];
    if (w == n)
        f[w][k] = 1;
    use[w][k] = 1;
    int dd = head[w];
    while (dd)
    {
        if (k >= d[a[dd].v] - d[w] + a[dd].w)
        {
            int l = dfs(a[dd].v, k - d[a[dd].v] + d[w] - a[dd].w);
            if (l == -1)
            {
                f[w][k] = -1;
                return -1;
            }
            f[w][k] = (f[w][k] + l) % p;
        }
        dd = a[dd].next;
    }
    use[w][k] = 0;
    return f[w][k];
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        sum = 0;
        ssum = 0;
        memset(head, 0, sizeof(head));
        memset(hhead, 0, sizeof(hhead));
        memset(f, 0, sizeof(f));
        memset(use, 0, sizeof(use));
        memset(vis, 0, sizeof(vis));
        scanf("%d%d%d%d", &n, &m, &k, &p);
        for (int i = 1; i <= m; ++i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            ins(u, v, w);
            iins(v, u, w);
        }
        dijkstra();
        printf("%d\n", dfs(1, k));
    }
    return 0;
}