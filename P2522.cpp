#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
int n, a, b, c, d, k, sum;
int vis[50005], pri[50005], mu[50005];
ll solve(int p, int q)
{
    ll ans = 0;
    if (q < p)
        swap(p, q);
    p /= k;
    q /= k;
    for (int l = 1, r; l <= p; l = r + 1)
    {
        r = min(p / (p / l), q / (q / l));
        ans += (ll)(mu[r] - mu[l - 1]) * (p / l) * (q / l);
    }
    return ans;
}
int main()
{
    mu[1] = 1;
    for (int i = 2; i <= 50000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= sum && vis[i] >= pri[j] && (ll)i * pri[j] <= 50000; ++j)
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
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("%lld\n", solve(b, d) - solve(a - 1, d) - solve(b, c - 1) + solve(a - 1, c - 1));
    }
    return 0;
}