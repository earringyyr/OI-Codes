#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, k, sum;
int head[105], vis[105], s[15], f[105][10005];
struct edge
{
    int v;
    int w;
    int nxt;
} a[1005];
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
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &s[i]);
        f[s[i]][1 << (i - 1)] = 0;
    }
    for (int i = 1; i < (1 << k); ++i)
    {
        for (int id = 1; id <= n; ++id)
        {
            for (int j = i & (i - 1); j; j = i & (j - 1))
                f[id][i] = min(f[id][i], f[id][j] + f[id][i ^ j]);
            if (f[id][i] != inf)
                q.push(node(id, f[id][i]));
        }
        dijkstra(i);
    }
    printf("%d", f[s[1]][(1 << k) - 1]);
    return 0;
}