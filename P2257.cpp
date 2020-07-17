#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
int num, mu[10000005], vis[10000005], pri[10000005];
ll sum[10000005];
int main()
{
    mu[1] = 1;
    for (int i = 2; i <= 10000000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++num] = i;
            mu[i] = -1;
            sum[i] = 1;
        }
        for (int j = 1; j <= num && pri[j] <= vis[i] && (ll)i * pri[j] <= 10000000; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (i % pri[j] == 0)
            {
                mu[i * pri[j]] = 0;
                sum[i * pri[j]] = mu[i];
            }
            else
            {
                mu[i * pri[j]] = mu[i] * mu[pri[j]];
                sum[i * pri[j]] = sum[i] * mu[pri[j]] + mu[i];
            }
        }
    }
    for (int i = 1; i <= 10000000; ++i)
        sum[i] = sum[i - 1] + sum[i];
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        ll ans = 0;
        scanf("%d%d", &n, &m);
        if (m < n)
            swap(m, n);
        for (int l = 1, r; l <= n; l = r + 1)
        {
            r = min(n / (n / l), m / (m / l));
            ans += (sum[r] - sum[l - 1]) * (n / l) * (m / l);
        }
        printf("%lld\n", ans);
    }
    return 0;
}