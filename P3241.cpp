#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int n, Q, A, sum, rt, cnt;
int head[150005], x[150005];
int siz[150005], sz[150005];
int f[150005], vis[150005];
int fa[150005], dis[150005];
int aa[150005], bb[150005], cc[150005];
int lg[300005], dfn[300005];
int st[300005][20];
ll ans;
vector<int> b[150005], c[150005];
struct node
{
    int v;
    int w;
    int nxt;
} a[300005];
struct bit
{
    int siz;
    vector<int> c;
    vector<ll> d;
    inline void init(int x)
    {
        siz = x;
        c.assign(x + 5, 0);
        d.assign(x + 5, 0);
        return;
    }
    inline int lowbit(int x)
    {
        return x & -x;
    }
    inline void add(int x, int val)
    {
        while (x <= siz)
        {
            ++c[x];
            d[x] += val;
            x += lowbit(x);
        }
        return;
    }
    inline int ask1(int x)
    {
        int num = 0;
        while (x >= 1)
        {
            num += c[x];
            x -= lowbit(x);
        }
        return num;
    }
    inline ll ask2(int x)
    {
        ll num = 0;
        while (x >= 1)
        {
            num += d[x];
            x -= lowbit(x);
        }
        return num;
    }
} bit[150005], cit[150005];
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
inline void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
inline void getrt(int k, int Fa)
{
    f[k] = 0;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != Fa && !vis[a[d].v])
        {
            getrt(a[d].v, k);
            siz[k] += siz[a[d].v];
            f[k] = max(f[k], siz[a[d].v]);
        }
        d = a[d].nxt;
    }
    f[k] = max(f[k], siz[0] - siz[k]);
    if (f[k] <= f[rt])
        rt = k;
    return;
}
inline void dfs(int k, int Fa)
{
    ++cnt;
    aa[cnt] = x[k];
    bb[cnt] = x[k];
    cc[cnt] = dis[k];
    int d = head[k];
    while (d)
    {
        if (a[d].v != Fa && !vis[a[d].v])
        {
            dis[a[d].v] = dis[k] + a[d].w;
            dfs(a[d].v, k);
        }
        d = a[d].nxt;
    }
}
inline void solve(int k)
{
    vis[k] = 1;
    cnt = 0;
    dis[k] = 0;
    dfs(k, 0);
    sort(bb + 1, bb + cnt + 1);
    int len = unique(bb + 1, bb + cnt + 1) - bb - 1;
    b[k].assign(bb, bb + len + 1);
    bit[k].init(len);
    for (register int i = 1; i <= cnt; ++i)
    {
        aa[i] = lower_bound(bb + 1, bb + len + 1, aa[i]) - bb;
        bit[k].add(aa[i], cc[i]);
    }
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            if (siz[a[d].v] < siz[k])
                siz[0] = siz[a[d].v];
            else
                siz[0] = sz[k] - siz[k];
            rt = 0;
            f[0] = siz[0];
            getrt(a[d].v, 0);
            sz[rt] = siz[0];
            fa[rt] = k;
            cnt = 0;
            dis[a[d].v] = a[d].w;
            dfs(a[d].v, 0);
            sort(bb + 1, bb + cnt + 1);
            int len = unique(bb + 1, bb + cnt + 1) - bb - 1;
            c[rt].assign(bb, bb + len + 1);
            cit[rt].init(len);
            for (int i = 1; i <= cnt; ++i)
            {
                aa[i] = lower_bound(bb + 1, bb + len + 1, aa[i]) - bb;
                cit[rt].add(aa[i], cc[i]);
            }
            solve(rt);
        }
        d = a[d].nxt;
    }
    return;
}
inline void getdis(int k, int Fa)
{
    dfn[k] = ++cnt;
    st[cnt][0] = dis[k];
    int d = head[k];
    while (d)
    {
        if (a[d].v != Fa)
        {
            dis[a[d].v] = dis[k] + a[d].w;
            getdis(a[d].v, k);
            st[++cnt][0] = dis[k];
        }
        d = a[d].nxt;
    }
    return;
}
inline int dist(int u, int v)
{
    int x = dfn[u], y = dfn[v];
    if (x > y)
        swap(x, y);
    return dis[u] + dis[v] - 2 * min(st[x][lg[y - x + 1]], st[y - (1 << lg[y - x + 1]) + 1][lg[y - x + 1]]);
}
int main()
{
    n = read();
    Q = read();
    A = read();
    for (register int i = 1; i <= n; ++i)
        x[i] = read();
    for (register int i = 1; i < n; ++i)
    {
        int u, v, w;
        u = read();
        v = read();
        w = read();
        ins(u, v, w);
        ins(v, u, w);
    }
    for (register int i = 2; i <= 2 * n; ++i)
        lg[i] = lg[i >> 1] + 1;
    siz[0] = n;
    f[0] = n;
    getrt(1, 0);
    sz[rt] = n;
    solve(rt);
    cnt = 0;
    getdis(1, 0);
    for (register int i = cnt; i >= 1; --i)
        for (register int j = 1; j <= lg[cnt - i + 1]; ++j)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    for (register int i = 1; i <= Q; ++i)
    {
        int u, aaa, bbb, L, R;
        u = read();
        aaa = read();
        bbb = read();
        L = min((aaa + ans) % A, (bbb + ans) % A);
        R = max((aaa + ans) % A, (bbb + ans) % A);
        ans = 0;
        int d = u;
        while (d)
        {
            int l = lower_bound(b[d].begin(), b[d].end(), L) - b[d].begin();
            int r = lower_bound(b[d].begin(), b[d].end(), R + 1) - b[d].begin() - 1;
            if (l <= bit[d].siz && l <= r)
            {
                int num1 = bit[d].ask1(r) - bit[d].ask1(l - 1);
                ll num2 = bit[d].ask2(r) - bit[d].ask2(l - 1);
                ans += (ll)num1 * dist(u, d) + num2;
            }
            d = fa[d];
        }
        d = u;
        while (fa[d])
        {
            int l = lower_bound(c[d].begin(), c[d].end(), L) - c[d].begin();
            int r = lower_bound(c[d].begin(), c[d].end(), R + 1) - c[d].begin() - 1;
            if (l <= bit[d].siz && l <= r)
            {
                int num1 = cit[d].ask1(r) - cit[d].ask1(l - 1);
                ll num2 = cit[d].ask2(r) - cit[d].ask2(l - 1);
                ans -= (ll)num1 * dist(u, fa[d]) + num2;
            }
            d = fa[d];
        }
        printf("%lld\n", ans);
    }
    return 0;
}