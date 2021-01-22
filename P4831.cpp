#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, num = 1, ans;
int fac[200005], inv[200005];
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
    scanf("%d%d", &n, &m);
    int top = max(2 * n, m);
    fac[0] = 1;
    for (int i = 1; i <= top; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[top] = ksm(fac[top], mod - 2);
    for (int i = top - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    while (num <= 2 * n)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    for (int i = 0; i <= n; ++i)
    {
        f[i] = (ll)C(n, i) * ksm(2, i) % mod * fac[2 * (n - i)] % mod;
        if (i & 1)
            f[i] = (mod - f[i]) % mod;
        g[i] = inv[i];
    }
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 0; i <= n; ++i)
        ans = (ans + (ll)C(m, i) * C(m - i, 2 * (n - i)) % mod * f[i] % mod * fac[i] % mod * ksm(ksm(2, n + i), mod - 2) % mod) % mod;
    printf("%d", ans);
    return 0;
}