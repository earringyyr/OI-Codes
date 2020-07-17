#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, m, k, sum;
int a[200005], pos[200005], l[1005], r[1005];
int num[200005], vis[200005];
int main()
{
    scanf("%d", &n);
    k = sqrt(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        pos[i] = i / k + 1;
    }
    for (int i = 0; i < n; i += k)
    {
        ++sum;
        l[sum] = i;
        r[sum] = i + k - 1;
    }
    r[sum] = n - 1;
    for (int i = 1; i <= sum; ++i)
        for (int j = r[i]; j >= l[i]; --j)
        {
            if (j + a[j] > r[i])
            {
                num[j] = 1;
                vis[j] = j + a[j];
            }
            else
            {
                num[j] = num[j + a[j]] + 1;
                vis[j] = vis[j + a[j]];
            }
        }
    scanf("%d", &m);
    for (int t = 1; t <= m; ++t)
    {
        int ii, jj;
        scanf("%d%d", &ii, &jj);
        if (ii == 1)
        {
            int ans = 0;
            while (jj < n)
            {
                ans += num[jj];
                jj = vis[jj];
            }
            printf("%d\n", ans);
        }
        else
        {
            int kk;
            scanf("%d", &kk);
            a[jj] = kk;
            for (int i = jj; i >= l[pos[jj]]; --i)
            {
                if (i + a[i] > r[pos[jj]])
                {
                    num[i] = 1;
                    vis[i] = i + a[i];
                }
                else
                {
                    num[i] = num[i + a[i]] + 1;
                    vis[i] = vis[i + a[i]];
                }
            }
        }
    }
    return 0;
}