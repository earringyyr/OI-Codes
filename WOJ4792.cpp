#include <iostream>
#include <cstdio>
#define mod 998244353
using namespace std;
int n, k, l, r, a[505], vis[505], f[505][505], c[505][505];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &a[i]);
        vis[a[i]] = 1;
    }
    scanf("%d%d", &l, &r);
    if (vis[1])
        f[1][1] = 0;
    else
        f[1][1] = 1;
    for (int d = 2; d <= n; ++d)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (i == 1)
            {
                f[i][d] = 1;
                continue;
            }
            for (int j = 1; j < i; ++j)
                f[i][d] = (f[i][d] + (long long)f[i - j][d] * f[j][d - 1] % mod * c[i - 2][j - 1] % mod) % mod;
        }
        for (int i = 1; i <= n; ++i)
            if (vis[i])
                f[i][d] = 0;
    }
    for (int i = l; i <= r; ++i)
        printf("%d ", ((f[n][i] - f[n][i - 1]) % mod + mod) % mod);
    return 0;
}