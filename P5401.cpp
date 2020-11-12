#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int D, n, m, num, ans;
int fac[100005], inv[100005];
int f[400005], g[400005], r[400005];
int ksm(int a, int k)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = (ll)a * b % mod;
        a = (ll)a * a % mod;
        k >>= 1;
    }
    return b;
}
void pre(int len)
{
    num = 1;
    while (num < len)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    return;
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
    scanf("%d%d%d", &D, &n, &m);
    if (2 * m <= n - D)
    {
        printf("%d", ksm(D, n));
        return 0;
    }
    if (2 * m > n)
    {
        printf("%d", 0);
        return 0;
    }
    fac[0] = 1;
    for (int i = 1; i <= D; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[D] = ksm(fac[D], mod - 2);
    for (int i = D - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    pre(2 * D + 1);
    for (int i = 0; i <= D; ++i)
    {
        f[i] = ((ll)ksm(-1, i) * ksm((D - 2 * i % mod + mod) % mod, n) % mod * inv[i] % mod + mod) % mod;
        g[i] = inv[i];
    }
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 0; i <= D; ++i)
    {
        f[i] = (ll)f[i] * fac[D] % mod * ksm(ksm(2, i), mod - 2) % mod * inv[D - i] % mod * fac[i] % mod;
        g[i] = (ksm(-1, i) * inv[i] + mod) % mod;
    }
    for (int i = 0; i <= D / 2; ++i)
        swap(f[i], f[D - i]);
    for (int i = D + 1; i < num; ++i)
    {
        f[i] = 0;
        g[i] = 0;
    }
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 0; i <= n - 2 * m; ++i)
        ans = (ans + (ll)f[D - i] * inv[i] % mod) % mod;
    printf("%d", ans);
    return 0;
}