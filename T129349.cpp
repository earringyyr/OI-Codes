#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define mod 998244353
using namespace std;
typedef long long ll;
ll ans;
ll fac[30005], ifac[30005], cnt[30005];
ll F[20][30005], f[120005], g[20][120005];
ll s[20][20];
ll ksm(ll a, ll k)
{
    ll b = 1;
    while (k)
    {
        if (k & 1)
            b = b * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return b;
}
void NTT(ll *a, int sum, int type)
{
    static int r[120005];
    int n = 1 << sum;
    for (int i = 0; i < n; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (sum - 1));
    for (int i = 0; i < n; ++i)
        if (i < r[i])
            swap(a[i], a[r[i]]);
    for (int mid = 1; mid < n; mid <<= 1)
    {
        ll w;
        if (type == 0)
            w = ksm(3, mod - 1 - (mod - 1) / (mid << 1));
        else
            w = ksm(3, (mod - 1) / (mid << 1));
        for (int j = 0; j < n; j += (mid << 1))
        {
            ll ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                ll x = a[j + k], y = a[j + k + mid] * ww % mod;
                a[j + k] = (x + y) % mod;
                a[j + k + mid] = ((x - y) % mod + mod) % mod;
                ww = ww * w % mod;
            }
        }
    }
    if (type == 0)
    {
        ll inv = ksm(n, mod - 2);
        for (int i = 0; i < n; ++i)
            a[i] = a[i] * inv % mod;
    }
    return;
}
void Inv(ll *inv, int sum, ll *a)
{
    static ll A[120005];
    if (sum == 0)
    {
        inv[0] = ksm(a[0], mod - 2);
        return;
    }
    Inv(inv, sum - 1, a);
    for (int i = (1 << sum); i < (1 << (sum + 1)); ++i)
    {
        A[i] = 0;
        inv[i] = 0;
    }
    for (int i = 0; i < (1 << sum); ++i)
        A[i] = a[i];
    NTT(inv, sum + 1, 1);
    NTT(A, sum + 1, 1);
    for (int i = 0; i < (1 << (sum + 1)); ++i)
        inv[i] = ((2 * inv[i] % mod - A[i] * inv[i] % mod * inv[i] % mod) % mod + mod) % mod;
    NTT(inv, sum + 1, 0);
    for (int i = (1 << sum); i < (1 << (sum + 1)); ++i)
        inv[i] = 0;
    return;
}
void calc(ll *ln, int sum, ll *a)
{
    static ll inv[120005], f[120005];
    for (int i = 0; i < (1 << (sum + 1)); ++i)
    {
        inv[i] = 0;
        f[i] = 0;
    }
    for (int i = 0; i < (1 << sum); ++i)
        f[i] = a[i];
    int n = 1 << sum;
    Inv(inv, sum, a);
    for (int i = 0; i < n - 1; ++i)
        f[i] = f[i + 1] * (i + 1) % mod;
    f[n - 1] = 0;
    NTT(inv, sum + 1, 1);
    NTT(f, sum + 1, 1);
    for (int i = 0; i < (1 << (sum + 1)); ++i)
        f[i] = f[i] * inv[i] % mod;
    NTT(f, sum + 1, 0);
    for (int i = n - 1; i > 0; --i)
        f[i] = f[i - 1] * ksm(i, mod - 2) % mod;
    f[0] = 0;
    for (int i = 0; i < (1 << sum); ++i)
        ln[i] = f[i];
    return;
}
void init(int n, int m)
{
    static ll tmp[120005], A[120005], B[120005];
    for (int i = 0; i <= n; ++i)
        cnt[i] = ksm(2, i * (i - 1) / 2);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = ksm(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    s[0][0] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= i; ++j)
            s[i][j] = (s[i - 1][j - 1] + j * s[i - 1][j] % mod) % mod;
    for (int i = 0; i <= n; ++i)
        cnt[i] = ksm(2, i * (i - 1) / 2);
    for (int i = 0; i <= n; ++i)
        tmp[i] = cnt[i] * ifac[i] % mod;
    ll sum = 0, num = n + 1;
    while (num)
    {
        ++sum;
        num >>= 1;
    }
    calc(f, sum, tmp);
    for (int i = 1; i <= n; ++i)
        f[i] = f[i] * fac[i] % mod * ifac[i - 1] % mod;
    NTT(f, sum + 1, 1);
    g[0][0] = 1;
    for (int j = 1; j <= m; ++j)
    {
        for (int i = 0; i <= n; ++i)
            g[j][i] = g[j - 1][i] * ifac[i] % mod;
        NTT(g[j], sum + 1, 1);
        for (int i = 0; i < (1 << (sum + 1)); ++i)
            g[j][i] = g[j][i] * f[i] % mod;
        NTT(g[j], sum + 1, 0);
        for (int i = n + 1; i < (1 << (sum + 1)); ++i)
            g[j][i] = 0;
        for (int i = 1; i <= n; ++i)
            g[j][i] = g[j][i] * fac[i - 1] % mod;
    }
    for (int i = 0; i <= n; ++i)
        B[i] = cnt[i] * ifac[i] % mod;
    NTT(B, sum + 1, 1);
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 0; j < (1 << (sum + 1)); ++j)
            A[j] = 0;
        for (int j = 1; j <= n; ++j)
            A[j] = g[i][j] * ifac[j] % mod;
        NTT(A, sum + 1, 1);
        for (int j = 0; j < (1 << (sum + 1)); ++j)
            A[j] = A[j] * B[j] % mod;
        NTT(A, sum + 1, 0);
        for (int j = 1; j <= n; ++j)
            F[i][j] = A[j] * fac[j] % mod;
    }
    return;
}
int main()
{
    init(30000, 15);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
            ans = (ans + F[i][n] * fac[i] % mod * s[m][i] % mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}