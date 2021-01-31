#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
typedef long long ll;
const int mod = 998244353, inv2 = 499122177;
int n, m, up, p, sum, rt, top, ans;
int head[200005], vis[200005];
int siz[200005], f[200005], sz[200005];
int fac[5200005], inv[5200005];
int g[200005];
unordered_map<int, int> val[200005];
struct edge
{
    int v;
    int nxt;
} a[400005];
struct node
{
    int id;
    int val;
    node(int aa = 0, int bb = 0)
    {
        id = aa;
        val = bb;
    }
} st[200005];
bool cmp(node aa, node bb)
{
    return aa.id > bb.id;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
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
int C(int n, int m)
{
    return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void dfs1(int k, int fa)
{
    int tot = 0;
    int num1 = 0, num2 = 0;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            tot = (tot + g[siz[a[d].v]]) % mod;
            if (m % 2 == 0)
            {
                int tmp = C(siz[a[d].v] + m / 2 - 1, m / 2);
                num1 = (num1 + tmp) % mod;
                num2 = (num2 + (ll)tmp * tmp % mod) % mod;
            }
        }
        d = a[d].nxt;
    }
    if (m % 2 == 0)
    {
        int tmp = C(n - siz[k] + m / 2 - 1, m / 2);
        num1 = (num1 + tmp) % mod;
        num2 = (num2 + (ll)tmp * tmp % mod) % mod;
    }
    tot = (tot + g[n - siz[k]]) % mod;
    tot = (C(n + m - 1, n - 1) - tot + mod) % mod;
    tot = (tot + ((ll)num1 * num1 % mod - num2 + mod) * inv2 % mod) % mod;
    ans = (ans + (ll)k * tot % mod) % mod;
    return;
}
void getrt(int k, int fa)
{
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
void dfs2(int k, int fa, int minx)
{
    minx = min(minx, k);
    if (fa)
        st[++top] = node(minx, val[fa][k]);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
            dfs2(a[d].v, k, minx);
        d = a[d].nxt;
    }
    return;
}
void solve(int k)
{
    vis[k] = 1;
    top = 0;
    dfs2(k, 0, k);
    sort(st + 1, st + top + 1, cmp);
    int tot = 0;
    for (int i = 1; i <= top; ++i)
    {
        ans = (ans + (ll)tot * st[i].val % mod * st[i].id % mod) % mod;
        tot = (tot + st[i].val) % mod;
    }
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            top = 0;
            dfs2(a[d].v, k, k);
            sort(st + 1, st + top + 1, cmp);
            int tot = 0;
            for (int i = 1; i <= top; ++i)
            {
                ans = (ans - (ll)tot * st[i].val % mod * st[i].id % mod + mod) % mod;
                tot = (tot + st[i].val) % mod;
            }
            int tmp = val[a[d].v][k];
            for (int i = 1; i <= top; ++i)
                ans = (ans + (ll)tmp * st[i].val % mod * st[i].id % mod) % mod;
            rt = 0;
            if (siz[a[d].v] > siz[k])
                siz[0] = sz[k] - siz[k];
            else
                siz[0] = siz[a[d].v];
            f[0] = siz[0];
            getrt(a[d].v, 0);
            sz[rt] = siz[0];
            solve(rt);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    up = m + n;
    p = (m + 1) / 2;
    fac[0] = 1;
    for (int i = 1; i <= up; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[up] = ksm(fac[up], mod - 2);
    for (int i = up - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    for (int i = p; i <= m; ++i)
        g[1] = (g[1] + C(m + n - i - 2, n - 2)) % mod;
    for (int i = 2; i <= n; ++i)
        g[i] = (g[i - 1] + (ll)C(p + i - 2, p - 1) * C(m + n - p - i, m - p) % mod) % mod;
    dfs1(1, 0);
    if (m % 2 == 0)
    {
        for (int i = 1; i <= n; ++i)
        {
            int tot = 0;
            int d = head[i];
            while (d)
            {
                int sze;
                if (siz[a[d].v] > siz[i])
                    sze = n - siz[i];
                else
                    sze = siz[a[d].v];
                tot = (tot + C(sze + m / 2 - 1, m / 2)) % mod;
                d = a[d].nxt;
            }
            d = head[i];
            while (d)
            {
                int sze;
                if (siz[i] > siz[a[d].v])
                    sze = n - siz[a[d].v];
                else
                    sze = siz[i];
                int tmp = C(sze + m / 2 - 1, m / 2);
                if (siz[a[d].v] > siz[i])
                    sze = n - siz[i];
                else
                    sze = siz[a[d].v];
                tmp = ((tmp - tot + mod) % mod + C(sze + m / 2 - 1, m / 2)) % mod;
                val[a[d].v][i] = tmp;
                d = a[d].nxt;
            }
        }
        rt = 0;
        siz[0] = n;
        f[0] = n;
        getrt(1, 0);
        sz[rt] = siz[0];
        solve(rt);
    }
    printf("%d", ans);
    return 0;
}