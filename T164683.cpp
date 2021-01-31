#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const double pi = acos(-1.0);
int n, cnt, rt, sum, minx, num;
int head[200005], dep[200005], r[800005];
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
    dep[k] = dep[fa] + 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
            dfs(a[d].v, k);
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
void dfsl(int k, int num, int flg)
{
    if (flg)
        fl[num].x += 1;
    if (tr[k].l && !vis[tr[k].l])
        dfsl(tr[k].l, num + 2, 0);
    if (tr[k].r && !vis[tr[k].r])
        dfsl(tr[k].r, num + 1, 1);
    return;
}
void dfsr(int k, int num, int flg)
{
    if (flg)
        fr[num].x += 1;
    if (tr[k].l && !vis[tr[k].l])
        dfsr(tr[k].l, num + 1, 1);
    if (tr[k].r && !vis[tr[k].r])
        dfsr(tr[k].r, num + 2, 0);
    return;
}
void dfsL(int k, int num, int flg)
{
    if (flg)
        gl[num].x += 1;
    if (tr[k].l && !vis[tr[k].l])
        dfsL(tr[k].l, num + 2, 0);
    if (tr[k].r && !vis[tr[k].r])
        dfsL(tr[k].r, num + 1, 1);
    return;
}
void dfsR(int k, int num, int flg)
{
    if (flg)
        gr[num].x += 1;
    if (tr[k].l && !vis[tr[k].l])
        dfsR(tr[k].l, num + 1, 1);
    if (tr[k].r && !vis[tr[k].r])
        dfsR(tr[k].r, num + 2, 0);
    return;
}
void dfsf(int k, int numl, int numr, int flg)
{
    if (tr[k].fa && !vis[tr[k].fa])
        if (flg == 1)
            dfsf(tr[k].fa, numl + 1, numr + 2, k == tr[tr[k].fa].l ? 1 : 0);
        else
            dfsf(tr[k].fa, numl + 2, numr + 1, k == tr[tr[k].fa].l ? 1 : 0);
    if (tr[k].l && !vis[tr[k].l] && flg == 0)
        dfsL(tr[k].l, numl + 1 + dep[k] - minx, 1);
    if (tr[k].r && !vis[tr[k].r] && flg == 1)
        dfsR(tr[k].r, numr + 1 + dep[k] - minx, 1);
    return;
}
void dfslef(int k, int num, int flg)
{
    if (flg)
        ++ans[num];
    if (tr[k].l && !vis[tr[k].l])
        dfslef(tr[k].l, num + 2, 0);
    if (tr[k].r && !vis[tr[k].r])
        dfslef(tr[k].r, num + 1, 1);
    return;
}
void dfsrig(int k, int num, int flg)
{
    if (flg)
        ++ans[num];
    if (tr[k].l && !vis[tr[k].l])
        dfsrig(tr[k].l, num + 1, 1);
    if (tr[k].r && !vis[tr[k].r])
        dfsrig(tr[k].r, num + 2, 0);
    return;
}
void solve(int k)
{
    vis[k] = 1;
    init(2 * sz[k]);
    if (tr[k].l && tr[k].r && !vis[tr[k].l] && !vis[tr[k].r])
    {
        dfsl(tr[k].l, 1, 1);
        dfsr(tr[k].r, 1, 1);
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
        --ans[dep[k] + 2];
    }
    dfsl(k, 0, k == tr[tr[k].fa].r ? 1 : 0);
    dfsr(k, 0, k == tr[tr[k].fa].l ? 1 : 0);
    int tmp = k;
    while (tr[tmp].fa && !vis[tr[tmp].fa])
        tmp = tr[tmp].fa;
    minx = dep[tmp];
    if (tr[k].fa && !vis[tr[k].fa])
    {
        dfsf(tr[k].fa, 2, 2, k == tr[tr[k].fa].l ? 1 : 0);
        if (k == tr[tr[k].fa].r && !vis[tr[tr[k].fa].l])
            dfslef(tr[tr[k].fa].l, dep[k] + 1, 0);
        if (k == tr[tr[k].fa].l && !vis[tr[tr[k].fa].r])
            dfsrig(tr[tr[k].fa].r, dep[k] + 1, 0);
    }
    fft(fl, 1);
    fft(fr, 1);
    fft(gl, 1);
    fft(gr, 1);
    for (int i = 0; i < num; ++i)
        g[i] = fl[i] * gr[i];
    fft(g, -1);
    for (int i = 0; i < num; ++i)
    {
        ans[i + minx - 1] += (ll)(g[i].x + 0.5);
        fl[i] = complex();
        gr[i] = complex();
    }
    for (int i = 0; i < num; ++i)
        g[i] = fr[i] * gl[i];
    fft(g, -1);
    for (int i = 0; i < num; ++i)
    {
        ans[i + minx - 1] += (ll)(g[i].x + 0.5);
        fr[i] = complex();
        gl[i] = complex();
    }
    ++ans[dep[k]];
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