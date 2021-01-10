#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, num;
int r[400005];
int f[400005], ff[400005], g[400005], gg[400005], ggg[400005];
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
void inv(int k)
{
    if (k == 1)
    {
        gg[0] = ksm(g[0], mod - 2);
        return;
    }
    inv((k + 1) >> 1);
    num = 1;
    while (num < (k << 1))
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    for (int i = 0; i < k; ++i)
        ff[i] = g[i];
    for (int i = k; i < num; ++i)
        ff[i] = 0;
    ntt(ff, 1);
    ntt(gg, 1);
    for (int i = 0; i < num; ++i)
        gg[i] = (2 * gg[i] % mod - (ll)ff[i] * gg[i] % mod * gg[i] % mod + mod) % mod;
    ntt(gg, -1);
    for (int i = k; i < num; ++i)
        gg[i] = 0;
    return;
}
void ln(int k)
{
    memset(gg, 0, sizeof(gg));
    inv(k);
    num = 1;
    while (num < (k << 1))
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    for (int i = 0; i < k - 1; ++i)
        ggg[i] = (ll)g[i + 1] * (i + 1) % mod;
    for (int i = k - 1; i < num; ++i)
        ggg[i] = 0;
    ntt(gg, 1);
    ntt(ggg, 1);
    for (int i = 0; i < num; ++i)
        gg[i] = (ll)gg[i] * ggg[i] % mod;
    ntt(gg, -1);
    ggg[0] = 0;
    for (int i = 1; i < k; ++i)
        ggg[i] = (ll)gg[i - 1] * ksm(i, mod - 2) % mod;
    for (int i = k; i < num; ++i)
        ggg[i] = 0;
    return;
}
void exp(int k)
{
    if (k == 1)
    {
        g[0] = 1;
        return;
    }
    exp((k + 1) >> 1);
    ln(k);
    num = 1;
    while (num < (k << 1))
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    for (int i = 0; i < k; ++i)
        ff[i] = (f[i] - ggg[i] + mod) % mod;
    for (int i = k; i < num; ++i)
        ff[i] = 0;
    ff[0] = (ff[0] + 1) % mod;
    ntt(ff, 0);
    ntt(g, 0);
    for (int i = 0; i < num; ++i)
        g[i] = (ll)ff[i] * g[i] % mod;
    ntt(g, -1);
    for (int i = k; i < num; ++i)
        g[i] = 0;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &f[i]);
    exp(n);
    for (int i = 0; i < n; ++i)
        printf("%d ", g[i]);
    return 0;
}