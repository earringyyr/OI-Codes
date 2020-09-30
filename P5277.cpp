#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, num = 1, f[400005], ff[400005], h[400005], g[400005], r[400005];
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
int ksm(int aa, int ww, int k)
{
    int bb = 1, cc = 1, dd = 0;
    while (k)
    {
        if (k & 1)
        {
            int tmp = ((ll)aa * dd % mod + (ll)bb * cc % mod) % mod;
            cc = ((ll)aa * cc % mod + (ll)bb * dd % mod * ww % mod) % mod;
            dd = tmp;
        }
        int tmp = (ll)2 * aa * bb % mod;
        aa = ((ll)aa * aa % mod + (ll)bb * bb % mod * ww % mod) % mod;
        bb = tmp;
        k >>= 1;
    }
    return cc;
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
void inv(int k)
{
    if (k == 1)
    {
        g[0] = ksm(h[0] * 2 % mod, mod - 2);
        return;
    }
    inv((k + 1) >> 1);
    num = 1;
    while (num < (k << 1))
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    for (int i = 0; i < k; ++i)
        ff[i] = h[i] * 2 % mod;
    for (int i = k; i < num; ++i)
        ff[i] = 0;
    ntt(ff, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        g[i] = (2 * g[i] % mod - (ll)g[i] * g[i] % mod * ff[i] % mod + mod) % mod;
    ntt(g, -1);
    for (int i = k; i < num; ++i)
        g[i] = 0;
    return;
}
void sqrt(int k)
{
    if (k == 1)
    {
        while (1)
        {
            int aa = rand() % mod;
            int ww = ((ll)aa * aa % mod - f[0] + mod) % mod;
            if (ksm(ww, (mod - 1) / 2) != mod - 1)
                continue;
            h[0] = ksm(aa, ww, (mod + 1) / 2) % mod;
            h[0] = min(h[0], mod - h[0]);
            break;
        }
        return;
    }
    sqrt((k + 1) >> 1);
    num = 1;
    while (num < k + 1)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        g[i] = 0;
    inv(k);
    for (int i = 0; i < k; ++i)
        ff[i] = f[i];
    for (int i = k; i < num; ++i)
        ff[i] = 0;
    ntt(ff, 1);
    ntt(h, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        h[i] = (ll)(ff[i] + (ll)h[i] * h[i] % mod) % mod * g[i] % mod;
    ntt(h, -1);
    for (int i = k; i < num; ++i)
        h[i] = 0;
    return;
}
int main()
{
    srand(time(0));
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &f[i]);
    while (num < n)
        num <<= 1;
    sqrt(n);
    for (int i = 0; i < n; ++i)
        printf("%d ", h[i]);
    return 0;
}