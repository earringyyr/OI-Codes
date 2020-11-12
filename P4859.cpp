#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000009;
int n, k, r = 1, ans;
int a[2005], b[2005];
int fac[2005], inv[2005], g[2005];
int f[2005][2005];
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
    if (n < m)
        return 0;
    return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main()
{
    scanf("%d%d", &n, &k);
    if ((n + k) % 2 != 0)
    {
        printf("%d", 0);
        return 0;
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[n] = ksm(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (r <= n && b[r] < a[i])
            ++r;
        f[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            f[i][j] = (f[i - 1][j] + (ll)max(0, r - j) * f[i - 1][j - 1] % mod) % mod;
    }
    k = (n + k) >> 1;
    for (int i = k; i <= n; ++i)
        g[i] = (ll)f[n][i] * fac[n - i] % mod;
    for (int i = k; i <= n; ++i)
        ans = ((ans + (ll)((i - k) % 2 == 0 ? 1 : -1) * C(i, k) % mod * g[i] % mod) % mod + mod) % mod;
    printf("%d", ans);
    return 0;
}