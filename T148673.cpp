#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
// pri 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
int n, sum, ans;
int a[1005], vis[1005], pri[1005];
int num[1005], val[1005], f[3005], g[3005];
int main()
{
    for (int i = 2; i <= 1000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
        }
        for (int j = 1; j <= sum && pri[j] <= vis[i] && i * pri[j] <= 1000; ++j)
            vis[i * pri[j]] = pri[j];
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        for (int j = 1; j <= 11; ++j)
            while (a[i] % pri[j] == 0)
            {
                val[i] |= (1 << (j - 1));
                a[i] /= pri[j];
            }
    }
    for (int i = 1; i <= n; ++i)
        if (a[i] == 1)
            for (int j = 0; j < (1 << 11); ++j)
                if ((j & val[i]) == val[i])
                    f[j] = max(f[j], f[j ^ val[i]] + 1);
    for (int i = 12; i <= sum; ++i)
    {
        memcpy(g, f, sizeof(f));
        for (int j = 1; j <= n; ++j)
            if (a[j] == pri[i])
            {
                for (int k = 0; k < (1 << 11); ++k)
                    if ((k & val[j]) == val[j])
                        g[k] = max(g[k], f[k ^ val[j]] + 1);
            }
        memcpy(f, g, sizeof(g));
    }
    for (int i = 0; i < (1 << 11); ++i)
        ans = max(ans, f[i]);
    printf("%d", ans);
    return 0;
}