#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int n, m, Q, k, s, sum, num, cnt, ans;
int vis[200005], dis[400005];
int head[400005], fa[400005];
int val[400005], dep[400005];
int lg[400005], f[400005][20];
struct edge
{
    int u;
    int v;
    int w;
    int nxt;
    edge(int uu = 0, int vv = 0, int ww = 0)
    {
        u = uu;
        v = vv;
        w = ww;
    }
} a[800005], b[400005];
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
bool cmp(edge aa, edge bb)
{
    return aa.w > bb.w;
}
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dijkstra()
{
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x7f, sizeof(dis));
    dis[1] = 0;
    q.push(node(1, 0));
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
            if (!vis[a[d].v] && dis[a[d].v] > dis[k] + a[d].w)
            {
                dis[a[d].v] = dis[k] + a[d].w;
                q.push(node(a[d].v, dis[a[d].v]));
            }
            d = a[d].nxt;
        }
    }
    return;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void dfs(int k, int ff)
{
    f[k][0] = ff;
    for (int i = 1; i <= lg[dep[k]]; ++i)
        f[k][i] = f[f[k][i - 1]][i - 1];
    int d = head[k];
    while (d)
    {
        if (a[d].v != ff)
        {
            dep[a[d].v] = dep[k] + 1;
            dfs(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        num = 0;
        sum = 0;
        memset(head, 0, sizeof(head));
        scanf("%d%d", &n, &m);
        for (int i = 1; i < 2 * n; ++i)
            fa[i] = i;
        for (int i = 1; i <= m; ++i)
        {
            int u, v, l, a;
            scanf("%d%d%d%d", &u, &v, &l, &a);
            ins(u, v, l);
            ins(v, u, l);
            b[++num] = edge(u, v, a);
        }
        scanf("%d%d%d", &Q, &k, &s);
        dijkstra();
        cnt = n;
        sum = 0;
        memset(head, 0, sizeof(head));
        sort(b + 1, b + num + 1, cmp);
        for (int i = 1; i <= num; ++i)
        {
            int u = getfather(b[i].u), v = getfather(b[i].v);
            if (u != v)
            {
                ++cnt;
                val[cnt] = b[i].w;
                dis[cnt] = min(dis[u], dis[v]);
                fa[u] = cnt;
                fa[v] = cnt;
                ins(cnt, u, b[i].w);
                ins(cnt, v, b[i].w);
            }
        }
        for (int i = 2; i <= cnt; ++i)
            lg[i] = lg[i >> 1] + 1;
        lg[0] = -1;
        dfs(cnt, 0);
        while (Q--)
        {
            int v, p;
            scanf("%d%d", &v, &p);
            v = (v + k * ans - 1) % n + 1;
            p = (p + k * ans) % (s + 1);
            for (int i = lg[dep[v]]; i >= 0; --i)
                if (lg[dep[v]] >= i && val[f[v][i]] > p)
                    v = f[v][i];
            ans = dis[v];
            printf("%d\n", ans);
        }
    }
    return 0;
}