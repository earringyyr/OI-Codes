#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, num = 1;
int g[300005], f[300005], rev[300005], ff[300005], gg[300005];
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
        if (i < rev[i])
            swap(c[i], c[rev[i]]);
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
    return;
}
void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    num = r - l + 1;
    for (int i = 0; i < num; ++i)
    {
        ff[i] = 0;
        gg[i] = 0;
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    }
    for (int i = l; i <= mid; ++i)
        ff[i - l] = f[i];
    for (int i = 1; i <= num; ++i)
        gg[i - 1] = g[i];
    ntt(ff, 1);
    ntt(gg, 1);
    for (int i = 0; i < num; ++i)
        ff[i] = (ll)ff[i] * gg[i] % mod;
    ntt(ff, -1);
    int inv = ksm(num, mod - 2);
    for (int i = mid + 1; i <= r; ++i)
    {
        ff[i - l - 1] = (ll)ff[i - l - 1] * inv % mod;
        f[i] = (f[i] + ff[i - l - 1]) % mod;
    }
    solve(mid + 1, r);
    return;
}
int main()
{
    scanf("%d", &n);
    f[0] = 1;
    for (int i = 1; i < n; ++i)
        scanf("%d", &g[i]);
    while (num < n)
        num <<= 1;
    solve(0, num - 1);
    for (int i = 0; i < n; ++i)
        printf("%d ", f[i]);
    return 0;
}