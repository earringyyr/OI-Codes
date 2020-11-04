#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int N, sum, vis[5000005], num[5000005], pri[5000005], d[5000005];
ll lef, rig, ans;
ll D(ll n)
{
    ll num = 0;
    for (ll l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        num += n / l * (r - l + 1);
    }
    return num - 2 * n + 1;
}
int main()
{
    scanf("%lld%lld", &lef, &rig);
    N = pow(rig, 2.0 / 3);
    for (int i = 2; i <= N; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            d[i] = 2;
            num[i] = 1;
        }
        for (int j = 1; j <= sum && vis[i] >= pri[j] && i * pri[j] <= N; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (vis[i] == pri[j])
            {
                d[i * pri[j]] = d[i] / (num[i] + 1) * (num[i] + 2);
                num[i * pri[j]] = num[i] + 1;
            }
            else
            {
                d[i * pri[j]] = d[i] * 2;
                num[i * pri[j]] = 1;
            }
        }
    }
    for (int i = 2; i <= N; ++i)
        d[i] = d[i - 1] + d[i] - 2;
    for (ll l = lef, r; l <= rig; l = r + 1)
    {
        r = min(rig / (rig / l), rig);
        if (rig / l <= N)
            ans += (r - l + 1) * d[rig / l];
        else
            ans += (r - l + 1) * D(rig / l);
    }
    printf("%lld", ans);
    return 0;
}