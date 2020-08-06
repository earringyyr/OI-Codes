#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, num;
int r[400005], f[400005], ff[400005], g[400005];
int ksm(int a, int k)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = (ll)b * a % mod;
        a = (ll)a * a % mod;
        k >>= 1;
    }
    return b;
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
                ww = (ll)ww * w % mod;
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
void solve(int k)
{
    if (k == 1)
    {
        g[0] = ksm(f[0], mod - 2);
        return;
    }
    solve((k + 1) >> 1);
    num = 1;
    while (num < (k << 1))
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    for (int i = 0; i < k; ++i)
        ff[i] = f[i];
    for (int i = k; i < num; ++i)
        ff[i] = 0;
    ntt(ff, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        g[i] = (2 * g[i] % mod - (ll)ff[i] * g[i] % mod * g[i] % mod + mod) % mod;
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
    solve(n);
    for (int i = 0; i < n - 1; ++i)
        f[i] = (ll)f[i + 1] * (i + 1) % mod;
    f[n - 1] = 0;
    num = 1;
    while (num < (n << 1))
        num <<= 1;
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        g[i] = (ll)f[i] * g[i] % mod;
    ntt(g, -1);
    f[0] = 0;
    for (int i = 1; i < n; ++i)
        f[i] = (ll)g[i - 1] * ksm(i, mod - 2) % mod;
    for (int i = 0; i < n; ++i)
        printf("%d ", f[i]);
    return 0;
}