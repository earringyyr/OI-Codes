#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1004535809;
int n, m, s, num = 1, ans;
int w[100005];
int fac[10000005], inv[10000005];
int r[400005], f[400005], g[400005];
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
void ntt(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int w = ksm(3, (mod - 1) / (mid << 1));
        if (type == -1)
            w = ksm(w, mod - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)ww * c[j + mid + k] % mod;
                c[j + k] = (x + y) % mod;
                c[j + mid + k] = (x - y + mod) % mod;
                ww = (ll)w * ww % mod;
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
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i <= m; ++i)
        scanf("%d", &w[i]);
    int lim = max(n, m);
    fac[0] = 1;
    for (int i = 1; i <= lim; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[lim] = ksm(fac[lim], mod - 2);
    for (int i = lim - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    lim = min(m, n / s);
    for (int i = 0; i <= lim; ++i)
        f[i] = (ll)C(m, i) * fac[n] % mod * ksm(inv[s], i) % mod * inv[n - i * s] % mod * ksm(m - i, n - i * s) % mod;
    for (int i = 0; i <= lim; ++i)
        g[i] = (ll)f[lim - i] * fac[lim - i] % mod;
    for (int i = 0; i <= lim; ++i)
        f[i] = ((i % 2 == 0 ? 1 : -1) * inv[i] + mod) % mod;
    while (num <= 2 * lim)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 0; i <= lim; ++i)
        ans = (ans + (ll)f[lim - i] * inv[i] % mod * w[i] % mod) % mod;
    printf("%d", ans);
    return 0;
}