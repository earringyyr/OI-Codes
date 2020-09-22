#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch i << 1
#define rch i << 1 | 1
using namespace std;
typedef long long ll;
int n;
int a[200005], lg[200005];
ll ans = 1e18;
ll f[200005][20], g[200005][20], dis[200005][20];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 2; i <= n; ++i)
    {
        scanf("%lld", &dis[i][1]);
        for (int j = 2; j <= lg[i]; ++j)
            dis[i][j] = dis[i >> 1][j - 1] + dis[i][1];
    }
    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= lg[i] + 1; ++j)
            if ((lch) <= n && (rch) <= n)
            {
                f[i][j] = min(dis[lch][1] * a[lch] + g[lch][1] + f[rch][j + 1], dis[rch][1] * a[rch] + g[rch][1] + f[lch][j + 1]);
                g[i][j] = min(dis[lch][1] * a[lch] + g[lch][1] + g[rch][j + 1], dis[rch][1] * a[rch] + g[rch][1] + g[lch][j + 1]);
            }
            else if ((lch) <= n)
            {
                f[i][j] = f[lch][j + 1] + dis[lch][1] * a[lch];
                g[i][j] = g[lch][j + 1] + dis[lch][1] * a[lch];
            }
            else
            {
                f[i][j] = dis[i][j] * a[i >> j];
                g[i][j] = (dis[i][j] + dis[(i >> (j - 1)) ^ 1][1]) * a[(i >> (j - 1)) ^ 1];
            }
    for (int i = 1; i <= n; ++i)
    {
        ll num = f[i][1];
        for (int j = 1; j <= lg[i]; ++j)
        {
            if (((i >> (j - 1)) ^ 1) <= n)
                num += f[(i >> (j - 1)) ^ 1][2] + dis[(i >> (j - 1)) ^ 1][1] * a[(i >> (j - 1)) ^ 1];
            else
                num += (dis[i][j + 1] - dis[i][j]) * a[i >> (j + 1)];
        }
        ans = min(ans, num);
    }
    printf("%lld", ans);
    return 0;
}