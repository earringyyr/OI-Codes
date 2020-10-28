#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int mod1 = 469762049, mod2 = 998244353, mod3 = 1004535809;
int n, m, p, mod, num = 1;
int r[400005], f[5][400005], g[5][400005];
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
    scanf("%d%d%d", &n, &m, &p);
    ++n;
    ++m;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &f[0][i]);
        f[1][i] = f[0][i] % mod1;
        f[2][i] = f[0][i] % mod2;
        f[3][i] = f[0][i] % mod3;
    }
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &g[0][i]);
        g[1][i] = g[0][i] % mod1;
        g[2][i] = g[0][i] % mod2;
        g[3][i] = g[0][i] % mod3;
    }
    while (num < n + m - 1)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    mod = mod1;
    ntt(f[1], 1);
    ntt(g[1], 1);
    for (int i = 0; i < num; ++i)
        f[1][i] = (ll)f[1][i] * g[1][i] % mod;
    ntt(f[1], -1);
    mod = mod2;
    ntt(f[2], 1);
    ntt(g[2], 1);
    for (int i = 0; i < num; ++i)
        f[2][i] = (ll)f[2][i] * g[2][i] % mod;
    ntt(f[2], -1);
    mod = mod3;
    ntt(f[3], 1);
    ntt(g[3], 1);
    for (int i = 0; i < num; ++i)
        f[3][i] = (ll)f[3][i] * g[3][i] % mod;
    ntt(f[3], -1);
    mod = mod2;
    int inv1 = ksm(mod1, mod2 - 2);
    mod = mod3;
    int inv2 = ksm((ll)mod1 * mod2 % mod3, mod3 - 2);
    mod = p;
    for (int i = 0; i < n + m - 1; ++i)
    {
        ll ans = (ll)(f[2][i] - f[1][i] + mod2) % mod2 * inv1 % mod2 * mod1 + f[1][i];
        ans = ((ll)((f[3][i] - ans) % mod3 + mod3) % mod3 * inv2 % mod3 * mod1 % mod * mod2 % mod + ans) % mod;
        printf("%d ", (int)ans);
    }
    return 0;
}