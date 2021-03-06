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
void ntt1(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int w = ksm(3, (mod1 - 1) / (mid << 1));
        if (type == -1)
            w = ksm(w, mod1 - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)ww * c[j + mid + k] % mod1;
                c[j + k] = (x + y) % mod1;
                c[j + mid + k] = (x - y + mod1) % mod1;
                ww = (ll)w * ww % mod1;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod1 - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod1;
    }
    return;
}
void ntt2(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int w = ksm(3, (mod2 - 1) / (mid << 1));
        if (type == -1)
            w = ksm(w, mod2 - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)ww * c[j + mid + k] % mod2;
                c[j + k] = (x + y) % mod2;
                c[j + mid + k] = (x - y + mod2) % mod2;
                ww = (ll)w * ww % mod2;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod2 - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod2;
    }
    return;
}
void ntt3(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int w = ksm(3, (mod3 - 1) / (mid << 1));
        if (type == -1)
            w = ksm(w, mod3 - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)ww * c[j + mid + k] % mod3;
                c[j + k] = (x + y) % mod3;
                c[j + mid + k] = (x - y + mod3) % mod3;
                ww = (ll)w * ww % mod3;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod3 - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod3;
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
    ntt1(f[1], 1);
    ntt1(g[1], 1);
    for (int i = 0; i < num; ++i)
        f[1][i] = (ll)f[1][i] * g[1][i] % mod;
    ntt1(f[1], -1);
    mod = mod2;
    ntt2(f[2], 1);
    ntt2(g[2], 1);
    for (int i = 0; i < num; ++i)
        f[2][i] = (ll)f[2][i] * g[2][i] % mod;
    ntt2(f[2], -1);
    mod = mod3;
    ntt3(f[3], 1);
    ntt3(g[3], 1);
    for (int i = 0; i < num; ++i)
        f[3][i] = (ll)f[3][i] * g[3][i] % mod;
    ntt3(f[3], -1);
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