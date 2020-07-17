#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int n, m, sum, rt, num, res, ans;
int val[100005], head[100005], vis[100005];
int siz[100005], sz[100005], f[100005], fa[100005];
int dis[100005], dfn[100005], t[100005], dep[100005];
int lg[200005], st[200005][20];
struct node
{
    int v;
    int nxt;
} a[200005];
struct bit
{
    int siz;
    vector<int> c;
    void init()
    {
        c.assign(siz + 5, 0);
        return;
    }
    int lowbit(int x)
    {
        return x & -x;
    }
    void add(int x, int val)
    {
        while (x <= siz)
        {
            c[x] += val;
            x += lowbit(x);
        }
        return;
    }
    int ask(int x)
    {
        x = min(x, siz);
        int cnt = 0;
        while (x >= 1)
        {
            cnt += c[x];
            x -= lowbit(x);
        }
        return cnt;
    }
} f1[100005], f2[100005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa)
{
    st[++num][0] = dis[k];
    dfn[k] = num;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dis[a[d].v] = dis[k] + 1;
            dfs(a[d].v, k);
            st[++num][0] = dis[k];
        }
        d = a[d].nxt;
    }
    return;
}
void getrt(int k, int fa)
{
    f[k] = fa;
    siz[k] = 1;
    f[k] = 0;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            getrt(a[d].v, k);
            siz[k] += siz[a[d].v];
            f[k] = max(f[k], siz[a[d].v]);
        }
        d = a[d].nxt;
    }
    f[k] = max(f[k], siz[0] - siz[k]);
    if (f[k] < f[rt])
        rt = k;
    return;
}
void getdis(int k, int fa)
{
    t[dep[k]] += val[k];
    res = max(res, dep[k]);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            dep[a[d].v] = dep[k] + 1;
            getdis(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
void calc(bit &k)
{
    k.siz = res + 1;
    k.init();
    for (int i = 0; i <= res; ++i)
    {
        k.add(i + 1, t[i]);
        t[i] = 0;
    }
    return;
}
void solve(int k)
{
    vis[k] = 1;
    dep[k] = 0;
    res = 0;
    getdis(k, 0);
    calc(f1[k]);
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            rt = 0;
            if (siz[a[d].v] < siz[k])
                siz[0] = siz[a[d].v];
            else
                siz[0] = sz[k] - siz[k];
            f[0] = siz[0];
            getrt(a[d].v, 0);
            sz[rt] = siz[0];
            res = 0;
            dep[a[d].v] = 1;
            getdis(a[d].v, 0);
            calc(f2[rt]);
            fa[rt] = k;
            solve(rt);
        }
        d = a[d].nxt;
    }
    return;
}
int dist(int u, int v)
{
    int x = dfn[u], y = dfn[v];
    if (x > y)
        swap(x, y);
    int t = lg[y - x + 1];
    return dis[u] + dis[v] - 2 * min(st[x][t], st[y - (1 << t) + 1][t]);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &val[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs(1, 0);
    for (int i = 2; i <= num; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = num; i >= 1; --i)
        for (int j = 1; j <= lg[num - i + 1]; ++j)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    siz[0] = n;
    f[0] = n;
    getrt(1, 0);
    sz[rt] = n;
    solve(rt);
    for (int i = 1; i <= m; ++i)
    {
        int type, x, y;
        scanf("%d%d%d", &type, &x, &y);
        x ^= ans;
        y ^= ans;
        if (type == 0)
        {
            ans = 0;
            int d = x;
            while (d)
            {
                ans += f1[d].ask(y - dist(d, x) + 1);
                d = fa[d];
            }
            d = x;
            while (fa[d])
            {
                ans -= f2[d].ask(y - dist(fa[d], x) + 1);
                d = fa[d];
            }
            printf("%d\n", ans);
        }
        if (type == 1)
        {
            int d = x;
            while (d)
            {
                f1[d].add(dist(d, x) + 1, y - val[x]);
                d = fa[d];
            }
            d = x;
            while (fa[d])
            {
                f2[d].add(dist(fa[d], x) + 1, y - val[x]);
                d = fa[d];
            }
            val[x] = y;
        }
    }
    return 0;
}