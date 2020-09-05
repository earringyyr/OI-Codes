#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, a[3005], sum[3005], f[3005], g[3005][3005];
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        sum[i] += sum[i - 1] + a[i];
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i - 1; j; --j)
            g[i][j] = g[i][j + 1] + sum[i] - sum[j] + min(3 * (i - j) * a[j], sum[i] - sum[j]);
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            f[i] = min(f[i], f[j] + g[i][j + 1] + (sum[n] - sum[i]) * ((i - j - 1) * 3 + i - j - 1 + 2));
    printf("%lld", f[n]);
    return 0;
}