#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, sum;
int head[200005], siz[200005];
int fac[200005], inv[200005];
int f[200005], g[200005], ans[200005];
struct node
{
    int v;
    int nxt;
} a[400005];
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
    if (n < m)
        return 0;
    return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int fa)
{
    f[k] = 1;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            f[k] = (ll)f[k] * f[a[d].v] % mod * C(siz[k] - 1, siz[a[d].v]) % mod;
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int fa)
{
    ans[k] = (ll)g[k] * f[k] % mod * C(n - 1, n - siz[k]) % mod;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            g[a[d].v] = (ll)ans[k] * ksm(f[a[d].v], mod - 2) % mod * ksm(C(n - 1, siz[a[d].v]), mod - 2) % mod;
            dfs2(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[n] = ksm(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    g[1] = 1;
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}