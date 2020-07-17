#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int T, n, m, num, vis[50005], pri[50005], mu[50005];
ll ans, sum[50005];
int main()
{
    mu[1] = 1;
    for (int i = 2; i <= 50000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++num] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= num && pri[j] <= vis[i] && (ll)i * pri[j] <= 50000; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (vis[i] == pri[j])
                mu[i * pri[j]] = 0;
            else
                mu[i * pri[j]] = mu[i] * mu[pri[j]];
        }
    }
    for (int i = 2; i <= 50000; ++i)
        mu[i] += mu[i - 1];
    for (int i = 1; i <= 50000; ++i)
        for (int l = 1, r; l <= i; l = r + 1)
        {
            r = i / (i / l);
            sum[i] += (r - l + 1) * (i / l);
        }
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        scanf("%d%d", &n, &m);
        if (m < n)
            swap(m, n);
        for (int l = 1, r; l <= n; l = r + 1)
        {
            r = min(n / (n / l), m / (m / l));
            ans += (ll)(mu[r] - mu[l - 1]) * sum[n / l] * sum[m / l];
        }
        printf("%lld\n", ans);
    }
    return 0;
}