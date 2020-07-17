#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long
using namespace std;
int t, n, m, p, sum, ssum, ans, head[100005], hhead[100005], x[100005], vis[100005], d[100005], dd[100005], fa[100005], mo[100005];
struct node
{
    int v;
    int w;
    int next;
} a[500005], b[500005];
struct point
{
    int id;
    int d;
    point(int aa, int bb)
    {
        id = aa;
        d = bb;
    }
    bool operator<(const point &bb) const
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
    b[ssum].v = v;
    b[ssum].w = w;
    b[ssum].next = hhead[u];
    hhead[u] = ssum;
    return;
}
void dijkstra1()
{
    memset(d, 0x7f, sizeof(d));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= p; ++i)
    {
        fa[x[i]] = x[i];
        d[x[i]] = 0;
        q.push(point(x[i], 0));
    }
    while (!q.empty())
    {
        point kk = q.top();
        q.pop();
        int id = kk.id;
        if (vis[id])
            continue;
        vis[id] = 1;
        int ddd = head[id];
        while (ddd)
        {
            if (d[a[ddd].v] > d[id] + a[ddd].w)
            {
                d[a[ddd].v] = d[id] + a[ddd].w;
                fa[a[ddd].v] = fa[id];
                q.push(point(a[ddd].v, d[a[ddd].v]));
            }
            ddd = a[ddd].next;
        }
    }
    return;
}
void dijkstra2()
{
    memset(dd, 0x7f, sizeof(d));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= p; ++i)
    {
        mo[x[i]] = x[i];
        dd[x[i]] = 0;
        q.push(point(x[i], 0));
    }
    while (!q.empty())
    {
        point kk = q.top();
        q.pop();
        int id = kk.id;
        if (vis[id])
            continue;
        vis[id] = 1;
        int ddd = hhead[id];
        while (ddd)
        {
            if (dd[b[ddd].v] > dd[id] + b[ddd].w)
            {
                dd[b[ddd].v] = dd[id] + b[ddd].w;
                mo[b[ddd].v] = mo[id];
                q.push(point(b[ddd].v, dd[b[ddd].v]));
            }
            ddd = b[ddd].next;
        }
    }
    return;
}
signed main()
{
    scanf("%lld", &t);
    for(int tt = 1; tt <= t; ++tt)
    {
        sum=0;
        ssum=0;
        ans = 0x7f7f7f7f7f7f7f7f;
        memset(head, 0, sizeof(head));
        memset(hhead, 0, sizeof(hhead));
        scanf("%lld%lld%lld", &n, &m, &p);
        for (int i = 1; i <= n; ++i)
        {
            fa[i] = 0;
            mo[i] = 0;
        }
        for (int i = 1; i <= m; ++i)
        {
            int u, v, w;
            scanf("%lld%lld%lld", &u, &v, &w);
            ins(u, v, w);
            iins(v, u, w);
        }
        for (int i = 1; i <= p; ++i)
            scanf("%lld", &x[i]);
        dijkstra1();
        dijkstra2();
        for(int i = 1; i <= m; ++i)
        	if(fa[b[i].v] != mo[a[i].v])
	            if(d[b[i].v] + a[i].w + dd[a[i].v] < ans)
	                ans = d[b[i].v] + a[i].w + dd[a[i].v];
        printf("%lld\n", ans);
    }
    return 0;
}
