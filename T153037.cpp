#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n, sum, a[1000005];
int vis[1000005], pri[1000005];
int pre[1000005], inv[1000005];
ll ans;
int main()
{
    for (int i = 2; i <= 1000000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            inv[i] = sum;
        }
        for (int j = 1; j <= sum && vis[i] >= pri[j] && i * pri[j] <= 1000000; ++j)
            vis[i * pri[j]] = pri[j];
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        int sqr = sqrt(a[i]);
        for (int j = 1; pri[j] <= sqr; ++j)
            if (a[i] % pri[j] == 0)
            {
                while (a[i] % pri[j] == 0)
                    a[i] /= pri[j];
                if (!pre[j])
                    ans += (ll)n * (n + 1) / 2;
                ans -= (ll)(i - pre[j]) * (i - pre[j] - 1) / 2;
                pre[j] = i;
            }
        if (a[i] > 1)
        {
            int j = inv[a[i]];
            if (!pre[j])
                ans += (ll)n * (n + 1) / 2;
            ans -= (ll)(i - pre[j]) * (i - pre[j] - 1) / 2;
            pre[j] = i;
        }
    }
    for (int i = 1; i <= sum; ++i)
        if (pre[i])
            ans -= (ll)(n - pre[i]) * (n - pre[i] + 1) / 2;
    printf("%lld", ans);
    return 0;
}