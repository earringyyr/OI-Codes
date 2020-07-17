#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
typedef long long ll;
const int N = 2000005;
int sum, vis[N], pri[N];
ll phi[N], mu[N];
unordered_map<int, ll> sumphi, summu;
ll getphi(int n)
{
    if (n <= N)
        return phi[n];
    if (sumphi[n])
        return sumphi[n];
    sumphi[n] = (ll)n * (n + 1) / 2;
    for (int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        sumphi[n] -= getphi(n / l) * (r - l + 1);
    }
    return sumphi[n];
}
ll getmu(int n)
{
    if (n <= N)
        return mu[n];
    if (summu[n])
        return summu[n];
    summu[n] = 1;
    for (int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        summu[n] -= getmu(n / l) * (r - l + 1);
    }
    return summu[n];
}
int main()
{
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= N; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; j <= sum && pri[j] <= vis[i] && (ll)i * pri[j] <= N; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (pri[j] == vis[i])
            {
                phi[i * pri[j]] = phi[i] * pri[j];
                mu[i * pri[j]] = 0;
            }
            else
            {
                phi[i * pri[j]] = phi[i] * phi[pri[j]];
                mu[i * pri[j]] = mu[i] * mu[pri[j]];
            }
        }
    }
    for (int i = 2; i <= N; ++i)
    {
        phi[i] += phi[i - 1];
        mu[i] += mu[i - 1];
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        printf("%lld %lld\n", getphi(n), getmu(n));
    }
    return 0;
}