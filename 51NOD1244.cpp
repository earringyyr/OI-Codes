#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
typedef long long ll;
const int N = 5000005;
int sum, vis[N], pri[N];
ll mu[N];
unordered_map<int, ll> summu;
ll getmu(ll n)
{
    if (n <= N)
        return mu[n];
    if (summu[n])
        return summu[n];
    summu[n] = 1;
    for (ll l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        summu[n] -= getmu(n / l) * (r - l + 1);
    }
    return summu[n];
}
int main()
{
    mu[1] = 1;
    for (int i = 2; i <= N; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= sum && pri[j] <= vis[i] && (ll)i * pri[j] <= N; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (pri[j] == vis[i])
                mu[i * pri[j]] = 0;
            else
                mu[i * pri[j]] = mu[i] * mu[pri[j]];
        }
    }
    for (int i = 2; i <= N; ++i)
        mu[i] += mu[i - 1];
    ll n, m;
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", getmu(m) - getmu(n - 1));
    return 0;
}