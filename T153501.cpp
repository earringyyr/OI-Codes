#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
uint n, mod, ans;
uint f[5005], g[5005], c[5005][5005];
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
int main()
{
    scanf("%u%u", &n, &mod);
    c[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    }
    for (int i = 1; i <= n; ++i)
        if (i % 2 == 0)
            for (int j = 0; j <= i / 2; ++j)
                f[i] = (f[i] + (ll)c[i][j] * c[i - j][j] % mod * c[i - 2 * j][(i - 2 * j) / 2] % mod) % mod;
    for (int i = 1; i <= n; ++i)
        if (i % 2 == 0)
        {
            g[i] = f[i];
            for (int j = 2; j < i; j += 2)
                g[i] = (g[i] + mod - (ll)g[j] * f[i - j] % mod) % mod;
        }
    ans = (ll)(n + 1) * ksm(4, n) % mod;
    for (int i = 1; i <= n; ++i)
        if (i % 2 == 0)
            ans = (ans + mod - (ll)ksm(4, n - i) * g[i] % mod * (n - i + 1) % mod) % mod;
    printf("%u", ans);
    return 0;
}