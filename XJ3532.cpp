#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, h, alpha, beta;
int p, q, pa, pb, qa, qb;
int c, num, ans;
int a[200005], b[200005];
int ph[200005], qh[200005], pw[200005], qw[200005];
int fac[400005], inv[400005];
int r[800005], f[800005], g[800005];
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
void init(int len)
{
    num = 1;
    while (num < len)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    return;
}
void ntt(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int ww = ksm(3, (mod - 1) / (mid << 1));
        if (type == -1)
            ww = ksm(ww, mod - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int w = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)w * c[j + mid + k] % mod;
                c[j + k] = (x + y) % mod;
                c[j + mid + k] = (x - y + mod) % mod;
                w = (ll)w * ww % mod;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod;
    }
    return;
}
int main()
{
    scanf("%d%d%d%d", &n, &h, &alpha, &beta);
    scanf("%d%d%d%d", &pa, &pb, &qa, &qb);
    p = (ll)pa * ksm(pb, mod - 2) % mod;
    q = (ll)qa * ksm(qb, mod - 2) % mod;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    c = ((ll)p * alpha + (ll)q * beta) % mod;
    int tmp = ksm(h, n + 1);
    ph[0] = 1;
    qh[0] = 1;
    pw[0] = 1;
    qw[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        ph[i] = (ll)ph[i - 1] * tmp % mod;
        qh[i] = (ll)qh[i - 1] * h % mod;
        pw[i] = (ll)pw[i - 1] * p % mod;
        qw[i] = (ll)qw[i - 1] * q % mod;
    }
    fac[0] = 1;
    for (int i = 1; i <= 2 * n; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[2 * n] = ksm(fac[2 * n], mod - 2);
    for (int i = 2 * n - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    init(2 * n - 1);
    for (int i = n - 1; i >= 0; --i)
    {
        f[i] = (f[i + 1] + ph[i + 1]) % mod;
        g[i] = (g[i + 1] + qh[i + 1]) % mod;
    }
    for (int i = 0; i < n; ++i)
    {
        f[i] = (ll)f[i] * pw[i] % mod * inv[i] % mod;
        g[i] = (ll)g[i] * qw[i] % mod * inv[i] % mod;
    }
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 0; i < num; ++i)
        ans = (ans + (ll)c * f[i] % mod * fac[i] % mod) % mod;
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    init(2 * n + 1);
    for (int i = 0; i <= n; ++i)
    {
        f[i] = a[i];
        g[i] = ph[n - i];
    }
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        g[i] = (ll)f[i] * g[i] % mod;
    ntt(g, -1);
    memset(f, 0, sizeof(f));
    for (int i = 0; i <= n; ++i)
        f[i] = (ll)g[n - i] * pw[i] % mod * inv[i] % mod;
    memset(g, 0, sizeof(g));
    for (int i = 0; i < n; ++i)
        g[i] = (ll)qw[i + 1] * qh[i + 1] % mod * inv[i] % mod;
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 0; i < num; ++i)
        ans = (ans + (ll)f[i] * fac[i]) % mod;
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    init(2 * n + 1);
    for (int i = 0; i <= n; ++i)
    {
        f[i] = b[i];
        g[i] = qh[n - i];
    }
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        g[i] = (ll)f[i] * g[i] % mod;
    ntt(g, -1);
    memset(f, 0, sizeof(f));
    for (int i = 0; i <= n; ++i)
        f[i] = (ll)g[n - i] * qw[i] % mod * inv[i] % mod;
    memset(g, 0, sizeof(g));
    for (int i = 0; i < n; ++i)
        g[i] = (ll)pw[i + 1] * ph[i + 1] % mod * inv[i] % mod;
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 0; i < num; ++i)
        ans = (ans + (ll)f[i] * fac[i]) % mod;
    for (int i = 1; i <= n; ++i)
    {
        ans = (ans + (ll)a[i] * ph[i]) % mod;
        ans = (ans + (ll)b[i] * qh[i]) % mod;
    }
    printf("%d", ans);
    return 0;
}