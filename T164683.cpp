#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const double pi = acos(-1.0);
int n, cnt, rt, sum, minx, num;
int head[200005], dep[200005], sze[200005], r[800005];
int vis[200005], siz[200005], sz[200005], dp[200005];
ll ans[200005];
struct node
{
    int l;
    int r;
    int fa;
} tr[200005];
struct edge
{
    int v;
    int nxt;
} a[400005];
struct complex
{
    double x;
    double y;
    complex(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
    complex operator+(const complex &bb)
    {
        return complex(x + bb.x, y + bb.y);
    }
    complex operator-(const complex &bb)
    {
        return complex(x - bb.x, y - bb.y);
    }
    complex operator*(const complex &bb)
    {
        return complex(x * bb.x - y * bb.y, x * bb.y + y * bb.x);
    }
} fl[800005], fr[800005], gl[800005], gr[800005], g[800005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void build(int &x, int l, int r)
{
    x = ++cnt;
    if (l == r)
        return;
    int mid;
    scanf("%d", &mid);
    build(tr[x].l, l, mid);
    build(tr[x].r, mid + 1, r);
    tr[tr[x].l].fa = x;
    tr[tr[x].r].fa = x;
    ins(x, tr[x].l);
    ins(tr[x].l, x);
    ins(x, tr[x].r);
    ins(tr[x].r, x);
    return;
}
void dfs(int k, int fa)
{
    sze[k] = 1;
    dep[k] = dep[fa] + 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, k);
            sze[k] += sze[a[d].v];
        }
        d = a[d].nxt;
    }
    return;
}
void init(int len)
{
    num = 1;
    while (num < len)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    return;
}
void fft(complex *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        complex ww(cos(pi / mid), type * sin(pi / mid));
        for (int j = 0; j < num; j += (mid << 1))
        {
            complex w(1);
            for (int k = 0; k < mid; ++k)
            {
                complex x = c[j + k], y = w * c[j + mid + k];
                c[j + k] = x + y;
                c[j + mid + k] = x - y;
                w = w * ww;
            }
        }
    }
    if (type == -1)
        for (int i = 0; i < num; ++i)
            c[i].x /= num;
    return;
}
void getrt(int k, int fa)
{
    dp[k] = 0;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            getrt(a[d].v, k);
            siz[k] += siz[a[d].v];
            dp[k] = max(dp[k], siz[a[d].v]);
        }
        d = a[d].nxt;
    }
    dp[k] = max(dp[k], siz[0] - siz[k]);
    if (dp[k] < dp[rt])
        rt = k;
    return;
}
void dfsl(int k, int num)
{
    fl[num].x += 1;
    if (tr[k].l && !vis[tr[k].l])
        dfsl(tr[k].l, num + 2);
    if (tr[k].r && !vis[tr[k].r])
        dfsl(tr[k].r, num + 1);
    return;
}
void dfsr(int k, int num)
{
    fr[num].x += 1;
    if (tr[k].l && !vis[tr[k].l])
        dfsr(tr[k].l, num + 1);
    if (tr[k].r && !vis[tr[k].r])
        dfsr(tr[k].r, num + 2);
    return;
}
void dfsL(int k, int num)
{
    gl[num].x += 1;
    if (tr[k].l && !vis[tr[k].l])
        dfsL(tr[k].l, num + 2);
    if (tr[k].r && !vis[tr[k].r])
        dfsL(tr[k].r, num + 1);
    return;
}
void dfsR(int k, int num)
{
    gr[num].x += 1;
    if (tr[k].l && !vis[tr[k].l])
        dfsR(tr[k].l, num + 1);
    if (tr[k].r && !vis[tr[k].r])
        dfsR(tr[k].r, num + 2);
    return;
}
void dfsf(int k, int numl, int numr)
{
    if (tr[k].fa && !vis[tr[k].fa])
        if (k == tr[tr[k].fa].l)
            dfsf(tr[k].fa, numl + 1, numr + 2);
        else
            dfsf(tr[k].fa, numl + 2, numr + 1);
    if (tr[k].l && !vis[tr[k].l] && tr[tr[k].l].fa != k)
        dfsL(tr[k].l, numl + 1 + dep[k] - minx);
    if (tr[k].r && !vis[tr[k].r] && tr[tr[k].r].fa != k)
        dfsR(tr[k].r, numr + 1 + dep[k] - minx);
    return;
}
void solve(int k)
{
    vis[k] = 1;
    init(2 * sz[k]);
    if (tr[k].l && tr[k].r && !vis[tr[k].l] && !vis[tr[k].r])
    {
        fl[0].x += 1;
        fr[0].x += 1;
        dfsl(tr[k].l, 1);
        dfsr(tr[k].r, 1);
        fft(fl, 1);
        fft(fr, 1);
        for (int i = 0; i < num; ++i)
            g[i] = fl[i] * fr[i];
        fft(g, -1);
        for (int i = 0; i < num; ++i)
        {
            ans[i + dep[k]] += (ll)(g[i].x + 0.5);
            fl[i] = complex();
            fr[i] = complex();
        }
    }
    dfsl(k, 0);
    dfsr(k, 0);
    int tmp = k;
    while (tr[tmp].fa && !vis[tr[tmp].fa])
        tmp = tr[tmp].fa;
    minx = dep[tmp];
    if (tr[k].fa && !vis[tr[k].fa])
        dfsf(tr[k].fa, 2, 2);
    fft(fl, 1);
    fft(fr, 1);
    fft(gl, 1);
    fft(gr, 1);
    for (int i = 0; i < num; ++i)
        g[i] = fl[i] * gr[i];
    fft(g, -1);
    for (int i = 0; i < num; ++i)
        ans[i + minx] += (ll)(g[i].x + 0.5);
    for (int i = 0; i < num; ++i)
        g[i] = fr[i] * gl[i];
    fft(g, -1);
    for (int i = 0; i < num; ++i)
    {
        ans[i + minx] += (ll)(g[i].x + 0.5);
        fl[i] = complex();
        fr[i] = complex();
        gl[i] = complex();
        gr[i] = complex();
    }
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            rt = 0;
            if (siz[a[d].v] > siz[k])
                siz[0] = sz[k] - siz[k];
            else
                siz[0] = siz[a[d].v];
            dp[0] = siz[0];
            getrt(a[d].v, k);
            sz[rt] = siz[0];
            solve(rt);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    build(rt, 1, n);
    dfs(1, 0);
    rt = 0;
    siz[0] = 2 * n - 1;
    dp[0] = siz[0];
    getrt(1, 0);
    sz[rt] = 2 * n - 1;
    solve(rt);
    for (int i = 1; i <= 2 * n - 1; ++i)
        printf("%lld ", ans[i]);
    return 0;
}