#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
int n, sum, vis[100005], pri[100005];
ll ans, phi[100005];
int main()
{
    scanf("%d", &n);
    phi[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= sum && vis[i] >= pri[j] && (ll)i * pri[j] <= n; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (vis[i] == pri[j])
                phi[i * pri[j]] = phi[i] * pri[j];
            else
                phi[i * pri[j]] = phi[i] * phi[pri[j]];
        }
    }
    for (int i = 2; i <= n; ++i)
        phi[i] += phi[i - 1];
    for (int i = 1; i <= n; ++i)
        ans += (phi[n / i] * 2 - 1) * i;
    printf("%lld", ans);
    return 0;
}