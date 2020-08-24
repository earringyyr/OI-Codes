#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, num = 1, c[100005], f[400005], ff[400005], h[400005], g[400005], r[400005];
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
void inv(int k)
{
    if (k == 1)
    {
        g[0] = ksm(h[0] % mod, mod - 2);
        return;
    }
    inv((k + 1) >> 1);
    num = 1;
    while (num < (k << 1))
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    for (int i = 0; i < k; ++i)
        ff[i] = h[i] % mod;
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
        h[0] = 1;
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
    for (int i = 0; i < num; ++i)
        h[i] = (ll)h[i] * ksm(2, mod - 2) % mod;
    for (int i = k; i < num; ++i)
        h[i] = 0;
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
        f[c[i]] = mod - 4;
    }
    sqrt(m + 1);
    h[0] = (h[0] + 1) % mod;
    memset(g, 0, sizeof(g));
    inv(m + 1);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", (int)((ll)g[i] * 2 % mod));
    return 0;
}