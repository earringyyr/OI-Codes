#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, p, sum, tot;
int head[1005], vis[1005], co[1005];
int s[15], top[15], st[15][15];
int f[1005][2005], g[2005], chk[2005];
struct edge
{
    int v;
    int w;
    int nxt;
} a[6005];
struct node
{
    int id;
    int dis;
    node(int aa = 0, int bb = 0)
    {
        id = aa;
        dis = bb;
    }
    bool operator<(const node &bb) const
    {
        return dis > bb.dis;
    }
};
priority_queue<node> q;
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dijkstra(int S)
{
    memset(vis, 0, sizeof(vis));
    while (!q.empty())
    {
        int k = q.top().id;
        q.pop();
        if (vis[k])
            continue;
        vis[k] = 1;
        int d = head[k];
        while (d)
        {
            if (!vis[a[d].v] && f[a[d].v][S] > f[k][S] + a[d].w)
            {
                f[a[d].v][S] = f[k][S] + a[d].w;
                q.push(node(a[d].v, f[a[d].v][S]));
            }
            d = a[d].nxt;
        }
    }
    return;
}
int main()
{
    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    scanf("%d%d%d", &n, &m, &p);
    for (register int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    for (register int i = 1; i <= p; ++i)
    {
        int c, d;
        scanf("%d%d", &c, &d);
        s[i] = d;
        ++top[c];
        co[d] = c;
        f[d][1 << (i - 1)] = 0;
    }
    for (register int i = 1; i < (1 << p); ++i)
    {
        for (int id = 1; id <= n; ++id)
        {
            for (int j = i & (i - 1); j; j = i & (j - 1))
                f[id][i] = min(f[id][i], f[id][j] + f[id][i ^ j]);
            g[i] = min(g[i], f[id][i]);
            if (f[id][i] != inf)
                q.push(node(id, f[id][i]));
        }
        dijkstra(i);
    }
    for (register int i = 1; i < (1 << p); ++i)
    {
        chk[i] = 1;
        int num[15] = {0};
        for (register int j = 1; j <= p; ++j)
            if (i & (1 << (j - 1)))
                ++num[co[s[j]]];
        for (register int j = 1; j <= p; ++j)
            if (num[j] && num[j] != top[j])
                chk[i] = 0;
    }
    for (register int i = 1; i < (1 << p); ++i)
        if (chk[i])
            for (register int j = i & (i - 1); j; j = i & (j - 1))
                if (chk[j])
                    g[i] = min(g[i], g[j] + g[i ^ j]);
    printf("%d", g[(1 << p) - 1]);
    return 0;
}