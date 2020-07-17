#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;
int n, m, Q, s, t, sum = 1, num;
int head[155], cur[155], lev[155], c[155], frst[155], lg[155], dep[155];
int fa[155][20], minx[155][20], ans[155][155];
struct node
{
    int v;
    int w;
    int nxt;
} a[6005], b[305], d[6005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = w;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
void add(int u, int v, int w)
{
    ++num;
    b[num].v = v;
    b[num].w = w;
    b[num].nxt = frst[u];
    frst[u] = num;
    return;
}
bool bfs()
{
    for (int i = 1; i <= n; ++i)
    {
        cur[i] = head[i];
        lev[i] = -1;
    }
    int hh = 0, tt = 1, l[155];
    l[1] = s;
    lev[s] = 0;
    while (hh < tt)
    {
        ++hh;
        int k = l[hh];
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && lev[a[d].v] == -1)
            {
                lev[a[d].v] = lev[k] + 1;
                l[++tt] = a[d].v;
            }
            d = a[d].nxt;
        }
    }
    return lev[t] != -1;
}
int dinic(int k, int flow)
{
    if (k == t)
        return flow;
    int d = cur[k], res = 0, delta;
    while (d)
    {
        if (a[d].w > 0 && lev[a[d].v] == lev[k] + 1)
        {
            delta = dinic(a[d].v, min(flow - res, a[d].w));
            if (delta)
            {
                a[d].w -= delta;
                a[d ^ 1].w += delta;
                res += delta;
                if (res == flow)
                    break;
            }
        }
        d = a[d].nxt;
        cur[k] = d;
    }
    if (res != flow)
        lev[k] = -1;
    return res;
}
bool cmp(int aa, int bb)
{
    return lev[aa] < lev[bb];
}
void solve(int l, int r)
{
    if (l == r)
        return;
    s = c[l];
    t = c[r];
    int res = 0;
    while (bfs())
        res += dinic(s, inf);
    add(s, t, res);
    add(t, s, res);
    int mid;
    sort(c + l, c + r + 1, cmp);
    for (int i = l; i <= r; ++i)
        if (lev[c[i]] != -1)
        {
            mid = i - 1;
            break;
        }
    memcpy(a, d, sizeof(d));
    solve(l, mid);
    solve(mid + 1, r);
    return;
}
void dfs(int k)
{
    for (int i = 1; i <= lg[dep[k]]; ++i)
    {
        fa[k][i] = fa[fa[k][i - 1]][i - 1];
        minx[k][i] = min(minx[k][i - 1], minx[fa[k][i - 1]][i - 1]);
    }
    int d = frst[k];
    while (d)
    {
        if (b[d].v != fa[k][0])
        {
            fa[b[d].v][0] = k;
            minx[b[d].v][0] = b[d].w;
            dep[b[d].v] = dep[k] + 1;
            dfs(b[d].v);
        }
        d = b[d].nxt;
    }
    return;
}
int query(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int ans = inf;
    while (dep[u] > dep[v])
    {
        ans = min(ans, minx[u][lg[dep[u] - dep[v]]]);
        u = fa[u][lg[dep[u] - dep[v]]];
    }
    if (u == v)
        return ans;
    for (int i = lg[dep[u]]; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            ans = min(ans, minx[u][i]);
            ans = min(ans, minx[v][i]);
            u = fa[u][i];
            v = fa[v][i];
        }
    ans = min(ans, minx[u][0]);
    ans = min(ans, minx[v][0]);
    return ans;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        sum = 1;
        num = 0;
        memset(head, 0, sizeof(head));
        memset(frst, 0, sizeof(frst));
        memset(fa, 0, sizeof(fa));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            ins(u, v, w);
        }
        memcpy(d, a, sizeof(a));
        for (int i = 1; i <= n; ++i)
            c[i] = i;
        solve(1, n);
        for (int i = 2; i <= n; ++i)
            lg[i] = lg[i >> 1] + 1;
        dfs(1);
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                ans[i][j] = query(i, j);
        scanf("%d", &Q);
        for (int i = 1; i <= Q; ++i)
        {
            int x, cnt = 0;
            scanf("%d", &x);
            for (int j = 1; j <= n; ++j)
                for (int k = j + 1; k <= n; ++k)
                    if (ans[j][k] <= x)
                        ++cnt;
            printf("%d\n", cnt);
        }
        printf("\n");
    }
    return 0;
}