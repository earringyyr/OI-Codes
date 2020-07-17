#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 4000001;
int n, sum, vis[4000005], pri[4000005];
ll ans, phi[4000005], f[4000005];
int main()
{
    phi[1] = 1;
    for (int i = 2; i <= N; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= sum && vis[i] >= pri[j] && (ll)i * pri[j] <= N; ++j)
        {
            vis[i * pri[j]] = pri[j];
            if (vis[i] == pri[j])
                phi[i * pri[j]] = phi[i] * pri[j];
            else
                phi[i * pri[j]] = phi[i] * phi[pri[j]];
        }
    }
    for (int i = 1; i <= N; ++i)
        for (int j = 2 * i; j <= N; j += i)
            f[j] += phi[j / i] * i;
    for (int i = 2; i <= N; ++i)
        f[i] += f[i - 1];
    while (scanf("%d", &n))
    {
        if (!n)
            break;
        printf("%lld\n", f[n]);
    }
    return 0;
}