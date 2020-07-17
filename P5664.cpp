#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod 998244353
using namespace std;
int n, m, a[105][2005];
long long ans = 1, sum[105], f[105][2005];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j]);
            sum[i] = (sum[i] + a[i][j]) % mod;
        }
        ans = ans * (sum[i] + 1) % mod;
    }
    ans = (ans + mod - 1) % mod;
    for (int i = 1; i <= m; ++i)
    {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int j = 1; j <= n; ++j)
            for (int k = 0; k <= 2 * j; ++k)
            {
                f[j][k] = (f[j][k] + f[j - 1][k] * (sum[j] - a[j][i]) % mod) % mod;
                f[j][k] = (f[j][k] + f[j - 1][k - 1]) % mod;
                f[j][k] = (f[j][k] + f[j - 1][k - 2] * a[j][i]) % mod;
            }
        for (int j = n + 1; j <= 2 * n; ++j)
            ans = (ans + mod - f[n][j]) % mod;
    }
    printf("%lld", ans);
    return 0;
}