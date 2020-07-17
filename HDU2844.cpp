#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, a[105], c[105], f[100005];
int main()
{
    while (scanf("%d%d", &n, &m))
    {
        if (!n && !m)
            return 0;
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &c[i]);
        for (int i = 1; i <= n; ++i)
        {
            int cnt = 0, w[15];
            for (int j = 1; j <= c[i]; j *= 2)
            {
                c[i] -= j;
                w[++cnt] = a[i] * j;
            }
            if (c[i])
                w[++cnt] = a[i] * c[i];
            for (int j = 1; j <= cnt; ++j)
                for (int k = m; k >= w[j]; --k)
                    f[k] = max(f[k], f[k - w[j]] + w[j]);
        }
        int ans = 0;
        for (int i = 1; i <= m; ++i)
            if (f[i] == i)
                ++ans;
        printf("%d\n", ans);
    }
    return 0;
}