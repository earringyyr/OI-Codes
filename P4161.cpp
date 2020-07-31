#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, num, vis[1005], pri[1005];
long long f[1005];
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++num] = i;
        }
        for (int j = 1; j <= num && vis[i] >= pri[j] && i * pri[j] <= n; ++j)
            vis[i * pri[j]] = pri[j];
    }
    f[0] = 1;
    for (int i = 1; i <= num; ++i)
        for (int j = n; j >= 1; --j)
        {
            int sum = pri[i];
            while (sum <= j)
            {
                f[j] += f[j - sum];
                sum *= pri[i];
            }
        }
    for (int i = 1; i <= n; ++i)
        f[0] += f[i];
    printf("%lld", f[0]);
    return 0;
}