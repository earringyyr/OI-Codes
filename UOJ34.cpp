#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int mod = 1004535809;
int n, m, num = 1, sum;
int f[300005], g[300005], r[300005];
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
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i)
        scanf("%d", &f[i]);
    for (int i = 0; i <= m; ++i)
        scanf("%d", &g[i]);
    while (num <= m + n)
    {
        num <<= 1;
        ++sum;
    }
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (sum - 1));
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    int inv = ksm(num, mod - 2);
    for (int i = 0; i <= m + n; ++i)
        printf("%d ", (int)((ll)f[i] * inv % mod));
    return 0;
}