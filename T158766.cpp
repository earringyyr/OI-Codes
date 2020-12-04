#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
const int inf = 0x7fffffff, mod = 19260817;
int n, m, sum, ssum, ans;
int head[500005], hhead[500005], x[500005], vis[500005];
int d[500005], dd[500005], fa[500005], mo[500005], hav[500005];
struct node
{
    int v;
    int w;
    int next;
} a[10000005], b[10000005];
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
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
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
    for (int i = 1; i <= n; ++i)
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
    for (int i = 1; i <= n; ++i)
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
int main()
{
    ans = inf;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &x[i]);
        if (hav[x[i]])
        {
            printf("0");
            return 0;
        }
        hav[x[i]] = 1;
    }
    for (int i = 0; i < (1 << 18); ++i)
        for (int j = 0; j < 18; ++j)
        {
            int u = i, v = i ^ (1 << j);
            int w = ksm(max(u, v), (1 << j)) + 1;
            ++m;
            ins(u, v, w);
            iins(v, u, w);
        }
    dijkstra1();
    dijkstra2();
    for (int i = 1; i <= m; ++i)
        if (fa[b[i].v] != mo[a[i].v])
            if ((ll)d[b[i].v] + a[i].w + dd[a[i].v] < ans)
                ans = d[b[i].v] + a[i].w + dd[a[i].v];
    printf("%d\n", ans);
    return 0;
}