#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, k, num;
int a[100005], b[200005];
int nxt[100005];
int fac[100005], inv[100005];
int r[600005], f[600005], g[600005];
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
    return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void init(int len)
{
    num = 1;
    while (num < len)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    return;
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
void kmp()
{
    int x = 0, y = k + 2;
    nxt[k + 2] = 0;
    while (y <= n)
        if (x == 0 || a[x] == a[y])
        {
            ++x;
            ++y;
            nxt[y] = x;
        }
        else
            x = nxt[x];
    return;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    if (k + 1 >= n)
    {
        printf("0");
        return 0;
    }
    for (int i = n + 1; i <= 2 * n - 1; ++i)
        b[i] = b[i - n];
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[n] = ksm(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    init(n + k + 2);
    for (int i = 0; i <= n; ++i)
        f[i] = a[i];
    for (int i = 0; i <= k + 1; ++i)
        g[i] = (((i & 1) ? -1 : 1) * C(k + 1, i) + mod) % mod;
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 1; i <= n; ++i)
        a[i] = f[i];
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    init(2 * n + k + 1);
    for (int i = 1; i <= 2 * n - 1; ++i)
        f[i] = b[i];
    for (int i = 0; i <= k + 1; ++i)
        g[i] = (((i & 1) ? -1 : 1) * C(k + 1, i) + mod) % mod;
    ntt(f, 1);
    ntt(g, 1);
    for (int i = 0; i < num; ++i)
        f[i] = (ll)f[i] * g[i] % mod;
    ntt(f, -1);
    for (int i = 1; i <= 2 * n - 1; ++i)
        b[i] = f[i];
    kmp();
    int j = k + 2;
    for (int i = k + 2; i <= 2 * n - 1; ++i)
        if (a[j] == b[i])
        {
            if (j == n)
            {
                printf("%d", i - n);
                return 0;
            }
            else
                ++j;
        }
        else
        {
            j = nxt[j];
            if (j)
                --i;
            else
                j = k + 2;
        }
    printf("-1");
    return 0;
}