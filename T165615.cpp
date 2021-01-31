#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, mod, ans;
int fac[405], inv[405], pw2[405];
int f[405][405], g[405][405], pw[405][405];
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
int C(int m, int n)
{
    return (ll)fac[m] * inv[n] % mod * inv[m - n] % mod;
}
int main()
{
    scanf("%d%d", &n, &mod);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[n] = ksm(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    pw2[0] = 1;
    pw[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        pw2[i] = pw2[i - 1] * 2 % mod;
        pw[i][0] = 1;
        for (int j = 1; j <= n; ++j)
            pw[i][j] = (ll)pw[i][j - 1] * (pw2[i] - 1) % mod;
    }
    for (int i = 1; i <= n; ++i)
        pw2[i] = ksm(2, i * (i - 1) / 2);
    g[1][1] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            for (int k = 1; k <= n - i; ++k)
            {
                int tmp = (ll)C(i + k - 1, k) * pw[j][k] % mod * pw2[k] % mod;
                f[i + k][k] = ((f[i + k][k] + (ll)f[i][j] * tmp % mod) % mod + (ll)g[i][j] * tmp % mod * (n - i) % mod) % mod;
                g[i + k][k] = (g[i + k][k] + (ll)tmp * g[i][j]) % mod;
            }
    for (int i = 1; i <= n; ++i)
        ans = (ans + f[n][i]) % mod;
    ans = (ll)ans * ksm(n - 1, mod - 2) % mod;
    printf("%d", ans);
    return 0;
}